/*
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include "init.h"

#define TURN_ON 1
#define TURN_OFF 0
#define TEST

volatile uint8_t updateDisplay;
volatile uint16_t sysTicker;
uint8_t currentDigit, currentBit;

int main(void)
{
    uint8_t state = 0;
    uint8_t digitNum = 0;
    const uint8_t digitData[] = {ZERO, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE};
    uint8_t data[DIGITS];
    data[0] = digitData[1];
    data[1] = digitData[3];

    setupPorts();
    setupTimers();

    sei();

    while(1)
    {
        if (updateDisplay)
        {
            switch (state)
            {
            case TURN_ON:
                if (data[currentDigit] & _BV(currentBit)) currentSegmentOn();
                state = TURN_OFF;
                break;

            case TURN_OFF:
                if (data[currentDigit] & _BV(currentBit)) currentSegmentOff();
                if (currentDigit == (DIGITS-1)) currentDigit = 0;
                else
                {
                    currentDigit++;
                    currentBit++;
                }
                (currentBit == sizeof(currentBit)*8) ? currentBit = 0 : currentBit;
                state = TURN_ON;
                break;
            }
            updateDisplay = 0;

        }
        #ifdef TEST
        if (sysTicker > 3999)
        {
            digitNum = (digitNum == 9) ? 0 : digitNum+1;
            data[1] = digitData[digitNum];
            sysTicker = 0;
        }
        #endif // TEST
    }

    return 0;
}

void setupPorts()
{
    uint8_t loop = 0;
    for (loop = 0; loop < SOURCEPINS; loop++)
    {
        *sourcePin[loop].mDDR |= _BV(sourcePin[loop].mPin);
    }
    for (loop = 0; loop < SINKPINS; loop++)
    {
        *sinkPin[loop].mDDR |= _BV(sinkPin[loop].mPin);
    }
//    for (loop = 0; loop < ANUNCPINS; loop++)
//    {
//        *displayAnuncPin[loop].mDDR |= _BV(displayAnuncPin[loop].mPin);
//    }
}

void setupTimers()
{
    TCCR1A = 0;
    TCCR1B = _BV(WGM12) | _BV(CS11); //CTC, PRESCALER AT 8
    OCR1A = 499; //2KHz, EACH SEG UPDATED AT 60HZ
    TIMSK1 = _BV(OCIE1A);
}

ISR(TIMER1_COMPA_vect)
{
    updateDisplay = 1;
    sysTicker++;
}
