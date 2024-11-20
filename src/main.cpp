#include <Arduino.h>
#include <CapacitiveSensor.h>

// Define capacitive sensors for shapes
// CapacitiveSensor capSensorCircle = CapacitiveSensor(2, 3);   // Circle
// CapacitiveSensor capSensorSquare = CapacitiveSensor(4, 5);   // Square
// CapacitiveSensor capSensorTriangle = CapacitiveSensor(6, 7); // Triangle

CapacitiveSensor capSensorHeart = CapacitiveSensor(3, 2);   // Heart
CapacitiveSensor capSensorSquare = CapacitiveSensor(6, 5);   // Square
CapacitiveSensor capSensorTriangle = CapacitiveSensor(9, 8); // Triangle

// Define speaker pin
#define SPEAKER_PIN 12

// Threshold for capacitive sensor activation
const long pressureThreshold = 1000;

// Variables to track game state
int activeTask = -1;  // Current task (0=Circle, 1=Square, 2=Triangle)
bool gameActive = false;

// Predefined messages for shapes
const char* shapes[3] = {"heart", "square", "triangle"};

// Start a new task by selecting a random shape
void startNewTask() {
  activeTask = random(0, 3);  // Random number between 0 and 2
  gameActive = true;

  // Announce the task
  Serial.print("Task: Press the "); // replace with recorded audio
  Serial.println(shapes[activeTask]);
}

// Play positive sound
void playPositiveSound() {
  tone(SPEAKER_PIN, 1000, 200);  // replace with recorded audio
  delay(250);
}

// Play negative sound
void playNegativeSound() {
  tone(SPEAKER_PIN, 400, 200);  // replace with recorded audio
  delay(250);
}

// Handle button press
void handleButtonPress(int button) {
  if (!gameActive) return;

  if (button == activeTask) {
    // Correct button press
    playPositiveSound();
    Serial.print("Correct! You pressed the ");
    Serial.println(shapes[button]);
    gameActive = false;

  } else {
    // Incorrect button press
    playNegativeSound();
    Serial.print("Incorrect! You pressed the ");
    Serial.println(shapes[button]);
  }

      // Wait briefly and start a new task
    delay(1000);
    startNewTask();
}

void setup() {
  // Initialize speaker pin as output
  pinMode(SPEAKER_PIN, OUTPUT);

  // Begin serial communication for debugging
  Serial.begin(9600);

  // Start the first task
  startNewTask();
}

void loop() {
  // Read the capacitive sensor values
  long heartValue = capSensorHeart.capacitiveSensor(30);
  long squareValue = capSensorSquare.capacitiveSensor(30);
  long triangleValue = capSensorTriangle.capacitiveSensor(30);

  // Debugging: Print sensor values
  // Serial.print("Heart: "); Serial.print(heartValue);
  // Serial.print(" Square: "); Serial.print(squareValue);
  // Serial.print(" Triangle: "); Serial.println(triangleValue);

  // Check if a shape's sensor is activated
  if (heartValue > pressureThreshold) {
    handleButtonPress(0); // Circle
  } else if (squareValue > pressureThreshold) {
    handleButtonPress(1); // Square
  } else if (triangleValue > pressureThreshold) {
    handleButtonPress(2); // Triangle
  }

  // Small delay to avoid rapid triggering
  delay(50);
}
