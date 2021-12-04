#include <Arduino.h>
#include <main.h>

/**
 *
 */
void setup()
{
    configure_serial();
    configure_gpio();
}

/**
 *
 */
void loop()
{
    play_relays();
}