#include<SoftwareSerial.h>
#include<Servo.h>

Servo head;

int pan=130,i;  // 130 degree of Head servo is the center position of the head.

unsigned long previousMillis = 0;        
const long interval = 30000;
SoftwareSerial mySerial(2,3);

void setup() {
  // put your setup code here, to run once:
head.attach(9);
Serial.begin(9600);
mySerial.begin(9600);
for(i=90;i<=130;i++)   // Go from default 90 degree position of servo to 130 degree.
{
  head.write(i);
  delay(10);
}
}

void loop() {
  // put your main code here, to run repeatedly:
 unsigned long currentMillis = millis();
if(Serial.available()>0)
{
  char d = Serial.read();
  switch(d)
  {
    case 'd':if(pan < 200)    // 200 degree is the maximum position of the head in the right side. 'd' indicates head should move right.
              {pan +=1;
              }
              break;
    case 'a':if(pan > 100)    // 100 degree is the maximum position of the head in the left side. 'a' indicates head should move left.
             {pan -=1;
             }
             break;
    case 'n':mySerial.write('n');
             break;
    case 'm':mySerial.write('m');
             break;
    default:break;                 
  }
  
  head.write(pan);
 }
if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
if(pan<130)
{
 while(pan<=130) 
{
  pan++;
  head.write(pan);
}
}
if(pan>130)
{
while(pan>=130)
{
  pan--;
  head.write(pan);
 
}
}
}
}
