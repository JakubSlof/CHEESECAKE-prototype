#include "SmartServoBus.hpp"
#include "RBCX.h"
#include<Arduino.h>
#include<thread>
auto &man = rb::Manager::get(); //pro fungovani RBCX
#include "Grabber.hpp"
#include"Comunication.hpp"
#include "Movement.hpp"
//struktury na ovladani robota
Grabber grabber;
Communication message;
Movemennt move;

bool open_grabber = false; //promena ridici otevirani grabberu v threadu 

//funkce pro jizdu do hriste
void GoToField(){
  move.Acceleration(300,32000,400);
  move.ArcRight(180,180);
  move.Straight(32000,100,5000);
  open_grabber = true; //tady se zacne otevirat grabber
  move.Arcleft(168, 150);
  move.Straight(32000, 430,4000);
  move.Acceleration(32000, 100, 320);
  move.Stop();
}

//ceka na zmacknuti on tlacitka pak program pokracuje
void WaitEorStart(){
  while (true){
    if (man.buttons().on() == 1){
      break;
    }
    delay(10);
  }
}
//funkce pro otevirani grabberu po ceste do hriste
void OpenGrabberBeforeField(){
  while (true)
  {
    if(open_grabber == true){
      break;
    }
    delay(50);
  }
  delay(460);
  grabber.Open();
}

void setup()
{
  //pro fungovani RBCX
  auto &man = rb::Manager::get();
  man.install();

  //parametry pro komunikaci se servy 
  servoBus.begin(2, UART_NUM_1, GPIO_NUM_27); 

  Serial.begin(115200);

  //nastaveni parametru pro autostop serv
  SmartServoBus::AutoStopParams par;
  par.max_diff_centideg = 1000;
  par.max_diff_readings = 1;

  servoBus.setAutoStop(0, false);//vypne autostop leveho serva 
  servoBus.setAutoStop(1, false);//vypne autostop praveho serva
  


//po zapnuti ceka na zpravu od Raspberry Pi ze je ready
//message.WaitForReadyMessage();
WaitEorStart();


grabber.Grab();
WaitEorStart();
delay(100);
///////////////////
std::thread t1(OpenGrabberBeforeField);//thread pro otevirani grabberu za jizdy
GoToField(); //cesta do hriste
t1.join();
message.SendInPosstionMessage();


grabber.Close();
}
void loop(){}