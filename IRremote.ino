#include <IRremote.h>  // Include the IRremote library for receiving IR signals

// Define the pin connected to the IR receiver
const int IR_RECEIVE_PIN = 9; 

// Variable to store the last time a signal was received
long lastsignalTime = 0;

// Setup function to initialize the IR receiver and motor control pins
void setup() { 
    Serial.begin(9600);  // Initialize the serial communication at a baud rate of 9600
    IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);  // Initialize the IR receiver with feedback LED enabled
    Serial.println("IR Receiver Initialized. Waiting for input...");  // Print a message to the Serial Monitor
  
    // Set motor control pins as output
    pinMode(7, OUTPUT);  // Left motor forward pin
    pinMode(5, OUTPUT);  // Left motor speed pin
    pinMode(8, OUTPUT);  // Right motor forward pin
    pinMode(3, OUTPUT);  // Enable pin for motor driver
    pinMode(6, OUTPUT);  // Right motor speed pin
} 

// Loop function that continuously checks for IR signals and responds accordingly
void loop() { 
    // Check if a signal has been received by the IR receiver
    if (IrReceiver.decode()) { 
        // Print the received IR signal's HEX value to the Serial Monitor
        Serial.print("Received HEX Value: 0x"); 
        Serial.println(IrReceiver.decodedIRData.decodedRawData, HEX); 

        // Prepare to receive the next signal
        IrReceiver.resume(); 
    }

    // Check which command was received and perform corresponding action
    if (IrReceiver.decodedIRData.command == 0x46) {  // Forward command
        lastsignalTime = millis();  // Update the time of the last signal
        forward(100);  // Call the forward function with speed 100
    } 
    else if (IrReceiver.decodedIRData.command == 0X15) {  // Backward command
        lastsignalTime = millis();  // Update the time of the last signal
        backwards(100);  // Call the backwards function with speed 100
    }
    else if (IrReceiver.decodedIRData.command == 0X44) {  // Left command
        lastsignalTime = millis();  // Update the time of the last signal
        left(100);  // Call the left function with speed 100
    }
    else if (IrReceiver.decodedIRData.command == 0X43) {  // Right command
        lastsignalTime = millis();  // Update the time of the last signal
        right(100);  // Call the right function with speed 100
    }
    else if (IrReceiver.decodedIRData.command == 0X40) {  // Stop command
        lastsignalTime = millis();  // Update the time of the last signal
        stop();  // Call the stop function to halt the motors
    }
}

// Function to move the robot forward with a given speed
void forward(int x) {
    digitalWrite(7, 1);  // Set the left motor forward pin HIGH
    analogWrite(5, x);  // Set the left motor speed using PWM
    digitalWrite(8, 1);  // Set the right motor forward pin HIGH
    analogWrite(6, x);  // Set the right motor speed using PWM
    digitalWrite(3, 1);  // Enable the motor driver
}

// Function to stop the robot's movement
void stop() {
    digitalWrite(7, 0);  // Set the left motor forward pin LOW (stop movement)
    analogWrite(5, 0);  // Set the left motor speed to 0 (stop motor)
    digitalWrite(8, 0);  // Set the right motor forward pin LOW (stop movement)
    analogWrite(6, 0);  // Set the right motor speed to 0 (stop motor)
    digitalWrite(3, 1);  // Keep the motor driver enabled
}

// Function to move the robot backward with a given speed
void backwards(int x) {
    digitalWrite(7, 0);  // Set the left motor forward pin LOW (move backward)
    analogWrite(5, x);  // Set the left motor speed using PWM
    digitalWrite(8, 0);  // Set the right motor forward pin LOW (move backward)
    analogWrite(6, x);  // Set the right motor speed using PWM
    digitalWrite(3, 1);  // Enable the motor driver
}

// Function to turn the robot to the right with a given speed
void right(int x) {
    digitalWrite(7, 0);  // Set the left motor forward pin LOW (stop left motor)
    analogWrite(5, x);  // Set the left motor speed to 0 (slow or stop motor)
    digitalWrite(8, 1);  // Set the right motor forward pin HIGH (move right motor)
    analogWrite(6, x);  // Set the right motor speed using PWM
    digitalWrite(3, 1);  // Enable the motor driver
}

// Function to turn the robot to the left with a given speed
void left(int x) {
    digitalWrite(7, 1);  // Set the left motor forward pin HIGH (move left motor)
    analogWrite(5, x);  // Set the left motor speed using PWM
    digitalWrite(8, 0);  // Set the right motor forward pin LOW (stop right motor)
    analogWrite(6, x);  // Set the right motor speed to 0 (slow or stop motor)
    digitalWrite(3, 1);  // Enable the motor driver
}
