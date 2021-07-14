#include "HX711.h"
const int setSw=4;
const int HX711_DOUT=3; //dataPin
const int HX711_CLK=2;//clockPin 

HX711 scale(HX711_DOUT, HX711_CLK);

float calibration_factor = -7050;//그냥 적당한 값으로 시작합니다.
long zeroFactor;
void setInit0(){
  scale.set_scale();
  scale.tare();	//Reset the scale to 0
  zeroFactor=scale.read_average(); //Get a baseline reading
  Serial.print("BaseLine: ");
  Serial.println(zeroFactor);
}

//init it as Nkg
const float N=10.0;
void setInitN(){
  scale.set_scale(calibration_factor); //Adjust to this calibration factor
  //make average
  float nowFactor=0;
  for(int i=0;i<100;++i){
    nowFactor+=scale.get_units();
  }
  nowFactor/=100;
  //set Factor
  calibration_factor+=N-nowFactor;
  scale.set_scale(calibration_factor);
}

//calculate thrust
float calthrust(){
  float result=0;
  for(int i=0;i<10;++i){
    result+=scale.get_units();
  }
  result/=10;
  return result;
}