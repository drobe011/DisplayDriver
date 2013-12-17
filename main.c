/*
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include "init.h"

#define TURN_ON 1
#define TURN_OFF 0

volatile uint8_t updateDisplay;
volatile uint8_t data[4];

int main(void)
{
    uint8_t state = TURN_ON;
    uint8_t currentDigit = 0, currentBit = 0;
    setupPorts();
    setupTimers();
    data[0] = ONE;
    data[1] = TWO;
    data[2] = THREE;
    data[3] = FOUR;

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
                break;

            case TURN_OFF:
                if (data[currentDigit] & _BV(currentBit))
                {
                    *displaySourcePin[displayDigit[currentDigit].Pin[0][currentBit]].mPORT &= ~_BV(displaySourcePin[displayDigit[currentDigit].Pin[0][currentBit]].mPin);
                    *displaySinkPin[displayDigit[currentDigit].Pin[1][currentBit]].mPORT &= ~_BV(displaySinkPin[displayDigit[currentDigit].Pin[1][currentBit]].mPin);
                }
                state = TURN_ON;
                if (currentBit == 7)
                {
                    (currentDigit == 3) ? currentDigit = 0 : currentDigit++;
                    currentBit = 0;
                }
                else currentBit++;

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
    OCR1A = 50;
    TIMSK1 = _BV(OCIE1A);
}

ISR(TIMER1_COMPA_vect)
{
    updateDisplay = 1;
}
