#pragma once

#define RELAY_COUNT 6

/**
 *
 */
void configure_gpio()
{
#if defined(__AVR_ATmega328P__)
    // The relays are on PORTB 0 to 5
    // (Arduino pins 8 to 13).
    // So set these pins to OUPUT.
    DDRB |= (1u << 0) | (1u << 1) | (1u << 2) | (1u << 3) | (1u << 4) | (1u << 5);

    // The analog inputs are on PORTC 0 to 5
    // (Arduino pins A0 to A5).
    // So set these pins to INPUT.
    DDRC &= ~(1u << 0) & ~(1u << 1) & ~(1u << 2) & ~(1u << 3) & ~(1u << 4) & ~(1u << 5);

    // The digital inputs are on PORTD 2 to 7
    // (Arduino pins 2 to 7).
    // So set these pins to INPUT.
    DDRD &= ~(1u << 2) & ~(1u << 3) & ~(1u << 4) & ~(1u << 5) & ~(1u << 6) & ~(1u << 7);
#endif

#if defined(__AVR_ATmega2560__)
    // Set relay pins to output.
    bitWrite(DDRB, DDB7, 1); // Pin 13
    bitWrite(DDRB, DDB6, 1); // Pin 12
    bitWrite(DDRB, DDB5, 1); // Pin 11
    bitWrite(DDRB, DDB4, 1); // Pin 10
    bitWrite(DDRH, DDH6, 1); // Pin  9
    bitWrite(DDRH, DDH5, 1); // Pin  8

    // Set analog input pins to input
    bitWrite(DDRF, DDF5, 0); // Pin A5
    bitWrite(DDRF, DDF4, 0); // Pin A4
    bitWrite(DDRF, DDF3, 0); // Pin A3
    bitWrite(DDRF, DDF2, 0); // Pin A2
    bitWrite(DDRF, DDF1, 0); // Pin A1
    bitWrite(DDRF, DDF0, 0); // Pin A0

    // Set digital input pins to input
    bitWrite(DDRE, DDE4, 0); // Pin 7
    bitWrite(DDRE, DDE5, 0); // Pin 6
    bitWrite(DDRG, DDG5, 0); // Pin 5
    bitWrite(DDRE, DDE3, 0); // Pin 4
    bitWrite(DDRH, DDH3, 0); // Pin 3
    bitWrite(DDRH, DDH4, 0); // Pin 2
#endif
}

/**
 *
 */
void configure_serial()
{
    // Write the settings to serial output.
    // Beware that PORTD0 and PORTD1 are both used for serial
    // communication and for LED GPIOs. That means that they cannot
    // work together and we need to close the serial port as
    // soon as we have written the information below.
    Serial.begin(BAUD_RATE);
    Serial.println(F("\n\n\n# RELAY TIMER\n"));
    Serial.print(F("FILE NAME:        "));
    Serial.println(__FILE__);
    Serial.print(F("COMPILATION DATE: "));
    Serial.println(COMPILATION_DATE);
    Serial.print(F("COMPILATION TIME: "));
    Serial.println(COMPILATION_TIME);
    Serial.println("");

    Serial.print(F("TCCR1A: B"));
    Serial.println(TCCR1A, BIN);
    Serial.print(F("TCCR1B: B"));
    Serial.println(TCCR1B, BIN);
    Serial.print(F("TIMSK1: B"));
    Serial.println(TIMSK1, BIN);
    Serial.print(F("OCIE1A: B"));
    Serial.println(OCIE1A, BIN);
    Serial.println("");

    float prescaler =
        bitRead(TCCR1B, CS10) * 1 +
        bitRead(TCCR1B, CS11) * 2 +
        bitRead(TCCR1B, CS12) * 4;
    float period_ms = prescaler / F_CPU * (OCR1A + 1);

    Serial.print(F("OCR1A:             "));
    Serial.println(OCR1A);
    Serial.print(F("PRESCALER N:       "));
    Serial.println(prescaler);
    Serial.print(F("CPU PERIOD (ns):   "));
    Serial.println(1.0 / float(F_CPU) * 1E9, 2);
    Serial.print(F("CPU FREQ (MHz):    "));
    Serial.println(F_CPU / 1E6);
    Serial.print(F("TIMER PERIOD (ms): "));
    Serial.println(period_ms * 1000.0, 6);
    Serial.print(F("TIMER FREQ (Hz):   "));
    Serial.println(1 / period_ms, 1);
    Serial.println(F(""));
}

