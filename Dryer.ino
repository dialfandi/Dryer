#include <virtuabotixRTC.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <DHT.h>
#include <Keypad.h>
#include "GlobalVariable.h"

virtuabotixRTC myRTC(2, 3, 4); //CLK. DAT, RST
LiquidCrystal_I2C lcd(0x27, 16, 2);

DHT dht1(dhtPin1, dhtType);
DHT dht2(dhtPin2, dhtType);

char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {5, 6, 7, 8}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {9, 10, 11, 12}; //connect to the column pinouts of the keypad

Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

String menu[5] = {"1. Suhu", "2. Kelembaban", "3. Status Kipas", "4. Status Lampu", "5. Bluetooth"};

int count;
//int state;

void Home() {
  myRTC.updateTime();
  lcd.setCursor(0, 0); lcd.print("Tgl: ");
  lcd.print(myRTC.dayofmonth); lcd.print("/");
  lcd.print(myRTC.month); lcd.print("/");
  lcd.print(myRTC.year);
  lcd.print(" ");
  lcd.setCursor(0, 1); lcd.print("Jam: ");
  lcd.print(myRTC.hours); lcd.print(":");
  lcd.print(myRTC.minutes);
  lcd.print(":");
  lcd.print(myRTC.seconds); lcd.println("     ");
}

void dht() {
  suhu1 = dht1.readTemperature();
  kelembaban1 = dht1.readHumidity();
  suhu2 = dht2.readTemperature();
  kelembaban2 = dht2.readHumidity();

  suhu = (suhu1 + suhu2) / 2;
  kelembaban = (kelembaban1 + kelembaban2) / 2;
  //
  //    Serial.print("SUHU: ");Serial.println(suhu2);
}

void showDHT() {
  dht();
}

void relayControl() {
  dht();
  showDHT();
  Serial.print(count);
  if (suhu >= 50) {
    //digitalWrite(BUZZER, HIGH);
    //      count++;
    analogWrite(relay13, 0);
    analogWrite(relay24, 0);
    //        if(count > 1000){
    //      digitalWrite(BUZZER, HIGH);
    //    }
    //     else if(count > 2000){
    //      digitalWrite(BUZZER, LOW);
    //    }
    digitalWrite(BUZZER, HIGH);
    delay(1000);
    digitalWrite(BUZZER, LOW);
    delay(3000);
  }
  else if (suhu < 50) {
    analogWrite(BUZZER, LOW);
    //      count = 0;
    analogWrite(relay13, 255);
    analogWrite(relay24, 255);
  }

  //  if(suhu>37){
  //    dht();
  //    count = 0;
  //    state = 0;
  //    analogWrite(relay13, 0);
  //    analogWrite(relay24, 0);
  //    if(currentMillis - previousMillis > 500){
  //      previousMillis = currentMillis;
  //      digitalWrite(BUZZER, HIGH);
  //      }
  //    else{digitalWrite(BUZZER, LOW);}
  //    count++;
  //    digitalWrite(BUZZER, HIGH);
  //    if(count <= 50 && state == 0){
  //      digitalWrite(BUZZER, HIGH);
  //      state = 1;
  //    }
  //    else if(count >=  55 && state == 1){
  //      digitalWrite(BUZZER, LOW);
  //      }
  //    }
  //   else{
  //    count=0;
  //    dht();
  //    analogWrite(relay13, 255);
  //    analogWrite(relay24, 255);

  //    count++;
  //    digitalWrite(BUZZER, HIGH);
  //    if(count > 10){
  //      digitalWrite(BUZZER, LOW);
}

void showRelayLampu() {
  dht();
  showDHT();
  if (suhu > 50) {
    lcd.setCursor(0, 0); lcd.print("     LAMPU     ");
    lcd.setCursor(0, 1); lcd.print("    M A T I      ");
  }
  else {
    lcd.setCursor(0, 0); lcd.print("     LAMPU     ");
    lcd.setCursor(0, 1); lcd.print("    MENYALA    ");
  }
}

void showRelayKipas() {
  dht();
  showDHT();
  if (suhu > 50) {
    lcd.setCursor(0, 0); lcd.print("     KIPAS     ");
    lcd.setCursor(0, 1); lcd.print("    M A T I      ");
  }
  else {
    lcd.setCursor(0, 0); lcd.print("     KIPAS     ");
    lcd.setCursor(0, 1); lcd.print("    MENYALA    ");
  }
}

