# gesture_detect



### Function Description:



You can control the movement of the two axis PTZ by making gestures on the gesture recognition module. Waving left and right corresponds to the left and right rotation angle adjustment of the PTZ, waving up and down corresponds to the up and down pitch angle adjustment of the PTZ, and four LED lights are configured to indicate the recognized gesture direction. The PTZ is equipped with a camera that can display the image in real time on the web page, which can be used to control the camera angle in the live broadcast or monitoring field.



### Hardware introduction:



* Raspberry pie 4B



The card handheld computer developed based on ARM chip runs the raspberry system based on Linux kernel and has a graphical interface. It can connect the computer through the network cable to share the WiFi LAN of the computer, and then the computer carries out raspberry wireless desktop operation through VNC viewer software. Like the main operating logic of Linux system, most instructions and program running modes can be carried out by inputting commands through the terminal command window.



* Paj7620u2 gesture recognition module



The built-in infrared LED and optical lens can realize gesture recognition in weak light environment. The effective distance of recognition is 5cm~15cm. It supports the recognition of 9 common gestures (up, down, left, right, front, back, clockwise, counterclockwise, swing). It is connected with raspberry pie through IIC communication interface. Raspberry pie can initialize the module through the configuration of registers, and then read the recognition results from the specified registers.



* Pan tilt



The pan tilt can realize two degrees of freedom: left and right rotation and up and down pitch. It is controlled by simulating the steering gear. The raspberry pie uses the wirengpi pin control library to control the pin output PWM signal. The frequency is 50Hz, of which 2.5% - 12.5% duty cycle corresponds to the steering gear rotation of -90% - 90 degrees. The raspberry pie software is configured to rotate 10 degrees every time a valid signal is recognized.



* LED



Raspberry pie controls the illumination and extinction of LED lights through the output high and low levels of the wirengi library control pin. Four LED lights correspond to four different gestures.



* CSI camera



Raspberry pie comes with its own CSI camera driver module. After opening the camera module in the system, the open source software mjpg streamer can broadcast the camera image on the LAN. The broadcast website address is IP address: 8080 (such as 192.168.137.163:8080)



### Software platform:



* The gesture control PTZ part is programmed with the geeny editor of raspberry pie, and the makefile Compilation Rules are written, and then compiled with make compilation. The executable program generated after compilation can be started directly by inputting instructions on the command line.



* The camera driver adopts mjpg streamer open source library, which can be downloaded and run directly.



### Programming process:



1. First initialize the gesture recognition module.



2. Then turn on the camera



3. Then initialize the PWM module to control the steering gear



4. Initialize LED control pin



5. The main loop reads the gesture recognition result register:



If an effective gesture is detected, control the pan tilt steering gear to move, light the corresponding indicator light, and wait for about 1s to turn off the indicator light.



### Note:

This program adopts C language and compiles with c++, and the next version is changed to c++.