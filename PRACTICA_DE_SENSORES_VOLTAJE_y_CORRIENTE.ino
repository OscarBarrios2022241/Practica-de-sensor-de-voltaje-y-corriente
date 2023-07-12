//Oscar Jose Barrios Cotom - 2022241

#include <Wire.h>//Librerias para comunicar con I2C
#include <LiquidCrystal_I2C.h>

int pinvoltaje = 2;
int pinamper = 3;
int sensorvoltaje = A0;
const float voltajeref = 5.0;
#define SCL A5
#define SDA A4
const float sensorcorri = A1;
const float corrienteref = 2.5;
const float ACS712_SENSITIVITY = 0.185;//Sensibilidad del sensor
 
#define LCD_ADDRESS 0x27

LiquidCrystal_I2C lcd(0x27, 16, 2);

 

void setup() {
  pinMode(pinvoltaje, INPUT_PULLUP);
  pinMode(pinamper, INPUT_PULLUP);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Modo Voltimetro");
  lcd.init();
  lcd.backlight();
}

 

void loop() {
  int voltmeterButtonState = digitalRead(pinvoltaje);
  int ampermeterButtonState = digitalRead(pinamper);

  if (voltmeterButtonState == LOW) {
    lcd.clear();
    lcd.print("Voltimetro:");
    float voltage = obtenerVoltaje();
    mostrarVoltaje(voltage);
  } else if (ampermeterButtonState == LOW) {
    lcd.clear();
    lcd.print("Amperimetro:");
    float current = obtenerCorriente();
    mostrarCorriente(current);
  }
}

 

float obtenerVoltaje() {
  int sensorValue = analogRead(sensorvoltaje);
  float voltage = (sensorValue * 4.85  / 1023.0) * voltajeref;
  return voltage;
}

 

float obtenerCorriente() {
  int sensorValue = analogRead(sensorcorri);
  float voltage = (sensorValue  / 1023.0) * voltajeref;
  float current = (voltage - corrienteref) / ACS712_SENSITIVITY;
  return current;
}

 

void mostrarVoltaje(float voltage) {
  lcd.setCursor(0, 1);
  lcd.print("Datos: ");
  lcd.print(voltage);
  lcd.print(" V");
}

 

void mostrarCorriente(float current) {
  lcd.setCursor(0, 1);
  lcd.print("Datos: ");
  lcd.print(current);
  lcd.print(" A");
}