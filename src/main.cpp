#include <Arduino.h>
#include <IRremote.h>
#include <pitches.h>

const int irrecvPin = 10;
int lightPins[] = {5, 6, 7, 8};
int speakerPin = 4;

int blueStatus;
int greenStatus;
int yellowStatus;
int redStatus;

int melody[] = {NOTE_C5, NOTE_D5, NOTE_E5, NOTE_F5};
int duration = 500;

// Objects
IRrecv irrecv(irrecvPin);
decode_results results;

void writeToPin(int pin, int status, int note) {
  if (status == HIGH) {
        Serial.println("Light is on, turning off.");
        digitalWrite(pin, LOW);
      }
  else if (status == LOW) {
        Serial.println("Light is off, turning on.");
        digitalWrite(pin, HIGH);
      }
  
  tone(speakerPin, melody[note], duration);
}


void translateIR(int blue, int green, int yellow, int red) {
  //Remote IR codes

  switch(results.value){
    case 0xFFA25d: 
      Serial.println("POWER"); 
      break;

    case 0xFFE21D:
      Serial.println("FUNC/STOP");
      break;

    case 0xFF629D:
      Serial.println("VOL+");
      break;

    case 0xFF22DD:
      Serial.println("FAST BACK");
      break;

    case 0xFF02FD:
      Serial.println("PAUSE");
      break;

    case 0xFFC23D: 
      Serial.println("FAST FORWARD");   
      break;

    case 0xFFE01F: 
      Serial.println("DOWN");    
      break;

    case 0xFFA857: 
      Serial.println("VOL-");    
      break;

    case 0xFF906F: 
      Serial.println("UP");    
      break;

    case 0xFF9867: 
      Serial.println("EQ");    
      break;

    case 0xFFB04F: 
      Serial.println("ST/REPT");    
      break;

    case 0xFF6897: 
      Serial.println("0");    
      break;

    case 0xFF30CF: 
      Serial.println("1- Blue Toggle");
      writeToPin(lightPins[0], blue, 0);
      break;

    case 0xFF18E7: 
      Serial.println("2- Green Toggle");
      writeToPin(lightPins[1], green, 1);
      break;

    case 0xFF7A85: 
      Serial.println("3- Yellow Toggle");
      writeToPin(lightPins[2], yellow, 2);
      break;

    case 0xFF10EF: 
      Serial.println("4- Red Toggle");
      writeToPin(lightPins[3], red, 3);    
      break;

    case 0xFF38C7: 
      Serial.println("5");    
      break;

    case 0xFF5AA5: 
      Serial.println("6");    
      break;

    case 0xFF42BD: 
      Serial.println("7");    
      break;

    case 0xFF4AB5: 
      Serial.println("8");    
      break;

    case 0xFF52AD: 
      Serial.println("9");    
      break;

    case 0xFFFFFFFF: 
      Serial.println("REPEAT");
      break;

    default:
      Serial.println("Unknown input");  
  }

  delay(500);

}


void setup() {
  Serial.begin(9600);
  Serial.println("IR Reciever Button Decode");
  irrecv.enableIRIn(); // Starts the reciever
  
  // Changes each pin's mode to output.
  pinMode(lightPins[0], OUTPUT);
  pinMode(lightPins[1], OUTPUT);
  pinMode(lightPins[2], OUTPUT);
  pinMode(lightPins[3], OUTPUT);

}

void loop() {
  blueStatus = digitalRead(lightPins[0]);
  greenStatus = digitalRead(lightPins[1]);
  yellowStatus= digitalRead(lightPins[2]);
  redStatus = digitalRead(lightPins[3]);

  if (irrecv.decode(&results)) {
    translateIR(blueStatus, greenStatus, yellowStatus, redStatus);
    irrecv.resume();
  }
}