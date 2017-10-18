#include<Wire.h>
#include<SPI.h>
#include<Adafruit_GFX.h>
#include<Adafruit_SSD1306.h>

#define led_pin 13
#define fsr_pin A0

#define OLED_MOSI   11 //D1
#define OLED_CLK   12 //D0
#define OLED_DC    9 //DC
#define OLED_CS    8 //CS
#define OLED_RESET 10 //RES
Adafruit_SSD1306 display(OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);
int logo = 1;


static const uint8_t imageVarName[] PROGMEM = {
  B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, 
  B00000000, B00000000, B00000000, B00001000, B00000000, B00000000, B00000000, B00000000, 
  B00000000, B00000000, B00000000, B00011110, B00000000, B00000000, B00000000, B00000000, 
  B00000000, B00000000, B00000000, B00111111, B10000000, B00000000, B00000000, B00000000, 
  B00000000, B00000000, B00000000, B11111111, B11000000, B00000000, B00000000, B00000000, 
  B00000000, B00000000, B00000000, B11111111, B11000000, B00000000, B00000000, B00000000, 
  B00000000, B00000000, B00000000, B00001111, B10000000, B00000000, B00000000, B00000000, 
  B00000000, B00000000, B00000000, B00001111, B11000000, B00000000, B00000000, B00000000, 
  B00000000, B00000000, B00000000, B00011111, B11000000, B00000000, B00000000, B00000000, 
  B00000000, B00000000, B00000000, B00111111, B10000000, B00000000, B00000000, B00000000, 
  B00000000, B00000000, B00001100, B01111111, B10000000, B00000000, B00000000, B00000000, 
  B00000000, B00000000, B00001111, B11111111, B10000010, B00000000, B00000000, B00000000, 
  B00000000, B00000000, B00010011, B11111111, B00000111, B00000000, B00000000, B00000000, 
  B00000000, B00000000, B00011111, B11111100, B00000110, B00000000, B00000000, B00000000, 
  B00000000, B00000000, B00111111, B11111110, B00000011, B00000000, B00000000, B00000000, 
  B00000000, B00000000, B00011001, B11111111, B00000011, B00000000, B00000000, B00000000, 
  B00000000, B00000000, B00001000, B11111111, B10000011, B00000000, B00000000, B00000000, 
  B00000000, B00000000, B00001000, B01111111, B11000011, B00000000, B00000000, B00000000, 
  B00000000, B00000000, B00000100, B00111111, B11100011, B00000000, B00000000, B00000000, 
  B00000000, B00000000, B00000100, B00011111, B11111110, B00000000, B00000000, B00000000, 
  B00000000, B00000000, B00000000, B00001111, B11111100, B00000000, B00000000, B00000000, 
  B00000000, B00000000, B00000000, B00001111, B11111100, B00000000, B00000000, B00000000, 
  B00000000, B00000000, B00000000, B00001111, B11101100, B00000000, B00000000, B00000000, 
  B00000000, B00000000, B00000000, B00000111, B11001000, B00000000, B00000000, B00000000, 
  B00000000, B00000000, B00000001, B11110111, B10000000, B00000000, B00000000, B00000000, 
  B00000000, B00000000, B00000000, B10011111, B10000000, B00000000, B00000000, B00000000, 
  B00000000, B00000000, B00000000, B00000001, B10000000, B00000000, B00000000, B00000000, 
  B00000000, B00000000, B00000000, B00000001, B10000000, B00000000, B00000000, B00000000, 
  B00000000, B00000000, B00000000, B00000011, B00000000, B00000000, B00000000, B00000000, 
  B00000000, B00000000, B00000000, B00000110, B00000000, B00000000, B00000000, B00000000, 
  B00000000, B00000000, B00000000, B00001100, B00000000, B00000000, B00000000, B00000000, 
  B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, 
  
};

