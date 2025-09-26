/*
replay button = jaune-rouge-orangee-bleu

*/

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // Largeur de l'écran OLED en pixels
#define SCREEN_HEIGHT 64 // Hauteur de l'écran OLED en pixels

// Création d'un objet écran OLED
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);




int pinLED[4] = {8, 12, 10, 11};
int buzzer_pin = 9;
int butt_pin[4] = {5,2,3,4};
int tens[] = {261, 294, 330, 349, 392, 392, 349, 330, 294, 261};
int duree[] = {250, 250, 250, 250, 500, 500, 250, 250, 250, 500};

String couleur[4] = {"jaune", "rouge", "orangée", "bleu"};
int* game;
int* score;

int* play;


void demons(int* sc){
  delay(500);
  for (int i=0; i<(*sc) +1; i++){
    digitalWrite(pinLED[game[i]], HIGH);
    tone(buzzer_pin, tens[game[i]], 500);
    delay(300);
    noTone(buzzer_pin);
    digitalWrite(pinLED[game[i]], LOW);
    delay(100);
  }

}



void setup() {
  // put your setup code here, to run once:
  for (int i=0; i<10; i++){
    duree[i] = duree[i]*1.5;
  }


  Serial.begin(115200);
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Adresse I2C 0x3C par défaut
    Serial.println(F("Échec de l'initialisation de l'écran OLED"));
    while (true); // Boucle infinie
  }
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.display();



  score = (int*)malloc(sizeof(int));
  play = (int*)malloc(sizeof(int));
  score[0] = 0;
  play[0] = 0;


  game = (int*)malloc(sizeof(int)*20);
  // random
  randomSeed(analogRead(A0));
  // begin pins
  for (int i=0; i<4; i++){
    pinMode(pinLED[i], OUTPUT);
    pinMode(butt_pin[i], INPUT_PULLUP);
  }
  pinMode(buzzer_pin, OUTPUT);
  game[0] = random(4);

  // animation debut
  for (int i=0; i<10; i++){
    digitalWrite(pinLED[i%4], HIGH);
    tone(buzzer_pin, tens[i], duree[i]);
    delay(duree[i]*1.3);
    noTone(buzzer_pin);
    digitalWrite(pinLED[i%4], LOW);
     
  }
  delay(500);
}

int butt_anim(){
  for (int i=0; i<4; i++){
    if (digitalRead(butt_pin[i])==LOW){
      digitalWrite(pinLED[i], HIGH);
      tone(buzzer_pin, tens[i], 500);

    }
    if (digitalRead(pinLED[i])==HIGH && digitalRead(butt_pin[i])==HIGH ){
      digitalWrite(pinLED[i], LOW);
      noTone(buzzer_pin);
      return i;
    }
    
  }
  return 10;

}

void blink(){
  display.clearDisplay();
  // right eye
  display.fillRoundRect(84, 22, 20, 5, 5, WHITE);
  // left eye
  display.fillRoundRect(44, 22, 20, 5, 5, WHITE);
  display.display();
  delay(75);


  // right eye
  display.fillRoundRect(84, 12, 20, 20, 5, WHITE);
  display.fillCircle(104, 0, 20, BLACK);
  // left eye
  display.fillRoundRect(44, 12, 20, 20, 5, WHITE);
  display.fillCircle(44, 0, 20, BLACK);
  display.display();
  delay(75);
  tear();

}

void tear(){
  for (int i=40; i<64; i=i+6){
    // dam3a right
    display.clearDisplay();
    display.fillRoundRect(84, 12, 20, 20, 5, WHITE);
    display.fillCircle(104, 0, 20, BLACK);
    // left eye
    display.fillRoundRect(44, 12, 20, 20, 5, WHITE);
    display.fillCircle(44, 0, 20, BLACK);


    display.fillCircle(94, i, 3, WHITE);
    // dam3a right
    display.fillCircle(54, i, 3, WHITE);
    delay(20);
    display.display();
  }

}






void loose(int* sc, int* p){
  Serial.println("U Lost :(");
  Serial.print("score : ");
  Serial.println(*sc-1);

  display.clearDisplay();
  display.setCursor(0,10);
  display.println("U Lost :(");
  display.println();
  display.print("score : ");
  display.println(*sc-1);
  display.display();

  for (int i=0; i<10; i++){
    digitalWrite(pinLED[i%4], HIGH);
    tone(buzzer_pin, tens[i], duree[i]);
    if (duree[i]==750) blink();
    else tear();
    digitalWrite(pinLED[i%4], LOW);
    noTone(buzzer_pin);
    if (duree[i]==750) blink();
    else tear();

  }

  while (1){
    int i = butt_anim();
    int j=10;
    int k = 10;
    int l = 10;
    while (i==0){
      j = butt_anim();
      if (j!=10 && j!=1){
        i=j;
      }
      Serial.println("1");
      while (j==1){
        k = butt_anim();
        if (k!=10 && k!=2){
          j=10;
          i=k;
        }
        Serial.println("2");
        while (k==2){
          l = butt_anim();
          if (l!=10 && l!=3){
            j=10;
            k=10;
            i=l;
          }
          Serial.println("3");
          while (l==3){
            Serial.println("new game");
            *sc = 0;
            *p = 0;
            return;

          }
        }
      }
    }
  }
}

void affiche(int* game, int* score){
  Serial.print("game : ");
  for (int i=0; i<score[0]; i++){
    Serial.print(couleur[game[i]]);
    Serial.print(" - ");
  }
  Serial.println();
}


void loop() {
  // put your main code here, to run repeatedly:
  if ((*play)==(*score)){
    play[0] =0;
    Serial.println("reinitialisé ");
    
    game[*score] = random(4);
    Serial.print("score : ");
    Serial.println(score[0]);
    
    display.clearDisplay();
    display.setCursor(0,10);
    display.print("score : ");
    display.println(score[0]);
    display.display();
    demons(score);
    *score = *score + 1;
    affiche(game, score);

  }
  int i = butt_anim();
  if ((i==1 || i==2 || i==3 || i==0)){
    if (game[play[0]] == i){
      *play = *play +1;
    }
    else if (i!=10){
      delay(350);
      loose(score, play);
      free(game);
      game = (int*)malloc(sizeof(int)*20);
      game[0] = random(4);
      delay(350);
    }
  
    //display.clearDisplay();
    display.setCursor(0,40);
    display.print(couleur[i]);
    display.display();
    
    Serial.print("Button N° ");
    Serial.print(i);
    Serial.println(" pressed");
    //delay(200);
    display.clearDisplay();
    display.setCursor(0,10);
    display.print("score : ");
    display.println(score[0]-1);
    display.display();
    
  }

}
