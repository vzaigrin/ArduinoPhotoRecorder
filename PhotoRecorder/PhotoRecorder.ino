#include <Wire.h>
#include "RTClib.h"
#include <SD.h>
#include <SoftwareSerial.h>
#include <Adafruit_VC0706.h>

#define chipSelect 10

RTC_DS1307 RTC;
DateTime now;
char dirname[7];
char filename[18];
File imgFile;

Adafruit_VC0706 cam = Adafruit_VC0706(&Serial);

void setup() {
  Wire.begin();
  RTC.begin();
  pinMode(10, OUTPUT);
  SD.begin(chipSelect);
  cam.begin();
  cam.setImageSize(VC0706_640x480);
  cam.setMotionDetect(true);
}

void loop() {

  if (cam.motionDetected()) {

    cam.setMotionDetect(false); 
    if (cam.takePicture()) {
      
      now = RTC.now();
      snprintf(dirname,7,"%.4d%.2d",now.year(),now.month());
      snprintf(filename,18,"%.4d%.2d/%.2d%.2d%.2d.jpg",now.year(),now.month(),now.day(),now.hour(),now.minute());

      if ( !SD.exists(dirname) )  {
        SD.mkdir(dirname);      
      }

      imgFile = SD.open(filename,FILE_WRITE);
      if ( SD.exists(filename) )  {

        uint16_t jpglen = cam.frameLength();
        while (jpglen > 0) {
          uint8_t *buffer;
          uint8_t bytesToRead = min(32, jpglen);
          buffer = cam.readPicture(bytesToRead);
          imgFile.write(buffer, bytesToRead);
          jpglen -= bytesToRead;
        }

        imgFile.close();
      }
    }
    cam.resumeVideo();
    cam.setMotionDetect(true);
  }

}
