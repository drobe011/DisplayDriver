/*
 */

#include <avr/io.h>
#include "init.h"

int main(void)
{

    // Insert code

    while(1)
    ;

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
}
