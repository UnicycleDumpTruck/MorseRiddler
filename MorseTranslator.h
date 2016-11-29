#ifndef MORSE_TRANSLATOR_H
#define MORSE_TRANSLATOR_H

#include "Arduino.h"

class MorseTranslator
{
    public:
        MorseTranslator();
        void emit(char);
        void tinyTone(unsigned char divisor, unsigned char octave, unsigned long duration);
        
    private:
        void dot();
        void dash();
        void endLetter();
        void space();
};

#endif
