#include <Arduino.h>


void WaitingForBearPosData(){

    //ceka na distance to bear 
      while (true)
      {
        if(Serial.available() > 0){
          int num = 9999;
           String data = Serial.readStringUntil('\n');
           const char* daata = data.c_str();
           num = std::atoi(daata);
    
           if (num !=9999)
           {
             x_distance = num;
            break;
        }
        delay(10);
      }
      //ceka na y distance medveda 
      }
        while (true)
      {
        if(Serial.available() > 0){
          int num = 9999;
           String data = Serial.readStringUntil('\n');
           const char* daata = data.c_str();
           num = std::atoi(daata);
    
           if (num !=9999)
           {
             y_distakce = num;
            break;
        }
        delay(10);
      }
      }
    
    
    }





    void WaitForreadyMessage(){
    while (true)
    {
      if (Serial.available() > 0)
      {
        String data = Serial.readStringUntil('\n');
        if (data == "ready")
        {
          man.leds().green(true);
          break;
        }
      }
      delay(10);
    }
    }