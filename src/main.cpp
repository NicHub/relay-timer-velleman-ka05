#include <Arduino.h>
#include <main.h>

bool DIGITAL_CHANGE = false;
volatile uint8_t PIND_COPY = PIND;

/**
 *
 */
ISR(PCINT2_vect)
{
    DIGITAL_CHANGE = true;
}

/**
 *
 */
void setup()
{
    configure_serial();
    configure_gpio();
    configure_interrupts();
    blink(5, 10);
}

/**
 *
 */
void loop()
{
    static uint8_t relayValue = 0;
    static unsigned long now = 0;
    static unsigned long last_now = 0;
    now = millis();

    if (DIGITAL_CHANGE)
    {
        DIGITAL_CHANGE = false;
        if (now - last_now < 20)
            return;
        last_now = now;
        PIND_COPY = PIND;
        print8bitValueToSerial(&PIND_COPY);
        relayValue = 0;
        blink(5, 2);
        if (!bitRead(PIND_COPY, 2))
        {
            bitWrite(relayValue, 0, HIGH);
            play_relays();
        }
        if (!bitRead(PIND_COPY, 3))
        {
            bitWrite(relayValue, 1, HIGH);
        }
        if (!bitRead(PIND_COPY, 4))
        {
            bitWrite(relayValue, 2, HIGH);
        }
        if (!bitRead(PIND_COPY, 5))
        {
            bitWrite(relayValue, 3, HIGH);
        }
        if (!bitRead(PIND_COPY, 6))
        {
            bitWrite(relayValue, 4, HIGH);
        }
        if (!bitRead(PIND_COPY, 7))
        {
            bitWrite(relayValue, 5, HIGH);
        }
        relayWrite(&relayValue);
    }
}