#include "DShot.h"
#include <stdint.h>

#define DSHOT_PORT PORTD

/*
 * Limit the max Speed in % if you want
 * 
 * !! Attention !!
 * The speedvalue is "CUT" hard, not scaled.
 */
#define MAX_SPEED_LIMIT_PERCENT 50

DShot esc1(DShot::Mode::DSHOT300);

#define LED_PIN 12

int max_throttle;

void setup() {
  /*
   * DShot settings
   */
  // Notice, all pins must be connected to same PORT
  esc1.attach(7);  
  esc1.setThrottle(0);
  /*
   * System settings
   */
  pinMode(LED_PIN, OUTPUT); // LED to show initialisation state

  digitalWrite(LED_PIN, LOW);
  delay(1000);
  /*
   * Wait until the user at least goes below 6.25%  of thrust !
   * Blink with 1HZ to show this
   */
  int cnt = 0; 
  while (analogRead(A0) > 64)
  {      
    delay(10);
    cnt +=10;
    if (cnt >= 500)
    {
      digitalWrite(LED_PIN, HIGH);
    } else {
      digitalWrite(LED_PIN, LOW);
    }
    if (cnt >= 1000) cnt = 0;
  }
  digitalWrite(LED_PIN, HIGH);
  /*
   * Attention the in between values are geater than max(int) -> we use int32
   */
  uint32_t maxs = MAX_SPEED_LIMIT_PERCENT;
  maxs = (maxs * 2047u);
  maxs /= 100;
  if (maxs > 2047u) maxs = 2047;
  
  max_throttle = maxs;
}
int cnt = 0;

void loop() {
  /*
   * Analog in [0..1023]
   */
  int speed = analogRead(A0);
  /*
   * DSHOT Throttle needs to be in [48..2047]
   */
  if (speed < 24) speed = 24;
  int throttle = (speed * 2);
  if (max_throttle < throttle) throttle = max_throttle;
  esc1.setThrottle(throttle);
  delay(10);
}
