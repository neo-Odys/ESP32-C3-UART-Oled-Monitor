#include <Arduino.h>
#include <U8g2lib.h>


#include <Wire.h>

#define SDA_PIN 5
#define SCL_PIN 6


U8G2_SSD1306_72X40_ER_F_HW_I2C small_oled(U8G2_R0, /* reset=*/U8X8_PIN_NONE);
U8G2_SSD1312_128X64_NONAME_F_SW_I2C big_oled(U8G2_R2, /* clock=*/9, /* data=*/8, /* reset=*/U8X8_PIN_NONE);

U8G2LOG u8g2log;
#define U8LOG_WIDTH 32
#define U8LOG_HEIGHT 10

uint8_t u8log_buffer[U8LOG_WIDTH * U8LOG_HEIGHT];

void setup(void) {
  Serial.begin(9600);
  Serial.setTimeout(10);

  Wire.begin(SDA_PIN, SCL_PIN);
  Wire.setClock(400000);
  small_oled.begin();
  big_oled.begin();

  small_oled.clearBuffer();
  small_oled.setFont(u8g2_font_ncenB08_tr);
  small_oled.drawStr(0, 10, "baud rate:");
  small_oled.drawStr(0, 20, "9600");

  small_oled.sendBuffer();

  big_oled.clearBuffer();
  //https://github.com/olikraus/u8g2/wiki/fntlist8
  //big_oled.setFont(u8g2_font_tom_thumb_4x6_mf);
  big_oled.setFont(  u8g2_font_tiny5duo_tf);
  big_oled.drawStr(0, 10, "baud rate:");  
  //big_oled.setFont(u8g2_font_squeezed_b6_tr);
  big_oled.sendBuffer();
  u8g2log.begin(big_oled, U8LOG_WIDTH, U8LOG_HEIGHT, u8log_buffer);

  u8g2log.setLineHeightOffset(0);  // set extra space between lines in pixel, this can be negative
  u8g2log.setRedrawMode(0);        // 1 - every char, 0 - whole string at once

}

void loop(void) {



  if (Serial.available() > 0) {
    String receivedText = "";

    while (Serial.available() > 0) {
      String temp = Serial.readStringUntil('\n');
      temp.trim();
      if (temp.length() > 0) {
        receivedText = temp;
      }
    }

    if (receivedText.length() > 0) {
      u8g2log.print(receivedText);
      u8g2log.print("\n");
    }
  }
}