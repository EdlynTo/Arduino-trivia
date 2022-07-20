#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 20, 4);
int LedG = 8;
int LedR = 9;
int up = 7;
int page_counter = 1 ;
boolean current_up = LOW;
boolean last_up = LOW;
int xposPin = A0;
int yposPin = A1;
int yourans;
int ans;
int score = 0;
int question = 0;

void setup() {
  lcd.init();
  lcd.backlight();
  Serial.begin(9600);
  pinMode(xposPin, INPUT);
  pinMode(yposPin, INPUT);
  pinMode(LedG, OUTPUT);
  pinMode(LedR, OUTPUT);
}

void loop() {
  current_up = debounce(last_up, up);
  int xpos = analogRead(xposPin);
  delay(150);
  int ypos = analogRead(yposPin);
  Serial.print("ypos =");
  Serial.println(ypos);

  if (last_up == LOW && current_up == HIGH) { //When up button is pressed
    lcd.clear();
    page_counter = 1;//When page is changed, lcd clear to print new page
    score = 0;
  }

  if (ypos > 1000) { //When moved up
    lcd.clear(); //When page is changed, lcd clear to print new page
    delay(100);

    if (page_counter < 6 ) { //Page counter never higher than 6(total of pages)
      page_counter = page_counter + 1; //Page up
    }
  }
  if (ypos < 150 ) { //When moved down
    lcd.clear(); //When page is changed, lcd clear to print new page
    delay(100);
    if (page_counter <= 6 && page_counter > 1) {
      //Page counter never higher than 6(total of pages)
      page_counter = page_counter - 1; //Page down
    }

  }
  last_up = current_up;


  switch (page_counter) {
    case 1: { //Design of home page 1
        lcd.setCursor(1, 0);
        lcd.print("Welcome to my");
        lcd.setCursor(2, 1);
        lcd.print("Trivia Game!");
      } break;

    case 2: { //Design of page 2
        lcd.setCursor(2, 0);
        lcd.print("Ada Lovelace born");
        lcd.setCursor(0, 1);
        lcd.print("1815        1924");
        correctionFunction(1);
      } break;

    case 3: { //Design of page 3
        lcd.setCursor(0, 0);
        lcd.print("Where do I live?");
        lcd.setCursor(0, 1);
        lcd.print("Canada       USA");
        correctionFunction(1);
      } break;

    case 4: { //Design of page 4
        lcd.setCursor(0, 0);
        lcd.print("Euclid is:");
        lcd.setCursor(0, 1);
        lcd.print("American   Greek");
        correctionFunction(1);
      } break;

    case 5: { //Design of page 5
        lcd.setCursor(0, 0);
        lcd.print("Steve Jobs made:");
        lcd.setCursor(0, 1);
        lcd.print("Google     Apple");
        correctionFunction(2);
      } break;

    case 6: { //Design of page 5
        lcd.setCursor(0, 0);
        lcd.print("Your score is: ");
        lcd.setCursor(0, 1);
        lcd.print(score);
        lcd.print(" / 4");
      } break;

  }//switch end

}//loop end

//---- De-bouncing function for all buttons----//
boolean debounce(boolean last, int pin) {

  boolean current = digitalRead(pin);

  if (last != current) {
    delay(5);
    current = digitalRead(pin);
  }

  return current;

}

int correctionFunction(int ans) {
  int xpos = analogRead(xposPin);
  int ypos = analogRead(yposPin);
  if (xpos > 800) {
    yourans = 2;
  }
  if (xpos < 350) {
    yourans = 1;
  }
  if (yourans == ans) {
    digitalWrite(LedG, HIGH);
    delay(1000);
    digitalWrite(LedG, LOW);
    yourans = 0;
    score += 1;
  }
  else if (yourans != ans and yourans == 1 or yourans == 2 and yourans != ans) {
    digitalWrite(LedR, HIGH);
    delay(1000);
    digitalWrite(LedR, LOW);
    yourans = 0;
  }
}
