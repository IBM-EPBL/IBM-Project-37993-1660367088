#include<Servo.h>
#include <LiquidCrystal.h>

const int temperaturePin = 0;
const int buzzer = 12; 
int gasSensorPin=A1;
int sensorval;

Servo servo1,servo2;
int servo1Pin=11;
int servo2Pin=10;

int node1_led=9;
int node2_led=8;

LiquidCrystal lcd(7, 6, 2, 3, 4, 5);

int buttonstate = 0;
const int resetbtn = 13;
int repeat = 0;

void setup()
{
  pinMode(buzzer, OUTPUT);
  
  servo1.attach(servo1Pin);
  servo2.attach(servo2Pin);
  servo1.write(90);
  servo2.write(90);
  
  pinMode(node1_led,OUTPUT);
  pinMode(node2_led,OUTPUT);
  pinMode(resetbtn,INPUT);
  
  lcd.begin(16,2);
}

void loop()
{
 	float voltage, degreesC;
  	voltage = getVoltage(temperaturePin);
	degreesC = (voltage - 0.5) * 100.0;
	
  	sensorval=analogRead(gasSensorPin);
 	buttonstate = digitalRead(resetbtn);
  
  if(buttonstate == HIGH) {
  	repeat = 0;
  }  
  	
  	if(degreesC>30 || sensorval>800 || repeat == 1)
  	{
      repeat = 1;
      
      tone(buzzer, 500, 500);
      
      servo1.write(0);
      servo2.write(0);
      
      lcd.clear();
      lcd.setCursor(0,0);
  	  lcd.print("Alart Fire Fire!!");
      lcd.setCursor(0,1);
      lcd.print("Quick RESQUE");
      
      digitalWrite(node1_led,HIGH);
      digitalWrite(node2_led,LOW);
      
      delay(1000);
      tone(buzzer,600,800);
      digitalWrite(node1_led,LOW);
      delay(2000);
  	}
  	else{
      servo1.write(90);
      servo2.write(90);
      delay(1000);
      
      digitalWrite(node2_led,HIGH);
      digitalWrite(node1_led,LOW);
      
      lcd.clear();
  	  lcd.setCursor(0,0);
  	  lcd.print("Safe Mode");
      lcd.setCursor(6,0);
      lcd.print(degreesC);
      lcd.print("C");
      lcd.setCursor(0,1);
      lcd.print("Gas Limit.:");
      lcd.print(sensorval);
  }
  
}
float getVoltage(int pin)
{
  
  return(analogRead(pin)*0.004882814);
}
