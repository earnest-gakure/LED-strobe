//strobing 2 LEDs in a pattern 


int led1 = 12;
int led2 = 11; // Define the pin for the second LED
long timer = 0;
long led2Timer = 0;
int state = LOW;
int led2State = LOW;
int blinkCount = 0;
int led2BlinkCount = 0;
bool inLongDelay = false;
const long shortInterval = 400000; // Adjust this value for short strobe interval and long delay
const long blinkInterval = shortInterval / 8; // Interval for each blink within the short interval

void setup() {
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT); // Set the second LED pin as output
  Serial.begin(9600); // Initialize serial communication
}

void loop() {
  // Increment both timers to keep them in sync
  timer++;
  led2Timer++;

  if (!inLongDelay) {
    if (timer >= blinkInterval) {
      state = !state; // Toggle the state
      digitalWrite(led1, state); // Update the first LED state

      if (state == HIGH) {
        Serial.println("LED1 ON");
        blinkCount++;
      } else {
        Serial.println("LED1 OFF");
      }

      timer = 0; // Reset the timer

      if (blinkCount >= 4) {
        inLongDelay = true;
        blinkCount = 0;
        state = LOW; // Ensure LED1 is off during the long delay
        digitalWrite(led1, state);
        Serial.println("Entering long delay...");
      }
    }
  } else {
    if (led2Timer >= blinkInterval) {
      led2State = !led2State; // Toggle the state for LED2
      digitalWrite(led2, led2State); // Update the second LED state

      if (led2State == HIGH) {
        Serial.println("LED2 ON");
        led2BlinkCount++;
      } else {
        Serial.println("LED2 OFF");
      }

      led2Timer = 0; // Reset the timer for LED2

      if (led2BlinkCount >= 4) {
        inLongDelay = false;
        led2BlinkCount = 0;
        led2State = LOW; // Ensure LED2 is off when returning to LED1 strobe
        digitalWrite(led2, led2State);
        Serial.println("Exiting long delay...");
      }
    }
  }
}
