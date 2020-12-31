#include <Arduino.h>
#include <NeoPixelBus.h>

constexpr int pixel_count = 3;
constexpr int led_count = pixel_count * 3;

/* Uses pin GPIO3 on esp8266 due to hardware issues. This is pin RXit . */
NeoPixelBus<NeoRgbFeature, Neo800KbpsMethod> pixels{pixel_count};

void setup() {
  Serial.begin(9600);

  pixels.Begin();
  pixels.ClearTo(RgbColor(0));
  pixels.Show();
}

static void set_led_color(int led, uint8_t value) {
  const int pixel_index = led / 3;
  const int channel_index = 2 - (led % 3);
  RgbColor color = pixels.GetPixelColor(pixel_index);
  ((uint8_t *)&color)[channel_index] = value;
  pixels.SetPixelColor(pixel_index, color);
}

static void led_effect__all_off(const int delay_in_ms) {
  pixels.ClearTo(RgbColor(0));
  pixels.Show();
  delay(delay_in_ms);
}

static void led_effect__enable_one_after_the_other(const int delay_in_ms) {
  pixels.ClearTo(RgbColor(0));
  for (int i = 0; i < led_count; i++) {
    set_led_color(i, 255);
    pixels.Show();
    delay(delay_in_ms);
  }
}

static void led_effect__shift_single(const int delay_in_ms) {
  for (int i = 0; i < led_count; i++) {
    pixels.ClearTo(RgbColor(0));
    set_led_color(i, 255);
    pixels.Show();
    delay(delay_in_ms);
  }
}

void loop() {
  led_effect__all_off(100);
  led_effect__enable_one_after_the_other(100);
  led_effect__shift_single(100);
}
