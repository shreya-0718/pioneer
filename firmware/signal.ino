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
int SEND = D0;
int DOT = D1;
int DASH = D2;
int SPACE = D3;

// Define LED pins
int LED1 = D10; // sun
int LED2 = D9;
int LED3 = D8;
int LED4 = D7;

String morse = "";
bool trainSpace = false; 
// to check if the last button pressed was trainSpace or not
long startTime = 0;

void setup() { 
    pinMode(SEND, INPUT);
    pinMode(DOT, INPUT);
    pinMode(DASH, INPUT);
    pinMode(SPACE, INPUT);

    pinMode(LED1, OUTPUT);
    pinMode(LED2, OUTPUT);
    pinMode(LED3, OUTPUT);
    pinMode(LED4, OUTPUT);

    startTime = millis();

    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, LOW);
    digitalWrite(LED4, LOW);
}

void loop() {
    if (digitalRead(DOT) == HIGH) {
        morse += ".";
        trainSpace = false;
        delay(300);
    }

    if (digitalRead(DASH) == HIGH) {
        morse += "_";
        trainSpace = false;
        delay(300);
    }
    if (digitalRead(SPACE) == HIGH) {
        if (trainSpace) {
            morse += "  "; // word space
            trainSpace = false;
        } else {
            morse += " "; // letter space
            trainSpace = true;
        }

        delay(300);
    }

    if (digitalRead(SEND) == HIGH) {
        flashAll(2); // flashes ALL LEDs
        sendMorse(morse);
        flashAll(2);

        trainSpace = false;

        delay(700);
    }
}

void sendMorse(String code) {
    for (int i = 0; i < code.length(); i++) {
        char c = code[i];

        // word space: three consecutive spaces
        if (c == ' ' && i + 1 < code.length() && code[i + 1] == ' ') {
            delay(1400);
            i++;
            continue;
        }

        if (c == '.') blinkDot();
        else if (c == '_') blinkDash();
        else if (c == ' ') delay(600); // letter space

        // space between symbols unless the next character is a space
        if (i < code.length() - 1 && code[i + 1] != ' ') delay(200);
    }
}

void blinkDot() {
    digitalWrite(LED1, HIGH);
    delay(600);
    digitalWrite(LED1, LOW);
}

void blinkDash() {
    digitalWrite(LED1, HIGH);
    delay(600);
    digitalWrite(LED1, LOW);
}

void flashAll(int times) {
    for (int i = 0; i < times; i++)
    {
        digitalWrite(LED1, HIGH);
        digitalWrite(LED2, HIGH);
        digitalWrite(LED3, HIGH);
        digitalWrite(LED4, HIGH);

        delay(300);

        digitalWrite(LED1, LOW);
        digitalWrite(LED2, LOW);
        digitalWrite(LED3, LOW);
        digitalWrite(LED4, LOW);
        
        delay(300);
    }
}