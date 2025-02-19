#include "SmartServoBus.hpp"
#include "RBCX.h"
#include<Arduino.h>
using namespace lx16a;
static SmartServoBus servoBus;
auto &man = rb::Manager::get(); // needs to be there to work man.sometning


// calculates angle for left klepeto
Angle left_angle(Angle angle)
{
  angle = 240_deg - angle;
  return angle;
}
double mm_to_ticks = 0.215;
int wheel_base = 150;
int last_ticks_M3 = 0;
int last_ticks_M2 = 0;


void Straight(int speed, int distance,int timeout)
{

  man.motor(rb::MotorId::M2).setCurrentPosition(0);
  man.motor(rb::MotorId::M3).setCurrentPosition(0);
  int time = 0;
  int ticks_M2 = 0;
  int ticks_M3 = 0;
  distance = distance / mm_to_ticks;
  Serial.println(distance);
  while (ticks_M2 < distance && time < timeout)
  { //(ticks_M2 < distance)&& (ticks_M3 < distance)
    man.motor(rb::MotorId::M2).speed(-speed);
    man.motor(rb::MotorId::M3).speed(speed);
    man.motor(rb::MotorId::M3).requestInfo([&ticks_M3](rb::Motor &info)
                                           {
            //Serial.println( info.position());
            ticks_M3 =  info.position(); });
    man.motor(rb::MotorId::M2).requestInfo([&ticks_M2](rb::Motor &info)
                                           {
            //Serial.println( -info.position());
            ticks_M2 =   -info.position(); });

    delay(10);
    time = time + 10;
  }
  // man.motor(rb::MotorId::M2).speed(0);
  // man.motor(rb::MotorId::M3).speed(0);
}









void setup()
{
  auto &man = rb::Manager::get(); // Get the manager instance as a singleton
  man.install(); // Install the manager
  servoBus.begin(2, UART_NUM_1, GPIO_NUM_27);
  
  //for setting autostop parameters
  SmartServoBus::AutoStopParams par;
  par.max_diff_centideg = 1000;
  par.max_diff_readings = 1;


// Straight(500,10000,5000);
  servoBus.setAutoStop(0, false);
  servoBus.setAutoStop(1, false);
  servoBus.set(0, 56_deg);
  servoBus.set(1, left_angle(100_deg));

delay(5000);
}
void loop(){}