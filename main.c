/*
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include "init.h"

#define TURN_ON 1
#define TURN_OFF 0

volatile uint8_t updateDisplay;
uint8_t data[DIGITS+ANUNCPINS];

int main(void)
{
    uint8_t state = TURN_ON;
    uint8_t currentDigit = 0, currentBit = 0;
    setupPorts();
    setupTimers();
    data[0] = ONE;
    data[1] = NINE;
    data[2] = THREE;
    data[3] = FOUR;
    data[4] = 1;
    data[5] = 1;


    sei();
    while(1)
    {
        if (updateDisplay)
        {
            TIMSK1 = 0;
            switch (state)
            {
            case TURN_ON:
                if (data[currentDigit] & _BV(currentBit))
                {
                    *displaySourcePin[displayDigit[currentDigit].Pin[0][currentBit]].mPORT |= _BV(displaySourcePin[displayDigit[currentDigit].Pin[0][currentBit]].mPin);
                    *displaySinkPin[displayDigit[currentDigit].Pin[1][currentBit]].mPORT |= _BV(displaySinkPin[displayDigit[currentDigit].Pin[1][currentBit]].mPin);
                }
                state = TURN_OFF;
                //OCR1A = 40000;
                break;

            case TURN_OFF:
                *displaySourcePin[displayDigit[currentDigit].Pin[0][currentBit]].mPORT &= ~_BV(displaySourcePin[displayDigit[currentDigit].Pin[0][currentBit]].mPin);
                *displaySinkPin[displayDigit[currentDigit].Pin[1][currentBit]].mPORT &= ~_BV(displaySinkPin[displayDigit[currentDigit].Pin[1][currentBit]].mPin);
                state = TURN_ON;
                if (currentBit > 6)
                {
                    (currentDigit == (DIGITS-1)) ? currentDigit = 0 : currentDigit++;
                    currentBit = 0;
                }
                else currentBit++;
                //OCR1A = 100;

                break;
            }
            updateDisplay = 0;
            TCNT1 = 0;
            TIMSK1 = _BV(OCIE1A);
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
    TCCR1B = _BV(WGM12) | _BV(CS11);
    OCR1A = 1200;
    TIMSK1 = _BV(OCIE1A);
}

ISR(TIMER1_COMPA_vect)
{
    updateDisplay = 1;
}
