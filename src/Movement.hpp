#include "SmartServoBus.hpp"
#include "RBCX.h"
#include<Arduino.h>
#include <Arduino.h>

struct Movemennt{


double mm_to_ticks = 0.215; // konstanta pro prepocet tics enkoderu na mm
int wheel_base = 150; // rovor  kol robota
int last_ticks_M3 = 0; // pravy motor
int last_ticks_M2 = 0; // llevy motor


/**
 * Fuknkce pro pohyb robota v oblouku doprava
 * @param angle: jaky uhel oblouku robot ujede
 * @param radius: polomer oblouku vnitrniho kola robota
 *
 * @return None
 */
  void ArcRight(int angle, int radius)
{
  //Nastaveni pocitadla tics na 0 pro oba motory
  man.motor(rb::MotorId::M2).setCurrentPosition(0);
  man.motor(rb::MotorId::M3).setCurrentPosition(0);
  //auto &man = rb::Manager::get();
  double inner_lenght = (((2 * PI * radius) / 360) * angle) / mm_to_ticks; //vzdalenost, kterou musi vnitrni kolo v oblouku ujet v tics enkoderu
  double outer_lenght = (((2 * 3.14 * (radius + wheel_base)) / 360) * angle) / mm_to_ticks; //vzdalenost, kterou musi vnejsi kolo v oblouku ujet v tics enkoderu
  //Serial.println(inner_lenght);
  int outer_sped = 3200; //rychlost vnejsiho kola
  int inner_speed = -(outer_sped * inner_lenght) / outer_lenght; // vypocet pro rychlost vnitrniho kola
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


/**
 * Funkce pro pohyb robota rovne 
 * @param speed: rychlost kterou robot pojede
 * @param distance: vzdalenost kterou ma robot ujet v mm
 * @param timeout: po jake dobe se ma funkce ukoncit i kdyz neujede pozadovanou vzdalenost
 * @return None
 */
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
  { 
    man.motor(rb::MotorId::M2).speed(-speed);
    man.motor(rb::MotorId::M3).speed(speed);
    man.motor(rb::MotorId::M3).requestInfo([&ticks_M3](rb::Motor &info)
                                           {
            ticks_M3 =  info.position(); });
    man.motor(rb::MotorId::M2).requestInfo([&ticks_M2](rb::Motor &info)
                                           {
            ticks_M2 =   -info.position(); });

    delay(10);
    time = time + 10;
  }
}




















































































































};


