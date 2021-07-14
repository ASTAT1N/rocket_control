#include <ThreeWire.h>  
#include <RtcDS1302.h>
//port
const int rtcIO=4;
const int rtcSCLK=5;
const int rtcCE=2;

//class
ThreeWire myWire(rtcIO,rtcSCLK,rtcCE); // IO, SCLK, CE
RtcDS1302<ThreeWire> Rtc(myWire);

//variable
bool RTCInitCheck=false;

//function
void RTCInit(){
    Rtc.Begin();
    RtcDateTime compiled = RtcDateTime(__DATE__, __TIME__);
    if (Rtc.GetIsWriteProtected()){//check write protect
        Serial.println("RTC was write protected, enabling writing now");
        Rtc.SetIsWriteProtected(false);
    }
    if (!Rtc.IsDateTimeValid()){//check time
        Serial.println("RTC lost confidence in the DateTime!");
        Rtc.SetDateTime(compiled);
    }
    if (!Rtc.GetIsRunning()){//check it running
        Serial.println("RTC was not actively running, starting now");
        Rtc.SetIsRunning(true);
    }
    RtcDateTime now = Rtc.GetDateTime();
    if (now < compiled) {//change time, when it is slower then compile time
        Serial.println("RTC is older than compile time!  (Updating DateTime)");
        Rtc.SetDateTime(compiled);
    }
    RTCInitCheck=true;
}
bool RTCValid(){ //valid=true
    RtcDateTime now = Rtc.GetDateTime();
    return now.IsValid();
}

#define countof(a) (sizeof(a) / sizeof(a[0]))

void printDateTime(){
    const RtcDateTime dt=Rtc.GetDateTime();
    char datestring[20];
    snprintf_P(datestring, 
        countof(datestring),
        PSTR("[%02u/%02u/%04u %02u:%02u:%02u]"),
        dt.Month(),
        dt.Day(),
        dt.Year(),
        dt.Hour(),
        dt.Minute(),
        dt.Second() );
    Serial.print(datestring);
}
