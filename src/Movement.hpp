#include "SmartServoBus.hpp"
#include "RBCX.h"
#include<Arduino.h>
#include <Arduino.h>





struct Movemennt{


  // r motor 3
//  l motor 2
double mm_to_ticks = 0.215; // konstanta pro prepocet tics enkoderu na mm
int wheel_base = 150;
int last_ticks_M3 = 0; // right
int last_ticks_M2 = 0; // left







  void ArcRight(int angle, int radius)
{
  //Nastaveni pocitadla tics na 0 pro oba motory
  man.motor(rb::MotorId::M2).setCurrentPosition(0);
  man.motor(rb::MotorId::M3).setCurrentPosition(0);
  //auto &man = rb::Manager::get();
  double inner_lenght = (((2 * PI * radius) / 360) * angle) / mm_to_ticks; //vzdalenost, kterou musi vnitrni kolo v oblouku ujet v tics enkoderu
  double outer_lenght = (((2 * 3.14 * (radius + wheel_base)) / 360) * angle) / mm_to_ticks; //vzdalenost, kterou musi vnejsi kolo v oblouku ujet v tics enkoderu
  //Serial.println(inner_lenght);
  int outer_sped = 3200;
  int inner_speed = -(outer_sped * inner_lenght) / outer_lenght;
  //Serial.println(inner_speed);
  int tics_M2 = 0;
  int tics_M3 = 0;
  //Serial.println(outer_lenght);
  while ((inner_lenght > tics_M3) && (outer_lenght > tics_M2))
  { 
    man.motor(rb::MotorId::M2).speed(-outer_sped);
    man.motor(rb::MotorId::M3).speed(-inner_speed);
    man.motor(rb::MotorId::M2).requestInfo([&tics_M2](rb::Motor &info)
                                           {
            tics_M2 = info.position(); });
    man.motor(rb::MotorId::M3).requestInfo([&tics_M3](rb::Motor &info)
                                           {
            tics_M3 = info.position(); });
    delay(10);
  }
}
};


