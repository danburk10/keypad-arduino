//keypad & sdcard read
// you punch two digits and then it reads the SD card for that line# and keyboard.print(line# data)

#include <SPI.h>
#include <SdFat.h>
#include <Keypad.h>
#include <Keyboard.h>

#define CHIP_SELECT 10       // change if your SD CS pin is different
#define MAX_LINE_LENGTH 128

uint8_t counter = 0;
uint8_t number = 0;
uint8_t firstNum = 0;

SdFat sd;
SdFile dataFile;
char lineBuffer[MAX_LINE_LENGTH];


const byte ROWS = 3; //four rows
const byte COLS = 4; //three columns
char keys[ROWS][COLS] = {
  {'A','3','6','9'},
  {'0','2','5','8'},
  {'B','1','4','7'},
};


byte rowPins[ROWS] = {9,8,7}; //{6, 5, 4, 3}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {6,5,4,3}; //{9, 8, 7}; //connect to the column pinouts of the keypad

//Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );


void initSD(){
  
  // Initialize SD card
  if (!sd.begin(CHIP_SELECT, SD_SCK_MHZ(50))) {
    Serial.println("SD card initialization failed!");
    return;
  }

  dataFile.close();

  // Open the file for reading
  if (!dataFile.open("file1.txt", O_READ)) {
    Serial.println("Error opening file1.txt");
    return;
  }

  Serial.println("SD card ready.");
}

// ----- Send specific line from SD -----
void sendLine(int lineNumber) {
  /*
  if (!dataFile.open("file1.txt", O_READ)) {
    Serial.println("Error opening file xxx");
    return;
  }
  */
  dataFile.rewind();
  int currentLine = 0;
  int charIndex = 0;
  char c;
  while (dataFile.available()) {
    dataFile.read(&c, 1);
    if (c == '\n' || c == '\r') {
      if (charIndex > 0) {
        if (currentLine == lineNumber) {
          lineBuffer[charIndex] = '\0';
          Serial.println(lineBuffer); //testing on uno - 
          // On Pro Micro, use: Keyboard.print(lineBuffer);
          break;
        }
      }
      currentLine++;
      charIndex = 0;
    } else if (charIndex < MAX_LINE_LENGTH - 1) {
      if (currentLine == lineNumber) {
        lineBuffer[charIndex++] = c;
      }
    }
  }

  //dataFile.close();
}

void setup() {
  Serial.begin(9600);
  while (!Serial); // wait for Serial on Leonardo/Pro Micro
  Serial.println("hello");

  initSD();
  
  /*
  // Initialize SD card
  if (!sd.begin(CHIP_SELECT, SD_SCK_MHZ(50))) {
    Serial.println("SD card initialization failed!");
    return;
  }
  Serial.println("SD card ready.");

  // Open the file for reading
  if (!dataFile.open("file1.txt", O_READ)) {
    Serial.println("Error opening file1.txt");
    return;
  }
  */
  ///Serial.println("hello2");
  //sendLine(0);
  //sendLine(1);
  //sendLine(2);
  //sendLine(49);
}

void loop() {
  char key = keypad.getKey();
  /*
  if (key) {
    Serial.println(key);
  }
  */

  if (key){
    if (key == 'A') {
      //nothing
    } else if (key == 'B') {
      //reload sd card
      initSD();
    } else {
      counter++;
      if (counter == 1){
        firstNum =  (key - '0') * 10;
      }
      if (counter == 2) {
        number = firstNum + (key - '0');
        Serial.print(number);
        Serial.print("-");
        sendLine(number);
        counter = 0;
      }
    }

    //Serial.println(number);
  }
  // nothing here

}
