//i2c Slave Code(Leonardo)
#include <Wire.h>
const int yellow = 2;
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
    
    //First player passing left
    if (c == 'K'){
      digitalWrite (2,HIGH);
    }

    //Second player passing right
    if (c == 'E'){
      digitalWrite (2,HIGH);
    }

    //Turning off manually
    if (c == 'F'){
      digitalWrite (2,LOW);
    }

    //Default turn off
    if (c == 'L'){
      digitalWrite(2,LOW);
    }
  }
}
