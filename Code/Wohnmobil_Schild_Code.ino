// Attiny85, 8Mhz clock

#include <avr/interrupt.h>
#include <avr/sleep.h>

#define SCHEINWERFER 1 // pwm for scheinwerfer
#define BLINKER 2      // digital pin for blinker
#define BUTTON_PIN 0

volatile bool buttonPressed = false;

ISR(PCINT0_vect) {
  if (digitalRead(BUTTON_PIN) == LOW) {
    // Button pressed, set flag
    buttonPressed = true;
  }
}

void customDelay(unsigned long ms) {
  while (ms--) {
    delayMicroseconds(1000);  // delay for 1ms
  }
}

void ablaufStart() {
  digitalWrite(BLINKER, HIGH);
  customDelay(300);
  digitalWrite(BLINKER, LOW);
  customDelay(500);
  digitalWrite(BLINKER, HIGH);
  customDelay(300);
  digitalWrite(BLINKER, LOW);
  customDelay(500);
  
  for (int i = 0; i<230; ++i) {
    analogWrite(SCHEINWERFER, i);
    customDelay(10);
  }
  
}

void ablaufEnde() {
  analogWrite(SCHEINWERFER, 230);
  for (int i = 230; i>1; --i) {
    analogWrite(SCHEINWERFER, i);
    customDelay(10);
  }
  digitalWrite(SCHEINWERFER, LOW);
  customDelay(500);

  digitalWrite(BLINKER, HIGH);
  customDelay(300);
  digitalWrite(BLINKER, LOW);
  customDelay(500);
  digitalWrite(BLINKER, HIGH);
  customDelay(300);
  digitalWrite(BLINKER, LOW);
  customDelay(500);
  
}

void ablaufLichtAnimation() {

  for (int i = 0; i>10;++i) {
    digitalWrite(BLINKER, HIGH);
    customDelay(500);
    digitalWrite(BLINKER, LOW);
    customDelay(500);
  }
  
  analogWrite(SCHEINWERFER, 150);

  for (int i = 0; i<10;++i) {
    digitalWrite(BLINKER, HIGH);
    customDelay(500);
    digitalWrite(BLINKER, LOW);
    customDelay(500);
  }

  analogWrite(SCHEINWERFER, 255);
  customDelay(1000);
  analogWrite(SCHEINWERFER, 150);

  for (int i = 0; i<10;++i) {
    digitalWrite(SCHEINWERFER, LOW);
    digitalWrite(BLINKER, HIGH);
    customDelay(500);
    digitalWrite(BLINKER, LOW);
    digitalWrite(SCHEINWERFER, HIGH);
    customDelay(500);
  }

  customDelay(5000);
  
}

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(SCHEINWERFER, OUTPUT);
  pinMode(BLINKER, OUTPUT);
  ADCSRA = 0; // ADC disabled
  GIMSK = 0b00100000;  // Enable Pin Change Interrupt (PCINT0)
  PCMSK = 0b00000001;  // Enable interrupts on PIN PB0 (BUTTON_PIN)
}

void loop() {
  if (buttonPressed) {
    ablaufStart();
    ablaufLichtAnimation();
    ablaufEnde();
    buttonPressed = false;  // reset flag
  }

  sleep_enable();
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  sleep_cpu();
}
