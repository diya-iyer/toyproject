#include <Arduino.h>

// Define LED pins
#define GREEN_LED 3
#define RED_LED 5
#define BLUE_LED 6
#define PURPLE_LED 9
#define WHITE_LED 10

// Define pressure sensor pins
#define PRESSURE_SENSOR_GREEN A0
#define PRESSURE_SENSOR_RED A1
#define PRESSURE_SENSOR_BLUE A2
#define PRESSURE_SENSOR_PURPLE A3
#define PRESSURE_SENSOR_WHITE A4

// Define speaker pin
#define SPEAKER_PIN 11

// Threshold for pressure sensor to detect a press
const int pressureThreshold = 100;

// Variables to track game state
int activeTask = -1;  // Current task (0=Green, 1=Red, etc.)
bool gameActive = false;

// Predefined messages (these could map to sound effects in a future MP3 system)
const char* shapes[5] = {"star", "circle", "triangle", "square", "heart"};
const char* colors[5] = {"green", "red", "blue", "purple", "white"};

void setup() {
  // Initialize LED pins as outputs
  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);
  pinMode(PURPLE_LED, OUTPUT);
  pinMode(WHITE_LED, OUTPUT);

  // Initialize pressure sensor pins as inputs
  pinMode(PRESSURE_SENSOR_GREEN, INPUT);
  pinMode(PRESSURE_SENSOR_RED, INPUT);
  pinMode(PRESSURE_SENSOR_BLUE, INPUT);
  pinMode(PRESSURE_SENSOR_PURPLE, INPUT);
  pinMode(PRESSURE_SENSOR_WHITE, INPUT);

  // Initialize speaker pin as output
  pinMode(SPEAKER_PIN, OUTPUT);

  // Begin serial communication for debugging
  Serial.begin(9600);

  // Start the game
  startNewTask();
}

void loop() {
  // Read the pressure sensor values
  int greenSensorValue = analogRead(PRESSURE_SENSOR_GREEN);
  int redSensorValue = analogRead(PRESSURE_SENSOR_RED);
  int blueSensorValue = analogRead(PRESSURE_SENSOR_BLUE);
  int purpleSensorValue = analogRead(PRESSURE_SENSOR_PURPLE);
  int whiteSensorValue = analogRead(PRESSURE_SENSOR_WHITE);

  // Check if each sensor is pressed
  if (greenSensorValue > pressureThreshold) {
    handleButtonPress(0);
  } else if (redSensorValue > pressureThreshold) {
    handleButtonPress(1);
  } else if (blueSensorValue > pressureThreshold) {
    handleButtonPress(2);
  } else if (purpleSensorValue > pressureThreshold) {
    handleButtonPress(3);
  } else if (whiteSensorValue > pressureThreshold) {
    handleButtonPress(4);
  }
}

// Start a new task by selecting a random button and lighting its LED
void startNewTask() {
  activeTask = random(0, 5);  // Random number between 0 and 4
  gameActive = true;

  // Announce the task (replace with sound)
  Serial.print("Task: Press the ");
  Serial.print(colors[activeTask]);
  Serial.print(" ");
  Serial.println(shapes[activeTask]);

  // Highlight the correct LED
  lightUpLED(activeTask);
}

// Handle button press
void handleButtonPress(int button) {
  if (!gameActive) return;

  if (button == activeTask) {
    // Correct button press
    playPositiveSound();
    Serial.print("Correct! You pressed the ");
    Serial.println(colors[button]);
    gameActive = false;

    // Wait briefly and start a new task
    delay(1000);
    turnOffAllLEDs();
    startNewTask();
  } else {
    // Incorrect button press
    playNegativeSound();
    Serial.print("Incorrect! You pressed the ");
    Serial.println(colors[button]);
  }
}

// Play positive sound (using the DeGraw DIY speaker)
void playPositiveSound() {
  tone(SPEAKER_PIN, 1000, 200);  // Frequency: 1000Hz, Duration: 200ms
  delay(250);
  tone(SPEAKER_PIN, 1200, 200);  // Frequency: 1200Hz, Duration: 200ms
}

// Play negative sound
void playNegativeSound() {
  tone(SPEAKER_PIN, 400, 200);  // Frequency: 400Hz, Duration: 200ms
  delay(250);
  tone(SPEAKER_PIN, 300, 200);  // Frequency: 300Hz, Duration: 200ms
}

// Turn on a specific LED based on the task
void lightUpLED(int task) {
  turnOffAllLEDs();
  switch (task) {
    case 0: digitalWrite(GREEN_LED, HIGH); break;
    case 1: digitalWrite(RED_LED, HIGH); break;
    case 2: digitalWrite(BLUE_LED, HIGH); break;
    case 3: digitalWrite(PURPLE_LED, HIGH); break;
    case 4: digitalWrite(WHITE_LED, HIGH); break;
  }
}

// Turn off all LEDs
void turnOffAllLEDs() {
  digitalWrite(GREEN_LED, LOW);
  digitalWrite(RED_LED, LOW);
  digitalWrite(BLUE_LED, LOW);
  digitalWrite(PURPLE_LED, LOW);
  digitalWrite(WHITE_LED, LOW);
}
