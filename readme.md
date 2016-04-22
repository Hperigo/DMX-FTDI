# Dmx - FTDI

This is a simple implementation of dmx protocol using th FTDI chip library ( http://www.ftdichip.com/Drivers/D2XX.htm ), only tested using a raspberry 2, but should work on windows and mac.


# Instructions 
1. Install the FTDI driver 
2. Add the files "ftdxx.h" and "WinTypes.h" to a "include" directory near you project main file.
3. Compile using:
```
  g++ -std=c++11 main.cpp -o dmx -lftd2xx
```
4. run

5. If the program can't be initialized, you may have a driver conflict, do this to delete the other FTDI driver
```
sudo lsmod
sudo rmmod ftdi_sio
sudo rmmod usbserial
https://www.ikalogic.com/ftdi-d2xx-linux-overcoming-big-problem/
```


