int BUT1 = D7;
int BUT2 = D5;
int BUT3 = D4;
int BUT4 = D2;
int LED1 = D8;
int LED2 = D6;
int LED3 = D3;
int LED4 = D1;

int patlen = 7;
int sequence[7];
int playerSequence[7];

int ledPins[] = {0, LED1, LED2, LED3, LED4};
int buttonPins[] = {0, BUT1, BUT2, BUT3, BUT4};

long lastDebounceTime[5] = {0, 0, 0, 0, 0};
int lastButtonState[5] = {HIGH, HIGH, HIGH, HIGH, HIGH};

void setup() {
  pinMode(BUT1, INPUT_PULLUP);
  pinMode(BUT2, INPUT_PULLUP);
  pinMode(BUT3, INPUT_PULLUP);
  pinMode(BUT4, INPUT_PULLUP);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);

  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);
  digitalWrite(LED4, LOW);

  randomSeed(analogRead(A0));
}

void loop() {
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

  bool gameReady = false;
  while (!gameReady) {
    int currentBut1State = digitalRead(BUT1);
    if (currentBut1State != lastButtonState[1]) {
      if (millis() - lastDebounceTime[1] > 50) {
        if (currentBut1State == LOW) {
          gameReady = true;
        }
      }
      lastDebounceTime[1] = millis();
    }
    lastButtonState[1] = currentBut1State;

    digitalWrite(LED1, HIGH);
    delay(150);
    digitalWrite(LED1, LOW);
    delay(150);
  }

  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);
  digitalWrite(LED4, LOW);
  delay(500);

  for (int i = 0; i < patlen; i++) {
    sequence[i] = random(1, 5);
  }

  delay(500);

  for (int i = 0; i < patlen; i++) {
    digitalWrite(ledPins[sequence[i]], HIGH);
    delay(400);
    digitalWrite(ledPins[sequence[i]], LOW);
    delay(200);
  }
  
  int inputIndex = 0;
  unsigned long startTime = millis();
  bool timeoutOccurred = false;
  bool playerMadeMistake = false;
  int debounceDelay = 50;

  while (inputIndex < patlen && !timeoutOccurred && !playerMadeMistake) {
    if (millis() - startTime > 10000) {
      timeoutOccurred = true;
      break;
    }

    for (int i = 1; i <= 4; i++) {
      int currentButtonState = digitalRead(buttonPins[i]);

      if (currentButtonState != lastButtonState[i]) {
        if (millis() - lastDebounceTime[i] > debounceDelay) {
          if (currentButtonState == LOW) {
            playerSequence[inputIndex] = i;

            if (playerSequence[inputIndex] != sequence[inputIndex]) {
              playerMadeMistake = true;
              digitalWrite(ledPins[i], HIGH);
              delay(500);
              digitalWrite(ledPins[i], LOW);
              break;
            }

            inputIndex++;
            digitalWrite(ledPins[i], HIGH);
            delay(50);
            digitalWrite(ledPins[i], LOW);

            startTime = millis();
            break;
          }
        }
        lastDebounceTime[i] = millis();
      }
      lastButtonState[i] = currentButtonState;
    }
    delay(10);
  }

  bool isCorrect = true;

  if (timeoutOccurred || playerMadeMistake) {
    isCorrect = false;
  }

  if (isCorrect) {
    digitalWrite(ledPins[1], HIGH); delay(300); digitalWrite(ledPins[1], LOW); delay(200);
    digitalWrite(ledPins[2], HIGH); delay(300); digitalWrite(ledPins[2], LOW); delay(200);
    digitalWrite(ledPins[3], HIGH); delay(300); digitalWrite(ledPins[3], LOW); delay(200);
    digitalWrite(ledPins[4], HIGH); delay(300); digitalWrite(ledPins[4], LOW); delay(200);
    digitalWrite(ledPins[4], HIGH); delay(300); digitalWrite(ledPins[4], LOW); delay(200);
    digitalWrite(ledPins[4], HIGH); delay(300); digitalWrite(ledPins[4], LOW); delay(200);
  } else {
    digitalWrite(ledPins[4], HIGH); delay(300); digitalWrite(ledPins[4], LOW); delay(200);
    digitalWrite(ledPins[3], HIGH); delay(300); digitalWrite(ledPins[3], LOW); delay(200);
    digitalWrite(ledPins[2], HIGH); delay(300); digitalWrite(ledPins[2], LOW); delay(200);
    digitalWrite(ledPins[1], HIGH); delay(300); digitalWrite(ledPins[1], LOW); delay(200);
    digitalWrite(ledPins[1], HIGH); delay(300); digitalWrite(ledPins[1], LOW); delay(200);
    digitalWrite(ledPins[1], HIGH); delay(300); digitalWrite(ledPins[1], LOW); delay(200);
  }
}