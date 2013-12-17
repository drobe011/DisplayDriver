#ifndef INIT_H_INCLUDED
#define INIT_H_INCLUDED

#define SOURCEPINS 14
#define SINKPINS 3
#define DIGITS 4
//DIGIT BITMASKS
#define A_SEG 0
#define B_SEG 1
#define C_SEG 2
#define D_SEG 3
#define E_SEG 4
#define F_SEG 5
#define G_SEG 6

//SINK PINS
#define pin_1 0
#define pin_2 1
#define pin_3 2

//SOURCE PINS
#define pin_4 0
#define pin_5 1
#define pin_6 2
#define pin_9 3
#define pin_10 4
#define pin_12 5
#define pin_13 6
#define pin_15 7
#define pin_16 8
#define pin_17 9
#define pin_18 10
#define pin_19 11
#define pin_20 12
#define pin_21 13

#define EMPTY 99

void setupPorts();

typedef struct _pin
{
    volatile uint8_t * mDDR;
    volatile const uint8_t * mPORT;
    volatile const uint8_t mPin;
}_pin;

_pin displaySourcePin[SOURCEPINS] =
{
    {&DDRA, &PORTA, 0},
    {&DDRA, &PORTA, 1},
    {&DDRA, &PORTA, 2},
    {&DDRA, &PORTA, 3},
    {&DDRA, &PORTA, 4},
    {&DDRA, &PORTA, 5},
    {&DDRA, &PORTA, 6},
    {&DDRA, &PORTA, 7},
    {&DDRC, &PORTC, 0},
    {&DDRC, &PORTC, 1},
    {&DDRC, &PORTC, 2},
    {&DDRC, &PORTC, 3},
    {&DDRC, &PORTC, 4},
    {&DDRC, &PORTC, 5},
};

_pin displaySinkPin[SINKPINS] =
{
    {&DDRC, &PORTC, 6},
    {&DDRC, &PORTC, 7},
    {&DDRB, &PORTB, 0}
};

typedef struct _digit
{
    uint8_t Pin[2][8];
    //uint8_t display;
}_digit;

_digit displayDigit[DIGITS] =
{
    {{{EMPTY, pin_6, pin_9, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY}, {EMPTY, pin_2, pin_2, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY}},},
    {{{pin_13, pin_10, pin_12, pin_12, pin_9, pin_13, pin_10, EMPTY}, {pin_2, pin_2, pin_2, pin_1, pin_1, pin_1, pin_1, EMPTY}},},
    {{{pin_15, pin_16, pin_17, pin_17, pin_18, pin_15, pin_16, EMPTY}, {pin_1, pin_1, pin_1, pin_2, pin_2, pin_2, pin_2, EMPTY}},},
    {{{pin_21, pin_19, pin_20, pin_20, pin_18, pin_21, pin_19, EMPTY}, {pin_2, pin_2, pin_2, pin_1, pin_1, pin_1, pin_1, EMPTY}}}
};

#endif // INIT_H_INCLUDED