/**
 *
 */
void relayPrintValuesToSerial(uint8_t *relayValues)
{
    for (int8_t cnt = 0; cnt < RELAY_COUNT; cnt++)
    {
        Serial.print(bitRead(*relayValues, cnt));
        Serial.print(" ");
    }
    Serial.println("");
}

/**
 *
 */
void relayWrite(uint8_t *relayValues)
{
    // In Velleman documentation, the relays
    // are numbered from 1 to 6.
    // But in this program, they are numbered
    // from 0 to 5.

    relayPrintValuesToSerial(relayValues);

#if defined(__AVR_ATmega328P__)
    static uint16_t newPortB = 0;
    newPortB = PORTB;
    for (int8_t cnt = 0; cnt < RELAY_COUNT; cnt++)
        bitWrite(newPortB, cnt, bitRead(*relayValues, cnt));
    PORTB = newPortB;
#endif

#if defined(__AVR_ATmega2560__)
    bitWrite(PORTB, PORTB7, bitRead(*relayValues, 5)); // Pin 13
    bitWrite(PORTB, PORTB6, bitRead(*relayValues, 4)); // Pin 12
    bitWrite(PORTB, PORTB5, bitRead(*relayValues, 3)); // Pin 11
    bitWrite(PORTB, PORTB4, bitRead(*relayValues, 2)); // Pin 10
    bitWrite(PORTH, PORTH6, bitRead(*relayValues, 1)); // Pin  9
    bitWrite(PORTH, PORTH5, bitRead(*relayValues, 0)); // Pin  8
#endif
}

/**
 *
 */