static const unsigned char PROGMEM Logo[] = {
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x0f,0x80,0x00,0x00,0x00,
  0x00,0x00,0x01,0xff,0xfc,0x00,0x00,0x00,
  0x00,0x01,0xf3,0xff,0xfe,0x7c,0x00,0x00,
  0x00,0x01,0xfb,0xfc,0xff,0x7c,0x00,0x00,
  0x00,0x01,0xfb,0xf0,0x7e,0x7c,0x00,0x00,
  0x00,0x01,0xd8,0xfd,0xfc,0xdc,0x00,0x00,
  0x00,0x00,0xee,0x7f,0xf3,0xbc,0x00,0x00,
  0x00,0x00,0xf3,0x1f,0xe6,0x7c,0x00,0x00,
  0x00,0x00,0xf9,0xcf,0x8c,0xf8,0x00,0x00,
  0x00,0x00,0xee,0xe7,0x1b,0xb8,0x00,0x00,
  0x00,0x00,0xf3,0x68,0x36,0x78,0x00,0x00,
  0x00,0x00,0x7d,0xed,0xbc,0xf0,0x00,0x00,
  0x00,0x00,0x3e,0x7f,0xb3,0xe0,0x00,0x00,
  0x00,0x00,0x0f,0xb7,0xb7,0x80,0x00,0x00,
  0x00,0x00,0x67,0xf7,0x7f,0x30,0x00,0x00,
  0x00,0x00,0x71,0xe7,0x3c,0x70,0x00,0x00,
  0x00,0x00,0x78,0x07,0x00,0x70,0x00,0x00,
  0x00,0x00,0x38,0x07,0x00,0x70,0x00,0x00,
  0x00,0x00,0x3c,0x37,0x61,0xf0,0x00,0x00,
  0x00,0x00,0x3e,0x77,0x73,0xf0,0x00,0x00,
  0x00,0x00,0x3e,0xf7,0x7b,0xf0,0x00,0x00,
  0x00,0x00,0x3e,0xf7,0x7b,0xe0,0x00,0x00,
  0x00,0x00,0x3e,0xf6,0x7b,0xe0,0x00,0x00,
  0x00,0x00,0x3e,0xf0,0x7b,0xe0,0x00,0x00,
  0x00,0x00,0x3e,0xff,0xfb,0xe0,0x00,0x00,
  0x00,0x00,0x1e,0xff,0xfb,0xc0,0x00,0x00,
  0x00,0x00,0x06,0xe0,0x3b,0x00,0x00,0x00,
  0x00,0x00,0x02,0xef,0x3a,0x00,0x00,0x00,
  0x00,0x00,0x00,0xcf,0xb8,0x00,0x00,0x00,
  0x00,0x00,0x00,0x1f,0x80,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
};

void setup()
{
  Serial.begin(115200);
  pinMode(led_pin, OUTPUT);
  display.begin(SSD1306_SWITCHCAPVCC);
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
}

void loop()
{
  int fsr_value = analogRead(fsr_pin); // 讀取FSR
  int led_value = map(fsr_value, 0, 1023, 0, 255); // 從0~1023映射到0~255
  //analogWrite(led_pin, led_value); // 改變LED亮度
  if(led_value <= 50 && logo != 1){
    Show_1();
    logo = 1;
  }
  if(led_value > 50 && logo != 2){
    Show_2();
    logo = 2;
  }
  if(led_value > 10 && led_value <= 20) digitalWrite(2,true);
  else digitalWrite(2,false);
  if(led_value > 20 && led_value <= 30) digitalWrite(3,true);
  else digitalWrite(3,false);
  if(led_value > 30 && led_value <= 40) digitalWrite(4,true);
  else digitalWrite(4,false);
  if(led_value > 40 && led_value <= 50) digitalWrite(5,true);
  else digitalWrite(5,false);
  if(led_value > 50 && led_value <= 60) digitalWrite(6,true);
  else digitalWrite(6,false);
  if(led_value > 60 && led_value <= 70) digitalWrite(7,true);
  else digitalWrite(7,false);
  Serial.println(fsr_value);
  Serial.println(led_value);
  Serial.println("-------------");
  delay(100);
}

void Show_1(){
  display.drawBitmap(23,0,imageVarName,64 ,32,WHITE);
  display.display();
  display.clearDisplay();
}

void Show_2(){
  display.drawBitmap(23,0,Logo,64 ,32,WHITE);
  display.display();
  display.clearDisplay();
}
