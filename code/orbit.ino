// #include <Arduino.h>

// Signal - a morse code flasher :)

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
int LED1 = D10; // sun
int LED2 = D9;
int LED3 = D8;
int LED4 = D7;

int time = 0; // time on da timer!
bool timerRunning = false;
bool timerPaused = false;
long startTime = 0;

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

    }
}

void updateLEDs() {

}