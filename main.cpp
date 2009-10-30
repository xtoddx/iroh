/*
 * REF: http://arcfn.com/2009/07/secrets-of-arduino-pwm.html
 * SRC: http://tthheessiiss.wordpress.com/2009/08/05/dirt-cheap-wireless/
 *
 * So, from what I understand, this is going to set up Pulse Width Modulation
 * (PWM), from the underlying Atmel architecture, which will use two pins
 * to pulse across, designated pins A & B.
 *
 * Control bits for the timers are stored in registers.
 *
 * (n = Timer number, X = output name)
 *
 * TCCRnA/B are the main registers that hold:
 * WGM = Waveform Generation Mode
 * CS = Clock Select Bits
 * COMnA/B = Compare Match Output - enable/disable/invert outputs
 *
 *
 * OCRnA/B are the Output Compare Registers
 * They are different for each register, see processor datasheet for details.
 * They set the levels where 
 *
 * FAST PWM: WGM=011
 * The timer builds from 0->255, then resets to 0.  It turns the output on at 0,
 * and off at the value of OCRnA for output A, and likewise for B.
 *
 * PHASE CORRECT PWM: WGM=001
 * The timer traveds 0->255->0, and is on for values below the OCRnX value.
 *
 * CHANGING THE TOP LIMIT: Instead of cycling to 255, it can cycle to OCRnA
 * It will make output A always on unless "Toggle OCnA on Compare Match" is set,
 * in which case A will be on for one complete cycle, and off for one cycle.
 * The output of B will still be on for values under OCRnB.
 *
 *
 */
void 
setup_timer()
{
  //generates 38kHz carrier wave on pin 9 and 10
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);

  // Clear Timer on Compare Match (CTC) Mode
  bitWrite(TCCR1A, WGM10, 0);
  bitWrite(TCCR1A, WGM11, 0);
  bitWrite(TCCR1B, WGM12, 1);
  bitWrite(TCCR1B, WGM13, 0);

  // Toggle OC1A and OC1B on Compare Match.
  bitWrite(TCCR1A, COM1A0, 1);
  bitWrite(TCCR1A, COM1A1, 0);
  bitWrite(TCCR1A, COM1B0, 1);
  bitWrite(TCCR1A, COM1B1, 0);

  // No prescaling
  bitWrite(TCCR1B, CS10, 1);
  bitWrite(TCCR1B, CS11, 0);
  bitWrite(TCCR1B, CS12, 0);

  OCR1A = 210;
  OCR1B = 210;
}

void
setup ()
{
  setup_timer()
  Serial.begin(2400);
}

void
loop()
{
  // WHAT WHAT?
}
