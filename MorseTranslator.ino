#define TONE_DIVISOR 239
#define TONE_OCTAVE 6 
#define MORSE_UNIT 125 // 250 is 5wpm, 125 is 10wpm, 62 is 20wpm
#define LED_PIN 0

MorseTranslator::MorseTranslator()
{
  // No initialization.
}

// The following tinyTone function came from: http://www.technoblogy.com/show?KVO
void MorseTranslator::tinyTone(unsigned char divisor, unsigned char octave, unsigned long duration)
{
 // TCCR1 = 0x90 | (8-octave);  // for 1MHz clock
  TCCR1 = 0x90 | (11-octave);   // for 8MHz clock
  OCR1C = divisor-1;            // set the OCR
  delay(duration);              // wait while tone plays
  TCCR1 = 0x90;                 // stop the counter
}

void MorseTranslator::dot()
{
    digitalWrite(LED_PIN, HIGH);                    // turn LED on
    tinyTone(TONE_DIVISOR,TONE_OCTAVE,MORSE_UNIT);  // play tone for one morse unit
    digitalWrite(LED_PIN, LOW);                     // turn LED off
    delay(MORSE_UNIT);                              // leave a morse unit of silence after
}

void MorseTranslator::dash()
{
    digitalWrite(LED_PIN, HIGH);                          // turn LED on
    tinyTone(TONE_DIVISOR,TONE_OCTAVE,(3 * MORSE_UNIT));  // play tone for three morse units
    digitalWrite(LED_PIN, LOW);                           // turn LED off
    delay(MORSE_UNIT);                                    // leave a morse unit of silence after
}

void MorseTranslator::endLetter()
{
    delay(15 * MORSE_UNIT); // the space between letters is 3 morse units of silence
}

void MorseTranslator::space()
{
    delay(35 * MORSE_UNIT); // the space between words is 7 morse units of silence
}

void MorseTranslator::emit(char c)
{
    switch (c) { // depending on what the character is, do one of the following:
      case 'a':
        dot();
        dash();
        endLetter();
        break;
      case 'b':
        dash();
        dot();
        dot();
        dot();
        endLetter();
        break;
      case 'c':
        dash();
        dot();
        dash();
        dot();
        endLetter();
        break;
      case 'd':
        dash();
        dot();
        dot();
        endLetter();
        break;
      case 'e':
        dot();
        endLetter();
        break;
      case 'f':
        dot();
        dot();
        dash();
        dot();
        endLetter();
        break;
      case 'g':
        dash();
        dash();
        dot();
        endLetter();
        break;
      case 'h':
        dot();
        dot();
        dot();
        dot();
        endLetter();
        break;
      case 'i':
        dot();
        dot();
        endLetter();
        break;
      case 'j':
        dot();
        dash();
        dash();
        dash();
        endLetter();
        break;
      case 'k':
        dash();
        dot();
        dash();
        endLetter();
        break;
      case 'l':
        dot();
        dash();
        dot();
        dot();
        endLetter();
        break;
      case 'm':
        dash();
        dash();
        endLetter();
        break;
      case 'n':
        dash();
        dot();
        endLetter();
        break;
      case 'o':
        dash();
        dash();
        dash();
        endLetter();
        break;
      case 'p':
        dot();
        dash();
        dash();
        dot();
        endLetter();
        break;
      case 'q':
        dash();
        dash();
        dot();
        dash();
        endLetter();
        break;
      case 'r':
        dot();
        dash();
        dot();
        endLetter();
        break;
      case 's':
        dot();
        dot();
        dot();
        endLetter();
        break;
      case 't':
        dash();
        endLetter();
        break;
      case 'u':
        dot();
        dot();
        dash();
        endLetter();
        break;
      case 'v':
        dot();
        dot();
        dot();
        dash();
        endLetter();
        break;
      case 'w':
        dot();
        dash();
        dash();
        endLetter();
        break;
      case 'x':
        dash();
        dot();
        dot();
        dash();
        endLetter();
        break;
      case 'y':
        dash();
        dot();
        dash();
        dash();
        endLetter();
        break;
      case 'z':
        dash();
        dash();
        dot();
        dot();
        endLetter();
        break;
      case '1':
        dot();
        dash();
        dash();
        dash();
        dash();
        endLetter();
        break;
      case '2':
        dot();
        dot();
        dash();
        dash();
        dash();
        endLetter();
        break;
      case '3':
        dot();
        dot();
        dot();
        dash();
        dash();
        endLetter();
        break;
      case '4':
        dot();
        dot();
        dot();
        dot();
        dash();
        endLetter();
        break;
      case '5':
        dot();
        dot();
        dot();
        dot();
        dot();
        endLetter();
        break;
      case '6':
        dash();
        dot();
        dot();
        dot();
        dot();
        endLetter();
        break;
      case '7':
        dash();
        dash();
        dot();
        dot();
        dot();
        endLetter();
        break;
      case '8':
        dash();
        dash();
        dash();
        dot();
        dot();
        endLetter();
        break;
      case '9':
        dash();
        dash();
        dash();
        dash();
        dot();
        endLetter();
        break;
      case '0':
        dash();
        dash();
        dash();
        dash();
        dash();
        endLetter();
        break;
      case '.':
        dot();
        dash();
        dot();
        dash();
        dot();
        dash();
        endLetter();
        break;
      case '?':
        dot();
        dot();
        dash();
        dash();
        dot();
        dot();
        endLetter();
        break;
      case ',':
        dash();
        dash();
        dot();
        dot();
        dash();
        dash();
        endLetter();
        break;
      case '!':
        dash();
        dot();
        dash();
        dot();
        dash();
        dash();
        endLetter();
        break;
      case '(':
        dash();
        dot();
        dash();
        dash();
        dot();
        endLetter();
        break;
      case ')':
        dash();
        dot();
        dash();
        dash();
        dot();
        dash();
        endLetter();
        break;
      case '-':
        dash();
        dot();
        dot();
        dot();
        dot();
        dash();
        endLetter();
        break;
      case ':':
        dash();
        dash();
        dash();
        dot();
        dot();
        dot();
        endLetter();
        break;        
      case '@':
        dot();
        dash();
        dash();
        dot();
        dash();
        dot();
        endLetter();
        break;
      case ' ':
        space();
        break;
    }
}
