#include "leds.h"

static uint16_t *leds_;
static uint16_t state_;

enum { ALL_LEDS_OFF = 0, ALL_LEDS_ON = ~ALL_LEDS_OFF };

static int NumberToBit(int led_idx) { return 1 << (led_idx - 1); }

void Leds_Init(uint16_t *address) {
  leds_ = address;
  state_ = ALL_LEDS_OFF;
  *leds_ = state_;
};

void Leds_TurnOn(int led) {
  state_ |= NumberToBit(led);
  *leds_ = state_;
};

void Leds_TurnOff(int led) {
  state_ &= ~NumberToBit(led);
  *leds_ = state_;
};

void Led_TurnAllOn(void) {
  state_ = ALL_LEDS_ON;
  *leds_ = state_;
}
