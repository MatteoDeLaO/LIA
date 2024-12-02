#include <IRremote.h> 

// Define the pin connected to the IR receiver 
const int IR_RECEIVE_PIN = 9; 

// Variable to store the time of the last received signal 
long lastsignalTime = 0;
  
void setup() { 
    // Initialize serial communication at 9600 baud rate
    Serial.begin(9600); 

    // Initialize the IR receiver on the defined pin with feedback enabled
    IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK); 

    // Print a message to the serial monitor indicating that the IR receiver is initialized
    Serial.println("IR Receiver Initialized. Waiting for input..."); 

    // Set pin modes for the motor control pins
    pinMode (7, OUTPUT); // Motor direction pin 1
    pinMode (5, OUTPUT); // Motor speed pin 1
    pinMode (8, OUTPUT); // Motor direction pin 2
    pinMode (3, OUTPUT); // Motor speed pin 2
    pinMode (6, OUTPUT); 
} 

void loop() { 
    // Check if an IR signal is received
    if (IrReceiver.decode()) { 
        // Print the received HEX value to the serial monitor
        Serial.print("Received HEX Value: 0x"); 
        Serial.println(IrReceiver.decodedIRData.decodedRawData, HEX); 

        // Resume the IR receiver to prepare for the next signal
        IrReceiver.resume(); 
    } 

    // Check the command received from the IR remote and perform corresponding actions
    if (IrReceiver.decodedIRData.command == 0x46) { // Forward command
        lastsignalTime = millis(); // Update the time of last signal
        forward(100); // Move forward with speed 100
    } 
    else if (IrReceiver.decodedIRData.command == 0X15) { // Backward command
        lastsignalTime = millis(); // Update the time of last signal
        backwards(100); // Move backward with speed 100
    }
    else if (IrReceiver.decodedIRData.command == 0X44) { // Left command
        lastsignalTime = millis(); // Update the time of last signal
        left(100); // Turn left with speed 100
    }
    else if (IrReceiver.decodedIRData.command == 0X43) { // Right command
        lastsignalTime = millis(); // Update the time of last signal
        right(100); // Turn right with speed 100
    }
    else if (IrReceiver.decodedIRData.command == 0X40) { // Stop command
        lastsignalTime = millis(); // Update the time of last signal
        stop(); // Stop the motors
    }
}

// Function to move the vehicle forward with a given speed
void forward(int x) {
    digitalWrite(7, 1); // Set motor direction pin 1 to forward
    analogWrite(5, x); // Set motor speed pin 1 to speed 'x'
    digitalWrite(8, 1); // Set motor direction pin 2 to forward
    analogWrite(6, x); // Set motor speed pin 2 to speed 'x'
    digitalWrite(3, 1); 
}

// Function to stop the vehicle
void stop() {
    digitalWrite(7, 0); // Set motor direction pin 1 to stop
    analogWrite(5, 0); // Set motor speed pin 1 to 0 (stop)
    digitalWrite(8, 0); // Set motor direction pin 2 to stop
    analogWrite(6, 0); // Set motor speed pin 2 to 0 (stop)
    digitalWrite(3, 1);
}

// Function to move the vehicle backward with a given speed
void backwards(int x) {
    digitalWrite(7, 0); // Set motor direction pin 1 to backward
    analogWrite(5, x); // Set motor speed pin 1 to speed 'x'
    digitalWrite(8, 0); // Set motor direction pin 2 to backward
    analogWrite(6, x); // Set motor speed pin 2 to speed 'x'
    digitalWrite(3, 1); 
}

// Function to turn the vehicle right with a given speed
void right(int x) {
    digitalWrite(7, 0); // Set motor direction pin 1 to stop
    analogWrite(5, x); // Set motor speed pin 1 to speed 'x'
    digitalWrite(8, 1); // Set motor direction pin 2 to forward (right turn)
    analogWrite(6, x); // Set motor speed pin 2 to speed 'x'
    digitalWrite(3, 1); 
}

// Function to turn the vehicle left with a given speed
void left(int x) {
    digitalWrite(7, 1); // Set motor direction pin 1 to forward (left turn)
    analogWrite(5, x); // Set motor speed pin 1 to speed 'x'
    digitalWrite(8, 0); // Set motor direction pin 2 to stop
    analogWrite(6, x); // Set motor speed pin 2 to speed 'x'
    digitalWrite(3, 1); 
}
