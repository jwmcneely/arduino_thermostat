//www.elegoo.com
//2016.12.9

#include <LiquidCrystal.h>
int tempPin = 0;
int tempTarget = 80;
//                BS  E  D4 D5  D6 D7
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);
void setup()
{
  /*lcd.begin(cols, rows)
    lcd: a variable of type LiquidCrystal
    cols: the number of columns that the display has
    rows: the number of rows that the display has 
  */
  lcd.begin(16, 2);
  pinMode(1, OUTPUT);
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
}
void loop()
{
  int tempReading = analogRead(tempPin);
  // This is OK
  double tempK = log(10000.0 * ((1024.0 / tempReading - 1)));
  tempK = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * tempK * tempK )) * tempK );       //  Temp Kelvin
  float tempC = tempK - 273.15;            // Convert Kelvin to Celcius
  float tempF = (tempC * 9.0)/ 5.0 + 32.0; // Convert Celcius to Fahrenheit
  /*  replaced
    float tempVolts = tempReading * 5.0 / 1024.0;
    float tempC = (tempVolts - 0.5) * 10.0;
    float tempF = tempC * 9.0 / 5.0 + 32.0;
  */

  //use pushbuttons to adjust temp target
  if (digitalRead(2) == HIGH)
  {
    tempTarget += 1;
  }
  if (digitalRead(3) == HIGH)
  {
    tempTarget -= 1;
  }
  
  // Display Temperature in C
  lcd.setCursor(0, 0);
//  lcd.print("Temp         C  ");
  // Display Temperature in F
  lcd.print("Temp         F  ");
  lcd.setCursor(6, 0);
  // Display Temperature in C
//  lcd.print(tempC);
  // Display Temperature in F
  lcd.print(tempF);
  delay(500);
  lcd.setCursor(0,1);
  lcd.print("Target: " + String(tempTarget) + " F");

  //if tempF is above tempTarget, turn off the LED (heat); if it is below the tempTarget, turn on the LED (heat)
  if(tempF >= tempTarget) {
    digitalWrite(1, LOW);
  }
  else{
    digitalWrite(1, HIGH);
  }
}
