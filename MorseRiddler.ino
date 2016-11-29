#include <avr/sleep.h>
#include <avr/power.h>
#include <avr/wdt.h>
#include <avr/pgmspace.h>
#include <EEPROM.h>
#include "MorseTranslator.h"

#define LED_PIN 0 // Pin that LED is attached to

// Following are the messages. They must be lower case. Supported punctuation includes .,?!()-:@
const char greeting[] PROGMEM = "cq cq cq "; // Name could go here, as in "hi melissa". Played once each power-up
const char intro[] PROGMEM = " every time power is given, this circuit will play the next undelivered message."; // Played once on first powerup
const char conclusion[] PROGMEM = "congratulations, you have made it through 30 riddles. now give this gadget to a friend or program it to do something else. "; // Played after last message in array
const char string_0[] PROGMEM = "what has a head and a tail, but no body?";
const char string_1[] PROGMEM = "a coin.";
const char string_2[] PROGMEM = "what has an eye but can not see?";
const char string_3[] PROGMEM = "a needle.";
const char string_4[] PROGMEM = "what gets wetter and wetter the more it dries?";
const char string_5[] PROGMEM = "a towel.";
const char string_6[] PROGMEM = "paul is six feet tall. he is an assistant at a butcher shop and wears size 9 shoes. what does he weigh?";
const char string_7[] PROGMEM = "meat.";
const char string_8[] PROGMEM = "what kind of room has no doors or windows?";
const char string_9[] PROGMEM = "a mushroom.";
const char string_10[] PROGMEM = "which word in the dictionary is spelled incorrectly?";
const char string_11[] PROGMEM = "incorrectly.";
const char string_12[] PROGMEM = "what gets broken without being held?";
const char string_13[] PROGMEM = "a promise.";
const char string_14[] PROGMEM = "if you have me, you want to share me. if you share me, you haven't got me. what am i?";
const char string_15[] PROGMEM = "a secret.";
const char string_16[] PROGMEM = "he has married many women, but has never been married. who is he?";
const char string_17[] PROGMEM = "a preacher.";
const char string_18[] PROGMEM = "take off my skin and i won't cry, but you will. what am i?";
const char string_19[] PROGMEM = "an onion.";
const char string_20[] PROGMEM = "what can you catch but not throw?";
const char string_21[] PROGMEM = "a cold.";
const char string_22[] PROGMEM = "what goes up but never comes down?";
const char string_23[] PROGMEM = "your age.";
const char string_24[] PROGMEM = "what building has the most stories?";
const char string_25[] PROGMEM = "the library.";
const char string_26[] PROGMEM = "what has no beginning, end, or middle?";
const char string_27[] PROGMEM = "a donut.";
const char string_28[] PROGMEM = "what is yours, but is used by other people more than you?";
const char string_29[] PROGMEM = "your name.";

const char* const string_table[] PROGMEM = { 
                                            string_0,
                                            string_1, 
                                            string_2, 
                                            string_3, 
                                            string_4, 
                                            string_5, 
                                            string_6, 
                                            string_7, 
                                            string_8, 
                                            string_9, 
                                            string_10, 
                                            string_11, 
                                            string_12, 
                                            string_13, 
                                            string_14, 
                                            string_15, 
                                            string_16, 
                                            string_17, 
                                            string_18, 
                                            string_19, 
                                            string_20, 
                                            string_21, 
                                            string_22, 
                                            string_23, 
                                            string_24, 
                                            string_25, 
                                            string_26, 
                                            string_27, 
                                            string_28, 
                                            string_29, 
                                            greeting,     // 30
                                            intro,        // 31
                                            conclusion};  // 32

char buffer[128];    // make sure this is large enough for the largest string it must hold
char c;
byte mlen;
byte iii;
byte messageCounter = 0;
//volatile long sleepCounter = 1L;
byte riddlePosition = 0;
int addr = 0;

MorseTranslator morseTranslator;
/*
ISR(WDT_vect)
{
//  sleepCounter++;
  //sleep_enable();
}
*/

void enterSleep(void)
{
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  sleep_enable();
  /* Now enter sleep mode. */
  sleep_mode();
  /* The program will continue from here after the WDT timeout*/
//  sleep_disable(); /* First thing to do is disable sleep. */
  /* Re-enable the peripherals. */
//  power_all_enable();
  /* Disable Analog to Digital Converter to preserve power */
//  (ADCSRA &= ~(1<<ADEN));
}

void playMessage(byte messageNumber)
{
    buffer[0] = '\0';
    c='.';
    iii=0;
    strcpy_P(buffer, (char*)pgm_read_word(&(string_table[messageNumber])));
    while(c != '\0') {
      c = buffer[iii];
      morseTranslator.emit(c);
      iii++;
    }
}

void putPlace()
{
  //Write value
  EEPROM.put(addr, riddlePosition);
}

void getPlace()
{
  //Read value
  EEPROM.get(addr, riddlePosition);
}

void setup()
{
  /* Enable output on pins for LED and Piezo Buzzer */
  pinMode(LED_PIN, OUTPUT);
  pinMode(1, OUTPUT);

  /* Disable Analog to Digital Converter to preserve power */
  (ADCSRA &= ~(1<<ADEN));

/*
  // Setup the WDT
  
  // Clear the reset flag.
  MCUSR &= ~(1<<WDRF);
  
   // In order to change WDE or the prescaler, we need to
   // set WDCE (This will allow updates for 4 clock cycles).
   
  WDTCR |= (1<<WDCE) | (1<<WDE);

  // set new watchdog timeout prescaler value
  WDTCR = 1<<WDP0 | 1<<WDP3; // 8.0 seconds
  
  // Enable the WD interrupt (note no reset).
  WDTCR |= _BV(WDIE);
*/

  // Turn on LED to let us know the battery was connected right
  //digitalWrite(0,HIGH);
  //delay(1000);
  //digitalWrite(0,LOW);

  getPlace(); // Get index of next riddle to play from EEPROM
  if(riddlePosition > 30)
  {
    riddlePosition = 0;
    putPlace();
  }
  playMessage(30); // greeting message
}

void loop()
{
  if(riddlePosition == 30)
  {
    playMessage(32); // "congrats, you're done"
    riddlePosition = 0; // Start over
  }
  playMessage(riddlePosition); // play next unplayed riddle
  riddlePosition++;
  putPlace(); // Record position in EEPROM to persist past power-down
  delay(500);
  morseTranslator.tinyTone(239,3,2000); // Play low pitch sound to signal end
  enterSleep();
}
