#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Initialize the LCD with I2C address 0x27, 16 columns, and 2 rows
LiquidCrystal_I2C lcd(0x27, 16, 2);

const int analogPin = A3;  // Analog input pin
const float a = 0.482048285939083;  // Calibration constant
const float b = -11.9956281416909;  // Calibration constant

void setup() {
  Serial.begin(9600);  // Initialize Serial Communication
  lcd.begin(16, 2);    // Initialize the LCD
  lcd.backlight();     // Turn on the LCD backlight
}

void loop() {
  // Display static messages on the LCD
  lcd.clear();
  lcd.print("Thermometer says");
  delay(1000);


  // Read and calculate the temperature
  int analogValue = analogRead(analogPin);       // Read the analog input value
  float voltage = (analogValue / 1023.0) * 5.0;  // Convert the analog value to voltage
  float temperature = (voltage - b) / a;        // Calculate temperature using the formula

  // Display temperature on the Serial Monitor and LCD
  lcd.clear();
  lcd.print("Temp: ");
  lcd.print(temperature, 2);
  lcd.print(" C");
  

  Serial.print("Current temperature: ");
  Serial.print(temperature, 2);
  Serial.println(" C");
  Serial.println("Voltage");
  Serial.println(voltage, 2);
  // Check if the temperature is out of range
  if (temperature > 35 || temperature < 25) {
    lcd.setCursor(0, 1);
    lcd.print("Out of range!");
    Serial.println("Temperature out of range!");
  } else {
    Serial.println("Temperature is within range.");
  }

  delay(5000);  // Delay for a second before reading again
}
