/*
      RoboCore - Motor Driver 2x2A example
                    (01/07/2015)

  Written by François.
  
  Example of how to use the Motor Driver 2x2A.
  Open a Serial Monitor and enter the comands:
    - u : for PWM 0 to 255
    - d : for PWM 255 to 0
    - o : for ON
    - f : for OFF
    - 1 : for Direction 1
    - 2 : for Direction 2

*/

const int motorA = 5;
const int motorB = 6;
const int dirA = 7;
const int dirB = 8;

byte b;

// ------------------------------------------------

void setup(){
  Serial.begin(9600);
  Serial.println("Start");
  
  pinMode(motorA, OUTPUT);
  pinMode(motorB, OUTPUT);
  pinMode(dirA, OUTPUT);
  pinMode(dirB, OUTPUT);
}

// ------------------------------------------------

void loop(){
  
  if(Serial.available()){
    b = Serial.read();
    
    switch(b){
      // PWM Up
      case 'u':
        for(int i=0 ; i <= 255 ; i++){
          analogWrite(motorA, i);
          analogWrite(motorB, i);
          delay(20);
        }
        Serial.println("\tok");
        break;
      
      // PWM Down
      case 'd':
        for(int i=255 ; i >= 0 ; i--){
          analogWrite(motorA, i);
          analogWrite(motorB, i);
          delay(20);
        }
        Serial.println("\tok");
        break;
      
      
      // On
      case 'o':
        digitalWrite(motorA, HIGH);
        digitalWrite(motorB, HIGH);
        Serial.println("ON");
        break;
      
      // Off
      case 'f':
        digitalWrite(motorA, LOW);
        digitalWrite(motorB, LOW);
        Serial.println("OFF");
        break;
      
      
      // Dir-1
      case '1':
        digitalWrite(dirA, HIGH);
        digitalWrite(dirB, HIGH);
        Serial.println("\tdir-1");
        break;
      
      // Dir-2
      case '2':
        digitalWrite(dirA, LOW);
        digitalWrite(dirB, LOW);
        Serial.println("\tdir-2");
        break;
      
      
      // PWM Max
      case '>':
          analogWrite(motorA, 240);
          analogWrite(motorB, 240);
        Serial.println("\tMax");
        break;
      
      // PWM Min
      case '<':
          analogWrite(motorA, 20);
          analogWrite(motorB, 20);
        Serial.println("\tMin");
        break;
      
      default:
        Serial.println("nothing");
        break;
    }
  }
  
}

// ------------------------------------------------

