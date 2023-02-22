//Arduino uno code for fire alarm System written by Helen Okereke

#include <LiquidCrystal_I2C.h>

//initializing the buzzer pins
int active = 2;
int passive = 4;

//initializing the buzzer tone rythm frequency
int hd = 1012;
int d = 524;

//initializing the alarm blink light pins
int red = 10;
int yellow = 12;
int green = 13;
int red2 = 6;
int green2 = 5;

//initializing the temperature pin and temperature variable
float temp;
int tempPin = 0;

//initializing the two flame sensors
int flame_sensor = A1 ;
int flame_detected ;

int flame_sensor2 = A3 ;
int flame2_detected ;

//initializing the water pump
int pump = 8;

// set the LCD address to 0x27 for a 16 chars and 2 line 
LiquidCrystal_I2C lcd(0x27,16,2);  

#define aref_voltage 3.3
void setup() {
  // put your setup code here, to run once:
  //setting up the sensors and actuators
  pinMode(active, OUTPUT);
  pinMode(passive, OUTPUT);
  pinMode(flame_sensor, INPUT);
  pinMode(flame_sensor2, INPUT) ;
  pinMode(green, OUTPUT);
  pinMode(red, OUTPUT);
  pinMode(green2, OUTPUT);
  pinMode(red2, OUTPUT);
  pinMode(yellow, OUTPUT);
  pinMode(pump, OUTPUT);
  pinMode(tempPin, INPUT) ;

  // setting up the lcd display
  lcd.init();
  lcd.clear();         
  lcd.backlight(); 
  analogReference(EXTERNAL);

  // setting up the arduino serial Monitor
  Serial.begin(9600); 

}

void loop() {
  // getting the value of flame sensor 1
  int analogread_flame1 = analogRead(flame_sensor);
  flame_detected = map(analogread_flame1, 0, 1024, 0, 3);


  //getting the value of flame sensor 2
  int analogread_flame = analogRead(flame_sensor2);
  flame2_detected = map(analogread_flame, 0, 1024, 0, 3);

  //printing the values of the flame sensors in the serial Monitor  
  Serial.println(flame2_detected);
  Serial.println(flame_detected);
  

  //turn the green led off, alarm and pump on when fire is detected
  if ((flame_detected == 0) || (flame2_detected == 0))
  {
    digitalWrite(green, LOW);
    digitalWrite(green2, LOW);
    digitalWrite(pump, HIGH);
    alarm();
  }

  else{
    // reading the temprature of the house to get the state of fire
    int reading = analogRead(tempPin);

  // Convert that reading into voltage
  float voltage = reading * (aref_voltage / 1024.0);

  // Convert the voltage into the temperature in Celsius
  temp = (voltage - 0.5) * 100;
    digitalWrite(pump, LOW);
    digitalWrite(green, HIGH);
    digitalWrite(green2, HIGH);
    lcd.clear();
    lcd.setCursor(1,0);
    lcd.print("No Troubles!!");
  }

}

//the buzzer beeping function
void alarm(){
  int reading = analogRead(tempPin);

  // Convert that reading into voltage
  float voltage = reading * (aref_voltage / 1024.0);

  // Convert the voltage into the temperature in Celsius
  temp = (voltage - 0.5) * 100;
   
  lcd.setCursor(1,0);
  lcd.print("Fire Detected!");
  lcd.setCursor(2,1);
  lcd.print("Temp: ");
  lcd.print(temp);
  lcd.print("*C");
  
  digitalWrite(active, HIGH);
  tone(passive, d, 900);
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
