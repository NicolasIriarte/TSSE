#include "leds.h"
#include <stddef.h>

static uint16_t *leds_ = NULL;
static uint16_t state_;

enum { ALL_LEDS_OFF = 0, ALL_LEDS_ON = ~ALL_LEDS_OFF };

static int NumberToBit(int led_idx) { return 1 << (led_idx - 1); }

int Leds_Init(uint16_t *address) {
  if (address == NULL)
    return -1;
  leds_ = address;
  state_ = ALL_LEDS_OFF;
  *leds_ = state_;
  return 0;
};

int Leds_TurnOn(int led) {
  if (led < 1 || led > 16) {
    return -1;
  }
  if (leds_ == NULL) {
    return -1;
  }

  state_ |= NumberToBit(led);
  *leds_ = state_;
  return 0;
};

int Leds_TurnOff(int led) {
  if (led < 1 || led > 16) {
    return -1;
  }
  if (leds_ == NULL) {
    return -1;
  }

  state_ &= ~NumberToBit(led);
  *leds_ = state_;
  return 0;
};

int Led_TurnAllOn(void) {
  if (leds_ == NULL) {
    return -1;
  }
  state_ = ALL_LEDS_ON;
  *leds_ = state_;
  return 0;
}
