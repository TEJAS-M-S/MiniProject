#include <LiquidCrystal.h>
#include <Servo.h>
#include <Wire.h> // Library for I2C communication
#include <LiquidCrystal_I2C.h> // Library for LCD
Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards
int irsensor = 2;
int pos = 0;    // variable to store the servo position
int value = A0;
#define trigPin 4
#define echoPin 3
#define trigPin1 6
#define echoPin1 7
#define buzz 5
// Define pins for LEDs
#define RED_LED 10
#define GREEN_LED 11
#define BLUE_LED 12
const int buzzerPin = 5; // Buzzer connected to digital pin 5
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 4);
void setup() {
  // Set pin modes for LEDs and Buzzer
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);
  // Initialize the ultrasonic sensor
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(buzz, OUTPUT);
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("TRASH IN");
  lcd.setCursor(0, 1);
  lcd.print("CASH OUT");
  delay(3000);
  lcd.clear();
  Serial.begin(9600); // Initialize serial communication for debugging
  lcd.setCursor(0, 0);
  lcd.print("Distance:");
  myservo.attach(9);  // attaches the servo on pin 9 to the servo objec
  myservo.write(100);
  delay(1000);
  pinMode (irsensor, INPUT);
  pinMode (value, INPUT);
}

void loop() {
  value = analogRead(A0);
  if (digitalRead(2) == LOW && value > 950)
  {
    myservo.write(30);
    delay(1000);
    myservo.write(100);
    delay(1000);
    lcd.setCursor(0, 0);
    lcd.print("DRY Waste ");
    lcd.setCursor(3, 1);
    lcd.print("Detected");
    delay (1000);
    // Generate a tone at 440 Hz (A4 note) for 1 second
    tone(buzzerPin, 440, 1000);
    delay(1000); // Wait for 1 second
    digitalWrite(RED_LED, HIGH);
    digitalWrite(GREEN_LED, LOW);

    // Measure distance
  long duration, distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 2) / 29.1; // Convert duration to distance in cm

  // Display the distance on the LCD
  lcd.setCursor(0, 1);
  lcd.print("                "); // Clear previous value
  lcd.setCursor(0, 1);
  lcd.print(distance);
  lcd.print(" cm");

  // Print distance to Serial Monitor (optional)
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Small delay before next measurement
  delay(500); 

  }
  else
  {



  }
  lcd.clear();
  value = analogRead(A0);
  if (value < 900) {
    Serial.println(value);
    myservo.write(170);
    delay(1000);
    myservo.write(100);
    delay(1000);
    lcd.setCursor(0, 0);
    lcd.print("WET Waste ");
    lcd.setCursor(3, 1);
    lcd.print("Detected");
    delay (1000);
    // Generate a tone at 880 Hz (A5 note) for 1 second
    tone(buzzerPin, 880, 1000);
    delay(1000); // Wait for 1 second
    digitalWrite(RED_LED, LOW);
    digitalWrite(GREEN_LED, HIGH);

     // Measure distance
  long duration, distance;
  digitalWrite(trigPin1, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);

  duration = pulseIn(echoPin1, HIGH);
  distance = (duration / 2) / 29.1; // Convert duration to distance in cm

  // Display the distance on the LCD
  lcd.setCursor(0, 1);
  lcd.print("                "); // Clear previous value
  lcd.setCursor(0, 1);
  lcd.print(distance);
  lcd.print(" cm");

  // Print distance to Serial Monitor (optional)
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Small delay before next measurement
  delay(500); 

  }
  else
  {



  }
  lcd.clear();
  long duration, inches, cm;

  // The PING))) is triggered by a HIGH pulse of 2 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(trigPin, LOW);
  

  // Take reading on echo pin
  duration = pulseIn(echoPin, HIGH);

  // convert the time into a distance
  inches = microsecondsToInches(duration);
  cm = microsecondsToCentimeters(duration);

  Serial.print(inches);
  Serial.print("in, ");
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();

  if (inches <3) {
    digitalWrite(buzz, HIGH);
    delay(500);
    lcd.setCursor(0,0);
    lcd.print("TRASH BIN ");
    lcd.setCursor(5,1);
    lcd.print("FULL");
    digitalWrite(RED_LED, LOW);
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(BLUE_LED, HIGH);
    // Generate a tone at 523 Hz (C5 note) for 1 second
    tone(buzzerPin, 523, 1000);
    delay(1000); // Wait for 1 second

  } else {

    Serial.println("no hand");
    digitalWrite(buzz, LOW);
    delay(500);
    digitalWrite(RED_LED, LOW);
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(BLUE_LED, LOW);
  }

  delay(100);
}

long microsecondsToInches(long microseconds)
{

  return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds)
{
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds / 29 / 2;
}
