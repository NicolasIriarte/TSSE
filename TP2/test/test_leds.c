/*

 * 2. Con todos los leds apagados prender el led 3 y verificar que efectivamente
 *   el bit 2 se pone en 1 y el resto de bit permanece en 0.
 * 3. Apagar un led prendido y ver que efectivamente se apaga y que el resto no
 *   cambia.
 * 4. Con todos los leds apagados prender un led y verificar que al consultar el
 *   estado del mismo me informa que esta prendido.
 * 5. Prender todos los leds que estan apagados antes de la operación
 * 6. Apagar todos los leds que ya estan prendidos
 * 7. Prender leds que ya esten prendidos de antes
 * 8. Apagar leds que ya esten apagados
 * 9. Comprobar valores prohibidos
 * 10. Comprobar los valores de limite
 */

#include "leds.h"
#include "unity.h"

static uint16_t ledsVirtuales;

void setUp(void) { Leds_Init(&ledsVirtuales); }

void tearDown(void) {}

// 1. Al iniciar el controlador los leds deben quedar todos los bits en 0 sin
// importar el estado anterior.
void test_LedsOffAfterCreate(void) {
  uint16_t leds = 0xFFFF;
  Leds_Init(&leds);
  TEST_ASSERT_EQUAL_HEX16(0, leds);
}

void test_TurnOnLedOne(void) {
  Leds_TurnOn(1);
  TEST_ASSERT_EQUAL_HEX16(1, ledsVirtuales);
}

void test_TurnOffLedOne(void) {
  Leds_TurnOn(1);
  Leds_TurnOff(1);
  TEST_ASSERT_EQUAL_HEX16(0, ledsVirtuales);
}

void test_TurnOnMultipleLeds(void) {
  Leds_TurnOn(8);
  Leds_TurnOn(9);
  TEST_ASSERT_EQUAL_HEX16(0x0180, ledsVirtuales);
}

void test_TurnOffAnyLed(void) {
  Led_TurnAllOn();
  Leds_TurnOff(8);
  TEST_ASSERT_EQUAL_HEX16(0xFF7F, ledsVirtuales);
}

void test_TurnAllOn(void) {
  Led_TurnAllOn();
  TEST_ASSERT_EQUAL_HEX16(0xFFFF, ledsVirtuales);
}

void test_LedMemoryIsNotReadable(void) {
  ledsVirtuales = 0xFFFF;
  Leds_TurnOn(8);
  TEST_ASSERT_EQUAL_HEX16(0x0080, ledsVirtuales);
}
