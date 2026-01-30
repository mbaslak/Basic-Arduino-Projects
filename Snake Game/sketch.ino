#include <LiquidCrystal_I2C.h>
#include <stdlib.h>
#include <time.h>

LiquidCrystal_I2C lcd(0x27,20,4);
struct coordination {
  int x;
  int y;
};
void setup() {
int up = 11;
int down = 10;
int right = 13;
int left = 12;
int button = right;
int randx = rand()%19;
int randy = rand()%3;
int grt = 3; // The initial index of the head.
int point = 0; 

pinMode(up, INPUT);
pinMode(down, INPUT);
pinMode(right, INPUT);
pinMode(left, INPUT);
lcd.begin(20,4);
lcd.backlight();
struct coordination snk[80];

char snake[80];
snake[0] = '.';
snake[1] = '.';
snake[2] = '.';
snake[3] = '.';
// Initial coordinates.
snk[0].x = 0;
snk[0].y = 0;
snk[1].x = 1;
snk[1].y = 0;
snk[2].x = 2;
snk[2].y = 0;
snk[3].x = 3;
snk[3].y = 0;

int i = 0;
while(i<grt+1) {
  lcd.setCursor(i,0);
  lcd.print(snake[i]);
  i++;
}
while(1) {
  int a = grt;
  for(; a>0; a--) {
    lcd.setCursor(snk[a].x, snk[a].y); // Every elements, except head, drop its character to cell of the element after itself
    lcd.print(snake[a-1]);
  }
    lcd.setCursor(snk[0].x,snk[0].y);
    lcd.print(" "); // Excess element is erased.
  int j = 0;
  for(; j<grt; j++) {
    snk[j].x = snk[j+1].x; // The coordinates are updated.
    snk[j].y = snk[j+1].y;
  }
if(button == up) {
    if(snk[grt].y-1 == -1 ){
      lcd.clear();
      lcd.setCursor(2,1);
      lcd.print("GAME OVER. ");lcd.print(point);lcd.print("P");
      return; // The snake crashed the wall.
    }
  for(int number = 0; number<grt; number++) {
    if(snk[grt].x == snk[number].x && snk[grt].y-1 == snk[number].y){
      lcd.clear();
      lcd.setCursor(2,1);
      lcd.print("GAME OVER. ");lcd.print(point);lcd.print("P");
      return; // The snake crashed itself.
    }
  }
      lcd.setCursor(snk[grt].x,snk[grt].y-1);
      lcd.print(snake[grt]); // The head of the snake moves in direction determined before.
      snk[grt].y--;
    if(snk[grt].x == randx && snk[grt].y == randy) {
        randx = rand()%19; // The place of the food is indicated.
        randy = rand()%3;
        grt++;
        snake[grt] = '.'; // The height of the snake increases.
        snk[grt].x = snk[grt-1].x;
        snk[grt].y = snk[grt-1].y;
        point++; // The points go up.
      }
}
else if(button == down) {
      if(snk[grt].y+1 == 4){
        lcd.clear();
        lcd.setCursor(2,1);
        lcd.print("GAME OVER. ");lcd.print(point);lcd.print("P");
        return;
    }
  for(int number = 0; number<grt; number++) {
    if(snk[grt].x == snk[number].x && snk[grt].y+1 == snk[number].y){
      lcd.clear();
      lcd.setCursor(2,1);
      lcd.print("GAME OVER. ");lcd.print(point);lcd.print("P");
      return;
     }
  }
      lcd.setCursor(snk[grt].x,snk[grt].y+1);
      lcd.print(snake[grt]);
      snk[grt].y++;
      if(snk[grt].x == randx && snk[grt].y == randy) {
        randx = rand()%19;
        randy = rand()%3;
        grt++;
        snake[grt] = '.';
        snk[grt].x = snk[grt-1].x;
        snk[grt].y = snk[grt-1].y;
        point++;
      }
}
else if(button == right) {
      if(snk[grt].x+1 == 20){
        lcd.clear();
        lcd.setCursor(2,1);
        lcd.print("GAME OVER. ");lcd.print(point);lcd.print("P");
        return;
    }
    for(int number = 0; number<grt; number++) {
      if(snk[grt].x+1 == snk[number].x && snk[grt].y == snk[number].y){
        lcd.clear();
        lcd.setCursor(2,1);
        lcd.print("GAME OVER. ");lcd.print(point);lcd.print("P");
        return;
     }
  }
      lcd.setCursor(snk[grt].x+1,snk[grt].y);
      lcd.print(snake[grt]);
      snk[grt].x++;
      if(snk[grt].x == randx && snk[grt].y == randy) {
        randx = rand()%19;
        randy = rand()%3;
        grt++;
        snake[grt] = '.';
        snk[grt].x = snk[grt-1].x;
        snk[grt].y = snk[grt-1].y;
        point++;
      }
}
else if(button == left) {
      if(snk[grt].x-1 == -1){
      lcd.clear();
      lcd.setCursor(2,1);
      lcd.print("GAME OVER. ");lcd.print(point);lcd.print("P");
      return;
    }
    for(int number = 0; number<grt; number++) {
      if(snk[grt].x-1 == snk[number].x && snk[grt].y == snk[number].y){
        lcd.clear();
        lcd.setCursor(2,1);
        lcd.print("GAME OVER. ");lcd.print(point);lcd.print("P");
        return;
        }
      }
       lcd.setCursor(snk[grt].x-1,snk[grt].y);
       lcd.print(snake[grt]);
       snk[grt].x--;
       if(snk[grt].x == randx && snk[grt].y == randy) {
        randx = rand()%19;
        randy = rand()%3;
        grt++;
        snake[grt] = '.';
        snk[grt].x = snk[grt-1].x;
        snk[grt].y = snk[grt-1].y;
        point++;
      }
}
  for(int b = 0; b<500; b++){   // The user data is taken from buttons.
    delay(1);
    if(button != down && digitalRead(up) ) {
      button = up;
    }
    else if(button != up && digitalRead(down)) {
      button = down;
    }
    else if(button != left && digitalRead(right)) {
      button = right;
    }
    else if(button != right && digitalRead(left)) {
      button = left;
    }
  }
  lcd.setCursor(randx,randy);
  lcd.print('o'); // The food is placed into the area.
}
}
void loop() {
}

 