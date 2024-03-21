#include <avr/io.h>

void setTimerMode(char mode){

  switch(mode){

    case 'n':
    case 'N':

      TCCR0A &= ~((1 << WGM02) & (1 << WGM01) & (1 << WGM00));
      break;

    case 'f':
    case 'F':

      TCCR0A &= ~(1 << WGM02);
      TCCR0A |= (1 << WGM01) | (1 << WGM00);
      break;

  }

}

void setTimerPrescalar(int prescalar){

  switch(prescalar){

    case 1:

      TCCR0B &= ~(1 << CS02);
      TCCR0B &= ~(1 << CS01);
      TCCR0B |= (1 << CS00);
      break;
    
    case 8:

      TCCR0B &= ~(1 << CS02);
      TCCR0B |= (1 << CS01);
      TCCR0B &= ~(1 << CS00);
      break;
    
    case 64:

      TCCR0B &= ~(1 << CS02);
      TCCR0B |= (1 << CS01);
      TCCR0B |= (1 << CS00);
      break;

    case 256:

      TCCR0B |= (1 << CS02);
      TCCR0B &= ~(1 << CS01);
      TCCR0B &= ~(1 << CS00);
      break;

    case 1024:

      TCCR0B |= (1 << CS02);
      TCCR0B &= ~(1 << CS01);
      TCCR0B |= (1 << CS00);
      break;

  }

}

void configureLogicChangePWM(char logicChange, char PWMpin){

  switch(logicChange){

    case 's':
    case 'S':

        switch(PWMpin){

            case 'A':
            case 'a':

                TCCR0A |= (1 << COM0A1) | (1 << COM0A0);
                break;

            case 'B':
            case 'b':

                TCCR0A |= (1 << COM0B1) | (1 << COM0B0);
                break;

        }

        break;

    case 'r':
    case 'R':
        switch(PWMpin){

            case 'A':
            case 'a':

                TCCR0A |= (1 << COM0A1);
                TCCR0A &= ~(1 << COM0A0);
                break;

            case 'B':
            case 'b':

                TCCR0A |= (1 << COM0B1);
                TCCR0A &= ~(1 << COM0B0);
                break;

        }

        break;   

  }

}

void setPWMDutyCycle(int dutyCycleVal, char pinPWM){

  int ratioForMCU = (dutyCycleVal/100) * 255;

  switch(pinPWM){

    case 'a':
    case 'A':

      OCR0A = ratioForMCU;
      break;

    case 'b':
    case 'B':

      OCR0B = ratioForMCU;
      break;

  }

}
