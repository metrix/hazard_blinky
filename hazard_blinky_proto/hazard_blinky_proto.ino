/*
 * blink led at 2kHz
 *
 * adapted from http://letsmakerobots.com/content/arduino-101-timers-and-interrupts
 */

int ledpin = 2;
int nxt = 0;

void setup()
{
  pinMode(ledpin, OUTPUT);

  // initialize timer1
  noInterrupts();           // disable all interrupts
  TCCR1A = 0;
  TCCR1B = 0;

  OCR1A = 999;            // [16000000 / (8 * <2000>) ] - 1 = 999
  TCCR1B |= (1 << WGM12); // CTC mode
  TCCR1B |= _BV(CS11);    // clk/8 prescaler
  TIMSK1 |= _BV(OCIE1A);  // enable timer overflow interrupt
  interrupts();           // enable all interrupts
}

// turn led on every 4th interrupt
ISR(TIMER1_COMPA_vect)      // interrupt service routine
{
  digitalWrite(ledpin, !nxt);
  nxt++;
  if (nxt > 3) nxt = 0;
}

void loop()
{
  delay(1000); // ? :/
}
