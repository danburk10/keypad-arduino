/* @file HelloKeypad.pde
|| @version 1.0
|| @author Alexander Brevig
|| @contact alexanderbrevig@gmail.com
||
|| @description
|| | Demonstrates the simplest use of the matrix Keypad library.
|| #
*/
#include <Keypad.h>
/*
const byte ROWS = 3; //four rows
const byte COLS = 4; //three columns

char keys[COLS][ROWS] = {
  {'1','2','3'},
  {'5','6','7'},
  {'8','9','10'},
  {'11','12','13'}
};
*/

const byte ROWS = 3; //four rows
const byte COLS = 4; //three columns
char keys[ROWS][COLS] = {
  {'1','4','7','A'},
  {'2','5','8','B'},
  {'3','6','9','C'},
};


byte rowPins[ROWS] = {9,8,7}; //{6, 5, 4, 3}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {6,5,4,3}; //{9, 8, 7}; //connect to the column pinouts of the keypad

//Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void setup(){
  Serial.begin(9600);
}
  
void loop(){
  char key = keypad.getKey();
  
  if (key){
    Serial.println(key);
  }
}
