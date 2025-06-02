// Arduino A
#include <Keypad.h>
const byte ROWS = 4; 
const byte COLS = 4; 
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {5, 6, 7, 9};
byte colPins[COLS] = {10, 11, 12, 13};
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

int buttonState = 0;
void setup() {
  Serial.begin(9600);
  pinMode(8, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  buttonState = digitalRead(8);
  if (buttonState == HIGH) {
    digitalWrite(LED_BUILTIN, HIGH);
    Serial.println(1);
  } else {
    digitalWrite(LED_BUILTIN, LOW);
  }
  char key = keypad.getKey();
  if (key) {
  switch (key) {
    case '2':  // Move Right
      Serial.println(2);
      break;
    case '3':  
      Serial.println(3);
      break;
    case '4':  // Move Left
      Serial.println(4);
      break;
    case '6':  // Shoot Right
      Serial.println(6);
      break;
    case '5':  // Shoot Left
      Serial.println(5);
      break;
    case '8':  // Attack Right
      Serial.println(8);
      break;
    case '7':  // Attack Left
      Serial.println(7);
      break;
    case '0':  // Change Y
      Serial.println(0);
      break;
    case '1':  // Start
      Serial.println(1);
      break;
    default:
      Serial.println(0);
      break;
   }
  }
  if (Serial.available() > 0) {

  }
   delay(100);  // Small delay for stability
}
