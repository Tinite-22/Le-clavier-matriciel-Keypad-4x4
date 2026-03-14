#include <Keypad.h> // Charge la bibliothèque "Keypad". Elle fait le travail complexe en arrière-plan : 
                    // scanner très rapidement les fils pour détecter une connexion
                    // et gérer l'anti-rebond matériel (éviter qu'un seul appui ne compte double).

// --- 1. Dimensions physiques du clavier ---
// On utilise 'const byte' au lieu du classique 'int'.
// 'byte' prend moins de place en mémoire (1 octet contre 2 pour un int). C'est une bonne habitude 
// sur Arduino. 'const' protège la variable : sa valeur ne pourra jamais être modifiée par erreur.
const byte LIGNES = 4;   // Notre clavier possède 4 lignes horizontales
const byte COLONNES = 4; // Notre clavier possède 4 colonnes verticales

// --- 2. Configuration du Buzzer ---
// Le buzzer est branché sur la broche 13.
const int brocheBuzzer = 13;

// --- 3. Cartographie (La Matrice) ---
// C'est un tableau à 2 dimensions. Il explique à l'Arduino quel caractère correspond 
// à quelle intersection physique de fils. 
// Exemple : Si le courant passe entre le fil de la Ligne 1 et le fil de la Colonne 1, 
// l'Arduino saura que c'est la touche '1'.
char touches[LIGNES][COLONNES] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

// --- 4. Le Câblage ---
// On indique à l'Arduino sur quelles broches précises on a connecté les 8 fils du clavier.
// Attention : L'ordre de ces numéros doit correspondre exactement à l'ordre de tes fils de gauche à droite.
byte brochesLignes[LIGNES] = {3, 4, 5, 6};      // Les 4 fils qui alimentent les lignes horizontales
byte brochesColonnes[COLONNES] = {7, 8, 9, 10}; // Les 4 fils qui lisent les colonnes verticales

// --- 5. Création du "cerveau" du clavier ---
// On initialise un objet nommé 'clavier' grâce à la bibliothèque. On lui donne la recette complète :
// la carte des touches (makeKeymap), où sont branchées les lignes, les colonnes, et la taille totale.
Keypad clavier = Keypad(makeKeymap(touches), brochesLignes, brochesColonnes, LIGNES, COLONNES);

void setup() {
  // --- Initialisation au démarrage de la carte ---
  
  // On configure la broche du buzzer en "Sortie" (OUTPUT). 
  // Cela signifie que l'Arduino a le droit d'envoyer du courant électrique (5V) vers ce composant.
  pinMode(brocheBuzzer, OUTPUT);

  // On ouvre le canal de communication série à une vitesse de 9600 bauds.
  // C'est ce qui permet à l'Arduino de discuter avec ton ordinateur via le câble USB.
  Serial.begin(9600);
  
  // On envoie un message texte de test dans le Moniteur Série de l'ordinateur 
  // pour vérifier que le programme a bien démarré sans planter.
  Serial.println("--- Démarrage du système matriciel ---");
  Serial.println("En attente de saisie...");
}

void loop() {
  // --- Boucle principale (s'exécute en boucle des milliers de fois par seconde) ---

  // On interroge le clavier : "Est-ce qu'une touche est enfoncée à cet instant précis ?"
  // Si oui, on stocke la lettre ou le chiffre dans la variable 'toucheAppuyee'.
  // Si non, la fonction renvoie rien (une valeur nulle).
  char toucheAppuyee = clavier.getKey();

  // La condition "if" vérifie s'il y a bien du contenu dans la variable.
  // Si la variable est vide (personne n'a appuyé), le code passe son chemin.
  if (toucheAppuyee) {
    
    // 1. Retour visuel : On envoie la valeur lue vers l'ordinateur.
    Serial.print("Touche validée : ");
    Serial.println(toucheAppuyee);
    
    // 2. Retour sonore : Le bip
    digitalWrite(brocheBuzzer, HIGH); // On envoie du courant (5V) -> Le buzzer sonne
    delay(100);                       // On fige tout le programme pendant 100 millisecondes (durée du bip)
    digitalWrite(brocheBuzzer, LOW);  // On coupe le courant (0V) -> Le buzzer s'arrête
  }
}