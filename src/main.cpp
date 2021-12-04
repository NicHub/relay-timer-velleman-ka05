#include <Arduino.h>

/**
 *
 */
void configure_gpio()
{
    // The relays are on PORTB 0 to 5
    // (Arduino pins 8 to 13).
    // So set these pins to OUPUT.
    DDRB |= (1u << 0) | (1u << 1) | (1u << 2) | (1u << 3) | (1u << 4) | (1u << 5);

    // The analog inputs are on PORTC 0 to 5
    // (Arduino pins A1 to A6).
    // So set these pins to INPUT.
    DDRC &= ~(1u << 0) & ~(1u << 1) & ~(1u << 2) & ~(1u << 3) & ~(1u << 4) & ~(1u << 5);

    // The digital inputs are on PORTD 1 to 6
    // (Arduino pins 2 to 7).
    // So set these pins to INPUT.
    DDRD &= ~(1u << 1) & ~(1u << 2) & ~(1u << 3) & ~(1u << 4) & ~(1u << 5) & ~(1u << 6);
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
void setup()
{
    configure_serial();
    configure_gpio();
}

/**
 *
 */
void play_relays()
{
    digitalWrite(8, HIGH);
    delay(50);
    digitalWrite(9, HIGH);
    delay(50);
    digitalWrite(10, HIGH);
    delay(50);
    digitalWrite(11, HIGH);
    delay(50);
    digitalWrite(12, HIGH);
    delay(50);
    digitalWrite(13, HIGH);
    delay(50);
    digitalWrite(8, LOW);
    delay(50);
    digitalWrite(9, LOW);
    delay(50);
    digitalWrite(10, LOW);
    delay(50);
    digitalWrite(11, LOW);
    delay(50);
    digitalWrite(12, LOW);
    delay(50);
    digitalWrite(13, LOW);
    delay(200);
    digitalWrite(13, HIGH);
    delay(50);
    digitalWrite(12, HIGH);
    delay(50);
    digitalWrite(11, HIGH);
    delay(50);
    digitalWrite(10, HIGH);
    delay(50);
    digitalWrite(9, HIGH);
    delay(50);
    digitalWrite(8, HIGH);
    delay(50);
    digitalWrite(13, LOW);
    delay(50);
    digitalWrite(12, LOW);
    delay(50);
    digitalWrite(11, LOW);
    delay(50);
    digitalWrite(10, LOW);
    delay(50);
    digitalWrite(9, LOW);
    delay(50);
    digitalWrite(8, LOW);
    delay(200);
    digitalWrite(13, HIGH);
    digitalWrite(8, HIGH);
    delay(50);
    digitalWrite(12, HIGH);
    digitalWrite(9, HIGH);
    delay(50);
    digitalWrite(11, HIGH);
    digitalWrite(10, HIGH);
    delay(200);
    digitalWrite(11, LOW);
    digitalWrite(10, LOW);
    delay(50);
    digitalWrite(12, LOW);
    digitalWrite(9, LOW);
    delay(50);
    digitalWrite(13, LOW);
    digitalWrite(8, LOW);
    delay(200);
    digitalWrite(13, HIGH);
    digitalWrite(12, HIGH);
    digitalWrite(11, HIGH);
    digitalWrite(10, HIGH);
    digitalWrite(9, HIGH);
    digitalWrite(8, HIGH);
    delay(200);
    digitalWrite(13, LOW);
    digitalWrite(12, LOW);
    digitalWrite(11, LOW);
    digitalWrite(10, LOW);
    digitalWrite(9, LOW);
    digitalWrite(8, LOW);
    delay(200);
    digitalWrite(13, HIGH);
    digitalWrite(12, HIGH);
    digitalWrite(11, HIGH);
    digitalWrite(10, HIGH);
    digitalWrite(9, HIGH);
    digitalWrite(8, HIGH);
    delay(50);
    digitalWrite(13, LOW);
    digitalWrite(12, LOW);
    digitalWrite(11, LOW);
    digitalWrite(10, LOW);
    digitalWrite(9, LOW);
    digitalWrite(8, LOW);
    delay(50);
    digitalWrite(13, HIGH);
    digitalWrite(12, HIGH);
    digitalWrite(11, HIGH);
    digitalWrite(10, HIGH);
    digitalWrite(9, HIGH);
    digitalWrite(8, HIGH);
    delay(50);
    digitalWrite(13, LOW);
    digitalWrite(12, LOW);
    digitalWrite(11, LOW);
    digitalWrite(10, LOW);
    digitalWrite(9, LOW);
    digitalWrite(8, LOW);
    delay(50);
    digitalWrite(13, HIGH);
    digitalWrite(12, HIGH);
    digitalWrite(11, HIGH);
    digitalWrite(10, HIGH);
    digitalWrite(9, HIGH);
    digitalWrite(8, HIGH);
    delay(50);
    digitalWrite(13, LOW);
    digitalWrite(12, LOW);
    digitalWrite(11, LOW);
    digitalWrite(10, LOW);
    digitalWrite(9, LOW);
    digitalWrite(8, LOW);
    delay(50);
    digitalWrite(13, HIGH);
    digitalWrite(12, HIGH);
    digitalWrite(11, HIGH);
    digitalWrite(10, HIGH);
    digitalWrite(9, HIGH);
    digitalWrite(8, HIGH);
    delay(50);
    digitalWrite(13, LOW);
    digitalWrite(12, LOW);
    digitalWrite(11, LOW);
    digitalWrite(10, LOW);
    digitalWrite(9, LOW);
    digitalWrite(8, LOW);
    delay(50);
    digitalWrite(13, HIGH);
    digitalWrite(12, HIGH);
    digitalWrite(11, HIGH);
    digitalWrite(10, HIGH);
    digitalWrite(9, HIGH);
    digitalWrite(8, HIGH);
    delay(50);
    digitalWrite(13, LOW);
    digitalWrite(12, LOW);
    digitalWrite(11, LOW);
    digitalWrite(10, LOW);
    digitalWrite(9, LOW);
    digitalWrite(8, LOW);
    delay(200);
}

/**
 *
 */
void play_relays_slow(int8_t val)
{
    static uint8_t cnt = 0;

    digitalWrite(13, HIGH);
    delay(100 + cnt++ * 6);
    digitalWrite(12, HIGH);
    delay(100 + cnt++ * 6);
    digitalWrite(11, HIGH);
    delay(100 + cnt++ * 6);
    digitalWrite(10, HIGH);
    delay(100 + cnt++ * 6);
    digitalWrite(9, HIGH);
    delay(100 + cnt++ * 6);
    digitalWrite(8, HIGH);
    delay(100 + cnt++ * 6);

    digitalWrite(8, LOW);
    delay(130 + cnt-- * 6);
    digitalWrite(9, LOW);
    delay(130 + cnt-- * 6);
    digitalWrite(10, LOW);
    delay(130 + cnt-- * 6);
    digitalWrite(11, LOW);
    delay(130 + cnt-- * 6);
    digitalWrite(12, LOW);
    delay(130 + cnt-- * 6);
    // digitalWrite(13, LOW);
    // delay(130 + cnt-- * 6);
}

/**
 *
 */
void loop()
{
    // play_relays_slow(LOW);
    // play_relays_slow(HIGH);
    play_relays();
}