#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){
	playButton.addListener(this, &ofApp::playVideo);
	playVid = false;

	
	result = ofSystemLoadDialog("Load file");
	
	videoPlayer.load(result.fileName);
	maxFrames = videoPlayer.getTotalNumFrames();
	videoHeight = videoPlayer.getHeight();
	videoWidth = videoPlayer.getWidth();

	gui.setup();

	gui.add(playButton.setup("Play"));
	gui.add(slider.setup("Video Slider", 0, 1,maxFrames));
	gui.add(sliderFrames.setup("Frames Value", 50, 1, 150));
	gui.add(sliderTreshold.setup("Treshold",23,1,150));



	scaleFactor = 1;

	scaledWidth = ((float)videoPlayer.getWidth()) * scaleFactor;
	scaledHeight = ((float)videoPlayer.getHeight()) * scaleFactor;

	std::cout << "Width is: " << videoWidth << " Height is: " << videoHeight << endl;

	
}



//--------------------------------------------------------------
void ofApp::update(){
	
	videoPlayer.update();
	videoManager();
	
	auto videoPixels = videoPlayer.getPixels();
	auto imgMat = ofxCv::toCv(videoPixels);

	// Our analysis goes here.
	cv::cvtColor(imgMat, imgMat, CV_BGR2GRAY);
	cv::resize(imgMat, imgMat, cv::Size(scaledWidth, scaledHeight));
	cv::GaussianBlur(imgMat, imgMat, cv::Point(25, 25), 0);
	if (framesCount < sliderFrames) {
		imgMat.copyTo(firstFrame);
		framesCount++;
	}

	cv::absdiff(firstFrame, imgMat, imgMat);
	int thresh = sliderTreshold; 
	cv::threshold(imgMat, imgMat, thresh, 255, cv::THRESH_BINARY);
	cv::dilate(imgMat, imgMat, {}, cv::Point(-1, -1), 2);

	vector<vector<cv::Point>> contours;
	vector<cv::Vec4i> hierarchy;
	cv::Mat forContours;
	imgMat.copyTo(forContours);
	cv::findContours(forContours, contours, CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE);

	boundingBoxes.clear();
	for (auto contour : contours) {
		if (cv::contourArea(contour) < 500) {
			continue;
		}
		boundingBoxes.push_back(cv::boundingRect(cv::Mat(contour)));
	}
	
	ofxCv::toOf(imgMat, analysisPixels);
	analysisTexture.loadData(analysisPixels);


	ofSetWindowShape(videoPlayer.getWidth(), videoPlayer.getHeight());
}

//--------------------------------------------------------------
void ofApp::draw(){

	
	//Responsive window size changes handles here
	//videoPlayer.draw(ofGetWidth()/2 - videoWidth/2, ofGetHeight()/2 - videoHeight/2);
	videoPlayer.draw(0, 0);
	gui.draw();

	ofNoFill();
	ofSetLineWidth(2);
	for (auto boundingBox : boundingBoxes) {
		int x = ((float)boundingBox.x) / scaleFactor;
		int y = ((float)boundingBox.y) / scaleFactor;
		int width = ((float)boundingBox.width) / scaleFactor;
		int height = ((float)boundingBox.height) / scaleFactor;
		ofDrawRectangle(x, y, width, height);

	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

	if (key == ' ')
		playVideo();

	
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

	//std::cout << "Mouse moved! Pos x: " << x << " Pos y: " << y << endl;

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

void ofApp::playVideo() {
	playVid = !playVid;

}



void ofApp::videoManager() {

	if (playVid) {
		videoPlayer.setPaused(false);
		slider = videoPlayer.getCurrentFrame();
	}

	else {
		videoPlayer.setPaused(true);
		videoPlayer.setFrame(slider);
	}
}


	