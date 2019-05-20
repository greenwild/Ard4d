#include "Arduino.h"
#include "ard4d.h"

ard4d::ard4d(byte DATA, byte WR, byte CS, byte LED )
{
	pinMode(DATA,OUTPUT);
	pinMode(WR,OUTPUT);
	pinMode(CS,OUTPUT);
	pinMode(LED,OUTPUT);

	_DATA=DATA;
	_WR=WR;
	_CS=CS;
    _LED=LED;
	//LcdInitial(); //don't know why if I add this line it will not work!
	delay(10);
   writeOneCommand(0x40); 
   writeOneCommand(0x30);             //
   writeOneCommand(0x00); 
   writeOneCommand(0x0a); 
   writeOneCommand(0x02); 
   writeOneCommand(0x06);
   delay(10);
	
}
void  ard4d::LcdInitial()
{  delay(10);
   writeOneCommand(0x40); 
   writeOneCommand(0x30);             //
   writeOneCommand(0x00); 
   writeOneCommand(0x0a); 
   writeOneCommand(0x02); 
   writeOneCommand(0x06);
   delay(10);
  }
void ard4d::sendMSBBits(byte dat, byte bits){
  byte i;
  byte j;
  //dat=dat<<(8-bits);
  for(i=0;i<bits;i++){
     digitalWrite(_WR,LOW); 
     j=dat&0x80;
     if(j==0x80){
    digitalWrite(_DATA,HIGH);
     }else{
    digitalWrite(_DATA,LOW);  
      }
     digitalWrite(_WR,HIGH); // write on up edge 
    dat=dat<<1;
    }
 
  }

 void ard4d::sendLSBBits(byte dat, byte bits){
  byte i;
  byte j;
 
  for(i=0;i<bits;i++){
     digitalWrite(_WR,LOW); 
     j=dat&0x01;
     if(j==0x01){
    digitalWrite(_DATA,HIGH);
     }else{
    digitalWrite(_DATA,LOW);  
      }
     digitalWrite(_WR,HIGH); // write on up edge 
    dat=dat>>1;
    }
 
  }

void ard4d::writeOneAdd(byte address,byte dat )
{  int add=address<<2;
   digitalWrite(_CS,LOW);
  sendMSBBits(0xa0,3);
  sendMSBBits(add,6);//write address
  sendLSBBits(dat,4);
   digitalWrite(_CS,HIGH);
  }
void ard4d::writeOneCommand(byte command)
{
   digitalWrite(_CS,LOW);
  sendMSBBits(0x80,4);//这里必须是4位，命令必须是9位一组
  sendMSBBits(command,8);//write command
   digitalWrite(_CS,HIGH);
  }

/* TO TURN ON OR OFF A LCD SEGMENT WITHOUT IMPACT ANOTHER SEGMENT */
void ard4d::writeOneSeg(byte segName,bool onOrOff)
{
  byte add=(segName&0xf0)>>4;  //take the address of ram
  byte data=(segName&0x0f); // take the data value
  byte ramData=VRAM[add];//take the ram data
 if(onOrOff==true){
   VRAM[add]=data|ramData; //light on the new seg without turn off the other
  }else{
   VRAM[add]=(~data)&ramData;// turn off the seg without impact the other seg
    }
 writeOneAdd(add,VRAM[add]); // display new ramData on LCD  
  }


/**********************************************public functions******************************************************************/
/*TO CLEAN ALL OF CONTENTS ON LCD  */
void ard4d::clearLCD( )
{
  for(byte i=0;i<16;i++){
    VRAM[i]=0x00; // clear the visual display ram
    writeOneAdd(i,VRAM[i]);//clear the real display ram
    }
  }
  
/*DISPLAY 0-9 ON DIGIT ONE*/
void ard4d::d1(byte num) 
{
  byte eight[]={d1a,d1b,d1c,d1d,d1e,d1f,d1g};// put eight on at first then turn off some segments to make other numbers. 
  // the rest number are all off segments on array 
  byte one[]={d1a,d1d,d1e,d1f,d1g};
  byte seven[]={d1d,d1e,d1f,d1g};
for(byte i=0;i<7;i++){
  writeOneSeg(eight[i],Y);
  } // turn 8 on 
  
  switch(num)
  {
    case 0:
    writeOneSeg(d1g,N);
     break;
   case 1:
    for(byte i=0;i<5;i++){
  writeOneSeg(one[i],N);
  }  
   break;
   case 2:
    writeOneSeg(d1c,N);
    writeOneSeg(d1f,N);
    break;
   case 3:
    writeOneSeg(d1e,N);
    writeOneSeg(d1f,N);
    break;
   case 4:
    writeOneSeg(d1a,N);
    writeOneSeg(d1e,N);
    writeOneSeg(d1d,N);
    break;
   case 5:
    writeOneSeg(d1b,N);
    writeOneSeg(d1e,N);
    break; 
   case 6:
    writeOneSeg(d1b,N);
    break; 
   case 7:
    for(byte i=0;i<4;i++){
           writeOneSeg(seven[i],N);
         }  
    break; 
   case 9:
    writeOneSeg(d1e,N);
    break; 
   default:
    break;
    }
  }
