#define led_pin 13
#define fsr_pin A0

void setup()
{
  Serial.begin(115200);
  pinMode(led_pin, OUTPUT);
}

void loop()
{
  int fsr_value = analogRead(fsr_pin); // 讀取FSR
  int led_value = map(fsr_value, 0, 1023, 0, 255); // 從0~1023映射到0~255
  analogWrite(led_pin, led_value); // 改變LED亮度
  Serial.println(fsr_value);
  Serial.println(led_value);
  Serial.println("-------------");
  delay(100);
}



