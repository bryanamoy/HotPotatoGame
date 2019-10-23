//i2c Slave Code(Leonardo)
#include <Wire.h>
const int red = 3;
void setup()
{
  Wire.begin(5);
  Wire.onReceive(receiveEvent);

   
  pinMode(3,OUTPUT);
  
  
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

    //First player passing right
    if (c == 'M'){
      digitalWrite (3,HIGH);
    }

    //Third player passing left
    if (c == 'J'){
      digitalWrite (3,HIGH);
    }

    //Turning off manually
    if (c == 'D'){
      digitalWrite (3,LOW);
    }

    //Default turn off
    if (c == 'L'){
      digitalWrite(3,LOW);
    }
  }
}
