#include <thread>
#include "include/ftd2xx.h"


#define DMX_DATA_SIZE 512

class DmxFTDI {
public:

  DmxFTDI(){

  }
  ~DmxFTDI(){

    if (_mFtHandle != nullptr){
      FT_Close(_mFtHandle);
    }

  }


  FT_STATUS init(int portNumber = 0){

    FT_STATUS ftStatus;


    char nameBuffer[64];
    ftStatus = FT_ListDevices(0,nameBuffer,FT_LIST_BY_INDEX|FT_OPEN_BY_DESCRIPTION);
    std::cout << "device names: " << nameBuffer << std::endl;


    ftStatus = FT_Open(portNumber, &_mFtHandle);
    if(ftStatus != FT_OK) {
      std::cout << "Error opening device: " << ftStatus << std::endl;
    }


    // Set boud rate
    ftStatus = FT_SetBaudRate(_mFtHandle, 250000);
    if (ftStatus != FT_OK) 
    { 
      FT_Close(_mFtHandle);
      printf("Failure.  FT_SetBaudRate returned %d.\n",
       (int)ftStatus);
      return ftStatus;
    }


    // set data model
    ftStatus = FT_SetDataCharacteristics(_mFtHandle, FT_BITS_8, FT_STOP_BITS_2,FT_PARITY_NONE);
    if(ftStatus != FT_OK)
    {
      FT_Close(_mFtHandle);
      printf("Can't set characteristics\n");
      return ftStatus;
    }


    memset(&_mDMXBuffer[0], 0, sizeof(_mDMXBuffer));
    return ftStatus;
  }


  void setChannelValue(size_t index, uint8_t value){

    /* assert */

    _mDMXBuffer[index] = value;

  }

  // 
  void setBuffer(unsigned char buffer, size_t size){
    memset(_mDMXBuffer, buffer, size);
  }

  void update(){

    FT_STATUS ftStatus = FT_SetBreakOn(_mFtHandle);
    std::this_thread::sleep_for( std::chrono::milliseconds(10) );
    // std::cout << "10ms" << std::endl;

    ftStatus = FT_SetBreakOff(_mFtHandle);
    std::this_thread::sleep_for( std::chrono::microseconds(8) );
    // std::cout << "8us" << std::endl;

    ftStatus = FT_Write(_mFtHandle, &_mStartCode, 1, &_mBytesWritten);
    ftStatus = FT_Write(_mFtHandle, _mDMXBuffer, DMX_DATA_SIZE, &_mBytesWritten);
    std::this_thread::sleep_for( std::chrono::milliseconds(15) );    

  }


private:
  FT_HANDLE _mFtHandle = nullptr;

  unsigned char _mStartCode = 0;
  unsigned char _mDMXBuffer[DMX_DATA_SIZE];

  unsigned int _mBytesWritten;

};