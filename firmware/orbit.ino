// #include <Arduino.h>

// Orbit - a timer!

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
int ROCKET = D0;
int FOOT = D1;
int COMPASS = D2;
int TRAIN = D3;

// Define LED pins
int LED1 = D9;
int LED2 = D8;
int LED3 = D7;
int LED4 = D10; // sun

int time = 0; // time on da timer!
bool timerRunning = false;
bool timerPaused = false;
long startTime = 0;

// set the threshold values
int thres1 = 5;
int thres2 = 20;
int thres3 = 35;
int thres4 = 50;

void setup() { 
  pinMode(ROCKET, INPUT); // it'll give errors but on vsc that's alr :)
  pinMode(FOOT, INPUT);
  pinMode(COMPASS, INPUT);
  pinMode(TRAIN, INPUT);

  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);

  startTime = millis();
}

void loop() {
    if (digitalRead(FOOT) == HIGH) {
        time += 5; // minutes
        if (time > 60) time = 0;
        updateLEDs();
        delay(300);
    }

    if (digitalRead(ROCKET) == HIGH && time > 0 && !timerRunning)
    {
        flashActiveLEDs(2);
        timerRunning = true;
        timerPaused = false;
        startTime = millis();
        delay(300);
    }

    if (digitalRead(COMPASS) == HIGH && timerRunning)
    {
        timerPaused = !timerPaused; // toggle
        delay(300);
    }

    if (digitalRead(TRAIN) == HIGH) {
        flashAllLEDs(3);
        time = 0;
        timerRunning = false;
        timerPaused = false;
        updateLEDs();
        delay(300);
    }

    // write timer logic
    if (timerRunning && !timerPaused) {
        long elapsed = (millis() - startTime) / 60000; // minutes passed since
        int remaining = time - elapsed;

        if (remaining != time) {
            time = remaining;
            checkLEDThresholds();
            updateLEDs();
        }

        if (time <= 0) {
            timerRunning = false;

            // light up LEDs in order
            digitalWrite(LED1, HIGH);
            delay(150);
            digitalWrite(LED2, HIGH);
            delay(150);
            digitalWrite(LED3, HIGH);
            delay(150);
            digitalWrite(LED4, HIGH);
            delay(300);

            flashAllLEDs(3);
            time = 0;
        }
    }

    if (timerPaused) {
        pulseActiveLEDs();
    }
}

void updateLEDs() {
    digitalWrite(LED1, (time >= thres1) ? HIGH : LOW);
    digitalWrite(LED2, (time >= thres2) ? HIGH : LOW);
    digitalWrite(LED3, (time >= thres3) ? HIGH : LOW);
    digitalWrite(LED4, (time >= thres4) ? HIGH : LOW);
}

void checkLEDThresholds() {
    if (time == thres4 - 1) flashLED(LED4);
    if (time == thres3 - 1) flashLED(LED3);
    if (time == thres2 - 1) flashLED(LED2);
    if (time == thres1 - 1) flashLED(LED1);
}

void flashActiveLEDs(int times) {
    for (int i = 0; i < times; i++) {
        setActiveLEDs(LOW);
        delay(200);
        setActiveLEDs(HIGH);
        delay(200);
    }
}

void setActiveLEDs(int state) {
    if (time >= thres1) digitalWrite(LED1, state);
    if (time >= thres2) digitalWrite(LED2, state);
    if (time >= thres3) digitalWrite(LED3, state);
    if (time >= thres4) digitalWrite(LED4, state);
}

void flashAllLEDs(int flashes) {
    for (int i = 0; i < flashes; i++) {
        digitalWrite(LED1, HIGH);
        digitalWrite(LED2, HIGH);
        digitalWrite(LED3, HIGH);
        digitalWrite(LED4, HIGH);
        delay(200);
        digitalWrite(LED1, LOW);
        digitalWrite(LED2, LOW);
        digitalWrite(LED3, LOW);
        digitalWrite(LED4, LOW);
        delay(200);
    }
}

void pulseActiveLEDs() { // fade in and out :)
  for (int brightness = 0; brightness <= 255; brightness += 5) {
    setActiveLEDsAnalog(brightness);
    delay(10);
  }
  for (int brightness = 255; brightness >= 0; brightness -= 5) {
    setActiveLEDsAnalog(brightness);
    delay(10);
  }
}

void setActiveLEDsAnalog(int brightness) {
  if (time >= thres1) analogWrite(LED1, brightness);
  if (time >= thres2) analogWrite(LED2, brightness); 
  if (time >= thres3) analogWrite(LED3, brightness);
  if (time >= thres4) analogWrite(LED4, brightness);
}