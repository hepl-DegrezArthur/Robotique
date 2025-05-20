// Simulation de mouvements du robot
void avancer() {
  // Code moteur pour avancer
  Serial.println("Le robot avance.");
  Serial3.println("LOG: Le robot avance.");
}

void reculer() {
  // Code moteur pour reculer
  Serial.println("Le robot recule.");
  Serial3.println("LOG: Le robot recule.");
}

void tournerGauche() {
  // Code moteur pour tourner à gauche
  Serial.println("Le robot tourne à gauche.");
  Serial3.println("LOG: Le robot tourne à gauche.");
}

void tournerDroite() {
  // Code moteur pour tourner à droite
  Serial.println("Le robot tourne à droite.");
  Serial3.println("LOG: Le robot tourne à droite.");
}

void arreter() {
  // Code moteur pour s'arrêter
  Serial.println("Le robot s'arrête.");
  Serial3.println("LOG: Le robot s'arrête.");
}

void setup() {
  Serial.begin(9600);     // Pour debug USB
  Serial3.begin(9600);    // Pour Bluetooth (GSM)
  Serial3.println("Système de log initialisé.");
}

void loop() {
  // Simule des actions du robot (à remplacer par tes vraies conditions)

  avancer();
  delay(2000);

  tournerGauche();
  delay(1500);

  reculer();
  delay(2000);

  arreter();
  delay(3000);
}
