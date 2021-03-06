#ifndef INIT_H_INCLUDED
#define INIT_H_INCLUDED

#define SOURCEPINS 14
#define SINKPINS 3
#define ANUNCPINS 2
#define DIGITS 4
#define SOURCE 0
#define SINK 1

//DIGIT BITMASKS
#define A_SEG 0
#define B_SEG 1
#define C_SEG 2
#define D_SEG 3
#define E_SEG 4
#define F_SEG 5
#define G_SEG 6

#define ONE _BV(B_SEG) | _BV(C_SEG)
#define TWO _BV(A_SEG) | _BV(B_SEG) | _BV(G_SEG) | _BV(E_SEG) | _BV(D_SEG)
#define THREE _BV(A_SEG) | _BV(B_SEG) | _BV(C_SEG) | _BV(D_SEG) | _BV(G_SEG)
#define FOUR _BV(B_SEG) | _BV(C_SEG) | _BV(F_SEG) | _BV(G_SEG)
#define FIVE _BV(A_SEG) | _BV(C_SEG) | _BV(D_SEG) | _BV(F_SEG) | _BV(G_SEG)
#define SIX _BV(A_SEG) | _BV(C_SEG) | _BV(D_SEG) | _BV(E_SEG) | _BV(F_SEG) | _BV(G_SEG)
#define SEVEN _BV(A_SEG) | _BV(B_SEG) | _BV(C_SEG)
#define EIGHT _BV(A_SEG) | _BV(B_SEG) | _BV(C_SEG) | _BV(D_SEG) | _BV(E_SEG) | _BV(F_SEG) | _BV(G_SEG)
#define NINE _BV(A_SEG) | _BV(B_SEG) | _BV(C_SEG) | _BV(D_SEG) | _BV(F_SEG) | _BV(G_SEG)
#define ZERO _BV(A_SEG) | _BV(B_SEG) | _BV(C_SEG) | _BV(D_SEG) | _BV(E_SEG) | _BV(F_SEG)

//SINK PINS
#define PIN_1 0
#define PIN_2 1
#define PIN_3 2

//SOURCE PINS
#define PIN_4 0
#define PIN_5 1
#define PIN_6 2
#define PIN_9 3
#define PIN_10 4
#define PIN_12 5
#define PIN_13 6
#define PIN_15 7
#define PIN_16 8
#define PIN_17 9
#define PIN_18 10
#define PIN_19 11
#define PIN_20 12
#define PIN_21 13

#define EMPTY 0

void setupPorts();
void setupTimers();
extern uint8_t currentDigit;
extern uint8_t currentBit;

typedef struct _pin
{
    volatile uint8_t *mDDR;
    volatile uint8_t *mPORT;
    volatile uint8_t mPin;
}_pin;

_pin sourcePin[SOURCEPINS] =
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
    {&DDRC, &PORTC, 5}
};

_pin sinkPin[SINKPINS] =
{
    {&DDRC, &PORTC, 6},
    {&DDRC, &PORTC, 7},
    {&DDRB, &PORTB, 0}
};

_pin anuncPin[ANUNCPINS] =
{
    {&DDRD, &PORTD, 5},
    {&DDRD, &PORTD, 7}
};

typedef struct _digit
{
    uint8_t Pin[2][8];
}_digit;

_digit portMap[DIGITS] = //+ANUNCPINS] =
{
    {{{EMPTY, PIN_6, PIN_9, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY}, {EMPTY, PIN_2, PIN_2, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY}},},
    {{{PIN_13, PIN_10, PIN_12, PIN_12, PIN_9, PIN_13, PIN_10, EMPTY}, {PIN_2, PIN_2, PIN_2, PIN_1, PIN_1, PIN_1, PIN_1, EMPTY}},},
    {{{PIN_15, PIN_16, PIN_17, PIN_17, PIN_18, PIN_15, PIN_16, EMPTY}, {PIN_1, PIN_1, PIN_1, PIN_2, PIN_2, PIN_2, PIN_2, EMPTY}},},
    {{{PIN_21, PIN_19, PIN_20, PIN_20, PIN_18, PIN_21, PIN_19, EMPTY}, {PIN_2, PIN_2, PIN_2, PIN_1, PIN_1, PIN_1, PIN_1, EMPTY}}}
    //{{{PIN_5, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY}, {PIN_1, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY}},},
    //{{{PIN_4, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY}, {PIN_3, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY}},},
};

__inline void currentSegmentOn()
{
    *sourcePin[portMap[currentDigit].Pin[SOURCE][currentBit]].mPORT |= _BV(sourcePin[portMap[currentDigit].Pin[SOURCE][currentBit]].mPin);
    *sinkPin[portMap[currentDigit].Pin[SINK][currentBit]].mPORT |= _BV(sinkPin[portMap[currentDigit].Pin[SINK][currentBit]].mPin);
}

__inline void currentSegmentOff()
{
    *sourcePin[portMap[currentDigit].Pin[SOURCE][currentBit]].mPORT &= ~_BV(sourcePin[portMap[currentDigit].Pin[SOURCE][currentBit]].mPin);
    *sinkPin[portMap[currentDigit].Pin[SINK][currentBit]].mPORT &= ~_BV(sinkPin[portMap[currentDigit].Pin[SINK][currentBit]].mPin);
}
#endif // INIT_H_INCLUDED
