#include<Servo.h>
#include<SoftwareSerial.h>

Servo arm;
SoftwareSerial mySerial(2,3);
int i,j,d=20,xcur=0,xprev=90;
char ch;
void setup() {
  // put your setup code here, to run once:
arm.attach(6);
pinMode(13,OUTPUT);
pinMode(12,OUTPUT);
digitalWrite(13,LOW);
digitalWrite(12,LOW);
mySerial.begin(9600);
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
 if(mySerial.available()>0)
   {
    ch=mySerial.read();
    switch(ch)
    {
      case 'n':Serial.println(ch); //Turn on the leds attached to the eyes.
               digitalWrite(12,HIGH);
               digitalWrite(13,HIGH);
             break;
      case 'm':Serial.println(ch);             //repeatedly move the Servo attached to the Arm from 130 to 80 degree back and forth.
              xcur=80;
              xprev=Servowrite(arm,xcur,xprev);
              xcur=130;
              xprev=Servowrite(arm,xcur,xprev);
              xcur=80;
              xprev=Servowrite(arm,xcur,xprev);
              xcur=130;
              xprev=Servowrite(arm,xcur,xprev);
              xcur=80;
              xprev=Servowrite(arm,xcur,xprev);
               xcur=100;
               xprev=Servowrite(arm,xcur,xprev);
               digitalWrite(12,LOW);
               digitalWrite(13,LOW);
               break;
       default:break;
    }
   }          
}

int Servowrite(Servo s,int cur,int prev)   //function for moving the Servo.
{
  if(prev<cur)
    { for(i=prev;i<=cur;i++)
        {s.write(i);
         delay(d);
         }
     } 
   else if(cur<prev)
     { for(i=prev;i>=cur;i--)
         {s.write(i);
          delay(d);
         }
     }
     //Serial.println();
     //Serial.print("prev=");
     //Serial.println(prev);
     //Serial.print("cur=");
     //Serial.println(cur);
     return cur;
}
