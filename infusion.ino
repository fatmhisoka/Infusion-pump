#include <SoftwareSerial.h>
#include <LiquidCrystal.h>

// Define pin numbers for LCD
const int rs = 12, en = 11, d4 = 7, d5 = 6, d6 = 5, d7 = 4;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// Define pin number for relay
const int IN2 = 8;

// Variables for flow sensor
volatile int flow_frequency; // Measures flow sensor pulses
unsigned int l_hour; // Calculated litres/hour
const unsigned char flowsensor = 9; // Sensor Input
unsigned long currentTime;
unsigned long cloopTime;

// Interrupt function for flow sensor
void flow() {
   flow_frequency++;
}

void setup() {
  Serial.begin(9600);
  // Initialize LCD
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Water Flow Meter");
  lcd.setCursor(0, 1);
  lcd.print("****************");
  
  // Initialize relay pin
  pinMode(IN2, OUTPUT);
  
  // Initialize flow sensor
  pinMode(flowsensor, INPUT);
  digitalWrite(flowsensor, HIGH); // Optional Internal Pull-Up
  attachInterrupt(0, flow, RISING); // Setup Interrupt
  sei(); // Enable interrupts
  currentTime = millis();
  cloopTime = currentTime;
}

void loop() {
  // Calculate flow rate
  currentTime = millis();
  l_hour = (flow_frequency * 60 / 7.5); // (Pulse frequency x 60 min) / 7.5Q = flowrate in L/hour
  flow_frequency = 0; // Reset Counter
  // Print flow rate to serial monitor
  Serial.print(l_hour, DEC);
  Serial.println(" L/hour");
  // Display flow rate on LCD
  lcd.print(l_hour, DEC);
  lcd.println(" L/hour"); 
  
  // Turn on the pump
  digitalWrite(IN2, HIGH);
  delay(5000); // Run the pump for 5 seconds
  
  // Turn off the pump
  digitalWrite(IN2, LOW);
  delay(10000); // Wait for 10 seconds before starting the next cycle
}
