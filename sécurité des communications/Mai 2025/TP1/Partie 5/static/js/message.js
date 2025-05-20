document.addEventListener("DOMContentLoaded", function () {
  const searchInput = document.getElementById("searchText");
  const userElements = document.querySelectorAll(".sideBar-body");
  const messageArea = document.getElementById("message-area");
  const textarea = document.querySelector(".reply textarea");
  const sendButton = document.querySelector(".reply-send");

  // Nouveaux éléments pour afficher l'interlocuteur
  const convAvatar = document.querySelector(".conversation-avatar img");
  const convUsername = document.querySelector(".conversation-username");

  let selectedUser = null;

  // Initialisation Socket.IO client
  const socket = io();  // Assure-toi que la lib Socket.IO est incluse dans ton HTML

  // --- Filtrer la liste des utilisateurs ---
  searchInput.addEventListener("input", function () {
    const searchTerm = searchInput.value.toLowerCase();

    userElements.forEach((userEl) => {
      const username = userEl.dataset.username?.toLowerCase() || "";
      if (username.includes(searchTerm)) {
        userEl.style.display = "";
      } else {
        userEl.style.display = "none";
      }
    });
  });

  // --- Sélection d'un utilisateur dans la sidebar ---
  userElements.forEach(userEl => {
    userEl.addEventListener("click", () => {
      // Mémorise l'utilisateur sélectionné
      selectedUser = userEl.dataset.username;
      console.log("Utilisateur sélectionné :", selectedUser);

      // Met à jour l'affichage avatar + nom en haut à gauche
      const avatarImg = userEl.querySelector(".avatar-icon img");
      if (avatarImg) {
        convAvatar.src = avatarImg.src;
        convAvatar.alt = "Avatar de " + selectedUser;
      } else {
        convAvatar.src = "";
        convAvatar.alt = "";
      }
      convUsername.textContent = selectedUser;

      // Indique visuellement la sélection
      userElements.forEach(el => el.classList.remove('selected'));
      userEl.classList.add('selected');

      // Charge les messages pour cet utilisateur
      loadMessagesForUser(selectedUser);
    });
  });

  // --- Fonction pour afficher les messages ---
  function displayMessages(messages) {
    messageArea.innerHTML = ""; // Vide l'affichage

    messages.forEach(msg => {
      // msg : {sender: "pseudo", receiver: "pseudo", content: "...", timestamp: "..."}

      // Adapte ici la variable username connectée (à définir côté template)
      console.log("Sender :", msg.sender);
      console.log("username :", username);
      console.log("msg data :", msg);
      const isSent = (msg.sender.toLowerCase() === username.toLowerCase());

      const messageDiv = document.createElement("div");
      messageDiv.classList.add("message");
      messageDiv.classList.add(isSent ? "sent" : "received");

      const p = document.createElement("p");
      p.textContent = msg.message;

      messageDiv.appendChild(p);
      messageArea.appendChild(messageDiv);
    });

    // Scroll en bas
    messageArea.scrollTop = messageArea.scrollHeight;
  }

  // --- Fonction pour charger les messages d'une conversation ---
  function loadMessagesForUser(username) {
    if (!username) return;

    fetch(`/messages/${username}`)
      .then(response => {
        if (!response.ok) throw new Error("Erreur de chargement des messages");
        return response.json();
      })
      .then(data => {
        // data doit être un tableau de messages
        displayMessages(data);
      })
      .catch(err => {
        console.error(err);
        messageArea.innerHTML = `<p style="color: red;">Impossible de charger les messages.</p>`;
      });
  }


  // --- Envoi via  Socket.IO au lieu de POST fetch ---
  function sendMessage() {
    const message = textarea.value.trim();
    console.log("Message à envoyer :", message);
    if (message === "") return;

    if (!selectedUser) {
      alert("Veuillez sélectionner un utilisateur pour discuter.");
      return;
    }
    // JOINDRE LE ROOM AVEC L'ID UTILISATEUR
    socket.emit('join_room', { user_id });

    // Envoi du message via Socket.IO
    socket.emit('send_message', {
      to: selectedUser,
      content: message
    }, (response) => {
      if (response.status === 'ok') {
        console.log('Message envoyé avec succès');
      } else {
        console.error('Erreur lors de l’envoi:', response.error);
      }
    });

    textarea.value = ""; // Vide le champ

    // On peut soit recharger la conversation en fetch, soit attendre l'event socket de nouveau message
    // Ici on attend l'event socket pour mise à jour temps réel
  }

  // --- Envoi avec Entrée ---
  textarea.addEventListener("keydown", function (e) {
    if (e.key === "Enter" && !e.shiftKey) {
      e.preventDefault();
      sendMessage();
    }
  });

  // --- Envoi avec le bouton avion ---
  sendButton.addEventListener("click", function () {
    sendMessage();
  });


  // --- Réception en temps réel d'un nouveau message via socket ---
  socket.on('receive_message', (msg) => {
    // Si le message reçu concerne la conversation ouverte, on recharge l'affichage
    if (selectedUser && msg) {
    //   console.log("ici");
      loadMessagesForUser(selectedUser);
    }
    
  });


  // ** Sélectionne par défaut le premier utilisateur **
  if (userElements.length > 0) {
    userElements[0].click();
  }

});
