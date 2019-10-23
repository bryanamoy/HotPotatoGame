//i2c Slave Code(Leonardo)
#include <Wire.h>
const int green = 2;
//const int timerled = 3;
//long randtime;
void setup()
{
  Wire.begin(5);
  Wire.onReceive(receiveEvent);
  

  pinMode(2,OUTPUT);


}
void loop()
{
  delay(100);
}

void receiveEvent(int howMany)
{
    
  while(Wire.available())
  {
    char c = Wire.read();
    
    //Third player passing right or Second player passing to left
    if (c == 'A' || c == 'G'){
      digitalWrite (2,HIGH);
    }

    //Turns off the LED after 
    if (c == 'B'){ 
      digitalWrite (2,LOW);
    }

    //Default turn off
    if (c == 'L'){
      digitalWrite(2,LOW);
    }
  }
}
