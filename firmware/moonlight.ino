// #include <Arduino.h>

// Moonlight - a meditation device and nightlight in one!

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
int LEDS[] = {LED1, LED2, LED3, LED4};

// Modes
enum Mode { OFF, MIST, TIDE, FIREFLY, MOONLIT };
Mode currentMode = OFF;

bool paused = false;
int pulseSpeed = 30;

// brightness
int bright_vals[4] = {0, 80, 160, 255};
int maxbright = 0;
int brightIndex = 0;

// mist mode
int mistBrightness = 0;
int mistFadeAmount = 5;

// tide mode
int tideStep = 0;
unsigned long lastTideUpdate = 0;
const int tideInterval = 300;
int tideBrightness = 0;
int tideFadeAmount = 5;

// firefly mode
int fireflyBrightness[4] = {0, 0, 0, 0};
int fireflyDirection[4] = {1, 1, 1, 1};
unsigned long fireflyTimers[4] = {0, 0, 0, 0};
int fireflySpeeds[4] = {15, 23, 18, 20};

// moonlit mode
int moonlitIndex = 0;
int moonlitBrightness = 0;
int moonlitFadeAmount = 2;

void setup() { 
  pinMode(ROCKET, INPUT); // it'll give errors but on vsc that's alr :)
  pinMode(FOOT, INPUT);
  pinMode(COMPASS, INPUT);
  pinMode(TRAIN, INPUT);

  for (int i = 0; i < 4; i++) {
    pinMode(LEDS[i], OUTPUT);
  }
}

void loop() {
    readButtons();

    if (paused) return;

    switch (currentMode) {
        case MIST:
            mistMode();
            break;
        case TIDE:
            tideMode();
            break;
        case FIREFLY:
            fireflyMode();
            break;
        case MOONLIT:
            moonlitMode();
            break;
        case OFF:
        default:
            turnOffAll();
            break;
    }
}

void readButtons() {
    if (digitalRead(FOOT) == HIGH) {
        brightIndex = (brightIndex + 1) % 4;
        maxbright = bright_vals[brightIndex];
        delay(300);
    }

    if (digitalRead(COMPASS) == HIGH)
    {
        paused = !paused; // toggle
        delay(300);
    }

    if (digitalRead(TRAIN) == HIGH) {
        if (currentMode != MOONLIT) {
            currentMode = MOONLIT;
            moonlitIndex = 0;
            moonlitBrightness = 0;
        } else {
            moonlitIndex = (moonlitIndex + 1) % 4;
        }
        
        delay(300);
    }

    if (digitalRead(ROCKET) == HIGH) {
        if (currentMode == MOONLIT) {
            currentMode = MIST;
        } else {
            currentMode = static_cast<Mode>((currentMode + 1) % 4); // OFF is skipped
        }
        delay(300);
    }

}

void turnOffAll() {
  for (int i = 0; i < 4; i++) {
    analogWrite(LEDS[i], 0);
  }
}

void mistMode() {
  // Update brightness once
  mistBrightness += mistFadeAmount;
  if (mistBrightness <= 0 || mistBrightness >= maxbright) {
    mistFadeAmount = -mistFadeAmount;
  }

  // Apply to all LEDs
  for (int i = 0; i < 4; i++) {
    analogWrite(LEDS[i], mistBrightness);
  }

  delay(pulseSpeed);
}

void tideMode() {
  tideBrightness += tideFadeAmount;
  if (tideBrightness <= 0 || tideBrightness >= maxbright) {
    tideFadeAmount = -tideFadeAmount;

    if (tideBrightness <= 0) {
      tideStep = (tideStep + 1) % 8;
    }
  }

  int ledsOn[4] = {0, 0, 0, 0};

  switch (tideStep) {
    case 0: ledsOn[0] = 1; break;
    case 1: ledsOn[0] = ledsOn[1] = 1; break;
    case 2: ledsOn[0] = ledsOn[1] = ledsOn[2] = 1; break;
    case 3: ledsOn[0] = ledsOn[1] = ledsOn[2] = ledsOn[3] = 1; break;
    case 4: ledsOn[1] = ledsOn[2] = ledsOn[3] = 1; break;
    case 5: ledsOn[2] = ledsOn[3] = 1; break;
    case 6: ledsOn[3] = 1; break;
    case 7: break; // all off
  }

  for (int i = 0; i < 4; i++) {
    analogWrite(LEDS[i], ledsOn[i] ? tideBrightness : 0);
  }

  delay(pulseSpeed);
}

void fireflyMode() {
  for (int i = 0; i < 4; i++) {
    if (millis() - fireflyTimers[i] > fireflySpeeds[i]) {
      fireflyTimers[i] = millis();
      fireflyBrightness[i] += fireflyDirection[i];

      if (fireflyBrightness[i] >= maxbright || fireflyBrightness[i] <= 0) {
        fireflyDirection[i] = -fireflyDirection[i];
      }

      analogWrite(LEDS[i], fireflyBrightness[i]);
    }
  }
}

void moonlitMode() {
  moonlitBrightness += moonlitFadeAmount;
  if (moonlitBrightness <= 0 || moonlitBrightness >= maxbright) {
    moonlitFadeAmount = -moonlitFadeAmount;
  }

  for (int i = 0; i < 4; i++) {
    analogWrite(LEDS[i], (i == moonlitIndex) ? moonlitBrightness : 0);
  }

  delay(pulseSpeed);
}
