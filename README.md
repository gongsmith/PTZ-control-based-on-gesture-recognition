# PTZ-control-based-on-gesture-recognition
# Introduction
The movement of the two-axis gimbal can be controlled by making gestures on the gesture recognition module. The left and right hand wave corresponds to the left and right rotation angle adjustment of the gimbal, and the up and down wave corresponds to the up and down pitch angle adjustment of the gimbal. It is equipped with four LED lights to indicate that it is recognized. gesture direction. The PTZ is equipped with a camera that can display the picture in real time on the web page, which can be applied to the user's gesture control of the camera angle in the field of live broadcast or monitoring.
# Hardware Requirements
**Raspberry Pi 4B:**   
The card-type handheld computer developed based on ARM chip runs the raspberry system based on the Linux kernel and has a graphical interface. It can be connected to the computer through a network cable to share the computer WiFi LAN, and then the computer can operate the Raspberry Pi wireless desktop through the VNC Viewer software. Like the main operation logic of the Linux system, most of the instructions and ways of running programs can be performed by entering commands through the terminal command window.  

**PAJ7620U2 gesture recognition module:**    
Built-in infrared LED and optical lens, which can realize gesture recognition in low light environment, the effective distance of recognition is 5CM~15CM, and supports recognition of 9 common gestures (up, down, left, right, front, back, clockwise, counterclockwise) , swing), connect with the Raspberry Pi through the IIC communication interface, the Raspberry Pi can initialize the module through the configuration of the register, and then read the recognition result from the specified register.    

**PTZ:**   
The gimbal can realize two degrees of freedom of left and right rotation and up and down pitch, which is controlled by the analog servo. The Raspberry Pi uses the wiringPi pin control library to control the pin output pwm signal, the frequency is 50Hz, of which 2.5% ~ 12.5% is occupied The ratio corresponds to the rotation of the steering gear -90° ~ 90°. The Raspberry Pi software is configured to rotate 10 degrees each time a valid signal is detected.    

**LED:**    
The Raspberry Pi controls the LED light on and off through the wiringPi library control pin output high and low level, 4 LED lights correspond to 4 different gestures.  

**CSI camera:**  
The Raspberry Pi comes with a CSI camera driver module. After the camera module is turned on in the system, the open source software mjpg-streamer can be used to broadcast the camera image on the LAN. The broadcast URL is IP address: 8080 (eg 192.168.137.163:8080). 
# Software Development
The gesture control gimbal part is programmed with the geany editor that comes with the Raspberry Pi, and the makefile compilation rules are written, and then compiled with the make compilation method. After compiling, the executable program can be started by directly inputting the command on the command line.

lugins
-------

Input plugins:

* input_file
* input_http
* input_opencv ([documentation](mjpg-streamer-experimental/plugins/input_opencv/README.md))
* input_ptp2
* input_raspicam ([documentation](mjpg-streamer-experimental/plugins/input_raspicam/README.md))
* input_uvc ([documentation](mjpg-streamer-experimental/plugins/input_uvc/README.md))

Output plugins:

* output_file
* output_http ([documentation](mjpg-streamer-experimental/plugins/output_http/README.md))
* ~output_rtsp~ (not functional)
* ~output_udp~ (not functional)
* output_viewer ([documentation](mjpg-streamer-experimental/plugins/output_viewer/README.md))
* output_zmqserver ([documentation](mjpg-streamer-experimental/plugins/output_zmqserver/README.md))

Building & Installation
=======================

we must have cmake installed. I used libjpeg8-dev. e.g.

    sudo apt-get install cmake libjpeg8-dev

You may need to install gcc (and g++ for the opencv plugin) too

    sudo apt-get install gcc g++

Simple compilation
------------------

This will build and install all plugins that can be compiled.

    cd mjpg-streamer-experimental
    make
    sudo make install
    
By default, everything will be compiled in "release" mode. If you wish to compile
with debugging symbols enabled, you can do this:

    cd mjpg-streamer-experimental
    make distclean
    make CMAKE_BUILD_TYPE=Debug
    sudo make install
    
Advanced compilation (via CMake)
--------------------------------

There are options available to enable/disable plugins, setup options, etc. This
shows the basic steps to enable the experimental HTTP management feature:

    cd mjpg-streamer-experimental
    mkdir _build
    cd _build
    cmake -DENABLE_HTTP_MANAGEMENT=ON ..
    make
    sudo make install

Usage
=====
From the mjpeg streamer experimental
folder:
```
export LD_LIBRARY_PATH=.
./mjpg_streamer -o "output_http.so -w ./www" -i "input_raspicam.so"
```


The camera driver part uses the mjpg-streamer open source library, which can be downloaded and run directly
# Project Flowchart
# Authors
This project is being completed by a team of Msc Electronics and Electrical Engineering students at the University of Glasgow.
* [Xun Gong, 2696601G](https://github.com/gongsmith)  

* [Hanwei Liang, 2669523L](https://github.com/BrippoLiang)

# Social Media
<div align="center">

[<img src="https://user-images.githubusercontent.com/102697479/163846803-5ffc0828-5dfa-442f-956b-b11ea940175b.png" width="200" height="100" alt="youtube"/><br/>](https://www.youtube.com/watch?v=4pA6-YC3y7Y)[<img src="https://user-images.githubusercontent.com/102697479/163846955-113c0a68-9902-4f2c-83f9-a514ce7df907.png" width="200" height="100" alt="tiktok"/><br/>](https://www.tiktok.com/@smartwheelchair/video/7087989169334652166?is_copy_url=1&is_from_webapp=v1)[<img src="https://user-images.githubusercontent.com/102697479/163991599-a21b2f16-51bd-4a6e-9639-141a1ae0b943.png" width="200" height="100" alt="Twitter"/><br/>](https://twitter.com/ThanhPhngLc1/status/1516405360973828099)
