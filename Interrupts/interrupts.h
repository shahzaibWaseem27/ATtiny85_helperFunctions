#include <avr/io.h>
#include <avr/interrupt.h>

#define RISING 1
#define FALLING 0


void configureExternaInterruptTrigger(char trigger){

    DDRB &= ~(1 << PB2);
    sei();
    GIMSK |= (1 << INT0);

    switch(trigger){

        case RISING:

            MCUCR |= (1 << ISC01) | (1 << ISC00);
            break;
        
        case FALLING:

            MCUCR |= (1 << ISC01);
            MCUCR &= ~(1 << ISC00);
            break;

    }

}

void configurePinChangeInterrupt(int pin){

    sei();
    GIMSK |= (1 << PCIE);

    switch(pin){

        case 0:

            DDRB &= ~(1 << PB0);
            PCMSK |= (1 << PCINT0);
            break;

        case 1:

            DDRB &= ~(1 << PB1);
            PCMSK |= (1 << PCINT1);
            break;

        case 2:

            DDRB &= ~(1 << PB2);
            PCMSK |= (1 << PCINT2);
            break;
        
        case 3:

            DDRB &= ~(1 << PB3);
            PCMSK |= (1 << PCINT3);
            break;

        case 4:

            DDRB &= ~(1 << PB4);
            PCMSK |= (1 << PCINT4);
            break;

        case 5:

            DDRB &= ~(1 << PB5);
            PCMSK |= (1 << PCINT5);
            break;

    }

}
