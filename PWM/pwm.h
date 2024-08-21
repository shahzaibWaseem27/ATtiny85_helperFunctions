#include <avr/io.h>

void setTimerMode(char mode) {
    switch (mode) {
        case 'n':
        case 'N':
            // Normal mode
            TCCR0A &= ~((1 << WGM00) | (1 << WGM01));
            TCCR0B &= ~(1 << WGM02);
            break;

        case 'f':
        case 'F':
            // Fast PWM mode
            TCCR0A |= (1 << WGM00) | (1 << WGM01);
            TCCR0B &= ~(1 << WGM02);
            break;

        // Add more modes if needed
    }
}

void setTimerPrescalar(int prescalar) {
    switch (prescalar) {
        case 1:
            TCCR0B &= ~((1 << CS02) | (1 << CS01));
            TCCR0B |= (1 << CS00);
            break;

        case 8:
            TCCR0B &= ~((1 << CS02) | (1 << CS00));
            TCCR0B |= (1 << CS01);
            break;

        case 64:
            TCCR0B &= ~(1 << CS02);
            TCCR0B |= (1 << CS01) | (1 << CS00);
            break;

        case 256:
            TCCR0B |= (1 << CS02);
            TCCR0B &= ~((1 << CS01) | (1 << CS00));
            break;

        case 1024:
            TCCR0B |= (1 << CS02);
            TCCR0B &= ~(1 << CS01);
            TCCR0B |= (1 << CS00);
            break;

        // Add more prescalars if needed
    }
}

void configureLogicChangePWM(char logicChange, char PWMpin) {
    switch (logicChange) {
        case 's':
        case 'S':  // Set on match
            if (PWMpin == 'A' || PWMpin == 'a') {
                TCCR0A |= (1 << COM0A1) | (1 << COM0A0);
            } else if (PWMpin == 'B' || PWMpin == 'b') {
                TCCR0A |= (1 << COM0B1) | (1 << COM0B0);
            }
            break;

        case 'r':
        case 'R':  // Clear on match
            if (PWMpin == 'A' || PWMpin == 'a') {
                TCCR0A |= (1 << COM0A1);
                TCCR0A &= ~(1 << COM0A0);
            } else if (PWMpin == 'B' || PWMpin == 'b') {
                TCCR0A |= (1 << COM0B1);
                TCCR0A &= ~(1 << COM0B0);
            }
            break;

        // Add more modes if needed
    }
}

void setPWMDutyCycle(int dutyCycleVal, char pinPWM) {
    // Correct calculation of the ratio for the 8-bit timer
    int ratioForMCU = (dutyCycleVal * 255) / 100;

    if (pinPWM == 'A' || pinPWM == 'a') {
        OCR0A = ratioForMCU;
    } else if (pinPWM == 'B' || pinPWM == 'b') {
        OCR0B = ratioForMCU;
    }
}
