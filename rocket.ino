#include "Thrust.h"
#include "RTC.h"
//port
const bool velstate=true;
const float loadK;

//velvePort
const int pwm=10;
const int paral[6]={5,6,7,8,9,10};

//valve switch
int val=true; //true= pwm, false= parallel

//velve start value
const int VelveStart=70;

//function

//velve control
void setVelve(unsigned int x){ //get x as 0 to 100
  if(velstate){
    //PWM(0~255)
    val=x*255;
    val/=100;
    analogWrite(pwm,val);
  }
  else{
    //parallel
    static int working=0;
    val=x/20;
    if(val!=working){
      //have to change
      digitalWrite(paral[working],LOW);
      digitalWrite(paral[val],HIGH);
      working=val;
    }
  }
}
//initialize load cell sensor
//init it as 0kg

//work
void setup() {
  //outputSetting
  pinMode(setSw,INPUT);
  Serial.begin(9600);
  RTCInit();
  setInit0();

}
int status=0;//0: 저울 초기화, 1: 추력 시작, 2: 추력 조절
bool sw=true;

int VelveControl;
float benchMark, currentTrust;
void loop() {
  if(status==0){
    if(sw){
      Serial.print("저울 초기화가 필요합니다. ");
      Serial.print(N);
      Serial.println("kg의 추를 올리고 스위치를 눌러주세요.");
      sw=false;
    }
    if(digitalRead(setSw)==true){
      setInitN();
      status+=1;
      sw=true;
    }
  }
  if(status==1){
    if(sw){
      Serial.print("현재시간 :");
      printDateTime();
      Serial.println("스위치를 눌러서 추력측정을 시작합니다.");
      sw=false;
    }
    if(digitalRead(setSw)==true){
      setVelve(VelveStart);
      VelveControl=VelveStart;
      benchMark=calthrust();
      Serial.print("현재 시간: ");
      printDateTime();
      Serial.print("기준 추력: ");
      Serial.print(benchMark);
      Serial.println("kg");
      status+=1;
    }
  }
  if(status==2){
    //current status
    printDateTime();
    currentTrust=calthrust();
    Serial.print(" ");
    Serial.print(currentTrust);
    Serial.println("kg");
    //check velve value
    if(currentTrust<calthrust()){
      VelveControl+=10;
    }
    else if(currentTrust>calthrust()){
      VelveControl-=10;
    }
    //apply value
    setVelve(VelveControl);
  }
}
