#include <Key.h>
#include <Keypad.h>
#include <Servo.h>

#define Password_Length 6 

Servo servo;

int signalPin = 11;

char Data[Password_Length]; 
char Master[Password_Length] = "3932*"; 
byte data_count = 0, master_count = 0;
bool Pass_is_good;
char customKey;

const byte ROWS = 4;
const byte COLS = 4;

const int buzzer = 10;

char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {9, 8, 7, 6};
byte colPins[COLS] = {5, 4, 3, 2};

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

void setup() {
  Serial.begin(9600);
  pinMode(buzzer, OUTPUT);
  servo.attach(11);
  servo.write(0);
  delay(2000);
}

void loop() {
  customKey = customKeypad.getKey();
  
  if (customKey){
    Serial.println(customKey);
    tone(buzzer, 1000); // Send 1KHz sound signal...
    delay(500);        // ...for 1 sec
    noTone(buzzer);
    Data[data_count] = customKey; 
    data_count++;
    if(customKey == 'C') {
      servo.write(0);
      clearData();
    }
  }

  if(data_count == Password_Length-1){

    if(!strcmp(Data, Master)){
      servo.write(90);
      }
    clearData();  
  }
}

void clearData(){
  while(data_count != 0){
    Data[data_count--] = 0; 
  }
  return;
}
