#include <LiquidCrystal_I2C.h>

// Initializing the buzzer pins
int active = 2;
int passive = 4;

// Initializing the buzzer tone rhythm frequency
int high_freq = 2000;
int low_freq = 1000;

// Initializing the alarm blink light pins
int red_led = 10;
int yellow_led = 12;
int green_led = 13;
int red2_led = 6;
int green2_led = 5;

// Initializing the temperature sensor pin and temperature variable
float temp_celsius;
int temp_sensor_pin = A0;

// Initializing the two flame sensors
int flame_sensor1_pin = A1;
int flame_detected1;
int flame_sensor2_pin = A2;
int flame_detected2;

// Initializing the water pump
int pump_pin = 8;

// Initializing the LCD display
LiquidCrystal_I2C lcd(0x27,16,2); 

// Initializing the state variables
bool fire_detected = false;
bool fire_extinguished = false;
bool fire_fighting = false;

// Constants
const int ANALOG_MAX_VALUE = 1023;
const float AREF_VOLTAGE = 3.3;
const float VOLTAGE_THRESHOLD = 0.5;
const float TEMP_WARNING_THRESHOLD = 50.0; // in Celsius
const float TEMP_CRITICAL_THRESHOLD = 100.0; // in Celsius
const int SENSOR_READ_INTERVAL = 1000; // in milliseconds
const int LCD_UPDATE_INTERVAL = 5000; // in milliseconds

void setup() {
  // Setting up the sensors and actuators
  pinMode(active, OUTPUT);
  pinMode(passive, OUTPUT);
  pinMode(flame_sensor1_pin, INPUT);
  pinMode(flame_sensor2_pin, INPUT);
  pinMode(green_led, OUTPUT);
  pinMode(red_led, OUTPUT);
  pinMode(green2_led, OUTPUT);
  pinMode(red2_led, OUTPUT);
  pinMode(yellow_led, OUTPUT);
  pinMode(pump_pin, OUTPUT);
  pinMode(temp_sensor_pin, INPUT);
  lcd.init();
  lcd.clear();         
  lcd.backlight(); 
  analogReference(EXTERNAL);
  Serial.begin(9600); // Setting up the Arduino serial monitor
}

void loop() {
  // Reading the values of the flame sensors
  int analog_read_flame1 = analogRead(flame_sensor1_pin);
  flame_detected1 = map(analog_read_flame1, 0, ANALOG_MAX_VALUE, 0, 3);

  int analog_read_flame2 = analogRead(flame_sensor2_pin);
  flame_detected2 = map(analog_read_flame2, 0, ANALOG_MAX_VALUE, 0, 3);

  // Checking if there is a fire
  if ((flame_detected1 == 0) || (flame_detected2 == 0)) {
    fire_detected = true;
    fire_fighting = true;
  }

  // If a fire has been detected, activate the alarm and turn on the water pump
  if (fire_detected) {
    digitalWrite(green_led, LOW);
    digitalWrite(green2_led, LOW);
    digitalWrite(pump_pin, HIGH);
    alarm();
  } 
  // If there is no fire, turn off the alarm and water pump
  else {
    digitalWrite(active, LOW);
    digitalWrite(pump_pin, LOW);
    digitalWrite(green_led, HIGH);
    digitalWrite(green2_led, HIGH);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("No fire detected.");
  }

 // buzzer alarm function for high temperature
void high_temp_alarm(){
digitalWrite(active, HIGH);
tone(passive, hd, 900);
digitalWrite(red, HIGH);
digitalWrite(red2, HIGH);
delay(200);
digitalWrite(red, LOW);
digitalWrite(red2, LOW);
delay(100);
digitalWrite(red, HIGH);
digitalWrite(red2, HIGH);
delay(200);
digitalWrite(red, LOW);
digitalWrite(red2, LOW);
digitalWrite(active, LOW);

digitalWrite(yellow, HIGH);
digitalWrite(red, HIGH);
digitalWrite(red2, HIGH);
delay(200);
digitalWrite(red, LOW);
digitalWrite(red2, LOW);
delay(200);
digitalWrite(yellow, LOW);
digitalWrite(red2, HIGH);
delay(300);
digitalWrite(red, HIGH);
digitalWrite(red2, HIGH);
digitalWrite(yellow, HIGH);
delay(200);
digitalWrite(red, LOW);
digitalWrite(red2, LOW);
digitalWrite(yellow, LOW);
}

// function to display temperature on LCD
void display_temp(){
lcd.clear();
lcd.setCursor(1,0);
lcd.print("Temperature:");
lcd.setCursor(2,1);
lcd.print(temp);
lcd.print(" *C");
}

// function to display fire detection on LCD
void display_fire_detection(){
lcd.clear();
lcd.setCursor(0,0);
lcd.print("FIRE DETECTED!");
lcd.setCursor(1,1);
lcd.print("Temp: ");
lcd.print(temp);
lcd.print("*C");
}

// function to turn off all LEDs and buzzers
void reset_system(){
digitalWrite(green, LOW);
digitalWrite(green2, LOW);
digitalWrite(red, LOW);
digitalWrite(red2, LOW);
digitalWrite(yellow, LOW);
digitalWrite(active, LOW);
noTone(passive);
digitalWrite(pump, LOW);
lcd.clear();
}
