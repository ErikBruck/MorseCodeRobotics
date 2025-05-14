const int irLedPin = 3;        // Pin for the IR LED (transmitter)
const int dotDuration = 50;   // Duration of a dot in ms
const int dashDuration = 150;  // Duration of a dash in ms
const int pauseDuration = 100; // Pause between parts of the same letter
const int letterPause = 300;   // Pause between letters
const int wordPause = 700;    // Pause between words

void setup() {
  pinMode(irLedPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  if (Serial.available() > 0) {
    String input = Serial.readStringUntil('\n');
    input.toUpperCase();
    sendMorse(input);
  }
}

//Pause between letters
void sendMorse(String message) {
  for (int i = 0; i < message.length(); i++) {
    char c = message.charAt(i);

    if (c == ' ') {
      delay(wordPause); // Pause between words
      continue;
    }

    String morse = getMorse(c);
    for (int j = 0; j < morse.length(); j++) {
      if (morse.charAt(j) == '.') {
        sendDot();
      } else if (morse.charAt(j) == '-') {
        sendDash();
      }

      // Pause between symbols in a letter, but not after the last symbol
      if (j < morse.length() - 1) {
        sendPause();
      }
    }

    sendLetterPause(); // Pause after each letter
  }
}

String getMorse(char letter) {
  switch (letter) {
    case 'A': return ".-";
    case 'B': return "-...";
    case 'C': return "-.-.";
    case 'D': return "-..";
    case 'E': return ".";
    case 'F': return "..-.";
    case 'G': return "--.";
    case 'H': return "....";
    case 'I': return "..";
    case 'J': return ".---";
    case 'K': return "-.-";
    case 'L': return ".-..";
    case 'M': return "--";
    case 'N': return "-.";
    case 'O': return "---";
    case 'P': return ".--.";
    case 'Q': return "--.-";
    case 'R': return ".-.";
    case 'S': return "...";
    case 'T': return "-";
    case 'U': return "..-";
    case 'V': return "...-";
    case 'W': return ".--";
    case 'X': return "-..-";
    case 'Y': return "-.--";
    case 'Z': return "--..";
    case '1': return ".----";
    case '2': return "..---";
    case '3': return "...--";
    case '4': return "....-";
    case '5': return ".....";
    case '6': return "-....";
    case '7': return "--...";
    case '8': return "---..";
    case '9': return "----.";
    case '0': return "-----";
    default: return "";
  }
}

void sendDot() {
  tone(irLedPin, 38000);
  delay(dotDuration);
  noTone(irLedPin);
}

void sendDash() {
  tone(irLedPin, 38000);
  delay(dashDuration);
  noTone(irLedPin);
}

void sendPause() {
  noTone(irLedPin); 
  delay(pauseDuration);
}

void sendLetterPause() {
  delay(letterPause);
}
