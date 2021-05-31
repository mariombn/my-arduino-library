#include <LiquidCrystal.h>
  
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
int incomingByte = 0;
boolean isSerialRead = false;
String serialBuffer;

void setup(){
  Serial.begin(9600);
  lcd.begin(16,2); 
  lcd.setCursor(0,0);
  lcd.print("APERTOU A TECLA");
  lcd.setCursor(0,1);
  lcd.print("   CARREGANDO   ");
}  
  
void loop(){  
  lcd.setCursor(0,1);
  if (analogRead(0) < 80) {
    lcd.print ("    DIREITA    ");
    Serial.println("Direita");
  } else if (analogRead(0) < 200) {
    lcd.print ("      CIMA     ");
    Serial.println("Cima");
  } else if (analogRead(0) < 400){
    lcd.print ("     BAIXO     ");
    Serial.println("Baixo");
  } else if (analogRead(0) < 600){
    lcd.print ("    ESQUERDA   ");
    Serial.println("Esquerda");
  } else if (analogRead(0) < 800){
    lcd.print ("     SELECT    ");
    Serial.println("Select");
  } else {
    lcd.print ("               ");
  }

  isSerialRead = false;
  while (Serial.available() > 0) {
    isSerialRead = true;
    char incomingByte = Serial.read();
    serialBuffer = serialBuffer + String(incomingByte);
  }

  if (!isSerialRead) {
    lcd.setCursor(0,1);
    lcd.print (serialBuffer);
  }
  
}
