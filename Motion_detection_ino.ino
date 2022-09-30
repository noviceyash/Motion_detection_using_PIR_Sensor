
#include<SoftwareSerial.h>
SoftwareSerial gsm(10,11); //TX/RX  
int buzzer = 3;                // the pin that the LED is atteched to

int led = 13;                // the pin that the LED is atteched to
int sensor = 2;              // the pin that the sensor is atteched to
int state = LOW;             // by default, no motion detected
int val = 0;                 // variable to store the sensor status (value)

void setup() {
   
// Open serial communications and wait for port to open:
Serial.begin(9600);

Serial.println("Calling through GSM Modem");

// set the data rate for the SoftwareSerial port
gsm.begin(9600);
delay(2000);
pinMode(sensor,INPUT);
pinMode(led,OUTPUT);
pinMode(buzzer,OUTPUT);


}

void loop() {
  val = digitalRead(sensor);   // read sensor value
  if (val == HIGH) {           // check if the sensor is HIGH
    digitalWrite(led, HIGH);   // turn LED ON
    delay(100);                // delay 100 milliseconds 
    
    if (state == LOW) {
      Serial.println("Motion detected!"); 
      digitalWrite(buzzer, HIGH);   // turn LED ON
          delay(1000);                // delay 100 milliseconds 

      digitalWrite(buzzer, LOW);   // turn LED ON

      sendsms();
      state = HIGH;       // update variable state to HIGH
    }
  } 
  else {
      digitalWrite(led, LOW); // turn LED OFF
      delay(200);             // delay 200 milliseconds 
      
      if (state == HIGH){
        Serial.println("Motion stopped!");
        //digitalWrite(buzzer, LOW);   // turn LED ON

        state = LOW;       // update variable state to LOW
    }
  }
  // put your main code here, to run repeatedly:
// print response over serial port
//if (gsm.available())
//Serial.write(gsm.read());
}

void sendsms(){
  Serial.println("Init");
  // put your setup code here, to run once:
   gsm.print("\r");
  delay(1000);                  
  gsm.println("AT+CMGF=1");    
  delay(1000);
  /*Replace XXXXXXXXXX to 10 digit mobile number &  ZZ to 2 digit country code*/
  
  gsm.print("AT+CMGS=\"+919137591273\"\r");    
  delay(1000);
  //The text of the message to be sent.
  gsm.print("Motion Detected\nSecurity Alert....!!!!! some one entered in the house");   
  delay(1000);
  gsm.println((char)26);
  delay(1000);
  Serial.println("Sent");

}