void play_relays()
{
    static uint8_t relayValue = 0;

    bitWrite(relayValue, 0, HIGH);
    relayWrite(&relayValue);
    delay(50);
    bitWrite(relayValue, 1, HIGH);
    relayWrite(&relayValue);
    delay(50);
    bitWrite(relayValue, 2, HIGH);
    relayWrite(&relayValue);
    delay(50);
    bitWrite(relayValue, 3, HIGH);
    relayWrite(&relayValue);
    delay(50);
    bitWrite(relayValue, 4, HIGH);
    relayWrite(&relayValue);
    delay(50);
    bitWrite(relayValue, 5, HIGH);
    relayWrite(&relayValue);
    delay(50);

    bitWrite(relayValue, 0, LOW);
    relayWrite(&relayValue);
    delay(50);
    bitWrite(relayValue, 1, LOW);
    relayWrite(&relayValue);
    delay(50);
    bitWrite(relayValue, 2, LOW);
    relayWrite(&relayValue);
    delay(50);
    bitWrite(relayValue, 3, LOW);
    relayWrite(&relayValue);
    delay(50);
    bitWrite(relayValue, 4, LOW);
    relayWrite(&relayValue);
    delay(50);
    bitWrite(relayValue, 5, LOW);
    relayWrite(&relayValue);
    delay(200);

    bitWrite(relayValue, 5, HIGH);
    relayWrite(&relayValue);
    delay(50);
    bitWrite(relayValue, 4, HIGH);
    relayWrite(&relayValue);
    delay(50);
    bitWrite(relayValue, 3, HIGH);
    relayWrite(&relayValue);
    delay(50);
    bitWrite(relayValue, 2, HIGH);
    relayWrite(&relayValue);
    delay(50);
    bitWrite(relayValue, 1, HIGH);
    relayWrite(&relayValue);
    delay(50);
    bitWrite(relayValue, 0, HIGH);
    relayWrite(&relayValue);
    delay(50);

    bitWrite(relayValue, 5, LOW);
    relayWrite(&relayValue);
    delay(50);
    bitWrite(relayValue, 4, LOW);
    relayWrite(&relayValue);
    delay(50);
    bitWrite(relayValue, 3, LOW);
    relayWrite(&relayValue);
    delay(50);
    bitWrite(relayValue, 2, LOW);
    relayWrite(&relayValue);
    delay(50);
    bitWrite(relayValue, 1, LOW);
    relayWrite(&relayValue);
    delay(50);
    bitWrite(relayValue, 0, LOW);
    relayWrite(&relayValue);
    delay(200);

    bitWrite(relayValue, 5, HIGH);
    relayWrite(&relayValue);
    bitWrite(relayValue, 0, HIGH);
    relayWrite(&relayValue);
    delay(50);
    bitWrite(relayValue, 4, HIGH);
    relayWrite(&relayValue);
    bitWrite(relayValue, 1, HIGH);
    relayWrite(&relayValue);
    delay(50);
    bitWrite(relayValue, 3, HIGH);
    relayWrite(&relayValue);
    bitWrite(relayValue, 2, HIGH);
    relayWrite(&relayValue);
    delay(200);

    bitWrite(relayValue, 3, LOW);
    relayWrite(&relayValue);
    bitWrite(relayValue, 2, LOW);
    relayWrite(&relayValue);
    delay(50);
    bitWrite(relayValue, 4, LOW);
    relayWrite(&relayValue);
    bitWrite(relayValue, 1, LOW);
    relayWrite(&relayValue);
    delay(50);
    bitWrite(relayValue, 5, LOW);
    relayWrite(&relayValue);
    bitWrite(relayValue, 0, LOW);
    relayWrite(&relayValue);
    delay(200);

    bitWrite(relayValue, 5, HIGH);
    relayWrite(&relayValue);
    bitWrite(relayValue, 4, HIGH);
    relayWrite(&relayValue);
    bitWrite(relayValue, 3, HIGH);
    relayWrite(&relayValue);
    bitWrite(relayValue, 2, HIGH);
    relayWrite(&relayValue);
    bitWrite(relayValue, 1, HIGH);
    relayWrite(&relayValue);
    bitWrite(relayValue, 0, HIGH);
    relayWrite(&relayValue);
    delay(200);

    bitWrite(relayValue, 5, LOW);
    relayWrite(&relayValue);
    bitWrite(relayValue, 4, LOW);
    relayWrite(&relayValue);
    bitWrite(relayValue, 3, LOW);
    relayWrite(&relayValue);
    bitWrite(relayValue, 2, LOW);
    relayWrite(&relayValue);
    bitWrite(relayValue, 1, LOW);
    relayWrite(&relayValue);
    bitWrite(relayValue, 0, LOW);
    relayWrite(&relayValue);
    delay(200);

    bitWrite(relayValue, 5, HIGH);
    relayWrite(&relayValue);
    bitWrite(relayValue, 4, HIGH);
    relayWrite(&relayValue);
    bitWrite(relayValue, 3, HIGH);
    relayWrite(&relayValue);
    bitWrite(relayValue, 2, HIGH);
    relayWrite(&relayValue);
    bitWrite(relayValue, 1, HIGH);
    relayWrite(&relayValue);
    bitWrite(relayValue, 0, HIGH);
    relayWrite(&relayValue);
    delay(50);

    bitWrite(relayValue, 5, LOW);
    relayWrite(&relayValue);
    bitWrite(relayValue, 4, LOW);
    relayWrite(&relayValue);
    bitWrite(relayValue, 3, LOW);
    relayWrite(&relayValue);
    bitWrite(relayValue, 2, LOW);
    relayWrite(&relayValue);
    bitWrite(relayValue, 1, LOW);
    relayWrite(&relayValue);
    bitWrite(relayValue, 0, LOW);
    relayWrite(&relayValue);
    delay(50);

    bitWrite(relayValue, 5, HIGH);
    relayWrite(&relayValue);
    bitWrite(relayValue, 4, HIGH);
    relayWrite(&relayValue);
    bitWrite(relayValue, 3, HIGH);
    relayWrite(&relayValue);
    bitWrite(relayValue, 2, HIGH);
    relayWrite(&relayValue);
    bitWrite(relayValue, 1, HIGH);
    relayWrite(&relayValue);
    bitWrite(relayValue, 0, HIGH);
    relayWrite(&relayValue);
    delay(50);

    bitWrite(relayValue, 5, LOW);
    relayWrite(&relayValue);
    bitWrite(relayValue, 4, LOW);
    relayWrite(&relayValue);
    bitWrite(relayValue, 3, LOW);
    relayWrite(&relayValue);
    bitWrite(relayValue, 2, LOW);
    relayWrite(&relayValue);
    bitWrite(relayValue, 1, LOW);
    relayWrite(&relayValue);
    bitWrite(relayValue, 0, LOW);
    relayWrite(&relayValue);
    delay(50);

    bitWrite(relayValue, 5, HIGH);
    relayWrite(&relayValue);
    bitWrite(relayValue, 4, HIGH);
    relayWrite(&relayValue);
    bitWrite(relayValue, 3, HIGH);
    relayWrite(&relayValue);
    bitWrite(relayValue, 2, HIGH);
    relayWrite(&relayValue);
    bitWrite(relayValue, 1, HIGH);
    relayWrite(&relayValue);
    bitWrite(relayValue, 0, HIGH);
    relayWrite(&relayValue);
    delay(50);

    bitWrite(relayValue, 5, LOW);
    relayWrite(&relayValue);
    bitWrite(relayValue, 4, LOW);
    relayWrite(&relayValue);
    bitWrite(relayValue, 3, LOW);
    relayWrite(&relayValue);
    bitWrite(relayValue, 2, LOW);
    relayWrite(&relayValue);
    bitWrite(relayValue, 1, LOW);
    relayWrite(&relayValue);
    bitWrite(relayValue, 0, LOW);
    relayWrite(&relayValue);
    delay(50);

    bitWrite(relayValue, 5, HIGH);
    relayWrite(&relayValue);
    bitWrite(relayValue, 4, HIGH);
    relayWrite(&relayValue);
    bitWrite(relayValue, 3, HIGH);
    relayWrite(&relayValue);
    bitWrite(relayValue, 2, HIGH);
    relayWrite(&relayValue);
    bitWrite(relayValue, 1, HIGH);
    relayWrite(&relayValue);
    bitWrite(relayValue, 0, HIGH);
    relayWrite(&relayValue);
    delay(50);

    bitWrite(relayValue, 5, LOW);
    relayWrite(&relayValue);
    bitWrite(relayValue, 4, LOW);
    relayWrite(&relayValue);
    bitWrite(relayValue, 3, LOW);
    relayWrite(&relayValue);
    bitWrite(relayValue, 2, LOW);
    relayWrite(&relayValue);
    bitWrite(relayValue, 1, LOW);
    relayWrite(&relayValue);
    bitWrite(relayValue, 0, LOW);
    relayWrite(&relayValue);
    delay(50);

    bitWrite(relayValue, 5, HIGH);
    relayWrite(&relayValue);
    bitWrite(relayValue, 4, HIGH);
    relayWrite(&relayValue);
    bitWrite(relayValue, 3, HIGH);
    relayWrite(&relayValue);
    bitWrite(relayValue, 2, HIGH);
    relayWrite(&relayValue);
    bitWrite(relayValue, 1, HIGH);
    relayWrite(&relayValue);
    bitWrite(relayValue, 0, HIGH);
    relayWrite(&relayValue);
    delay(50);

    bitWrite(relayValue, 5, LOW);
    relayWrite(&relayValue);
    bitWrite(relayValue, 4, LOW);
    relayWrite(&relayValue);
    bitWrite(relayValue, 3, LOW);
    relayWrite(&relayValue);
    bitWrite(relayValue, 2, LOW);
    relayWrite(&relayValue);
    bitWrite(relayValue, 1, LOW);
    relayWrite(&relayValue);
    bitWrite(relayValue, 0, LOW);
    relayWrite(&relayValue);
    delay(200);
}
