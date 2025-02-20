#include "SmartServoBus.hpp"
#include "RBCX.h"
#include<Arduino.h>

//pro spravne fungovani SmartServoBus.hpp
using namespace lx16a;
static SmartServoBus servoBus;

//funkce pro vypocet o jaky uhel se ma otocit prave servo
Angle RightAngle(Angle angle)
{
  angle = 240_deg - angle;
  return angle;
}

//mozne stavy klepet
enum klepeta_state
    {
        full_closed,
        full_open,
        triangle
    };

//na startu se otevira leve klepeto jako prvni
klepeta_state klepeta_last_state = full_closed; //stav klepet na startu

//nastavi klepeta na pozici triangle 
void KlepetaTriangle(){
if (klepeta_last_state == full_closed){
    servoBus.set(0, 90_deg); 
    delay(1000);//nutna prodleva, aby nedoslo ke kolizi klepet pri otvirani
    servoBus.set(1, RightAngle(90_deg)); 
}
if (klepeta_last_state == full_open){
    servoBus.set(0, 90_deg);
    servoBus.set(1, RightAngle(90_deg)); 
}
}

//nastavi klepeta na pozici full_open
void KlepetaFullOpen(){
    if (klepeta_last_state == full_closed){
        servoBus.set(0, 0_deg);
        delay(1000);//nutna prodleva, aby nedoslo ke kolizi klepet pri otvirani
        servoBus.set(1, RightAngle(0_deg)); 
    }
    if (klepeta_last_state == triangle){
        servoBus.set(0, 0_deg); 
        servoBus.set(1, RightAngle(0_deg)); 
    
    }
    }

//nastavi klepeta na pozici full_closed
void KlepetaFullClosed(){
    if (klepeta_last_state == full_open){
        servoBus.set(0, 50_deg); 
        delay(1000);
        servoBus.set(1, RightAngle(150_deg)); 
        delay(2000);//nutna prodleva, aby nedoslo ke kolizi klepet pri otvirani
        servoBus.set(0, 148_deg); 
    }
    if (klepeta_last_state == triangle){
        servoBus.set(0, 50_deg); 
        delay(1000);
        servoBus.set(1, RightAngle(150_deg));
        delay(2000);//nutna prodleva, aby nedoslo ke kolizi klepet pri otvirani
        servoBus.set(0, 148_deg); 
    }
    }