#include <Arduino.h>

//>>>>>>>>>>DHT PIN<<<<<<<<<<<<<
#define dhtPin1 A0
#define dhtPin2 A1
#define dhtType DHT11
//>>>>>>>>>LCD PIN<<<<<<<<<<<<<<
#define SCL A5
#define SDA A4
//>>>>>>>>>RELAY PIN<<<<<<<<<<<
#define relay13 A2 //PeltierFanLampu
#define relay24 A3 //PeltierFanLampu
#define BUZZER 13
//>>>>>>>>RTC<<<<<<<<<<<<<<<<<
//Pin(Digital 2, 3, 4)
//>>>>>>>>Keypad<<<<<<<<<<<<<<
//Pin(Digital 5, 6, 7, 8, 9, 10, 11, 12)

//Keypad Definition
char YA = 'A';
char TIDAK = 'B';
char NEXT = 'C';
char BACK = 'D';
char HOME = '#';


float suhu1;
float kelembaban1;
float suhu2;
float kelembaban2;
float suhu;
float kelembaban;
int state=1;

char Tombol;
char temperature[100];
char humidity[100];

unsigned long currentMillis;
int previousMillis = 0;
int interval = 1000;

const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
