/*
ard4d library is for display numbers on  4 digit LCD module Ard4d.
Created by Tom.Xu ,June 8th, 2018. This library is only for test purpose.
Released into the public domain.

*/

#ifndef ard4d_h   //判定是否重复导入库
#define ard4d_h //定义库
#include "Arduino.h"//导入arduino库



// segName,the first 4 bits are address(0-15) , the rest 4 bits are data ,the default segment status is ON.
// digit 1
#define d1a 0xf1 // THERE IS NO ";" BEHIND DEFINE!
#define d1b 0x41
#define d1c 0x42
#define d1d 0x52
#define d1e 0x62
#define d1f 0x61
#define d1g 0x51
// digit 2
#define d2a 0xe1
#define d2b 0x11
#define d2c 0x12
#define d2d 0x22
#define d2e 0x32
#define d2f 0x31
#define d2g 0x21

// digit 3
#define d3a 0xc1
#define d3b 0xb1
#define d3c 0xb2
#define d3d 0x02
#define d3e 0xd2
#define d3f 0xd1
#define d3g 0xc2

// digit 4
#define d4a 0x81
#define d4b 0x71
#define d4c 0x72
#define d4d 0xa2
#define d4e 0x92
#define d4f 0x91
#define d4g 0x82

//dots
#define p1 0xf2
#define p2 0x01
#define p3 0xe2
#define p4 0xa1


class  ard4d    //定义类
{
 public:
  
  ard4d(byte DATA, byte WR, byte CS, byte LED );//constructor
  
  void d1(byte num);//函数公开输入参数
  void d2(byte num);
  void d3(byte num);
  void d4(byte num);
  void dot1(bool onOrOff);
  void dot2(bool onOrOff);
  void dot3(bool onOrOff);
  void dotClock(bool onOrOff);
  void clearLCD( );
 private:
   bool Y=true;
   bool N=false; 
   byte VRAM[16]; //visual display ram , data store as xxxx0001 .
   byte _DATA;
   byte _WR;
   byte _CS;
   byte _LED;
   void LcdInitial();
   void sendMSBBits(byte dat, byte bits);
   void sendLSBBits(byte dat, byte bits);
   void writeOneAdd(byte address,byte dat );
   void writeOneCommand(byte command);
   void writeOneSeg(byte segName,bool onOrOff);
  
};
#endif