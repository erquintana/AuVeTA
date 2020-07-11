#include <Arduino.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(0, 1); // RX, TX

void setup() {

  pinMode(8,OUTPUT);
  pinMode(2,OUTPUT);
  pinMode(12,OUTPUT);

  Serial.begin(9600);
  mySerial.begin(38400);
}

void loop() {
 if(mySerial.available()){
  int c = mySerial.read();
  if(c=='0'){
    digitalWrite(8,HIGH);
    delay(1000);
    digitalWrite(8,LOW);
    }
  if(c=='1'){
    digitalWrite(2,HIGH);
    delay(1000);
    digitalWrite(2,LOW);
    }
  if(c=='2'){
    digitalWrite(12,HIGH);
    delay(1000);
    digitalWrite(12,LOW);
    }

  }
}
