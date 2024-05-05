#include <SoftwareSerial.h>
#include <LiquidCrystal.h>

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


//Variable of relay
int IN2=8;

#define LED_PIN 13
int buzzer = 10;


const int trigPin = 7;
const int echoPin = 6;

float duration, distance,  actual_d, volume;

unsigned char flowsensor = 9; // Sensor Input



void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(buzzer,OUTPUT);

  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Water Flow Meter");
  delay(2000);

  pinMode(IN2,OUTPUT);      // Relay for pump
 
  pinMode(flowsensor, INPUT);

}
void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = (duration*.0343)/2;
  actual_d = 14 - distance ;
  volume = (22/7) * 16 * actual_d ;
  Serial.print("Distance: ");
  Serial.println(distance);
  Serial.print("volume: ");
  Serial.println(volume);



  uint32_t pulse = pulseIn(flowsensor,HIGH);

 
  //flowmeter 

  float Hz = 1/(2*pulse*pow(10,-6));
  float flow = 0.0137*(float)Hz + 8*pow(10,-15);
  lcd.setCursor(0,0); 
  lcd.print(flow); // Print litres/hour
  lcd.println(" L/hour"); 

  Serial.print(flow); // Print litres/hour
  Serial.println(" L/hour");
  delay(200);

      
   
  if (distance > 7){
    digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
  }
  digitalWrite(IN2, HIGH);
  if (distance > 9){
    tone(buzzer,13500);

    digitalWrite(IN2, LOW);
    lcd.setCursor(0,1);
    lcd.print("Volume"); // Print litres/hour
    lcd.println(volume); 


    delay(2000);
  }

  
   
}
