/**
 * Arduino Plant Watering Indicator
 * 
 * Measures the concentration of water in a plant and tells you
 * whether the plant needs water.
 * 
 * Hardware:
 * - Arduino
 * - Water Sensor
 * - 3 jumper wires (male to male)
 * 
 * And optionally, if you want LEDs to tell the output:
 * - 4 jumper wires (male to male)
 * - Red, yellow/orange and green LED
 * - 3x 220 ohm resistor
 * 
 * Tested with Arduino Nano, but compatible with all Arduino boards.
 * See README for pinout used with this code.
 * 
 * (c) Romein van Buren 2021.
 * MIT lisenced.
 */

// SETTINGS BEGIN ----------------------
// You can modify the following settings as per your requirements.

/**
 * Which monitor you want to use.
 * 
 * "monitor" for text and "plotter" for chart
 */
#define MONITOR          "monitor"

/**
 * Signal pin, which goes to the water sensor.
 */
#define PIN_SIGNAL       A0

/**
 * Pin of the LED which blinks if there is too less water.
 */
#define LED_LOW          10

/**
 * Pin of the LED which blinks if there is a medium
 * concentration of water.
 */
#define LED_MEDIUM       11

/**
 * Pin of the LED which blinks if there is enough water.
 */
#define LED_HIGH         12

// SETTINGS END ------------------------
// Here begins the program.

/**
 * Tresholds.
 * 
 * These have been fine-tuned, so do not modify these unless you
 * know what you're doing.
 */
#define TRESHOLD_MEDIUM  200
#define TRESHOLD_HIGH    500

/**
 * Output of the sensor
 */
int val;

/**
 * Output indicator.
 * 
 * Can be one of "low", "medium" or "high".
 */
String indicator;

/**
 * Instruction congruent to indicator.
 */
String instruction;

/**
 * Setup
 */
void setup() {
  Serial.begin(9600);
  pinMode(LED_LOW,    OUTPUT);
  pinMode(LED_MEDIUM, OUTPUT);
  pinMode(LED_HIGH,   OUTPUT);
}

/**
 * Loop
 */
void loop() {
  val = analogRead(PIN_SIGNAL);
  indicate();
  led();
  delay(1000);
}

/**
 * Indicate
 */
void indicate() {
  if (val > TRESHOLD_HIGH) {
    indicator = "high";
    instruction = "This plant has more than enough water.";
  } else if (val > TRESHOLD_MEDIUM) {
    indicator = "medium";
    instruction = "You should water this plant shortly.";
  } else {
    indicator = "low";
    instruction = "How did you not kill this plant?";
  }

  if (MONITOR == "monitor") {
    Serial.print(val);
    Serial.print("\t");
    Serial.print(indicator);
    Serial.print("\t");
    Serial.println(instruction);
  } if (MONITOR == "plotter") {
    Serial.println(val);
  }
}

/**
 * Setup LED's
 */
void led() {
  if (indicator == "high") {
    digitalWrite(LED_HIGH,   HIGH);
    digitalWrite(LED_MEDIUM, LOW);
    digitalWrite(LED_LOW,    LOW);
  } else if (indicator == "medium") {
    digitalWrite(LED_HIGH,   LOW);
    digitalWrite(LED_MEDIUM, HIGH);
    digitalWrite(LED_LOW,    LOW);
  } else if (indicator == "low") {
    digitalWrite(LED_HIGH,   LOW);
    digitalWrite(LED_MEDIUM, LOW);
    digitalWrite(LED_LOW,    HIGH);
  } else {
    Serial.println("ERROR: I don't know which LED to turn on.");
  }
}
