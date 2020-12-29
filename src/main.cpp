#include <Arduino.h>
#include <NeoPixelBus.h>

constexpr int pixel_count = 1;

/* Uses pin GPIO3 on esp8266 due to hardware issues. This is pin RXit . */
NeoPixelBus<NeoRgbFeature, Neo800KbpsMethod> pixels{pixel_count};

void setup() {
  Serial.begin(9600);

  pixels.Begin();
  pixels.Show();
}

static void updateLEDs(uint8_t v1, uint8_t v2, uint8_t v3) {
  pixels.SetPixelColor(0, RgbColor(v1, v2, v3));
  pixels.Show();
}

void loop() {
  updateLEDs(255, 20, 20);
  delay(1000);
  updateLEDs(20, 255, 20);
  delay(1000);
  updateLEDs(20, 20, 255);
  delay(1000);
}
