#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxOpenCv.h"

#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		enum COLOR_DETECT_METHOD {
			RGB, NORMALIZED_RGB
		};

		vector<cv::Mat> convertColor(cv::Mat* tempPlanes, COLOR_DETECT_METHOD);

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
		
		ofImage testImage, bgImage, checkImage, finalOfImage;
		ofxCvColorImage cvImage, cvBgImage, cvImage2, combinedImage;
		ofxCvGrayscaleImage thresImage;
		ofPixels pixels, bgPixels, tempPixels, tempBgPixels;

		ofxIntSlider red_lt, red_ut, green_lt,green_ut, blue_lt, blue_ut;
		ofxPanel gui;

		ofVideoPlayer videoPlayer;
		ofEasyCam cam, cam2;
		ofVboMesh sphereVboMesh, bgSphereVboMesh;
		ofFbo ldFbo, ldBgFbo;

};
