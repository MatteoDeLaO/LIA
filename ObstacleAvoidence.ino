#include <NewPing.h>        // Ultrasonic sensor function library. You must install this library for ultrasonic distance measurement.
#include <Servo.h>          // Servo motor library. Standard library for controlling servo motors.

int leftMotorPin = 7;           // Pin for the left motor control
int leftMotorSpeed = 5;         // Pin for controlling the left motor speed
int rightMotorPin = 8;          // Pin for the right motor control
int rightMotorSpeed = 6;        // Pin for controlling the right motor speed
int enablePin = 3;              // Pin used for enabling motor control

// Sensor pins for the ultrasonic sensor
#define trig_pin 13            // Trigger pin for the ultrasonic sensor
#define echo_pin 12            // Echo pin for the ultrasonic sensor
#define maximum_distance 200   // Maximum measurable distance in cm

boolean goesForward = false;    // Boolean flag to track whether the robot is moving forward or not
int distance = 100;             // Variable to store the current distance reading from the ultrasonic sensor

NewPing sonar(trig_pin, echo_pin, maximum_distance); // Create a NewPing object for ultrasonic sensor
Servo servo_motor;             // Create a Servo object for controlling the servo motor

// Setup function to initialize pins and configurations
void setup(){
  // Set motor control pins to output mode
  pinMode(7, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(6, OUTPUT);
  
  // Attach the servo to pin 10 and set its initial position
  servo_motor.attach(10); // Attach the servo to pin 10
  servo_motor.write(115);  // Set the servo to initial position
  delay(2000);             // Wait for the servo to settle
  
  // Scan the environment multiple times to initialize distance
  distance = scan(); delay(100);
  distance = scan(); delay(100);
  distance = scan(); delay(100);
  distance = scan(); delay(100);
}

// Main loop that repeatedly checks the distance and controls movement
void loop(){
  int distanceRight = 0;  // Variable to store distance to the right
  int distanceLeft = 0;   // Variable to store distance to the left
  delay(50);              // Small delay for stability

  // If an obstacle is detected within 20cm
  if (distance <= 20){
    Stop();               // Stop the robot
    delay(300);           // Wait for a moment
    Backward();           // Move backward to avoid the obstacle
    delay(400);           // Wait for a moment
    Stop();               // Stop again

    // Scan the right and left directions to find the best path
    distanceRight = lookRight(); 
    delay(300); 
    distanceLeft = lookLeft(); 
    delay(300); 

    // Choose the direction to avoid the obstacle
    if (distance >= distanceLeft){
      Right();             // Turn right if the right path is clearer
      Stop();              // Stop after turning
    }
    else{
      Left();              // Turn left if the left path is clearer
      Stop();              // Stop after turning
    }
  }
  else{
    Forward();            // Continue moving forward if no obstacle is detected
  }

  distance = scan();     // Re-scan the distance in the loop for continuous feedback
}

// Function to look right by moving the servo to 0 degrees
int lookRight(){  
  servo_motor.write(0);   // Move the servo to the right (0 degrees)
  delay(500);              // Wait for servo to position
  int distance = scan();  // Scan distance at right
  delay(100);              // Small delay after scanning
  servo_motor.write(90);  // Reset the servo to 90 degrees (center)
  return distance;         // Return the distance measured
}

// Function to look left by moving the servo to 180 degrees
int lookLeft(){
  servo_motor.write(180);  // Move the servo to the left (180 degrees)
  delay(500);               // Wait for servo to position
  int distance = scan();   // Scan distance at left
  delay(100);               // Small delay after scanning
  servo_motor.write(90);   // Reset the servo to 90 degrees (center)
  return distance;          // Return the distance measured
}

// Function to scan distance using the ultrasonic sensor
int scan(){
  delay(70);                // Small delay for sensor stabilization
  int cm = sonar.ping_cm(); // Measure distance in centimeters
  if (cm == 0){             // If no reading (0 cm), assume it's 250 cm (out of range)
    cm = 250;
  }
  return cm;                // Return the measured distance
}

// Function to stop the robot
void Stop(){
  digitalWrite(7, 0);    // Stop the left motor
  analogWrite(5, 0);     // Set the left motor speed to 0
  digitalWrite(8, 0);    // Stop the right motor
  analogWrite(6, 0);     // Set the right motor speed to 0
  digitalWrite(3, 1);    // Enable the motor driver
}

// Function to move the robot forward
void Forward(){
  if(!goesForward){
    goesForward = true;   // Set goesForward to true when the robot moves forward
    
    digitalWrite(7, 1);   // Activate left motor
    analogWrite(5, 50);   // Set left motor speed
    digitalWrite(8, 1);   // Activate right motor
    analogWrite(6, 50);   // Set right motor speed
    digitalWrite(3, 1);   // Enable the motor driver
  }
}

// Function to move the robot backward
void Backward(){
  goesForward = false;   // Set goesForward to false when the robot moves backward

  digitalWrite(7, 0);    // Deactivate left motor
  analogWrite(5, 50);    // Set left motor speed to move backward
  digitalWrite(8, 0);    // Deactivate right motor
  analogWrite(6, 50);    // Set right motor speed to move backward
  digitalWrite(3, 1);    // Enable the motor driver
}

// Function to make the robot turn right
void Right(){
  digitalWrite(7, 0);    // Deactivate left motor
  analogWrite(5, 50);    // Set left motor speed to slow
  digitalWrite(8, 1);    // Activate right motor
  analogWrite(6, 50);    // Set right motor speed to slow
  digitalWrite(3, 1);    // Enable the motor driver
  
  delay(500);            // Wait for the robot to turn
  
  digitalWrite(7, 0);    // Deactivate left motor
  analogWrite(5, 50);    // Set left motor speed to slow
  digitalWrite(8, 1);    // Activate right motor
  analogWrite(6, 50);    // Set right motor speed to slow
  digitalWrite(3, 1);    // Enable the motor driver
}

// Function to make the robot turn left
void Left(){
  digitalWrite(7, 1);    // Activate left motor
  analogWrite(5, 50);    // Set left motor speed to slow
  digitalWrite(8, 0);    // Deactivate right motor
  analogWrite(6, 50);    // Set right motor speed to slow
  digitalWrite(3, 1);    // Enable the motor driver
  
  delay(500);            // Wait for the robot to turn
  
  digitalWrite(7, 1);    // Activate left motor
  analogWrite(5, 50);    // Set left motor speed to slow
  digitalWrite(8, 0);    // Deactivate right motor
  analogWrite(6, 50);    // Set right motor speed to slow
  digitalWrite(3, 1);    // Enable the motor driver
}
