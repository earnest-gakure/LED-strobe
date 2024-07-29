int led = 13;
long timer = 0;
int state = LOW;
int blinkCount = 0;
bool inLongDelay = false;
const long shortInterval = 300000; // Adjust this value for short strobe interval and long delay
const long blinkInterval = shortInterval / 6; // Interval for each blink within the short interval

void setup() {
  pinMode(led, OUTPUT);
  Serial.begin(9600); // Initialize serial communication
}

void loop() {
  timer++;

  if (!inLongDelay) {
    if (timer >= blinkInterval) {
      state = !state; // Toggle the state
      digitalWrite(led, state); // Update the LED state

      if (state == HIGH) {
        Serial.println("LED ON");
        blinkCount++;
      } else {
        Serial.println("LED OFF");
      }

      timer = 0; // Reset the timer

      if (blinkCount >= 3) {
        inLongDelay = true;
        blinkCount = 0;
        state = LOW; // Ensure the LED is off during the long delay
        digitalWrite(led, state);
        Serial.println("Entering long delay...");
      }
    }
  } else {
    if (timer >= shortInterval) {
      inLongDelay = false;
      timer = 0; // Reset the timer for the next strobe cycle
      Serial.println("Exiting long delay...");
    }
  }
}
