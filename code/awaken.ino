// #include <Arduino.h>

// Awaken - first script for Pioneer

// Temporary defining pin numbers:
#define D0 0
#define D1 1
#define D2 2
#define D3 3
#define D7 7
#define D8 8
#define D9 9
#define D10 10

// Define button pins
int BUT1 = D0;
int BUT2 = D1;
int BUT3 = D2;
int BUT4 = D3;

// Define LED pins
int LED1 = D10;
int LED2 = D9;
int LED3 = D8;
int LED4 = D7;

// Initialize functions
void footMode();
void compassMode(bool orbitDir);
void trainMode();
void rocketMode();
void readButtons();
void turnOffAll();
void pulseSun();

enum Mode {
    OFF,
    FOOT,
    COMPASS,
    TRAIN,
    ROCKET
};

Mode currentMode = OFF;
bool orbitDir = true; // true is clockwise 123, false is counterclockwise: 321

void setup() { 
  pinMode(BUT1, INPUT); // it'll give errors but on vsc that's alr :)
  pinMode(BUT2, INPUT);
  pinMode(BUT3, INPUT);
  pinMode(BUT4, INPUT);

  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);

  long startTime = millis();
}

void loop() { 
  // main code to run repeatedly:
  readButtons();

  switch(currentMode) {
    case FOOT:
      footMode();
      break;
    case COMPASS:
      compassMode(orbitDir);
      break;
    case TRAIN:
      trainMode();
      break;
    case ROCKET:
      rocketMode();
      break;
    case OFF:
    default:
      turnOffAll();
      break;
  }
}

void turnOffAll() {
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);
  digitalWrite(LED4, LOW);
}

int brightness = 0;
int fadeAmount = 5;

void pulseSun() {
  analogWrite(LED1, brightness);
  brightness += fadeAmount;
  if (brightness <= 0 || brightness >= 255) {
    fadeAmount = -fadeAmount;
  }
  delay(30); // Adjust for speed of pulsing
}

void readButtons() {
  static unsigned long lastDebounceTime = 0;
  const unsigned long debounceDelay = 200;
  unsigned long now = millis();

  if (now - lastDebounceTime < debounceDelay) return;

  if (digitalRead(BUT2) == HIGH) { // Foot
    currentMode = (currentMode == FOOT) ? OFF : FOOT;
    lastDebounceTime = now;
  }
  else if (digitalRead(BUT3) == HIGH) { // Compass
    if (currentMode == COMPASS) {
      orbitDir = !orbitDir;
    } else {
      currentMode = COMPASS;
    }
    lastDebounceTime = now;
  }
  else if (digitalRead(BUT4) == HIGH) { // Train 
    currentMode = TRAIN;
    lastDebounceTime = now;
  }
  else if (digitalRead(BUT1) == HIGH) { // Rocket
    currentMode = ROCKET;
    lastDebounceTime = now;
  }  
}

void footMode() {
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);
  digitalWrite(LED4, LOW);
  pulseSun();
}

void compassMode(bool orbitDir) {
  static unsigned long lastStepTime = 0;
  static int index = 0;
  const unsigned long stepDelay = 300;

  if (millis() - lastStepTime >= stepDelay) {
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, LOW);
    digitalWrite(LED4, LOW);

    int led = orbitDir ? (index % 3) : (2 - (index % 3));
    // sets order of orbit
    if (led == 0) digitalWrite(LED2, HIGH);
    else if (led == 1) digitalWrite(LED3, HIGH);
    else if (led == 2) digitalWrite(LED4, HIGH);

    index++;
    lastStepTime = millis();
  }

  pulseSun(); 
}

void trainMode() {
  static unsigned long lastStepTime = 0;
  static int step = 0;
  const unsigned long stepDelay = 200;

  if (millis() - lastStepTime >= stepDelay) {
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, LOW);
    digitalWrite(LED4, LOW);

    switch (step % 4) {
      case 0: digitalWrite(LED2, HIGH); break;
      case 1: digitalWrite(LED3, HIGH); break;
      case 2: digitalWrite(LED4, HIGH); break;
      case 3: digitalWrite(LED1, HIGH); break;
    }

    step++;
    lastStepTime = millis();
  }
}

void rocketMode() {
  static bool launched = false;

  if (!launched) {
    digitalWrite(LED2, HIGH); delay(200);
    digitalWrite(LED3, HIGH); delay(200);
    digitalWrite(LED4, HIGH); delay(200);
    digitalWrite(LED1, HIGH); delay(300);

    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, LOW);
    digitalWrite(LED4, LOW);
    delay(300);

    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, HIGH);
    digitalWrite(LED3, HIGH);
    digitalWrite(LED4, HIGH);

    launched = true;
  }
}