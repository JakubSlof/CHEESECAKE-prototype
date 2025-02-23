#include "SmartServoBus.hpp"
#include "RBCX.h"
#include<Arduino.h>
auto &man = rb::Manager::get(); //pro fungovani RBCX
#include "Grabber.hpp"
#include"Comunication.hpp"
#include "Movement.hpp"
//struktury na ovladani robota
Grabber grabber;
Communication message;
Movemennt move;



void GoToField(){
  move.Acceleration(300,32000,400);
  move.ArcRight(180,180);
  move.Straight(32000,100,5000);
  move.Arcleft(168, 150);
  move.Straight(32000, 630,4000);
  move.Acceleration(32000, 100, 320);
  move.Stop();
}

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
  


//po zapnuti ceka na zpravu od Raspberry Pi ze je ready
//message.WaitForReadyMessage();

//grabber.last_state = open;
//grabber.Grab();


GoToField();
}
void loop(){}