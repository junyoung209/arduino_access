#include <DistanceGP2Y0A21YK.h>
#include <SoftwareSerial.h>

int blueTx=2;//TX(보내는핀 설정)
int blueRx=3;//Rx(받는핀)
SoftwareSerial mySerial(blueTx, blueRx);//시러얼 통신을 위한 객체선언



DistanceGP2Y0A21YK Dist1, Dist2;
int distance1, distance2;
int flag1, flag2;
int state;
int testCount = 2;
double passRate = 0.7;
int passPoint = 20;

void setup()
{
  Serial.begin(9600);
  mySerial.begin(9600);
  //Dist 초기화
  Dist1.begin(0);
  Dist2.begin(1);
  //Dist1.setARefVoltage(5);
  //Dist2.setARefVoltage(3);

  //
  flag1=0;
  flag2=0;
}

void loop()
{

if(mySerial.available()){
  Serial.write(mySerial.read());//블루투스측 내용을 시리얼모니터에 출력
}
if(Serial.available()){
  mySerial.write(Serial.read());//시리얼 모니터 내용을 블루투스측에 write
}

  
  //
  while(1){

    for(int i=0; i<1; i++){
            //state0==============================================================================
            if(state ==0){
                int count1=0;
                int count2=0;
                for(int i=0; i<testCount; i++){
                  distance1 = Dist1.getDistanceCentimeter();
                  if(distance1 <passPoint){ count1++;    }
                }
         
                if(count1 >=testCount*passRate){ 
                  flag1=1;
                  state =2;
                  continue;
                }



                for(int i=0; i<testCount; i++){
                  distance2 = Dist2.getDistanceCentimeter();
                  if(distance2 <passPoint){ count2++;    }
                }
                
                if(count2 >=testCount*passRate){ 
                 flag2=1;
                 state =6;
                 continue;
                }
              }
             //========================================================================================

            //state2===============================================================================
            else if(state ==2){
                int count2=0;
                for(int i=0; i<testCount; i++){
                  distance2 = Dist2.getDistanceCentimeter();
                  if(distance2 <passPoint){ count2++;    }
                }
                if(count2 >=testCount*passRate){ 
                  state = 3;
                  continue;
                }
            }
            //===================================================================================

            

            //state3===============================================================================
            else if(state ==3){
                int count2=0;
                for(int i=0; i<testCount; i++){
                  distance2 = Dist2.getDistanceCentimeter();
                  if(distance2 >=passPoint){ count2++;    }
                }
                if(count2 >=testCount*passRate){
                  
                 int byteSent =  mySerial.write("i");
                  //들어옴 처리 
             
                 Serial.print("\n들어옴");
                  state= 10;
                  continue;
                }
            }
            //===================================================================================



            //state6=========================================================================
            else if(state ==6){
                int count1=0;
                for(int i=0; i<testCount; i++){
                  distance1 = Dist1.getDistanceCentimeter();
                  if(distance1 <passPoint){ count1++;    }
                }
                if(count1 >=testCount*passRate){ 
                  state = 7;
                  continue;
                }
            }
            //=====================================================================================


            //state7=========================================================================
            else if(state ==7){
                int count1=0;
                for(int i=0; i<testCount; i++){
                  distance1 = Dist1.getDistanceCentimeter();
                  if(distance1 >=passPoint){ count1++;    }
                }
                if(count1 >=testCount*passRate){ 
                  //나감 출력
                  int byteSent = mySerial.write("o");
                 Serial.print("\n나감");
                  state = 10;
                    continue;
                }
            }
            //=====================================================================================
          
            //state10=======마무리 초기화==========================================================
            else{
             flag1=0;
             flag2=0;
             state =0;
            }
            //=====================================================================================
    }




          
          Serial.print("\n");
          Serial.print("[flag1");
          Serial.print(flag1);
          Serial.print(" flag2:");
          Serial.print(flag2);
          Serial.print("]");
          Serial.print("[Distance1 in centimers: ");
          Serial.print(distance1);
          Serial.print("] [Distance2 in centimers: ");        
          Serial.print(distance2);
          Serial.print("] state : ");
          Serial.print(state);
          delay(10); //make it readable
    
  }

}
