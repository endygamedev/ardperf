#include <Wire.h> 
#include <LiquidCrystal.h> 


const int v0 = 75; // Some magic here. See more details:
                   // https://youtu.be/zzGWcZ2E5CY

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


String split(String data, char separator, int index) {
  int found = 0;
  int strIndex[] = { 0, -1 };
  int maxIndex = data.length() - 1;

  for (int i = 0; i <= maxIndex && found <= index; ++i) {
    if (data.charAt(i) == separator || i == maxIndex) {
      ++found;
      strIndex[0] = strIndex[1] + 1;
      strIndex[1] = (i == maxIndex) ? i+1 : i;
    }
  }

  return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}


void printStats() {
  String input = Serial.readString();
  String first_row = split(input, '\n', 0);
  String second_row = split(input, '\n', 1);

  lcd.setCursor(0, 0);
  lcd.print(first_row);

  lcd.setCursor(0, 1);
  lcd.print(second_row);
}


void printWaiting() {
  lcd.setCursor(0, 0);
  lcd.print("WAITING");

  lcd.setCursor(0, 1);
  lcd.print("DATA...");
}


void setup() {
  analogWrite(6, v0);
  lcd.begin(16, 2);
  Serial.begin(9600);
  
  printWaiting();
}


void loop() {
  if (Serial.available() > 0) {
    printStats();
  } else {
    lcd.clear();
    printWaiting();
  }

  delay(2000); // Sleep for 2 seconds
}
