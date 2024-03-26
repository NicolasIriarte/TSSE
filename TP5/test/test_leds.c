#include "leds.h"
#include "unity.h"

static uint16_t leds_;

#define IDX_TO_BIT(idx) (1 << (idx - 1))

void setUp(void) {
    Leds_Init(&leds_);
}

void tearDown(void) {
}

// 1. Al iniciar el controlador los leds deben quedar todos los bits en 0 sin
// importar el estado anterior.
void test_LedsOffAfterCreate(void) {
    uint16_t leds = 0xFFFF;
    Leds_Init(&leds);
    TEST_ASSERT_EQUAL(0, leds);
}

// 2. Con todos los leds apagados prender el led 3 y verificar que efectivamente
// el bit 2 se pone en 1 y el resto de bit permanece en 0.
void test_TurnOnLedOne(void) {
    Leds_TurnOn(3);
    TEST_ASSERT_EQUAL(IDX_TO_BIT(3), leds_);
}

// 3. Apagar un led prendido y ver que efectivamente se apaga y que el resto no
// cambia.

// And

// 4. Con todos los leds apagados prender un led y verificar que al consultar el
// estado del mismo me informa que esta prendido.
void test_TurnOffLedOne(void) {
    Leds_TurnOn(1);
    TEST_ASSERT_EQUAL(1, leds_);
    Leds_TurnOff(1);
    TEST_ASSERT_EQUAL(0, leds_);
}

// 5. Se pueden prender varios leds al mismo tiempo
void test_TurnOnMultipleLeds(void) {
    Leds_TurnOn(8);
    Leds_TurnOn(9);
    TEST_ASSERT_EQUAL(0x0180, leds_);
}

// 6. Prender todos los leds que estan apagados con una unica operación
void test_TurnAllOn(void) {
    Led_TurnAllOn();
    TEST_ASSERT_EQUAL_HEX16(0xFFFF, leds_);
}

// 7. Se puede apagar un led en particular
void test_TurnOffAnyLed(void) {
    Led_TurnAllOn();
    Leds_TurnOff(7);
    TEST_ASSERT_EQUAL(0xFFBF, leds_);
}

// 8. Comprobar valores prohibidos
void test_InvalidValuesOnInit(void) {
    uint16_t leds = 0xFFFF;
    int init_value = Leds_Init(NULL);
    TEST_ASSERT_EQUAL(-1, init_value);

    init_value = Leds_Init(&leds);
    TEST_ASSERT_EQUAL(0, init_value);
}

void test_InvalidValuesOnTurnOn(void) {
    // Invalid index 0
    int turn_on_value = Leds_TurnOn(0);
    TEST_ASSERT_EQUAL(-1, turn_on_value);

    // Invalid index 17
    turn_on_value = Leds_TurnOn(17);
    TEST_ASSERT_EQUAL(-1, turn_on_value);

    // Valid index but driver uninitialized
    Leds_Init(NULL);

    turn_on_value = Leds_TurnOn(1);
    TEST_ASSERT_EQUAL(-1, turn_on_value);
}

void test_InvalidValuesOnTurnOff(void) {
    // Invalid index 0
    int turn_off_value = Leds_TurnOff(0);
    TEST_ASSERT_EQUAL(-1, turn_off_value);

    // Invalid index 17
    turn_off_value = Leds_TurnOff(17);
    TEST_ASSERT_EQUAL(-1, turn_off_value);

    // Valid index but driver uninitialized
    Leds_Init(NULL);

    turn_off_value = Leds_TurnOff(1);
    TEST_ASSERT_EQUAL(-1, turn_off_value);
}

void test_InvalidValuesOnTurnAllOn(void) {
    // Trying to turn all leds on with uninitialized driver
    Leds_Init(NULL);

    int turn_all_on_value = Led_TurnAllOn();
    TEST_ASSERT_EQUAL(-1, turn_all_on_value);
}

void test_InvalidValuesOnIsLedOn(void) {
    // Invalid index 0
    int is_led_on_value = Leds_IsLedOn(0);
    TEST_ASSERT_EQUAL(-1, is_led_on_value);

    // Invalid index 17
    is_led_on_value = Leds_IsLedOn(17);
    TEST_ASSERT_EQUAL(-1, is_led_on_value);

    // Valid index but driver uninitialized
    Leds_Init(NULL);

    is_led_on_value = Leds_IsLedOn(1);
    TEST_ASSERT_EQUAL(-1, is_led_on_value);
}

// 9. Se puede consultar el estado de un led en particular
void test_LedState(void) {
    Leds_TurnOn(3);
    TEST_ASSERT_EQUAL(1, Leds_IsLedOn(3));
    TEST_ASSERT_EQUAL(0, Leds_IsLedOn(4));
}
