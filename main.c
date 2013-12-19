/*
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include "init.h"

#define TURN_ON 1
#define TURN_OFF 0

volatile uint8_t updateDisplay = 1;
volatile uint16_t secs;
uint8_t data[DIGITS+ANUNCPINS];

int main(void)
{
    uint8_t state = 0;
    uint8_t currentDigit = 0, currentBit = 0, digitNum = 0;
    const uint8_t digitData[] = {ZERO, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE};

    setupPorts();
    setupTimers();
    data[0] = digitData[1];
    data[1] = TWO;
    data[2] = THREE;
    data[3] = FOUR;
    data[4] = 1;
    data[5] = 1;


    sei();
    while(1)
    {
        if (updateDisplay)
        {
            switch (state)
            {
            case TURN_ON:
                if (data[currentDigit] & _BV(currentBit))
                {
                    *displaySourcePin[displayDigit[currentDigit].Pin[0][currentBit]].mPORT |= _BV(displaySourcePin[displayDigit[currentDigit].Pin[0][currentBit]].mPin);
                    *displaySinkPin[displayDigit[currentDigit].Pin[1][currentBit]].mPORT |= _BV(displaySinkPin[displayDigit[currentDigit].Pin[1][currentBit]].mPin);
                }
                state = TURN_OFF;
                updateDisplay = 0;
                break;

            case TURN_OFF:
                if (data[currentDigit] & _BV(currentBit))
                {
                    *displaySourcePin[displayDigit[currentDigit].Pin[0][currentBit]].mPORT &= ~_BV(displaySourcePin[displayDigit[currentDigit].Pin[0][currentBit]].mPin);
                    *displaySinkPin[displayDigit[currentDigit].Pin[1][currentBit]].mPORT &= ~_BV(displaySinkPin[displayDigit[currentDigit].Pin[1][currentBit]].mPin);
                }
                state = TURN_ON;
                if (currentDigit == (DIGITS-1)) currentDigit = 0;
                else
                {
                    currentDigit++;
                    currentBit++;
                }

                if (currentBit == 8) currentBit = 0;
                break;
            }

        }
        if (secs > 999)
        {
            digitNum = (digitNum == 9) ? 0 : digitNum+1;
            data[1] = digitData[digitNum];
            secs = 0;
        }
    }

    return 0;
}

void setupPorts()
{
    uint8_t loop = 0;
    for (loop = 0; loop < SOURCEPINS; loop++)
    {
        *displaySourcePin[loop].mDDR |= _BV(displaySourcePin[loop].mPin);
    }
    for (loop = 0; loop < SINKPINS; loop++)
    {
        *displaySinkPin[loop].mDDR |= _BV(displaySinkPin[loop].mPin);
    }
    for (loop = 0; loop < ANUNCPINS; loop++)
    {
        *displayAnuncPin[loop].mDDR |= _BV(displayAnuncPin[loop].mPin);
    }
}

void setupTimers()
{
    TCCR1A = 0;
    TCCR1B = _BV(WGM12) | _BV(CS10);
    OCR1A = 7999; //1KHz
    TIMSK1 = _BV(OCIE1A);
}

ISR(TIMER1_COMPA_vect)
{
    updateDisplay = 1;
    secs++;
}
