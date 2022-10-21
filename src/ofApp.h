#pragma once

#include "ofMain.h"
#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxCv.h"
#include "ofxGui.h"
#include <math.h>

using namespace ofxCv;
using namespace cv;

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
		float distance(Vec2f a, Vec2f b);
		float findSlope(Vec2f a, Vec2f b);
		void finishBtnEvent();
		void gotMessage(ofMessage msg);

		ofImage img;
		Mat imgMat;
		vector<Vec4i> lines;
		int lineIndex = 0;
		Vec2f location;
		ofxPanel gui;
		ofxIntSlider lowThreshold;
		ofxIntSlider lineVoteThreshold;
		ofxButton finishBtn;
		bool bfinish = false;
		int minLength;
		int maxGap;
		enum Direction {right,left} direction;
};