void menuDisplay() {
homeRtc:
  while (true) {
    relayControl();
    Tombol = customKeypad.getKey();
    Home();
    if (Tombol == NEXT) {
      lcd.clear();
      goto menu1;
    }
  }

menu1:
  while (true) {
    Tombol = customKeypad.getKey();
    relayControl();
    lcd.setCursor(0, 0); lcd.print(menu[0]);
    lcd.setCursor(0, 1); lcd.print(menu[1]);
    if (Tombol == NEXT) {
      lcd.clear();
      goto menu2;
    }
    if (Tombol == '1') {
      lcd.clear();
      goto statusSuhu;
    }
    if (Tombol == '2') {
      lcd.clear();
      goto statusKelembaban;
    }
    if (Tombol == HOME) {
      lcd.clear();
      goto homeRtc;
    }
    if (Tombol == BACK) {
      lcd.clear();
      goto menu1;
    }
  }

menu2:
  while (true) {
    Tombol = customKeypad.getKey();
    relayControl();
    lcd.setCursor(0, 0); lcd.print(menu[2]);
    lcd.setCursor(0, 1); lcd.print(menu[3]);
    if (Tombol == NEXT) {
      lcd.clear();
      goto menu3;
    }
    if (Tombol == '3') {
      lcd.clear();
      goto statusKipas;
    }
    if (Tombol == '4') {
      lcd.clear();
      goto statusLampu;
    }
    if (Tombol == HOME) {
      lcd.clear();
      goto homeRtc;
    }
    if (Tombol == BACK) {
      lcd.clear();
      goto menu1;
    }
  }

menu3:
  while (true) {
    Tombol = customKeypad.getKey();
    relayControl();
    lcd.setCursor(0, 0); lcd.print(menu[4]);
    if (Tombol == '5') {
      lcd.clear();
      goto bluetooth;
    }
    if (Tombol == HOME) {
      lcd.clear();
      goto homeRtc;
    }
    if (Tombol == BACK) {
      lcd.clear();
      goto menu2;
    }
  }

statusSuhu:
  while (true) {
    currentMillis = millis();
    Tombol = customKeypad.getKey();
    relayControl();
    if (currentMillis - previousMillis > interval) {
      previousMillis = currentMillis;
      showDHT();
      lcd.setCursor(0, 0); lcd.print("      SUHU      ");
      lcd.setCursor(5, 1); lcd.print(suhu); lcd.print(" C");
    }
    if (Tombol == BACK) {
      lcd.clear();
      goto menu1;
    }
  }

statusKelembaban:
  while (true) {
    currentMillis = millis();
    Tombol = customKeypad.getKey();
    relayControl();
    if (currentMillis - previousMillis > interval) {
      previousMillis = currentMillis;
      showDHT();
      lcd.setCursor(0, 0); lcd.print("   KELEMBABAN");
      lcd.setCursor(5, 1); lcd.print(kelembaban); lcd.print(" %");
    }
    if (Tombol == BACK) {
      lcd.clear();
      goto menu1;
    }
  }

statusLampu:
  while (true) {
    showDHT();
    Tombol = customKeypad.getKey();
    relayControl();
    showRelayLampu();
    if (Tombol == BACK) {
      lcd.clear();
      goto menu2;
    }
  }

statusKipas:
  while (true) {
    showDHT();
    Tombol = customKeypad.getKey();
    relayControl();
    showRelayKipas();
    if (Tombol == BACK) {
      lcd.clear();
      goto menu2;
    }
  }

bluetooth:
  while (true) {
    showDHT();
    Tombol = customKeypad.getKey();
    relayControl();
    lcd.setCursor(0, 0); lcd.print("MENU KOSONG");
    if (Tombol == BACK) {
      lcd.clear();
      goto menu3;
    }
  }
}

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  dht1.begin();
  dht2.begin();
  pinMode(BUZZER, OUTPUT);
  //myRTC.setDS1302Time(11, 34, 0, 4, 16, 8, 2020);
}

void loop() {
    menuDisplay();
//  Tombol = customKeypad.getKey();
//  Serial.println(Tombol);
//  delay(100);
}
