#include <LiquidCrystal_I2C.h>
#include <Wire.h>

const int irReceiverPin = 2; // IR receiver connected to digital pin 2

// Timing thresholds (must match the sender's)
const int dotThreshold = 75;
const int dashThreshold = 200;
const int letterPause = 250;
const int wordPause = 500;
const long lcdClearThreshold = 30000; // 20 seconds to clear LCD
const long scrollDelay = 600; // 500ms delay between scrolls

String currentSymbol = "";
String message = ""; // Stores the full message for scrolling
unsigned long lastChangeTime = 0;
unsigned long lastScrollTime = 0;
bool lastState = HIGH;
bool isScrolling = false;
int scrollOffset = 0;

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  pinMode(irReceiverPin, INPUT);
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Morse reader");
  delay(2500);
  lcd.clear();
}

void loop() {
  bool state = digitalRead(irReceiverPin);
  unsigned long now = millis();

  if (state != lastState) {
    unsigned long duration = now - lastChangeTime;

    if (lastState == LOW) {
      // Signal just ended (HIGH now), measure pulse
      if (duration < dotThreshold) {
        currentSymbol += ".";
      } else if (duration < dashThreshold) {
        currentSymbol += "-";
      }
    } else {
      // Silence just ended (LOW now), measure gap
      if (duration >= wordPause) {
        decodeMorse(currentSymbol);
        message += " "; // Add space after word
        Serial.println(); // End of word
        currentSymbol = "";
      } else if (duration >= letterPause) {
        decodeMorse(currentSymbol);
        currentSymbol = "";
      }
    }

    lastChangeTime = now;
    lastState = state;
  }

  // Flush last symbol if idle
  if ((millis() - lastChangeTime) > 1000 && currentSymbol.length() > 0) {
    decodeMorse(currentSymbol);
    Serial.println(); // End of message
    currentSymbol = "";
    lastChangeTime = millis();
  }

  // Check if idle for 20 seconds and clear LCD
  checkIdleAndClearLCD();

  // Scroll the message if necessary
  scrollMessage();
}

// Check if no new letters for 20 seconds and clear LCD
void checkIdleAndClearLCD() {
  if (millis() - lastChangeTime > lcdClearThreshold) {
    lcd.clear();
    message = ""; // Clear the message
    isScrolling = false; // Stop scrolling
    scrollOffset = 0; // Reset scroll position
    lastChangeTime = millis(); // Reset to prevent repeated clearing
  }
}

// Scroll the message if it exceeds LCD width
void scrollMessage() {
  if (message.length() <= 16) {
    isScrolling = false; // No need to scroll if message fits
    lcd.setCursor(0, 0);
    lcd.print(message);
    return;
  }

  isScrolling = true;
  unsigned long now = millis();

  if (now - lastScrollTime >= scrollDelay) {
    lcd.clear();
    // Extract substring to display based on scrollOffset
    String displayText = message.substring(scrollOffset, scrollOffset + 16);
    lcd.setCursor(0, 0);
    lcd.print(displayText);

    scrollOffset++;
    // Loop back to start when reaching the end
    if (scrollOffset > message.length() - 16) {
      scrollOffset = 0;
    }

    lastScrollTime = now;
  }
}

// Decode Morse to characters
void decodeMorse(String symbol) {
  String decodedChar = "";
  if (symbol == ".-") decodedChar = "A";
  else if (symbol == "-...") decodedChar = "B";
  else if (symbol == "-.-.") decodedChar = "C";
  else if (symbol == "-..") decodedChar = "D";
  else if (symbol == ".") decodedChar = "E";
  else if (symbol == "..-.") decodedChar = "F";
  else if (symbol == "--.") decodedChar = "G";
  else if (symbol == "....") decodedChar = "H";
  else if (symbol == "..") decodedChar = "I";
  else if (symbol == ".---") decodedChar = "J";
  else if (symbol == "-.-") decodedChar = "K";
  else if (symbol == ".-..") decodedChar = "L";
  else if (symbol == "--") decodedChar = "M";
  else if (symbol == "-.") decodedChar = "N";
  else if (symbol == "---") decodedChar = "O";
  else if (symbol == ".--.") decodedChar = "P";
  else if (symbol == "--.-") decodedChar = "Q";
  else if (symbol == ".-.") decodedChar = "R";
  else if (symbol == "...") decodedChar = "S";
  else if (symbol == "-") decodedChar = "T";
  else if (symbol == "..-") decodedChar = "U";
  else if (symbol == "...-") decodedChar = "V";
  else if (symbol == ".--") decodedChar = "W";
  else if (symbol == "-..-") decodedChar = "X";
  else if (symbol == "-.--") decodedChar = "Y";
  else if (symbol == "--..") decodedChar = "Z";
  else if (symbol == "-----") decodedChar = "0";
  else if (symbol == ".----") decodedChar = "1";
  else if (symbol == "..---") decodedChar = "2";
  else if (symbol == "...--") decodedChar = "3";
  else if (symbol == "....-") decodedChar = "4";
  else if (symbol == ".....") decodedChar = "5";
  else if (symbol == "-....") decodedChar = "6";
  else if (symbol == "--...") decodedChar = "7";
  else if (symbol == "---..") decodedChar = "8";
  else if (symbol == "----.") decodedChar = "9";

  if (decodedChar != "") {
    message += decodedChar; // Append to message
    lcd.setCursor(0, 0);
    // Display the latest part of the message (up to 16 chars)
    if (message.length() <= 16) {
      lcd.print(message);
    } else {
      lcd.print(message.substring(message.length() - 16));
    }
  }

  // Output to Serial for non-LCD characters
  if (symbol == "-.." || symbol == "." || symbol == "..-." || symbol == "...-" ||
      symbol == ".--." || symbol == "--.-" || symbol == ".-." || symbol == "..." ||
      symbol == "-" || symbol == "..-" || symbol == ".--" || symbol == "-..-" ||
      symbol == "-.--" || symbol == "--.." || symbol == "-----" || symbol == ".----" ||
      symbol == "..---" || symbol == "...--" || symbol == "....-" || symbol == "....." ||
      symbol == "-...." || symbol == "--..." || symbol == "---.." || symbol == "----.") {
    Serial.print(decodedChar);
  }
}