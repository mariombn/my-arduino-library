#include <Arduino.h>
#include <Wire.h>
#include <MicroLCD.h>
#include <Servo.h>

#define pinMotorDir   5
#define pinMotorEsq   6
#define pinMotorCab   7
#define pinMotorGarra 4
#define pinBuzzer    13

#define servoParado      90
#define servoEsqFrente    0 
#define servoDirFrente  180 
#define servoEsqTras    180 
#define servoDirTras      0     
#define servoVirando     15     

Servo motorDir;
Servo motorEsq;
Servo motorCab;
Servo motorGarra;

//LCD_SH1106 lcd; /* para módulo controlado pelo CI SH1106 OLED */ 
LCD_SSD1306 lcd;  /* para módulo contralado pelo CI SSD1306 OLED */

char comando;

void setup() {
  Serial.begin(9600);
  lcd.begin();

  motorCab.attach(pinMotorCab);
  motorGarra.attach(pinMotorGarra);
  
  motorCab.write(180);
  delay(500);
  motorCab.write(0);
  delay(500);
  motorCab.write(90);

  bipYes();
  delay(200);
  bipNo();
  delay(200);

  //motorGarra.write(180);
  //delay(500);
  //motorGarra.write(0);
  //delay(500);
  //motorGarra.write(90);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.setFontSize(FONT_SIZE_SMALL);
  lcd.printLong(12345678);
  delay(1000);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.setFontSize(FONT_SIZE_MEDIUM);
  lcd.printLong(12345678);
  delay(1000);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.setFontSize(FONT_SIZE_LARGE);
  lcd.printLong(12345678);
  delay(1000);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.setFontSize(FONT_SIZE_XLARGE);
  lcd.printLong(12345678);
  delay(1000);
}

void loop() {

  comando = 'Z'; 
  if (Serial.available()) {
    comando = Serial.read();
  }

  switch (comando) {
    case 'F': {
        moveFront();
        break;
      }

    case 'B': {
        moveBack();
        break;
      }

    case 'L': {
        moveLeft();
        break;
      }
      
    case 'R': {
        moveRight();
        break;
      }
      
    case 'G': {
        moveFrontLeft();
        break;
      }
      
    case 'I': {
        moveFrontRight();
        break;
      }
      
    case 'H': {
        moveBackLeft();
        break;
      }
      
    case 'J': {
        moveBackRight();
        break;
      }
      
    case 'S': {
        moveStop();      
        break;
      }
    case 'Z': {
      //moveStop();      
      break;
    }

    case 'q': {
        //Posição da Cabeça
        motorCab.write(0); 
        break;
      }
    case 'W': {
      bipYes();
      break;
    }
    case 'w': {
      bipYes();
      break;
    }
    case 'U': {
      bipNo();
      break;
    }
    case 'u': {
      bipNo();
      break;
    }
    case 'V': {
      bipWaring();
      break;
    }
    case 'v': {
      bipWaring();
      break;
    }
    default: {
      //Posição da Cabeça 
      moveHead(comando);
      break;
    }
  }
}

void moveHead(int position)
{
  if ((position >= 48) && (position <= 57)) {
     motorCab.write((11-(position - 47))*18); 
  }
}

void bipYes()
{
  tone(pinBuzzer, 700, 100);
  delay(200);
  tone(pinBuzzer, 1000, 100);
  delay(200);
  tone(pinBuzzer, 1200, 100);
  delay(200);
}

void bipNo()
{
  tone(pinBuzzer, 1200, 100);
  delay(200);
  tone(pinBuzzer, 1000, 100);
  delay(200);
  tone(pinBuzzer, 700, 100);
  delay(200);
}

void bipWaring()
{
  tone(pinBuzzer, 700, 100);
  delay(200);
  tone(pinBuzzer, 1000, 100);
  delay(200);
  tone(pinBuzzer, 700, 100);
  delay(200);
  tone(pinBuzzer, 1000, 100);
  delay(200);
  tone(pinBuzzer, 700, 100);
  delay(200);
  tone(pinBuzzer, 1000, 100);
  delay(200);
}

void moveStop()
{
  motorDir.write(servoParado);
  motorEsq.write(servoParado);
  motorDir.detach();
  motorEsq.detach();
}

void moveFront()
{
  motorDir.attach(pinMotorDir);
  motorEsq.attach(pinMotorEsq);
  motorDir.write(servoDirFrente);
  motorEsq.write(servoEsqFrente);
}

void moveBack()
{
  motorDir.attach(pinMotorDir);
  motorEsq.attach(pinMotorEsq);
  motorDir.write(servoDirTras);
  motorEsq.write(servoEsqTras);
}

void moveLeft()
{
  motorDir.attach(pinMotorDir);
  motorEsq.attach(pinMotorEsq);
  motorDir.write(servoDirTras);
  motorEsq.write(servoEsqFrente);
}

void moveRight()
{
  motorDir.attach(pinMotorDir);
  motorEsq.attach(pinMotorEsq);
  motorDir.write(servoDirFrente);
  motorEsq.write(servoEsqTras);
}

void moveFrontLeft()
{
  motorDir.attach(pinMotorDir);
  motorEsq.attach(pinMotorEsq);
  motorDir.write(servoParado + servoVirando);
  motorEsq.write(servoEsqFrente);
}

void moveFrontRight()
{
  motorDir.attach(pinMotorDir);
  motorEsq.attach(pinMotorEsq);
  motorDir.write(servoDirFrente);
  motorEsq.write(servoParado - servoVirando);
}

void moveBackLeft()
{
  motorDir.attach(pinMotorDir);
  motorEsq.attach(pinMotorEsq);
  motorDir.write(servoParado - servoVirando);
  motorEsq.write(servoEsqTras);
}

void moveBackRight()
{
  motorDir.attach(pinMotorDir);
  motorEsq.attach(pinMotorEsq);
  motorDir.write(servoDirTras );
  motorEsq.write(servoParado + servoVirando);
}