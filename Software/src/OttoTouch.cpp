#include <Arduino.h>
#include "Otto.h"

#define LEFTLEG 2
#define RIGHTLEG 3
#define LEFTFOOT 4
#define RIGHTFOOT 5
#define BUZZER 13
#define SENSOR_PIN A0 // touch sensor

const int MOVEMENT_IDLE = 0;
const int MOVEMENT_AVOID = 1;

int last_state = LOW;
int current_state;
int movement = MOVEMENT_IDLE;
bool obstacle_detected = false;
Otto otto;

void setup()
{
  Serial.begin(9600);
  otto.init(LEFTLEG, RIGHTLEG, LEFTFOOT, RIGHTFOOT, true, BUZZER);
  pinMode(SENSOR_PIN, INPUT);
  otto.home();
  otto.sing(S_happy);
}

void loop()
{
  readTouchSensor();
  switch (movement)
  {
  case MOVEMENT_AVOID:
    if (obstacle_detected) {
      Serial.println("obstacle detected");
      otto.sing(S_OhOoh);

    }
    break;
  
  default:
    break;
  }
}

void readTouchSensor()
{
  current_state = digitalRead(SENSOR_PIN);
  if (last_state == LOW && current_state == HIGH)
  {
    Serial.println(current_state);
    movement++;
    delay(500);
  }
  last_state = current_state;
}