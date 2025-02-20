#include "SmartServoBus.hpp"
#include "RBCX.h"
#include<Arduino.h>
#include "Klepeta.hpp"
auto &man = rb::Manager::get(); //pro fungovani RBCX


void setup()
{
  //pro fungovani RBCX
  auto &man = rb::Manager::get();
  man.install();

  //parametry pro komunikaci se servy 
  servoBus.begin(2, UART_NUM_1, GPIO_NUM_27); 

  //nastaveni parametru pro autostop serv
  SmartServoBus::AutoStopParams par;
  par.max_diff_centideg = 1000;
  par.max_diff_readings = 1;

  servoBus.setAutoStop(0, false);//vypne autostop leveho serva 
  servoBus.setAutoStop(1, false);//vypne autostop praveho serva 

  servoBus.set(0, 90_deg); //nastavy pozici leveho serva na 90 stupnu
  servoBus.set(1, RightAngle(90_deg)); //nastavy pozici praveho srva na 90 stupnu
}
void loop(){}