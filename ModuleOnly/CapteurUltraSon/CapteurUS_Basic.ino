// Définition des broches
const int trigPin = 12;
const int echoPin = 11;

// Variables de mesure
long duration;
int distance;

void setup() {
    // Configuration des broches
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    
    // Initialisation de la communication série
    Serial.begin(9600);
}

void loop() {
    // Envoi d'une impulsion ultrasonique
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    // Lecture du signal de retour
    duration = pulseIn(echoPin, HIGH);

    // Calcul de la distance en cm
    distance = duration * 0.034 / 2;

    // Affichage de la distance sur le moniteur série
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");

    // Petit délai pour éviter des rafraîchissements trop rapides
    delay(100);
}
