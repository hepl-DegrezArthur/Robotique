#include <avr/io.h>
#include <avr/interrupt.h>

// Constants for the timer
#define Clock 16000000                                 	// Clock frequency of the 328P
#define Prescaler 256                                  	// Prescaler value
#define Periode 0.1                                   	// Desired frequency
#define CounterValue ((Clock/Prescaler)*Periode)   		// Calculation for the compare value

// Définition des broches
#define DataDirectionRegister DDRD		// A changer quand il faudra passer sur l'arduino mega
#define PORT PORTD						// A changer quand il faudra passer sur l'arduino mega				
#define trig1Pin PD2
#define echo1Pin PD3
#define trig2Pin PD5
#define echo2Pin PD4
#define LEDPin PD7


// Variables de mesure
long duration1;
int distance1;
long duration2;
int distance2;

void setup() {
  // Timer1 configuration in CTC mode
  TCCR1A = 0x00;                               // CTC mode, no output pin connected
  TCCR1B = (1 << WGM12) | (1 << CS12);         // CTC mode and prescaler set to 256
  TCCR1B &= ~(0x20);                           // Ensure the reserved bit is set to 0 when writing to the register
  OCR1A = CounterValue;                        // Set the compare value
  TIMSK1 |= (1 << OCIE1A);                     // Enable the interrupt on compare match A
  sei();                                       // Enable global interrupts
  
  DataDirectionRegister |= (1 << trig1Pin); 
  DataDirectionRegister |= (0 << echo1Pin);
  DataDirectionRegister |= (1 << trig2Pin); 
  DataDirectionRegister |= (0 << echo2Pin);
  DataDirectionRegister |= (1 << LEDPin); 
  
  // Initialisation de la communication série
  Serial.begin(9600);
}

void loop() {
  
}

ISR(TIMER1_COMPA_vect) {
  GetDistances();
  while (distance1 <= 15 || distance2 <= 15){
    GetDistances();
    // Fct StopMotors
    PORT |= (1 << LEDPin);
    delay(100);			// Delai juste pour voir les valeurs
  }
  PORT &= ~(1 << LEDPin);
  delay(100);			// Delai pour simuler un code
}

void GetDistances(){
  // Envoi d'une impulsion ultrasonique
  	PORT &= ~(1 << trig1Pin);
  	delayMicroseconds(2);
  	PORT |= (1 << trig1Pin);
  	delayMicroseconds(10);
  	PORT &= ~(1 << trig1Pin);
  	// Lecture du signal de retour
  	duration1 = pulseIn(echo1Pin, HIGH);
  
  	// Envoi d'une impulsion ultrasonique
  	PORT &= ~(1 << trig2Pin);
  	delayMicroseconds(2);
  	PORT |= (1 << trig2Pin);
  	delayMicroseconds(10);
  	PORT &= ~(1 << trig2Pin);
  	// Lecture du signal de retour
  	duration2 = pulseIn(echo2Pin, HIGH);

  	// Calcul de la distance en cm
  	distance1 = duration1 * 0.034 / 2;
  	distance2 = duration2 * 0.034 / 2;
  
  	// Affichage de la distance sur le moniteur série
  	Serial.print("Distance 1: ");
  	Serial.print(distance1);
  	Serial.println(" cm");
  	Serial.print("Distance 2: ");
  	Serial.print(distance2);
  	Serial.println(" cm");
}
