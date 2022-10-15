#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetFrameRate(60);
	gui.setup();
	gui.add(lowThreshold.setup("low threshold", 50, 0, 100));
	gui.add(lineVoteThreshold.setup("line vote threshold", 10, 0, 200));
	gui.add(minLength.setup("minLength", 1, 0, 100));
	gui.add(maxGap.setup("Gap", 0, 0, 100));

	img.load("line1.jpg");
	img.resize(1000, 1000);

	imgMat = toCv(img);
	cvtColor(imgMat, imgMat, CV_BGR2GRAY);
	GaussianBlur(imgMat, 3);
	Canny(imgMat, imgMat, lowThreshold, lowThreshold * 2);
	dilate(imgMat, 2);
	erode(imgMat, 3);
	HoughLinesP(imgMat, lines, 1, CV_PI / 180, lineVoteThreshold, minLength, maxGap);
	sort(lines.begin(), lines.end(), [&](Vec4i a, Vec4i b) {
		return (a[0] < b[0] || (a[0] == b[0] && a[1]>b[1]));
		});
	if (lines.size() > 0) {
		location[0] = lines[0][0];
		location[1] = lines[0][1];
	}
	direction = Direction::right;
}

//--------------------------------------------------------------
void ofApp::update(){

	if (direction == Direction::right) {
		Vec2i headPoint, tailPoint, targetPoint;
		headPoint[0] = lines[lineIndex][0];
		headPoint[1] = lines[lineIndex][1];
		tailPoint[0] = lines[lineIndex][2];
		tailPoint[1] = lines[lineIndex][3];
		targetPoint = (location[0] < headPoint[0]) ? headPoint : tailPoint;
		float rad = atan2(targetPoint[1] - location[1], targetPoint[0] - location[0]);
		float deltaX = cos(rad);
		float deltaY = sin(rad);
		float speed = (1 > distance(location, targetPoint)) ? distance(location, targetPoint) : 1;
		location[0] += speed * deltaX;
		location[1] += speed * deltaY;
		if (location[0] >= tailPoint[0]) {
			lineIndex++;
		}
		if (lineIndex >= lines.size()) {
			direction = Direction::left;
			lineIndex = lines.size() - 1;
		}
	}

	if(direction == Direction::left) {
		Vec2i headPoint, tailPoint, targetPoint;
		headPoint[0] = lines[lineIndex][2];
		headPoint[1] = lines[lineIndex][3];
		tailPoint[0] = lines[lineIndex][0];
		tailPoint[1] = lines[lineIndex][1];
		targetPoint = (location[0] > headPoint[0]) ? headPoint : tailPoint;
		float rad = atan2(location[1]- targetPoint[1],location[0]- targetPoint[0]);
		float deltaX = cos(rad);
		float deltaY = sin(rad);
		float speed = (1 > distance(location, targetPoint)) ? distance(location, targetPoint) : 1;
		location[0] += -speed * deltaX;
		location[1] += -speed * deltaY;
		if (location[0] <= tailPoint[0]) {
			lineIndex--;
		}
		if (lineIndex <= 0) {
			direction = Direction::right;
			lineIndex = 0;
		}
	}
	//location[0] = lines[lineIndex][0];
	//location[1] = lines[lineIndex][1];
	//lineIndex++;
	cout << location[0] <<":"<< lineIndex << endl;
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofSetColor(255, 255, 255);
	drawMat(imgMat,0,0);
	ofSetColor(255, 0, 0);
	for (int i = 0; i < lines.size(); i++) {
		float x1 = lines[i][0];
		float y1 = lines[i][1];
		float x2 = lines[i][2];
		float y2 = lines[i][3];
		ofPolyline l;
		l.addVertex(x1, y1);
		ofDrawCircle(x1, y1, 2);
		l.addVertex(x2, y2);
		ofDrawCircle(x2, y2, 2);
		l.draw();
	}
	ofSetColor(255, 255, 0);
	ofDrawCircle(int(location[0]), int(location[1]), 10);
	gui.draw();
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

float ofApp::distance(Vec2f a, Vec2f b) {
	return sqrt(pow(a[0] - b[0], 2) + pow(a[1] - b[1], 2));
}

float ofApp::findSlope(Vec2f a, Vec2f b) {
	return (a[1] - b[1])/ a[0] - b[0];
}
