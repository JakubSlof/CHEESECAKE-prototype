#include "RBCX.h"
#include "Arduino.h"
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