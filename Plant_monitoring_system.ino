#include <DHT.h>
#include <LiquidCrystal_I2C.h>

#define DHTPIN 2
#define DHTTYPE DHT11
#define MOISTURE_PIN A0
#define PUMP_PIN 7

#define LCD_ADDRESS 0x27
#define LCD_COLS 16
#define LCD_ROWS 2

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(LCD_ADDRESS, LCD_COLS, LCD_ROWS);

void setup() {
  Serial.begin(9600);
  dht.begin();
  pinMode(MOISTURE_PIN, INPUT);
  pinMode(PUMP_PIN, OUTPUT);
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Plant Monitoring");
}

void loop() {
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
  int moisture = analogRead(MOISTURE_PIN);
  bool needsWatering = (moisture < 500);

  lcd.setCursor(0, 1);
  lcd.print("Temp: ");
  lcd.print(temperature);
  lcd.print("C Hum: ");
  lcd.print(humidity);
  lcd.print("%");
  
  if (needsWatering) {
    lcd.setCursor(0, 0);
    lcd.print("Needs Watering! ");
    digitalWrite(PUMP_PIN, HIGH);
    delay(5000);
    digitalWrite(PUMP_PIN, LOW);
  }
  
  delay(10000);
}
