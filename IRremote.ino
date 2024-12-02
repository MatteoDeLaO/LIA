#include <IRremote.h> 
const int IR_RECEIVE_PIN = 9; // Define the pin connected to the IR receiver 
long lastsignalTime = 0;
  
void setup() { 
    Serial.begin(9600); 
    IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK); // Initialize the receiver 
    Serial.println("IR Receiver Initialized. Waiting for input..."); 
 pinMode (7,OUTPUT);
 pinMode (5,OUTPUT);
 pinMode (8,OUTPUT);
 pinMode (3,OUTPUT);
 pinMode (6,OUTPUT);
} 

  
void loop() { 
    // Check if a signal is received 


    if (IrReceiver.decode()) { 
        Serial.print("Received HEX Value: 0x"); 
        Serial.println(IrReceiver.decodedIRData.decodedRawData, HEX); // Print the HEX value of the received signal 
        IrReceiver.resume(); // Prepare to receive the next signal 
    } 


if (IrReceiver.decodedIRData.command == 0x46) {
lastsignalTime = millis();
forward(100);
} else if (IrReceiver.decodedIRData.command == 0X15){
  lastsignalTime = millis();
  backwards(100);
}else if (IrReceiver.decodedIRData.command == 0X44){
  lastsignalTime = millis();
  left(100);
}else if (IrReceiver.decodedIRData.command == 0X43){
  lastsignalTime = millis();
  right(100);
}else if (IrReceiver.decodedIRData.command == 0X40){
  lastsignalTime = millis();
  stop();
}
}

void forward(int x) {
digitalWrite (7,1);
analogWrite (5,x);
digitalWrite (8,1);
analogWrite (6,x);
digitalWrite (3,1);
}
void stop () {
digitalWrite (7,0);
analogWrite (5,0);
digitalWrite (8,0);
analogWrite (6,0);
digitalWrite (3,1);
}
void backwards (int x){
digitalWrite (7,0);
analogWrite (5,x);
digitalWrite (8,0);
analogWrite (6,x);
digitalWrite (3,1); 
}
void right (int x){
digitalWrite (7,0);
analogWrite (5,x);
digitalWrite (8,1);
analogWrite (6,x);
digitalWrite (3,1); 
}
void left (int x){
digitalWrite (7,1);
analogWrite (5,x);
digitalWrite (8,0);
analogWrite (6,x);
digitalWrite (3,1); 
}