/*DISPLAY 0-9 ON DIGIT TWO*/
void ard4d::d2(byte num) 
{
  byte eight[]={d2a,d2b,d2c,d2d,d2e,d2f,d2g};// put eight on at first then turn off some segments to make other numbers. 
  // the rest number are all off segments on array 
  byte one[]={d2a,d2d,d2e,d2f,d2g};
  byte seven[]={d2d,d2e,d2f,d2g};
for(byte i=0;i<7;i++){
  writeOneSeg(eight[i],Y);
  } // turn 8 on 
  
  switch(num)
  {
    case 0:
    writeOneSeg(d2g,N);
     break;
   case 1:
    for(byte i=0;i<5;i++){
  writeOneSeg(one[i],N);
  }  
   break;
   case 2:
    writeOneSeg(d2c,N);
    writeOneSeg(d2f,N);
    break;
   case 3:
    writeOneSeg(d2e,N);
    writeOneSeg(d2f,N);
    break;
   case 4:
    writeOneSeg(d2a,N);
    writeOneSeg(d2e,N);
    writeOneSeg(d2d,N);
    break;
   case 5:
    writeOneSeg(d2b,N);
    writeOneSeg(d2e,N);
    break; 
   case 6:
    writeOneSeg(d2b,N);
    break; 
   case 7:
    for(byte i=0;i<4;i++){
           writeOneSeg(seven[i],N);
         }  
    break; 
   case 9:
    writeOneSeg(d2e,N);
    break; 
   default:
    break;
    }
  }
/*DISPLAY 0-9 ON DIGIT THREE*/
void ard4d::d3(byte num) 
{
  byte eight[]={d3a,d3b,d3c,d3d,d3e,d3f,d3g};// put eight on at first then turn off some segments to make other numbers. 
  // the rest number are all off segments on array 
  byte one[]={d3a,d3d,d3e,d3f,d3g};
  byte seven[]={d3d,d3e,d3f,d3g};
for(byte i=0;i<7;i++){
  writeOneSeg(eight[i],Y);
  } // turn 8 on 
  
  switch(num)
  {
    case 0:
    writeOneSeg(d3g,N);
     break;
   case 1:
    for(byte i=0;i<5;i++){
  writeOneSeg(one[i],N);
  }  
   break;
   case 2:
    writeOneSeg(d3c,N);
    writeOneSeg(d3f,N);
    break;
   case 3:
    writeOneSeg(d3e,N);
    writeOneSeg(d3f,N);
    break;
   case 4:
    writeOneSeg(d3a,N);
    writeOneSeg(d3e,N);
    writeOneSeg(d3d,N);
    break;
   case 5:
    writeOneSeg(d3b,N);
    writeOneSeg(d3e,N);
    break; 
   case 6:
    writeOneSeg(d3b,N);
    break; 
   case 7:
    for(byte i=0;i<4;i++){
           writeOneSeg(seven[i],N);
         }  
    break; 
   case 9:
    writeOneSeg(d3e,N);
    break; 
   default:
    break;
    }
  }
/*DISPLAY 0-9 ON DIGIT FOUR*/
void ard4d::d4(byte num) 
{
  byte eight[]={d4a,d4b,d4c,d4d,d4e,d4f,d4g};// put eight on at first then turn off some segments to make other numbers. 
  // the rest number are all off segments on array 
  byte one[]={d4a,d4d,d4e,d4f,d4g};
  byte seven[]={d4d,d4e,d4f,d4g};
for(byte i=0;i<7;i++){
  writeOneSeg(eight[i],Y);
  } // turn 8 on 
  
  switch(num)
  {
    case 0:
    writeOneSeg(d4g,N);
     break;
   case 1:
    for(byte i=0;i<5;i++){
  writeOneSeg(one[i],N);
  }  
   break;
   case 2:
    writeOneSeg(d4c,N);
    writeOneSeg(d4f,N);
    break;
   case 3:
    writeOneSeg(d4e,N);
    writeOneSeg(d4f,N);
    break;
   case 4:
    writeOneSeg(d4a,N);
    writeOneSeg(d4e,N);
    writeOneSeg(d4d,N);
    break;
   case 5:
    writeOneSeg(d4b,N);
    writeOneSeg(d4e,N);
    break; 
   case 6:
    writeOneSeg(d4b,N);
    break; 
   case 7:
    for(byte i=0;i<4;i++){
           writeOneSeg(seven[i],N);
         }  
    break; 
   case 9:
    writeOneSeg(d4e,N);
    break; 
   default:
    break;
    }
  }
void ard4d::dot1(bool onOrOff)
{ 
  if(onOrOff==true){
    writeOneSeg(p1,Y);
    }else{
    writeOneSeg(p1,N);
      }
}
void ard4d::dot2(bool onOrOff)
{ 
  if(onOrOff==true){
    writeOneSeg(p2,Y);
    }else{
    writeOneSeg(p2,N);
      }
}
void ard4d::dot3(bool onOrOff)
{ 
  if(onOrOff==true){
    writeOneSeg(p4,Y);
    }else{
    writeOneSeg(p4,N);
      }
}
void ard4d::dotClock(bool onOrOff)
{ 
  if(onOrOff==true){
    writeOneSeg(p3,Y);
    }else{
    writeOneSeg(p3,N);
      }
}

  

