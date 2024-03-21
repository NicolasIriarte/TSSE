#include "leds.h"
#include <stddef.h>

#include <stdio.h>

#define RETURN_IF_INVALID_ADDRESS(ADDR)                                        \
  if (ADDR == NULL)                                                            \
    return -1;

#define RETURN_IF_INVALID_RANGE(LED_ID)                                        \
  if (LED_ID < 1 || LED_ID > 16)                                               \
    return -1;

static uint16_t *leds_ = NULL;
static uint16_t state_;

enum { ALL_LEDS_OFF = 0, ALL_LEDS_ON = ~ALL_LEDS_OFF };

static int NumberToBit(int led_idx) { return 1 << (led_idx - 1); }

int Leds_Init(uint16_t *address) {
  RETURN_IF_INVALID_ADDRESS(address)

  leds_ = address;
  state_ = ALL_LEDS_OFF;
  *leds_ = state_;
  return 0;
};

int Leds_TurnOn(int led) {
  RETURN_IF_INVALID_RANGE(led);

  RETURN_IF_INVALID_ADDRESS(leds_);

  state_ |= NumberToBit(led);
  *leds_ = state_;
  return 0;
};

int Leds_TurnOff(int led) {
  RETURN_IF_INVALID_RANGE(led);
  RETURN_IF_INVALID_ADDRESS(leds_);

  state_ &= ~NumberToBit(led);
  *leds_ = state_;
  return 0;
};

int Led_TurnAllOn(void) {
  RETURN_IF_INVALID_ADDRESS(leds_);

  state_ = ALL_LEDS_ON;
  *leds_ = state_;
  return 0;
}

int Leds_IsLedOn(int led) {
  RETURN_IF_INVALID_RANGE(led);
  RETURN_IF_INVALID_ADDRESS(leds_);

  return state_ & NumberToBit(led);
}
