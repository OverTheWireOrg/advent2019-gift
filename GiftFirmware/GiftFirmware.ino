
#include "DigiKeyboard.h"

#define LED_BUILTIN 1

//For letters
char* letters[] = {
".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", // A-I
".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", // J-R 
"...", "-", "..-", "...-", ".--", "-..-", "-.--", "--.." // S-Z
};

//For Numbers
char* numbers[] = {
  "-----", ".----", "..---", "...--", "....-", ".....",
"-....", "--...", "---..", "----."
};
int dotDelay = 200;

void sendMorse(const char *str) {
  for(int i = 0; str[i] != '\0'; i++) {
    const char c = str[i];

    if(c == ' ') {
      // space
      DigiKeyboard.delay(dotDelay * 7);
    } else {
      // regular letter
      if(c >= 'a' && c <= 'z') {
        flashSequence(letters[c - 'a']);       
      } else {
        flashSequence(numbers[c - '0']);
      }
      DigiKeyboard.delay(dotDelay * 3); //inter-letter space
    }
  }
}

void flashSequence(char* sequence) {
  int i = 0;
  while (sequence[i] != '\0') {
    flashDotOrDash(sequence[i++]);
  }
}


void flashDotOrDash(char dotOrDash) {
  digitalWrite(LED_BUILTIN, HIGH); 
  if (dotOrDash == '.') DigiKeyboard.delay(dotDelay);
  else DigiKeyboard.delay(dotDelay * 3);
  digitalWrite(LED_BUILTIN, LOW); 
  DigiKeyboard.delay(dotDelay);
}





const uint8_t HEART[] PROGMEM = {8, 70, 11, 70, 129, 6, 74, 7, 74, 129, 4, 78, 3, 78, 129, 2, 81, 1, 81, 129, 1, 101, 129, 103, 129, 103, 129, 103, 129, 1, 101, 129, 2, 99, 129, 3, 97, 129, 4, 95, 129, 6, 91, 129, 8, 87, 129, 10, 83, 129, 12, 79, 129, 14, 75, 129, 16, 71, 129, 18, 67, 129, 19, 65};
const char * const HEARTCHARS[] = { " ", "#", "\n" };

#define GETCODE(x) ((uint8_t)(x >> 6))
#define GETCOUNT(x) ((uint8_t)(x & 0x3f))

void printHeart() {
  DigiKeyboard.sendKeyStroke(0);
  DigiKeyboard.println("                        ");
  DigiKeyboard.println();
  DigiKeyboard.println();
  
  for(int i = 0; i < sizeof(HEART); i++) {
    uint8_t x = pgm_read_byte(&HEART[i]);
    const char *str = HEARTCHARS[GETCODE(x)];

    for(byte j = 0; j < GETCOUNT(x); j++) {
      if(str[0] == '\n') DigiKeyboard.println();
      else DigiKeyboard.print(str);
    }
  }
  DigiKeyboard.println();
  DigiKeyboard.println();
  DigiKeyboard.println(F("         Thank you for playing"));
  DigiKeyboard.println(F("      OverTheWire Advent CTF 2019"));
  DigiKeyboard.println();
}

void setup() {
  // don't need to set anything up to use DigiKeyboard
  pinMode(LED_BUILTIN, OUTPUT);
}

const char msg1[] PROGMEM = "The important thing is not to stop questioning. Curiosity has its own reason for existing. -- Albert Einstein";
const char msg2[] PROGMEM = "OverTheWire Advent Bonanza CTF will return in 2020! We would be terribly disappointed if you did not join us again :)";

#define REPEATS 3

void loop() {
  static int counter = 0;
  
  printHeart();
  
  switch(counter) {
    case 0 ... (REPEATS-1): 
          sendMorse("best wishes for 2020 from the overthewire advent ctf team"); break;
    case REPEATS: sendMorse("what other secrets are hiding in this device"); break;
    case REPEATS+1: sendMorse("rira pnrfne jbhyq pbafvqre neqhvab vfc jvgu nieqhqr"); break;
  }

  counter++;
  counter %= (REPEATS+2);

  DigiKeyboard.delay(5000);
}
