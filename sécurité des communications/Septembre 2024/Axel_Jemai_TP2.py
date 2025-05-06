"""
JEMAI Axel TD3 TP6
TP1 : Sécurité des communications
"""
# Importation des bibliothèques
from sympy import primerange
import math
import random

"""
Partie 1 : Implémentation des fonctions de base
"""
# Fonction qui test si un nombre est premier grace a la méthode de la racine carré
def est_premier(n):
    ret = True
    if n < 2:
        ret = False
    elif n > 3:
        sqrt = int(math.sqrt(n))
        # boucle qui test si n est un multiple de la liste des nombre premier comprit [2 ; sqrt ]
        for p in primerange(2, sqrt + 1): # ajout de 1 pour que la valeur entière de la racine carré soit prise en compte
            if (n % p == 0):    
                ret = False
                break
    return ret 
print("### Test de la fonction est_premier ###")
print(est_premier(19), True)
print(est_premier(163), True)
print(est_premier(195), False)
print(est_premier(28), False)
print(est_premier(3), True)
print(est_premier(-3), False)
print(est_premier(2), True)
print()

#Fonction qui retourne le pgcd entre deux nombres
def pgcd (a,b):
    if a<b:
        a,b=b,a
    while b!=0:
        r=a%b # on calcule le reste de la division euclidienne de a par b
        a=b # on échange les valeurs de a et de b
        b=r # on échange les valeurs de b et du reste r
    return a # a est le pgcd de a et b
print("### Test de la fonction pgcd ###")
print(pgcd(12,15),3)
print(pgcd(12,13),1)
print(pgcd(12,0),12)
print(pgcd(0,0),0)
print()

# Fonction qui permert de faire euclide étendu
def euclid_etendu(a, b):
    # Initialisation des variables nécessaires pour suivre l'algorithme d'Euclide étendu
    u, v, u1, v1 = 1, 0, 0, 1
    if a < b:
        a, b = b, a
    if b == 0:
        return (a, u, v)
    while b != 0:
        q = a // b  # Quotient de la division entière de a par b
        # Mise à jour de a et b comme dans l'algorithme d'Euclide
        a, b = b, a%b 
        # Mise à jour des coefficients de Bézout (u, v)
        u, u1 = u1, u - q * u1
        v, v1 = v1, v - q * v1
    
    # À la fin de la boucle, a contient le PGCD, et (u, v) sont les coefficients de Bézout
    return (a, u, v)

print("### Test de la fonction euclid_etendu ###")
print(euclid_etendu(23, 22), (1, 1, 0)) 
print(euclid_etendu(12, 15), (3, -1, 1))
print(euclid_etendu(12, 13), (1, 5, -4))
print(euclid_etendu(12, 0), (12, 1, 0))
print()

# Fonction exponentiation rapide
def exponentiation_rapide(a,b,n):
    resultat=1 # initialisation du résultat
    while b>0:
        if b%2==1:
            resultat=(resultat*a)%n # on multiplie le résultat par a modulo n si b est impair
        b=b//2 # on divise b par 2
        a=a*a%n # on élève a au carré modulo n
    return resultat

print("### Test de la fonction exponentiation_rapide ###")
print(exponentiation_rapide(2, 3, 5), 3)
print(exponentiation_rapide(2, 3, 7), 1)
print(exponentiation_rapide(2, 3, 8), 0)
print(exponentiation_rapide(2, 3, 9), 8)
print()

"""
Partie 2 : Implémentation de RSA
"""
# Fonction qui permet de trouver l'inverse modulaire
def inverse_modulaire(a,b):
    (pgcd,u,v)=euclid_etendu(a,b)
    if pgcd==1:
        return u%b # retourne u modulo b pour que u (l'inverse qui peut être négatif) soit positif
    else:
        return None
print("### Test de la fonction inverse_modulaire ###")
print(inverse_modulaire(3, 11), 4)
print(inverse_modulaire(3, 10), 7)
print(inverse_modulaire(3, 9), None)
print(inverse_modulaire(3, 0), None)
print()       
# Fonction qui permet de trouver la fonction indicatrice d'Euler
def phin(p,q):
    return (p-1)*(q-1)

# Fonction qui permet de générer une clé publique et une clé privée
def generer_cle(p,q,e):
    phi=phin(p,q) # on calcule phi
    # on vérifie que p et q sont premiers, que e est premier avec phi et que phi n'est pas nul
    if(not est_premier(p)) or (not est_premier(q)) or (phi is None) or (pgcd(e,phi)!=1):
        raise ValueError("p et q doivent être premiers et e doit être premier avec phi")
    else:
        n=p*q
        d=inverse_modulaire(e,phi)
        if d is None:
            raise ValueError("Impossible de trouver un inverse modulaire pour e.")
        # on retourne la clé publique et la clé privée
        k_publique=(e,n)
        k_prive=(d,n)
        return (k_publique,k_prive)

# Fonction qui permet de chiffrer un message
def chiffrement_RSA(m,k_publique):
    return exponentiation_rapide(m,k_publique[0],k_publique[1]) # m^e mod n soit c
