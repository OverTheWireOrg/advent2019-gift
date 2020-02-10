#include <DigiCDC.h>
#include <avr/pgmspace.h>

#define USERNAME "rudolf"
#define PASSWORD "T1nyPW"
#define PWBUFSIZE 8

const uint8_t HEART[] PROGMEM = {8, 70, 11, 70, 129, 6, 74, 7, 74, 129, 4, 78, 3, 78, 129, 2, 81, 1, 81, 129, 1, 101, 129, 103, 129, 103, 129, 103, 129, 1, 101, 129, 2, 99, 129, 3, 97, 129, 4, 95, 129, 6, 91, 129, 8, 87, 129, 10, 83, 129, 12, 79, 129, 14, 75, 129, 16, 71, 129, 18, 67, 129, 19, 65};

const char * const HEARTCHARS[] = { " ", "@", "\r\n" };

bool readNewLine() {
  SerialUSB.refresh();
  if(SerialUSB.peek() == '\r') {
    SerialUSB.read();
    if(SerialUSB.peek() == '\n') SerialUSB.read();
    return true;
  }
  return false;
}

bool checkUsername() {
  int counter = 0;
  bool success = false;

  SerialUSB.print(F("Login: "));

  while(true) {
    char c;
    if(SerialUSB.available()) {
      if(counter == strlen(USERNAME) && readNewLine()) {
        success = true;
        goto done;
      }
      
      c = SerialUSB.read();
      SerialUSB.print(c);

      if(counter >= strlen(USERNAME)) goto done;    
      if(c != USERNAME[counter]) goto done;
      counter++;
    } else {
      SerialUSB.refresh();
    }
  }

done:
  SerialUSB.println();
  if(!success) { 
    SerialUSB.println(F("Unknown user"));
    SerialUSB.println();
  }
  return success;
}

struct pwtype {
  char buf[PWBUFSIZE];
  char pw[PWBUFSIZE];
} pw;
  
bool checkPassword() {
  int counter = 0;

  // can we send 0 bytes??
  SerialUSB.print(F("Password: "));

  while(true) {
    if(SerialUSB.available()) { 
      if(readNewLine()) {
        pw.buf[counter] = '\0';
        
        if(!strcmp(pw.buf, pw.pw)) {
          if(strlen(pw.pw) == 0) {
            SerialUSB.println();
            SerialUSB.print(F("Password correct, but length 0?! HACKZ!"));
            return false;
          }

          SerialUSB.println();
          return true;
        } else {
          SerialUSB.println();
          SerialUSB.print(F("Password incorrect. Password has length "));
          SerialUSB.println(strlen(pw.pw), DEC);
          return false;
        }
      } else {
        SerialUSB.print("*");
        char c = SerialUSB.read();        
        pw.buf[counter++] = c;
      }

      if(counter >= sizeof(pw)) {
        SerialUSB.println();
        SerialUSB.print(F("Password too long. Password has length "));
        SerialUSB.println(strlen(pw.pw), DEC);
        return false;
      }


    } else {
      SerialUSB.refresh();
    }
  }
}


#define GETCODE(x) ((uint8_t)(x >> 6))
#define GETCOUNT(x) ((uint8_t)(x & 0x3f))

void printHeart() {
  for(int i = 0; i < sizeof(HEART); i++) {
    uint8_t x = pgm_read_byte(&HEART[i]);
    const char *str = HEARTCHARS[GETCODE(x)];

    if(GETCODE(x) == 1) {
      SerialUSB.print(F("\033[1;31m"));
    } else {
      SerialUSB.print(F("\033[0m"));      
    }
    for(byte j = 0; j < GETCOUNT(x); j++) {
      SerialUSB.print(str);
    }
    SerialUSB.refresh();
  }
  SerialUSB.print(F("\033[0m\r\n\r\nThank you for playing OverTheWire Advent CTF 2019\r\nSee you again next year! :)\r\nPress any key to reset"));
  while(!SerialUSB.available()) SerialUSB.refresh();
  SerialUSB.read();
}

#define LED_BUILTIN 1
void setup() {
  strcpy(pw.pw, PASSWORD);
  //pinMode(LED_BUILTIN, OUTPUT);
  //digitalWrite(LED_BUILTIN, LOW);
  SerialUSB.begin();
}

void loop() {
  //digitalWrite(LED_BUILTIN, HIGH); 
  SerialUSB.println("\033[0m\033[2JA tiny challenge... :)");
  
  if(checkUsername() && checkPassword()) {
    SerialUSB.println();
    printHeart();
  } else {
    SerialUSB.delay(1500);
  }
}
