//port
const int setSw=4;
const int sensorIn=A1;
const bool velstate=true;
const float loadK;

//velvePort
const int pwm=3;
const int paral[6]={5,6,7,8,9,10};

//valve switch
int val=true; //true= pwm, false= parallel

//

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
void setInit0(){
  bool sw=true;
  while(sw){
    if(digitalRead(setSw)==true){
      
    }
  }
  
}

//init it as Nkg
const int N=10;
void setInitN(){

}

//calculate thrust
int calthrust(){
  int val=analogRead(sensorIn);
  //val*=k;
  
  
}


//work
void setup() {
  //outputSetting
  pinMode(3,OUTPUT);
  pinMode(setSw,INPUT);
  

}

void loop() {
  
}
