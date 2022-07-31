# PTZ-control-based-on-gesture-recognition
![0fd1788615d1b8d2062f0da62b8785c](https://user-images.githubusercontent.com/93221038/182014852-75d2c85f-aed1-49de-be07-14901c2e3ea7.jpg)

# gesture_ detect



This program adopts c++ object-oriented programming and applies multithreading processing scheme.



### Function Description:



You can control the movement of the two axis PTZ by making gestures on the gesture recognition module. Waving left and right corresponds to the left and right rotation angle adjustment of the PTZ, waving up and down corresponds to the up and down pitch angle adjustment of the PTZ, and four LED lights are configured to indicate the recognized gesture direction. The PTZ is equipped with a camera, which can view images in real time on the wireless desktop. It can be used in the live broadcast or monitoring field for users to gesture control the camera angle.



### Hardware introduction:



* Raspberry pie 4B



The card handheld computer developed based on ARM chip runs the raspberry system based on Linux kernel and has a graphical interface. It can connect the computer through the network cable to share the WiFi LAN of the computer, and then the computer carries out raspberry wireless desktop operation through VNC viewer software. Like the main operating logic of Linux system, most instructions and program running modes can be carried out by inputting commands through the terminal command window.



* PAJ7620u2 gesture recognition module



The built-in infrared LED and optical lens can realize gesture recognition in weak light environment. The effective distance of recognition is 5cm~15cm. It supports the recognition of 9 common gestures (up, down, left, right, front, back, clockwise, counterclockwise, swing). It is connected with raspberry pie through IIC communication interface. Raspberry pie can initialize the module through the configuration of registers, and then read the recognition results from the specified registers.



* Pan tilt



The pan tilt can realize two degrees of freedom: left and right rotation and up and down pitch. It is controlled by simulating the steering gear. The raspberry pie uses the wirengpi pin control library to control the pin output PWM signal. The frequency is 50Hz, of which 2.5% - 12.5% duty cycle corresponds to the steering gear rotation of -90% - 90 degrees. The raspberry pie software is configured to rotate 10 degrees every time a valid signal is recognized.



* LED



Raspberry pie controls the illumination and extinction of LED lights through the output high and low levels of the wirengi library control pin. Four LED lights correspond to four different gestures.



* CSI camera



Raspberry pie comes with a CSI camera driver module. Using the capture (0) function of videocapture class in OpenCV image processing library, it can directly read the camera data stream and transfer it to image storage class mat with c++ data stream operation. The image is displayed in real time through imshow function, and the image frame rate is controlled through waitkey function



### Software platform:



* The gesture control PTZ part is programmed with the geeny editor of raspberry pie, and the makefile Compilation Rules are written, and then compiled with make compilation. The executable program generated after compilation can be started directly by inputting instructions on the command line.



* The camera adopts opencv open source library.



### Programming process:



#### Opencv installation process:



* First clone the opencv Repository:



 `git clone https://github.com/opencv/opencv.git `



* Install necessary dependencies



```

sudo apt-get install cmake

sudo apt-get install build-essential libgtk2.0-dev libavcodec-dev libavformat-dev libjpeg-dev libswscale-dev libtiff5-dev

sudo apt-get install libgtk2.0-dev

sudo apt-get install pkg-config

```



* Create a new build folder under the opencv3.4.15 folder, configure the installation path and compile (it takes a long time)



```

mkdir build

cd build

cmake -D CMAKE_ BUILD_ TYPE=Release -D CMAKE_ INSTALL_ PREFIX=/usr/local ..

sudo make

sudo make install

```



* Configure opencv usage environment



```

sudo gedit /etc/ld.so.conf.d/opencv.conf

```



Add the following:



```

/usr/local/lib

```



Save the file changes, and then execute the command to make the configuration effective



```

sudo ldconfig

```



* Modify environment variables



```

sudo gedit /etc/bash.bashrc

```



Add at the end of the text:



```

PKG_ CONFIG_ PATH=$PKG_ CONFIG_ PATH:/usr/local/lib/pkgconfig

export PKG_ CONFIG_ PATH

```



Then enter the command:



```

source /etc/bash.bashrc

pkg-config opencv --modversion

```



If the version number appears, opencv is successfully installed



* If there is no opencv.pc, which leads to an error, you need to create opencv.pc manually



```

cd /usr/local/lib

sudo mkdir pkgconfig

cd pkgconfig

sudo touch opencv.pc

```



Add the following information to opencv.pc. Note that these information should correspond to the library path when you install opencv:



```

prefix=/usr/local

exec_ prefix=${prefix}

includedir=${prefix}/include

libdir=${exec_prefix}/lib



Name: opencv

Description: The opencv library

Version:4.0.1

Cflags: -I${includedir}/opencv4

Libs: -L${libdir} -lopencv_ stitching -lopencv_ objdetect -lopencv_ calib3d -lopencv_ features2d -lopencv_ highgui -lopencv_ videoio -lopencv_ imgcodecs -lopencv_ video -lopencv_ photo -lopencv_ ml -lopencv_ imgproc -lopencv_ flann -lopencv_ core

~

```



Check the opencv version again



```

pkg-config opencv --modversion

```



#### Procedural framework



Three classes are set to encapsulate all functions, corresponding to gesture recognition module, led and steering gear respectively, and four threads are used to control gesture recognition module, LED light, steering gear and camera respectively.




1. First initialize the gesture recognition module.

2. Then initialize the PWM module to control the steering gear

3. Initialize LED control pin

4. Create LED control thread and steering gear control thread

   * Main thread: read the result register of gesture recognition module in real time and detect gestures

   * LED control thread: control the corresponding led to light up in real time according to the gesture recognition results, and turn it off after a delay of 1s

   * Actuator control thread: control and modify the actuator PWM duty cycle in real time according to the gesture recognition results

   * Camera thread: initialize the camera object to read the data stream and display the image in the window in real time
 
# Authors
This project is being completed by a team of Msc Electronics and Electrical Engineering students at the University of Glasgow.
* [Xun Gong, 2696601G](https://github.com/gongsmith)   
* [Hanwei Liang, 2669523L](https://github.com/BrippoLiang)
# Social Media
Welcome to follow us!

<div align="center">

[<img src="https://user-images.githubusercontent.com/102697479/163846803-5ffc0828-5dfa-442f-956b-b11ea940175b.png" width="200" height="100" alt="youtube"/><br/>](https://youtu.be/ROjjHk1d5WQ)[<img src="https://user-images.githubusercontent.com/102697479/163991599-a21b2f16-51bd-4a6e-9639-141a1ae0b943.png" width="200" height="100" alt="Twitter"/><br/>](https://twitter.com/ThanhPhngLc1/status/1516405360973828099)


 </div>
