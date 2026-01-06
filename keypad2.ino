#version two - read file1.txt and print selected records

#include <SPI.h>
#include <SdFat.h>
#include <Keypad.h>
#include <Keyboard.h>

#define CHIP_SELECT 10       // change if your SD CS pin is different
#define MAX_LINE_LENGTH 128

SdFat sd;
SdFile dataFile;
char lineBuffer[MAX_LINE_LENGTH];

// ----- Send specific line from SD -----
void sendLine(int lineNumber) {
  /*
  if (!dataFile.open("file1.txt", O_READ)) {
    Serial.println("Error opening file xxx");
    return;
  }
  */

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
  ///Serial.println("hello2");
  sendLine(0);
  sendLine(1);
  sendLine(2);
  sendLine(49);
}

void loop() {
  // nothing here
}
