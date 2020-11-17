/* *************FT_light*************
           Разработал FT Xivan
   По вопросам и идеям писать на почту asuste035@gmail.com
               ВНИМАНИЕ!!!
      Если вы подключаете
*/

#include <FastLED.h> //Подключаем все нужные библиотеки
#include <GyverButton.h>

//*********Настройки********

//*********СВЕТОДИОДНАЯ ЛЕНТА********

#define NUM_LEDS 16 // КОЛИЧЕСТВО СВЕТОДИОДОВ
#define DATA_PIN 7 // ПИН ЛЕНТЫ (НУ КУДА ТЫ ПОДКЛЮЧАЛ , У МЕНЯ D7)

//**********КНОПКА СЕНСОРНАЯ*********

#define butt 5 // ПИН КНОПКИ (НУ У МЕНЯ D5)
#define timeout_b 600 // ДАЙ ОТДОХНУТЬ КНОПКЕ, ТАЙМАУТ (по умолчанию 600 МСЕК)

//**************МИКРОФОН*************

#define MP_PIN 3 // ПИН МИКРОФОНА (У МЕНЯ А3)

//*****НАСТРОЙКИ ДЛЯ КАСТОМИЗАЦИИ****

#define BRIGHTSESS 210 // ЯРКОСТЬ СТАНДАРТНАЯ, РЕКОМЕНДУЮ 210 
#define COLORS_STANDARD 3 // 1 = ЗЕЛЕНЫЙ , 2 = КРАСНЫЙ , 3 = СИНИЙ
#define SPEED_RAINBOW 5 // СКОРОСТЬ РАДУГИ (ЧЕМ БОЛЬШЕ ТЕМ МЕДЛЕНЕЕ)
#define SPEED_FADE 9 // СКОРОСТЬ FADE ИЗМЕНЕНИЕЯРК (ЧЕМ БОЛЬШЕ ТЕМ МЕДЛЕНЕЕ)

// ТАМ ВНИЗУ КОД

int color;
int effect;
int rainbow_val;
int brig_fade;
int color_rand;

GButton button(butt);
CRGB leds[NUM_LEDS];

void off() {
  for (int i = 0; i < NUM_LEDS; i++) {
    if (color == 0) {
      leds[i] = CRGB::Black;
    }
  }
}

void music() {
  FastLED.setBrightness(210);
  color = analogRead(MP_PIN);
  color = map(color, 10 , 600 , 0 , 3);
  for (int i = 0; i < NUM_LEDS; i++) {
    if (color == 0) {
      leds[i] = CRGB::Red;
    }
    if (color == 1) {
      leds[i] = CRGB::Black;
    }
    if (color == 2) {
      leds[i] = CRGB::Green;
    }
    if (color == 3) {
      leds[i] = CRGB::Blue;
    }
  }
}

void rainbow() {
  FastLED.setBrightness(210);
  for (int i = 0; i < NUM_LEDS; i++ ) {
    leds[i] = CHSV(rainbow_val + i * 2, 255, 255);
  }
  rainbow_val++;
  delay(SPEED_RAINBOW);
}

void colors() {
  FastLED.setBrightness(210);
  if (COLORS_STANDARD == 1) {
    for (int i = 0; i < NUM_LEDS; i++ ) {
      leds[i] = CRGB::Green;
    }
  }
  if (COLORS_STANDARD == 2) {
    for (int i = 0; i < NUM_LEDS; i++ ) {
      leds[i] = CRGB::Red;
    }
  }
  if (COLORS_STANDARD == 3) {
    for (int i = 0; i < NUM_LEDS; i++ ) {
      leds[i] = CRGB::Blue;
    }
  }
}

void fade() {
  if (COLORS_STANDARD == 1) {
    for (int i = 0; i < NUM_LEDS; i++ ) {
      leds[i] = CRGB::Green;
    }
  }
  if (COLORS_STANDARD == 2) {
    for (int i = 0; i < NUM_LEDS; i++ ) {
      leds[i] = CRGB::Red;
    }
  }
  if (COLORS_STANDARD == 3) {
    for (int i = 0; i < NUM_LEDS; i++ ) {
      leds[i] = CRGB::Blue;
    }
  }
  brig_fade++;
  if (brig_fade == 210) brig_fade = 0;
  delay(SPEED_FADE);
  FastLED.setBrightness(brig_fade);
}

void randoms() {
  for (int i = 0; i < NUM_LEDS; i++ ) {
    color_rand = random(0, 255);
    leds[i] = CHSV(color_rand, 255, 255);
    delay(7);
  }
}

void setup() {
  Serial.begin(9600);
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(210);
  button.setClickTimeout(600);
  button.setType(HIGH_PULL);
}

void loop() {
  button.tick();
  if (button.isClick()) effect++;
  if (effect == 7) effect = 0;
  Serial.println(effect);
  switch (effect) {
    case 0: off();
      break;
    case 1: music();
      break;
    case 2: rainbow();
      break;
    case 3: colors();
      break;
    case 4: fade();
      break;
    case 5: randoms();
      break;
  }
  FastLED.show();
}
