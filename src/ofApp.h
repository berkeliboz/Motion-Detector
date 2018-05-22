#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxOpenCv.h"
#include "ofxCv.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
	
		void playVideo();
		void videoManager();
		
		ofVideoPlayer videoPlayer;
		int videoHeight;
		int videoWidth;
		string fileName;
		

		ofxPanel gui; 

		bool playVid;
		int maxFrames;

		ofxIntSlider slider;

		ofxIntSlider sliderTreshold;
		ofxIntSlider sliderFrames;


		ofxButton playButton;
		string filePath;

		ofFileDialogResult result;

		ofPixels analysisPixels;
		ofTexture analysisTexture;

		int scaledWidth;
		int scaledHeight;

		float scaleFactor;

		int framesCount;
		cv::Mat firstFrame;

		vector<cv::Rect> boundingBoxes;
	
};
