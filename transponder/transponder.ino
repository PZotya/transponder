#include <PPMDecoder.h>
#include <FSKModem.h>


byte check;
byte transcount;
char message[8]="$GPGGA";
char received;
boolean trans;

void setup() {
  PPM.begin(2);
  PPM.setChannnel(1,PPM2PWM,4);
  PPM.setChannnel(2,PPM2PWM,5);
  PPM.setChannnel(3,PPM2PWM,6);
  PPM.setChannnel(4,PPM2PWM,7);
  PPM.setChannnel(5,PPM2PWM,8);
  PPM.setChannnel(6,PPM2PWM,9);
  modem.begin(1200,10,0);
  Serial.begin(38400);
  check=0;
  trans=false;
  transcount=0;
}

void loop() {
  // put your main code here, to run repeatedly:
  while (Serial.available()>0)
  {
    received=Serial.read();
    if ((received!='$') && trans)
    {
      modem.write(received);
    } else
    {
      trans=false;
      if (message[check]==received)
      {
        check++;
        if (check==6)
        {
          transcount++;
          check=0;
          if (transcount>1)
          {
            modem.write(13);modem.write(13);
            for(int i=0;i<6;i++)
            {
              modem.write(message[i]);
            }
          trans=true;
          transcount=0;
          }
        }
      } else
      {
        check=0;
      }
    }
  }
}
