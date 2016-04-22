/* 
--- Instructions ----

1. Compiling:
  g++ -std=c++11 main.cpp -o dmx -lftd2xx

2. Deleting FTDI Driver: 
  - sudo lsmod
  - sudo rmmod ftdi_sio
  - sudo rmmod usbserial
  - https://www.ikalogic.com/ftdi-d2xx-linux-overcoming-big-problem/
*/

#include <stdio.h>
#include <iostream>
#include <cstring>
#include <cmath> 

#include <ctime>

#include "DmxFtdi.h"


uint8_t getColorCycle(int framecount, const float& timescale)
{
  float v = (std::sin(framecount * timescale) * 255 + 255) * 0.5f;
  return (uint8_t)v;
}


int main()
{
  std::cout << "starting dmx... " << std::endl; 

  DmxFTDI mDevice;
  mDevice.init();


  mDevice.setChannelValue(0, 255);
  
  mDevice.setChannelValue(2, 0);  
  mDevice.setChannelValue(3, 0);

  unsigned int framecount = 0;
  double timeCount = 0;
  while(true){

    clock_t begin = clock();

    uint8_t valueRed =  getColorCycle(framecount, 0.01 );
    uint8_t valueGreen =  getColorCycle(framecount, 0.035 );
    uint8_t valueBlue =  getColorCycle(framecount, 0.07 );
    

    mDevice.setChannelValue(1, valueRed);
    mDevice.setChannelValue(2, valueGreen);
    mDevice.setChannelValue(3, valueBlue);

    mDevice.update();

    clock_t end = clock();
 // / CLOCKS_PER_SEC
    double elapsed_time = float(framecount) / double(end-begin);

    timeCount += elapsed_time;

    if(framecount % 60 == 0){
      std::cout << "took: " << elapsed_time << "ms" << std::endl;
      timeCount = 0;
    }

    
    framecount++;
  }
  
}
