#include <Keypad.h> // Inclusion de la bibliothèque pour gérer le clavier matriciel

// --- Configuration du matériel ---
// On définit la taille physique du clavier (matrice 4x4)
const byte LIGNES = 4; 
const byte COLONNES = 4; 

// --- Cartographie des touches ---
// On crée un tableau à deux dimensions qui représente visuellement le clavier.
// Cela permet d'associer une coordonnée (ligne, colonne) à un caractère précis.
char touches[LIGNES][COLONNES] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

// --- Branchements électriques ---
// Définition des broches numériques de l'Arduino connectées au clavier.
// Assurez-vous que l'ordre des fils sur l'Arduino correspond bien à ces numéros.
byte brochesLignes[LIGNES] = {3, 4, 5, 6};    // Broches reliées aux lignes (R1, R2, R3, R4)
byte brochesColonnes[COLONNES] = {7, 8, 9, 10}; // Broches reliées aux colonnes (C1, C2, C3, C4)

// --- Initialisation de l'objet Keypad ---
// On crée une instance nommée "clavier". La fonction makeKeymap fait le lien 
// entre la disposition physique (les broches) et la disposition logique (les caractères).
Keypad clavier = Keypad(makeKeymap(touches), brochesLignes, brochesColonnes, LIGNES, COLONNES);

void setup() {
  // Initialisation du port série à 9600 bauds pour afficher les résultats sur l'ordinateur
  Serial.begin(9600);
  
  // Petit message de bienvenue dans le Moniteur Série
  Serial.println("--- Test du clavier matriciel 4x4 ---");
  Serial.println("Pret ! Appuyez sur une touche :");
}

void loop() {
  // La fonction .getKey() vérifie si une touche est pressée à l'instant T.
  // Elle renvoie le caractère (char) ou 'NO_KEY' (0) si rien ne se passe.
  char toucheAppuyee = clavier.getKey();

  // On vérifie si "toucheAppuyee" contient bien une valeur (différente de 0)
  if (toucheAppuyee) {
    // Affichage de la touche sur le Moniteur Série
    Serial.print("Touche detectee : ");
    Serial.println(toucheAppuyee);
    
    // Note : La bibliothèque gère elle-même l'anti-rebond (debouncing),
    // donc pas besoin d'ajouter de delay() ici !
  }
}