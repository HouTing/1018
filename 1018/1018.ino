#include<Wire.h>
#include<SPI.h>
#include<Adafruit_GFX.h>
#include<Adafruit_SSD1306.h>

#define OLED_MOSI 11//d1
#define OLED_CLK 12//D0
#define OLED_DC 13//DC
#define OLED_CS 9//CS
#define OLED_RESET 10//RES
Adafruit_SSD1306 display(OLED_MOSI,OLED_CLK,OLED_DC,OLED_RESET,OLED_CS);
const int ledCount = 10; // the number of LEDs in the bar graph
int ledPins[] = { 2, 3, 4, 5, 6, 7, 8};
#define fsr_pin A0
static const unsigned char PROGMEM Logo[] = {
 B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, 
  B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, 
  B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, 
  B00000000, B00000000, B00000000, B00001111, B11110000, B00000000, B00000000, B00000000, 
  B00000000, B00000000, B00000111, B11111110, B01111111, B11100000, B00000000, B00000000, 
  B00000000, B00000000, B00111111, B11110000, B00001111, B11111100, B00000000, B00000000, 
  B00000000, B00000001, B11111111, B11111000, B00011111, B11111111, B10000000, B00000000, 
  B00000000, B00000111, B11111111, B00001000, B00010000, B11111111, B11100000, B00000000, 
  B00000000, B00001111, B11111000, B00000000, B00000000, B00011111, B11110000, B00000000, 
  B00000000, B00110011, B11111100, B00000000, B00000000, B00111111, B11101100, B00000000, 
  B00000000, B01110001, B11111110, B11110000, B00001111, B01111111, B10001110, B00000000, 
  B00000000, B01100000, B00000110, B00010000, B00000101, B01100000, B00000111, B00000000, 
  B00000000, B11000000, B00011000, B10100110, B01110100, B00011100, B00000011, B00000000, 
  B00000000, B10000000, B01110100, B00100000, B00000100, B10101110, B00000001, B10000000, 
  B00000001, B00110001, B11110100, B10000000, B00000001, B00101111, B10001100, B10000000, 
  B00000000, B00000011, B11110010, B01000000, B00001001, B01001111, B11000000, B00000000, 
  B00000000, B01100011, B11111010, B01001100, B00110010, B01011111, B11000110, B00000000, 
  B00000000, B00000111, B11111010, B01001000, B00010010, B01001111, B11100000, B00000000, 
  B00000000, B01100111, B11100100, B10010000, B00001001, B00000111, B11100111, B00000000, 
  B00000000, B00001111, B11001011, B00100000, B00000110, B01001011, B11110000, B00000000, 
  B00000000, B01100011, B10010010, B01100000, B00000010, B01001001, B11100110, B00000000, 
  B00000000, B00001100, B00001001, B00100000, B00000100, B10010000, B00010000, B00000000, 
  B00000000, B00000000, B00011100, B10001000, B00011001, B00111000, B00000000, B00000000, 
  B00000000, B00000100, B11111010, B01001100, B00010010, B01011111, B00110000, B00000000, 
  B00000000, B00000001, B01110100, B01001100, B00010011, B00101110, B11000000, B00000000, 
  B00000000, B00000000, B01101100, B10011000, B00011001, B10010010, B00000000, B00000000, 
  B00000000, B00000000, B00001001, B00110000, B00001100, B11010000, B00000000, B00000000, 
  B00000000, B00000000, B00000000, B00100000, B00000100, B00000000, B00000000, B00000000, 
  B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, 
  B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, 
  B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, 
  B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000,
};
static const unsigned char PROGMEM Logo1[] = {
B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, 
  B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, 
  B00000000, B00000000, B01100110, B01101111, B10001100, B11001101, B00000000, B00000000, 
  B00000000, B00000000, B11110110, B01101111, B10011110, B11011001, B00000000, B00000000, 
  B00000000, B00000001, B10010110, B01101100, B00110010, B11011001, B00000000, B00000000, 
  B00000000, B00000001, B10000110, B01101100, B00110000, B11010001, B00000000, B00000000, 
  B00000000, B00000001, B10000110, B01101100, B00110000, B11110001, B00000000, B00000000, 
  B00000000, B00000001, B10000111, B11101111, B10110000, B11110001, B00000000, B00000000, 
  B00000000, B00000001, B10000111, B11101111, B10110000, B11110001, B00000000, B00000000, 
  B00000000, B00000001, B10000110, B01101100, B00110000, B11110001, B00000000, B00000000, 
  B00000000, B00000001, B10000110, B01101100, B00110000, B11011001, B00000000, B00000000, 
  B00000000, B00000001, B10010110, B01101100, B00110010, B11011000, B00000000, B00000000, 
  B00000000, B00000000, B11110110, B01101111, B10011110, B11001001, B10000000, B00000000, 
  B00000000, B00000000, B01100110, B01101111, B10001100, B11001101, B10000000, B00000000, 
  B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, 
  B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, 
  B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, 
  B00000000, B00000000, B00000000, B11111111, B11111000, B00000000, B00000000, B00000000, 
  B00000000, B00000000, B00000000, B10000000, B00000100, B00000000, B00000000, B00000000, 
  B00000000, B00000000, B00000000, B10000010, B00000100, B00000000, B00000000, B00000000, 
  B00000000, B00000000, B00000000, B00000111, B00000100, B00000000, B00000000, B00000000, 
  B00000000, B00000000, B00000000, B10000100, B10000110, B00000000, B00000000, B00000000, 
  B00000000, B00000000, B00000000, B10000001, B10000110, B00000000, B00000000, B00000000, 
  B00000000, B00000000, B00000000, B10000001, B10000110, B00000000, B00000000, B00000000, 
  B00000000, B00000000, B00000000, B10001010, B10000110, B00000000, B00000000, B00000000, 
  B00000000, B00000000, B00000000, B10000110, B10000110, B00000000, B00000000, B00000000, 
  B00000000, B00000000, B00000000, B10000100, B10000110, B00000000, B00000000, B00000000, 
  B00000000, B00000000, B00000000, B00000111, B00000100, B00000000, B00000000, B00000000, 
  B00000000, B00000000, B00000000, B10000010, B00000100, B00000000, B00000000, B00000000, 
  B00000000, B00000000, B00000000, B10000000, B00000100, B00000000, B00000000, B00000000, 
  B00000000, B00000000, B00000000, B11111111, B11111000, B00000000, B00000000, B00000000, 
  B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, 
};
void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  display.begin(SSD1306_SWITCHCAPVCC);
  display.clearDisplay();
  display.drawBitmap(30,0,Logo,64,32,WHITE);
  display.display();

  Serial.begin(115200);
  for (int thisLed = 0; thisLed < ledCount; thisLed++) {
    pinMode(ledPins[thisLed], OUTPUT);
    }
}

void loop() {
  // put your main code here, to run repeatedly:
  int fsr_value = analogRead(fsr_pin); // 讀取FSR
  int led_value = map(fsr_value, 0, 1023, 0, 10); // 從0~1023映射到0~10
  for (int thisLed = 0; thisLed < ledCount;
  thisLed++) {
  if (thisLed < led_value) {
    digitalWrite(ledPins[thisLed], HIGH);
    }
    else {
      digitalWrite(ledPins[thisLed], LOW);
      }
   }
   if(led_value>3){
     display.clearDisplay();
     display.drawBitmap(-2,0,Logo1,128 ,32,WHITE);
     display.display();
   }
   else{
    display.clearDisplay();
    display.drawBitmap(30,0,Logo,64,32,WHITE);
    display.display();
   }
}


