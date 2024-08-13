//2 LED strobe
int led1 = 11;
int led2 = 12;
long timer = 0;
int state = LOW;
const long Interval = 200000;      // Overall duration for on/off
const long strobeInterval = 10000; // Duration for each strobe (half on, half off)
int strobeCount = 0;               // Counter for the number of strobes
int maxStrobe = 3;
void setup() {
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  Serial.begin(9600);  // Initialize serial communication
}

void loop() {
  while (1) {
    timer++;
    timerON();
    timerOFF();
  }
}

void timerON() {
  if (state == LOW && timer >= Interval) {
    strobe();  // Call the strobe function for led1
    state = HIGH;
    timer = 0;  // Reset the timer after strobing
  }
}

void timerOFF() {
  if (state == HIGH && timer >= Interval) {
    digitalWrite(led1, LOW);
    Serial.println("LED1 OFF");
    strobe2();  // Call the strobe function for led2
    state = LOW;
    timer = 0;  // Reset the timer after turning the LED off
    strobeCount = 0;  // Reset the strobe counter
  }
}

void strobe() {
  long strobeTimer = 0;
  strobeCount = 0;

  while (strobeCount <= maxStrobe) {  // Strobe only 3 times
    if (strobeTimer % (2 * strobeInterval) < strobeInterval) {
      digitalWrite(led1, HIGH);  // Turn the LED on during the first half of the strobeInterval
    } else {
      digitalWrite(led1, LOW);   // Turn the LED off during the second half of the strobeInterval
    }

    strobeTimer++;  // Increment the strobe timer

    // Check if a full strobe cycle (on + off) has completed
    if (strobeTimer >= 2 * strobeInterval) {
      strobeTimer = 0;  // Reset the strobe timer for the next cycle
      strobeCount++;    // Increment the strobe count
    }
  }

  Serial.println("LED1 Strobe complete");
}

void strobe2() {
  long strobeTimer = 0;
  strobeCount = 0;

  while (strobeCount <= maxStrobe) {  // Strobe only 3 times
    if (strobeTimer % (2 * strobeInterval) < strobeInterval) {
      digitalWrite(led2, HIGH);  // Turn LED2 on during the first half of the strobeInterval
    } else {
      digitalWrite(led2, LOW);   // Turn LED2 off during the second half of the strobeInterval
    }

    strobeTimer++;  // Increment the strobe timer

    // Check if a full strobe cycle (on + off) has completed
    if (strobeTimer >= 2 * strobeInterval) {
      strobeTimer = 0;  // Reset the strobe timer for the next cycle
      strobeCount++;    // Increment the strobe count
    }
  }

  Serial.println("LED2 Strobe complete");
}
