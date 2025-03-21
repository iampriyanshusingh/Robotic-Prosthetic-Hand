#include <Servo.h>
#define numOfValsRec 5 
#define digitsPerValRec 1

Servo servoThumb;
Servo servoIndex;
Servo servoMiddle;
Servo servoRing;
Servo servoPinky;

int valsRec[numOfValsRec];
int stringLength = numOfValsRec * digitsPerValRec+1;
int counter = 0;
bool counterStart = false;
String receievedString;


void setup() {

  Serial.begin(9600);
  servoThumb.attach(12);
   servoIndex.attach(8);
    servoMiddle.attach(9);
     servoRing.attach(10);
      servoPinky.attach(11);
}

void receieveData(){
  while(Serial.available())
  {
    char c = Serial.read();

    if(c=='$'){
      counterStart = true;
    }
    if(counterStart){
      if(counter < stringLength){
        receievedString = String(receievedString+c);
        counter++;
      }
      if (counter >= stringLength){
        for(int i =0; i<numOfValsRec;i++)
        {
          int num = (i*digitsPerValRec)+1;
        valsRec[i]= receievedString.substring(num,num+digitsPerValRec).toInt();
        }
        receievedString = "";
        counter = 0;
        counterStart = false;
      }
    }
  }
}

void loop() {
 
  receieveData();
  if(valsRec[0]==1){servoThumb.write(0);}else{servoThumb.write(180);}
  if(valsRec[1]==1){servoIndex.write(0);}else{servoIndex.write(180);}
  if(valsRec[2]==1){servoMiddle.write(0);}else{servoMiddle.write(180);}
  if(valsRec[3]==1){servoRing.write(0);}else{servoRing.write(180);}
  if(valsRec[4]==1){servoPinky.write(0);}else{servoPinky.write(180);}

}
