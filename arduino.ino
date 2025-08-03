#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
Servo myservo;

#define ir_car1 2
#define ir_car2 3
#define ir_car3 4
#define ir_enter 5
#define ir_exit 6
#define servoPin 9

int S1 = 0, S2 = 0, S3 = 0;
int totalSlots = 3;

void setup() {
  Serial.begin(9600); // Communication with ESP8266
  Wire.begin();
  lcd.init();
  lcd.backlight();
  
  pinMode(ir_car1, INPUT);
  pinMode(ir_car2, INPUT);
  pinMode(ir_car3, INPUT);
  pinMode(ir_enter, INPUT);
  pinMode(ir_exit, INPUT);
  
  myservo.attach(servoPin);
  myservo.write(0);
  lcd.setCursor(0, 0);
  lcd.print("Car Parking");
  lcd.setCursor(0, 1);
  lcd.print("System Ready");
  delay(2000);
  lcd.clear();
}

void loop() {
  Read_Sensors();

  lcd.setCursor(0, 0);
  lcd.print("Slots: ");
  lcd.print(totalSlots - (S1 + S2 + S3));
  lcd.print(" ");

  lcd.setCursor(0, 1);
  lcd.print("S1:"); lcd.print(S1 ? "F " : "E ");
  lcd.print("S2:"); lcd.print(S2 ? "F " : "E ");
  lcd.print("S3:"); lcd.print(S3 ? "F " : "E ");

  // Send data to ESP8266 for Blynk
  Serial.print(S1);
  Serial.print(",");
  Serial.print(S2);
  Serial.print(",");
  Serial.println(S3);
  delay(1000);
}

void Read_Sensors() {
  S1 = digitalRead(ir_car1) == LOW ? 1 : 0;
  S2 = digitalRead(ir_car2) == LOW ? 1 : 0;
  S3 = digitalRead(ir_car3) == LOW ? 1 : 0;
}