# Fonction qui permet de déchiffrer un message
def dechiffrer_RSA(c,k_prive):
    return exponentiation_rapide(c,k_prive[0],k_prive[1]) # c^d mod n soit m

"""
Partie 3 :  Factorisation de n 

La complexité de la factorisation d'un entier n en produit de deux facteurs premiers proches
est une tâche difficile qui augmente exponentiellement avec la taille en bits de n. 
La méthode de factorisation naïve prendrait O (sqrt(n))
opérations, ce qui est impraticable pour des nombres aussi grands.


voici une méthode pour factoriser un entier n en utilisant la méthode de la racine carrée
cette méthode est extremement lente pour des nombres très grands

def trouver_factors(n):
    racine = math.isqrt(n)
    p = racine
    print("racine: ",racine)
    while p > 1:
        if n % p == 0:  # si p divise n, alors p est un facteur
            q = n // p
            return p, q
        p -= 1
        print("p: ",p)
    return None, None

n= 4840015169768242918240815055699674259180276588222516131662837
print("p,q ",trouver_factors(n))

"""

"""
Partie 4 : Codage par bloc de caractères 
"""
# Définition de l'alphabet
alphabet = "abcdefghijklmnopqrstuvwxyz "

# Fonction qui permet de générer un nombre premier de taille taille_bits
def generer_premier(taille_bits):
    loop = True
    while loop:
        p = random.getrandbits(taille_bits)
        if est_premier(p) and len(bin(p))-2 == taille_bits: # Vérifier que p est premier et de la bonne taille
            loop = False
    return p
# Exemple d'appel de la fonction generer_premier
print("### Test de la fonction generer_premier ###")
print(generer_premier(16), " 16 bits")
print(generer_premier(8), " 8 bits")
print(generer_premier(32), " 32 bits")
print()


# Fonction qui retourne la taille de block de caractère
def taille_block(alphabet, n):
    return int(math.log(n,len(alphabet))) # grace a la formule log(n)/log(L) on trouve la taille du bloc

# Fonction qui permet de coder un message en blocs, converti chaque lettre en bloc de nombre
def codage_bloc(phrase, alphabet, k):
    L = len(alphabet)
    code = []
    # Ajouter un remplissage au dernier bloc si nécessaire
    if len(phrase) % k != 0:
        padding_length = k - (len(phrase) % k) # calculer la longueur du remplissage
        phrase += alphabet[0] * padding_length  # Remplir avec le premier caractère de l'alphabet
    # Transformer chaque bloc en nombre
    for i in range(0, len(phrase), k):
        bloc = phrase[i:i+k] # Extraire un bloc de k caractères
        # Convertir le bloc en nombre grace a la formule Somme de (L^j)*index(bloc[j])
        num = sum(alphabet.index(bloc[j]) * (L ** j) for j in range(len(bloc)))
        code.append(num)
    return code # retourner la liste des blocs

# Fonction qui permet de décoder un message en blocs, converti chaque bloc de nombre en lettre
def decodage_bloc(bloc_code, alphabet, message_length):
    L = len(alphabet)
    index_decode = []
    for bloc in bloc_code:
        bloc_chiffres = []
        # Extraire les chiffres du bloc
        while bloc > 0:
            bloc_chiffres.append(bloc % L)
            bloc //= L # on divise le bloc par L
        index_decode.extend(bloc_chiffres)  # Ajoute les chiffres dans le bon ordre
    print("bloc_chiffres: ",index_decode) # Affichage des chiffres correspondant aux lettres
    # Convertir les chiffres en lettres grace a l'index et a l'alphabet
    decoded_message = ''.join([alphabet[chiffre] for chiffre in index_decode])

    return decoded_message[:message_length]
# Fonction principale qui permet de chiffrer et déchiffrer un message
def main(p, q, message, alphabet):
    print("### Test de la fonction main ###")
    kpub, kpriv = generer_cle(p, q, e) # Générer les clés publique et privée
    print("p: ",p," q: ",q)
    print("Clé publique : ", kpub)
    print("Clé privée : ", kpriv)
    print("Message initial : ", message)

    # Taille du bloc
    len_block = taille_block(alphabet, kpub[1])
    print("Taille du bloc : ", len_block)
    
    # Codage du message en blocs
    block = codage_bloc(message, alphabet, len_block)
    print("Message codé en blocs : ", block)
    # Chiffrement des blocs
    chiffre = [chiffrement_RSA(b, kpub) for b in block]
    print("Message chiffré : ", chiffre)

    # Déchiffrement des blocs
    blocs_dechiffres = [dechiffrer_RSA(b, kpriv) for b in chiffre]
    print("Message déchiffré bloc: ", blocs_dechiffres)
    print("Message déchiffré clair: ",decodage_bloc(blocs_dechiffres, alphabet, len(message)))



# Exemple d'appel de la fonction main avec des valeurs p, q et un message sur un n de 16 bits
p = generer_premier(8)
q = generer_premier(8)
while p == q:  # S'assurer que p et q sont distincts
    q = generer_premier(8)

e = 65537
main(p,q,"securite des communications", alphabet)
