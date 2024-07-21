#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Ultrasonic.h>

#define TRIGGER_PIN 4 // Connect the HC-SR04 trigger pin to digital pin 4
#define ECHO_PIN 5    // Connect the HC-SR04 echo pin to digital pin 5
Ultrasonic ultrasonic(TRIGGER_PIN, ECHO_PIN);

LiquidCrystal_I2C lcd(0x27, 16, 2); // Set the I2C address and LCD dimensions
const int relayPin = 2; // Connect the relay control pin to digital pin 2

void setup() {
  Wire.begin(); // Initialize I2C communication
  lcd.init();   // Initialize the LCD
  lcd.backlight(); // Turn on the backlight
  lcd.clear();

  lcd.print("HC-SR04");
  lcd.setCursor(0, 1);
  lcd.print("LCD Control");

  pinMode(relayPin, OUTPUT); // Set the relay control pin as an output

  Serial.begin(9600); // Initialize Serial communication
}

void loop() {
  long distance = ultrasonic.read(); // Read the distance from the HC-SR04 sensor

  // Display the distance on the LCD
  lcd.clear();
  lcd.print("Distance: ");
  lcd.print(distance);
  lcd.print(" cm");

  // If the distance is less than a threshold (e.g., 10 cm), turn on the relay
  if (distance < 10) {
    digitalWrite(relayPin, HIGH); // Turn on the relay
  } else {
    digitalWrite(relayPin, LOW); // Turn off the relay
  }

  delay(1000); // Delay for stability
}
