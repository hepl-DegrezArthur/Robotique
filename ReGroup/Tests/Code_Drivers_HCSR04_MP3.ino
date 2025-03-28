#include <avr/io.h>
#include <avr/interrupt.h>
#include <JQ6500_Serial.h>

//*************************************************//
// All the defines and the most globals variables  // 
//*************************************************//

// Global define
#define Clock 16000000

// Define for the timer 3 for interrupt
#define Prescaler_Timer3 256
#define Periode_Timer3 0.05 
#define CounterValue ((uint16_t)((Clock / Prescaler_Timer3) * Periode_Timer3))

// Define and variabled for the HC-SR04
#define trig1Pin 22
#define echo1Pin 24
#define trig2Pin 23
#define echo2Pin 25
#define DistanceImpact 20
volatile long duration1, duration2;
volatile int distance1 = 100, distance2 = 100;
bool moving = false; 

// Define for the drivers
#define IN2D 7  // PH4 - Mauve
#define IN1D 6  // PH3 - Orange
#define IN2G 9  // PH6 - Mauve
#define IN1G 8  // PH5 - Orange

// Define for the MP3
JQ6500_Serial mp3(Serial2);


//*************************************************//
//            Setup all the components             // 
//*************************************************//
void setup() {
  Serial.begin(9600);
  
  // Setup the HC-SR04
  pinMode(trig1Pin, OUTPUT);
  pinMode(echo1Pin, INPUT);
  pinMode(trig2Pin, OUTPUT);
  pinMode(echo2Pin, INPUT);

  // Setup the drivers
  pinMode(IN1D, OUTPUT);
  pinMode(IN2D, OUTPUT);
  pinMode(IN1G, OUTPUT);
  pinMode(IN2G, OUTPUT);

  // Init timer 3 
  Init_Timer3ForInterrupt();

  // Init MP3
  Serial2.begin(9600);
  mp3.reset();
  mp3.setVolume(30);
  mp3.setLoopMode(MP3_LOOP_NONE);
}



//*************************************************//
//                  Main code                      // 
//*************************************************//
void loop() {
  // Vérification des distances mesurées
  if (distance1 >= DistanceImpact && distance2 >= DistanceImpact) {
    if (!moving) {
      Start_Front();
      mp3.playFileByIndexNumber(2);
      moving = true;
    }
  } else {
    if (moving) {
      StopMoving();
      mp3.playFileByIndexNumber(1);
      delay(300);
      Start_Reverse();
      delay(1000);
      StopMoving();
      delay(500);
      Turn();
      delay(1000);
      moving = false;
    }
  }
  delay(50); // Petite pause pour éviter une boucle trop rapide
}


//*************************************************//
//           All the functions are below           // 
//*************************************************//

// Interruption Timer3
ISR(TIMER3_COMPA_vect) {
  GetDistances();
}

void GetDistances() {
  cli(); // Disable interrrupts to make sure there is no conflicts with the PWM

  // Mesure distance 1
  digitalWrite(trig1Pin, LOW);
  delayMicroseconds(2);
  digitalWrite(trig1Pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig1Pin, LOW);
  duration1 = pulseIn(echo1Pin, HIGH, 15000); 
  distance1 = (duration1 > 0) ? duration1 * 0.034 / 2 : 100;

  // Mesure distance 2
  digitalWrite(trig2Pin, LOW);
  delayMicroseconds(2);
  digitalWrite(trig2Pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig2Pin, LOW);
  duration2 = pulseIn(echo2Pin, HIGH, 15000);
  distance2 = (duration2 > 0) ? duration2 * 0.034 / 2 : 100;

  sei(); // Activate interrupts
  /*
  // Affichage des distances
  Serial.print("Capteur 1: ");
  Serial.print(distance1);
  Serial.println(" cm");

  Serial.print("Capteur 2: ");
  Serial.print(distance2);
  Serial.println(" cm");
  */
}

void Init_Timer3ForInterrupt() {
  TCCR3A = 0x00;
  TCCR3B = (1 << WGM32) | (1 << CS32); // CTC mode et prescaler 256
  OCR3A = CounterValue;
  TIMSK3 |= (1 << OCIE3A); // Active l’interruption pour Timer3
  sei();
}

void Stop_Timer3() {
  TCCR3B &= ~((1 << CS30) | (1 << CS31) | (1 << CS32));
}

void Start_Front() {
  digitalWrite(IN1D, LOW);
  digitalWrite(IN1G, LOW);
  analogWrite(IN2D, 80); 
  analogWrite(IN2G, 80);
}

void Turn(){
  digitalWrite(IN2D, LOW);
  digitalWrite(IN1G, LOW);
  analogWrite(IN1D, 100);
  analogWrite(IN2G, 100);
}

void StopMoving() {
  digitalWrite(IN1D,HIGH);
  digitalWrite(IN2D,HIGH);
  digitalWrite(IN1G,HIGH);
  digitalWrite(IN2G,HIGH);
  
}

void Start_Reverse(){
  digitalWrite(IN2D, LOW);
  digitalWrite(IN2G, LOW);
  analogWrite(IN1D, 80); 
  analogWrite(IN1G, 80);
}
