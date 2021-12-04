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
    PIND_COPY = PIND;
}

/**
 *
 */
void setup()
{
    configure_serial();
    configure_gpio();
    configure_interrupts();
    play_relays();
}

/**
 *
 */
void loop()
{
    static unsigned long time = 0;
    static unsigned long last_time = 0;
    time = millis();

    if (DIGITAL_CHANGE)
    {
        DIGITAL_CHANGE = false;
        if (time - last_time < 100)
            return;
        last_time = time;
        print8bitValueToSerial(&PIND_COPY);
        if (!bitRead(PIND_COPY, 2))
        {
            Serial.println("PIN 2 is ON");
        }
        if (!bitRead(PIND_COPY, 3))
        {
            Serial.println("PIN 3 is ON");
        }
        if (!bitRead(PIND_COPY, 4))
        {
            Serial.println("PIN 4 is ON");
        }
        if (!bitRead(PIND_COPY, 5))
        {
            Serial.println("PIN 5 is ON");
        }
        if (!bitRead(PIND_COPY, 6))
        {
            Serial.println("PIN 6 is ON");
        }
        if (!bitRead(PIND_COPY, 7))
        {
            Serial.println("PIN 7 is ON");
        }
    }
}