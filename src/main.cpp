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


enum Sector
{
  blue,
  red,
  yellow,
  green
};
Sector sector = blue; //vychozi sektor je blue

//funkce pro jizdu do hriste
void GoToField(){
  move.Acceleration(300,32000,400);
  move.ArcRight(180,180);
  move.Straight(32000,100,5000);
  open_grabber = true; //tady se zacne otevirat grabber
  move.Arcleft(168, 150);
  move.Straight(20000, 430,4000);
  move.Acceleration(20000, 100, 320);
  move.Stop();
}

void GoForBear(int x, int y){
  x=x*10;
  y=y*10;
  //sector blue
  if (x < 400){
    sector = blue;
    if (y>1400){
      y=1300;
    }
    move.Straight(2000,y,4000);
    move.Stop();
  }

  //sector red
  if (x >= 400 && x <= 600){
    sector = red;
    if (y>1400){
      y=1300;
    }
    move.TurnRight(45);
    move.Straight(2000,200,4000);
    move.TurnLeft(45);
    move.Straight(2000,y-200,4000);
    move.Stop();
  }

  //sector yellow
  if (x > 600 && y>300){
    sector = yellow;
    if(y>1400){
      y=1300;
    }
    move.Straight(2000,y,4000);
    move.TurnRight(90);
    if(x>1400){
      x=1300;
    }
    move.Straight(2000,x,4000);
    move.Stop();
  }

  //sector green
  if (x > 600 && y<=300){
    sector = green;
    if(y<300){
      y=300;
      }
    move.Straight(2000,y,4000);
    move.TurnRight(90);
    if(x>1400){
      x=1300;
    }
    move.Straight(2000,x,4000);
    move.Stop();
  }
}

//funkce pro jizdu zpet do domovske pozice
void GoHome(){
  if (sector == blue){
    move.BackwardUntillWall();
    //move.Straight(2000, 100, 99999);//
    //move.TurnRight(90);
    move.Arcleft(95, 100);
    move.BackwardUntillWall();
    move.Straight(2000, 150, 99999);
    move.ArcRight(90, 300);
    move.Straight(2000, 100, 99999);
    move.Arcleft(190, 170);
    move.Straight(2000, 200, 99999);
    //grabber.Open();
  }
else{
  move.BackwardUntillWall();
  move.Straight(2000, 30, 99999); 
  move.TurnLeft(90);
  //////////////////////////
  move.BackwardUntillWall();
    //move.Straight(2000, 100, 99999);//
    //move.TurnRight(90);
    move.Arcleft(95, 100);
    move.BackwardUntillWall();
    move.Straight(2000, 150, 99999);
    move.ArcRight(90, 300);
    move.Straight(2000, 100, 99999);
    move.Arcleft(190, 170);
    move.Straight(2000, 200, 99999);
    //grabber.Open();
}
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
  //servoBus.begin(2, UART_NUM_1, GPIO_NUM_27); 

  Serial.begin(115200);
  int x_distance = 0;
   while (true)
        {
          if(Serial.available() > 0){
            int num;
             String data = Serial.readStringUntil('\n');
             const char* daata = data.c_str();
             num = std::atoi(daata);
             if (num == 1){
                man.leds().green(true); //rozsviti zelenou diodu
             }
             break;
          
        }}

}
void loop(){}