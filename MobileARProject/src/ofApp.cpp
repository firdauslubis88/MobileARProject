#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofDisableArbTex();

	testImage.allocate(1280, 640, OF_IMAGE_COLOR);
	cvImage.allocate(1280, 640);
	thresImage.allocate(1280, 640);
	pixels.allocate(1280, 640, OF_IMAGE_COLOR);
	testImage.load("test-image.png");

	gui.setup();
	gui.add(red_lt.setup("red_lt", 0, 0, 255));
	gui.add(red_ut.setup("red_ut", 255, 0, 255));
	gui.add(green_lt.setup("green_lt", 0, 0, 255));
	gui.add(green_ut.setup("green_ut", 255, 0, 255));
	gui.add(blue_lt.setup("blue_lt", 0, 0, 255));
	gui.add(blue_ut.setup("blue_ut", 255, 0, 255));

	sphereVboMesh = ofSpherePrimitive(2000, 24).getMesh();
	for (int i = 0; i<sphereVboMesh.getNumTexCoords(); i++) {
		sphereVboMesh.setTexCoord(i, ofVec2f(1.0) - sphereVboMesh.getTexCoord(i));
	}
	for (int i = 0; i<sphereVboMesh.getNumNormals(); i++) {
		sphereVboMesh.setNormal(i, sphereVboMesh.getNormal(i) * ofVec3f(-1));
	}

	ldFbo.allocate(1280, 640);

	videoPlayer.load("001_er.mp4");
	videoPlayer.setLoopState(OF_LOOP_NORMAL);
	videoPlayer.play();

	cam.setAutoDistance(false);
	cam.setDistance(0);

}

//--------------------------------------------------------------
void ofApp::update(){
	videoPlayer.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
//	videoPlayer.draw(0, 0);
	ldFbo.begin();
	cam.begin();
	//		ofClear(0);
	//		_shader.begin();
	//		_shader.setUniformTexture("mainTex", ldVideoGrabber.getTexture(), 0);
	//		_shader.setUniforms(ldParameterGroup);
	//		myImage.rotate90(3);
	//		ldVideoGrabber.getTexture().
	videoPlayer.getTextureReference().bind();
	sphereVboMesh.draw();
	videoPlayer.getTextureReference().unbind();
	//		_shader.end();
	cam.end();
	ldFbo.end();
//	ldFbo.draw(0, 0, 1280, 640);
	ldFbo.readToPixels(pixels);
	testImage.setFromPixels(pixels);
	testImage.setImageType(OF_IMAGE_COLOR);
	cvImage.setFromPixels(testImage.getPixels());

	//	cvImage.setFromPixels(testImage.getPixels());
	cv::Mat matInputImage, matOutputImage[5], matOutputImage_ut[3], matOutputImage_lt[3], tempPlanes[3], tempAdd[3];
	matInputImage = cv::cvarrToMat(cvImage.getCvImage());
	cv::cvtColor(matInputImage, matInputImage, CV_BGR2HSV);
	cv::split(matInputImage, tempPlanes);
	vector<cv::Mat>planes = convertColor(tempPlanes, COLOR_DETECT_METHOD::RGB);

	cv::threshold(planes[0], matOutputImage_ut[0], red_ut, 255, 1);
	cv::threshold(planes[0], matOutputImage_lt[0], red_lt, 255, 0);
	cv::threshold(planes[1], matOutputImage_ut[1], green_ut, 255, 1);
	cv::threshold(planes[1], matOutputImage_lt[1], green_lt, 255, 0);
	cv::threshold(planes[2], matOutputImage_ut[2], blue_ut, 255, 1);
	cv::threshold(planes[2], matOutputImage_lt[2], blue_lt, 255, 0);
	cv::bitwise_and(matOutputImage_lt[0], matOutputImage_ut[0], matOutputImage[0]);
	cv::bitwise_and(matOutputImage_lt[1], matOutputImage_ut[1], matOutputImage[1]);
	cv::bitwise_and(matOutputImage_lt[2], matOutputImage_ut[2], matOutputImage[2]);
	cv::bitwise_and(matOutputImage[0], matOutputImage[1], matOutputImage[3]);
	cv::bitwise_and(matOutputImage[2], matOutputImage[3], matOutputImage[4]);
	IplImage temp = matOutputImage[4];
	IplImage* pTemp = &temp;
	thresImage = pTemp;
	
	thresImage.draw(0, 0, 1280, 640);

	gui.draw();
}

vector<cv::Mat> ofApp::convertColor(cv::Mat* tempPlanes, COLOR_DETECT_METHOD method) {
	vector<cv::Mat> vPlanes;
	if (method == COLOR_DETECT_METHOD::NORMALIZED_RGB)
	{
		cv::Mat tempAdd[3], planes[3];
		//	planes = new cv::Mat[3];
		//	tempAdd = new cv::Mat[3];
		cv::add(tempPlanes[0], tempPlanes[1], tempAdd[0]);
		cv::add(tempAdd[0], tempPlanes[2], tempAdd[1]);
		cv::divide(tempPlanes[0], tempAdd[1], planes[0], 255.0);
		cv::divide(tempPlanes[1], tempAdd[1], planes[1], 255.0);
		cv::divide(tempPlanes[2], tempAdd[1], planes[2], 255.0);

		vPlanes.push_back(planes[0]);
		vPlanes.push_back(planes[1]);
		vPlanes.push_back(planes[2]);

		return vPlanes;
	}
	else if(method == COLOR_DETECT_METHOD::RGB)
	{
		vPlanes.push_back(tempPlanes[0]);
		vPlanes.push_back(tempPlanes[1]);
		vPlanes.push_back(tempPlanes[2]);

		return vPlanes;
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

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
