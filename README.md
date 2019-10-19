﻿# Motion Detector

For this project, OpenGL and OpenCv libraries are used.

This application detects motion from video files and puts the motion in a frame highlight.

## ofApp.H
 Include the following header files: 
 - #include “ofMain.h" 
 - #include “ofxGui.h" 
 - #include “ofxOpenCv.h" 
 - #include “ofxCv.h" 
 Declare the relevant parameters inside ofApp class

## ofApp.cpp
**void ofApp::setup()**

This function is called once the program is executed. Load relevant files at this step. 

 -  Example -> mySound.load("beep.wav"); (This line of code loads the “beep.wav” into mySound object, which is type ofSoundPlayer.)

ofFileDialogResult -> is used to open File Chooser Dialog 
ofxIntSlider -> is used to declare slider for gui 
ofVideoPlayer -> is used to declare an openFrameworks video 

 - Setup GUI elements Example -> gui.setup(); gui.add(playButton.setup(“Play”)); (This line of code generates the gui panel and adds a Button called “Play”)

**void ofApp::update()**

This function is called in every frame.

 - use getPixels() to convert ofVideoPlayer object to ofPixels object.
 - use toCv() to convert openFrameworks data to OpenCv data. In our code, toCv() is used to convert ofPixels data to OpenCv supported Matrix type.
 - cvtColor() to apply an adaptive threshold to the Matrix.
 - resize() the Matrix according to scaledWidth and scaledHeight
 - use GaussianBlur on Matrix to reduce the image noise and reduce detail using a Point(25,25).

**void ofApp::update()**

Example on GaussianBlur
![alt text](https://github.com/berkeliboz/Motion-Detector/blob/master/images/1200px-Cappadocia_Gaussian_Blur.svg.png)

- create a copy of the current matrix. 
- use absdiff( ) to compute the perelement absolute difference between both matrixes.
- Apply Treshold Binary.

![alt text](https://github.com/berkeliboz/Motion-Detector/blob/master/images/Capture.PNG)

- Use Dilation for 2 iteration on matrix generated by Treshold Binary method. 
- Generate a copy of the Matrix to use for finding contours.


Example result from findContours

![alt text](https://github.com/berkeliboz/Motion-Detector/blob/master/images/Capture1.PNG)

- Delete the previous Rect type vector by iterating between all members. 
- Use an iteration for every contour and push back contours to a cv::Rect 
- Call toOf() allocate a texture from Matrix 
- Convert ofPixels data to ofTexture type.


**void ofApp::draw()** 
This function is used to draw images to the screen. 
	• Video is drawn in this function every frame. 
	• Draw Rectangles. 

**void ofApp::keyPressed(int key)** 
	This function handles key presses. 	
 
 • Example: 
	  	
	if (key == ' ') { 
		playVideo(); 
		mySound.play(); 
	} 

(The code above will play the video and play the sound file when space key is pressed.)
