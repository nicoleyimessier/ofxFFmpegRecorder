#include "ofApp.h"


void ofApp::setup() {
	ofSetFrameRate(30);

	//get back a list of devices.
	vector<ofVideoDevice> devices = m_Grabber.listDevices();

	for (size_t i = 0; i < devices.size(); i++) {
		if (devices[i].bAvailable) {
			//log the device
			ofLogNotice() << devices[i].id << ": " << devices[i].deviceName;
		}
		else {
			//log the device and note it as unavailable
			ofLogNotice() << devices[i].id << ": " << devices[i].deviceName << " - unavailable ";
		}
	}


	m_Grabber.setDeviceID(0);
	m_Grabber.setDesiredFrameRate(30);
	m_Grabber.setup(width, height);

	mCapFbo.allocate(width, height, GL_RGB);

	m_Recorder.setup(true, true, glm::vec2(m_Grabber.getWidth(), m_Grabber.getHeight()));
	m_Recorder.setOverWrite(true);

	// you don't need to set this if FFMPEG is in your system path //
	m_Recorder.setFFmpegPathToAddonsPath();

	/**
	 * You can also use the following methods to crop the output file
	 *     m_Recorder.addAdditionalOutputArgument("-vf \"crop=300:300:0:0\"");
	 * Or you can change the output codec
	 *     m_Recorder.setVideCodec("libx264");
	 **/
}

void ofApp::update() {

	if (useGrabber)
		m_Grabber.update();

}

void ofApp::draw() {

	mCapFbo.begin(); {

		if (useGrabber) {
			ofSetColor(255);
			m_Grabber.draw(0, 0, mCapFbo.getWidth(), mCapFbo.getHeight());
		}

		ofSetColor(ofColor::green);
		if (m_Recorder.isRecording()) ofSetColor(ofColor::red);
		ofDrawCircle(mCapFbo.getWidth() / 2, mCapFbo.getHeight() / 2, ((sin(ofGetElapsedTimef() * 6.) * 0.5 + 0.5) + 0.5) * 100 + 20);
	} mCapFbo.end();

	if (m_Recorder.isRecording()) {
		// ofxFastFboReader can be used to speed this up :)
		mCapFbo.readToPixels(mPix);
		if (mPix.getWidth() > 0 && mPix.getHeight() > 0) {
			m_Recorder.addFrame(mPix);
		}
	}

	mCapFbo.draw(0, 0, width, height);

	ofDrawBitmapStringHighlight(std::to_string(m_Recorder.getRecordedDuration()), 40, 45);
	ofDrawBitmapStringHighlight("FPS: " + std::to_string(ofGetFrameRate()), 10, 16);

	ofPushStyle(); {
		if (m_Recorder.isPaused() && m_Recorder.isRecording()) {
			ofSetColor(ofColor::yellow);
		}
		else if (m_Recorder.isRecording()) {
			ofSetColor(ofColor::red);
		}
		else {
			ofSetColor(ofColor::green);
		}
		ofDrawCircle(ofPoint(10, 40), 10);

		// Draw the information
		ofDrawBitmapStringHighlight("Press spacebar to toggle record custom."
			"\nPress (t) to save thumbnail.",
			10, ofGetHeight() - 200);
	}
	ofPopStyle();
}

void ofApp::keyPressed(int key)
{

}

void ofApp::keyReleased(int key) {
	if (key == ' ') {

		if (m_Recorder.isRecording()) {
			// stop
			m_Recorder.stop();
		}
		else {
			//#if defined(TARGET_OSX)
			//            m_Recorder.setOutputPath( ofToDataPath(ofGetTimestampString() + ".mp4", true ));
			//#else
			//            m_Recorder.setOutputPath( ofToDataPath(ofGetTimestampString() + ".avi", true ));
			//#endif
			//            m_Recorder.startCustomRecord();

			string time_stamp = ofToDataPath(ofGetTimestampString(), true);
			m_Recorder.setOutputPath(time_stamp + ".mp4");
			m_Recorder.setAudioOutputPath(time_stamp + ".mp3");
			
			if(useGrabber)
				m_Recorder.startCustomRecord();
			else
				m_Recorder.record();
		}
	}
	else if (key == 't') {
		m_Recorder.saveThumbnail(0, 0, 2, "thumbnail.png", ofVec2f(0, 0), ofRectangle(0, 0, 500, 400));
	}
	else if( key == 'c')
	{
		m_Grabber.close();
		m_Recorder.setOutputPath(ofToDataPath(ofGetTimestampString() + ".mp4", true));
		m_Recorder.record();
	}
	else if(key == 'o')
	{
		m_Recorder.stop();
		m_Grabber.setDeviceID(0);
		m_Grabber.setup(width, height); 
	}
	else if(key == 's')
	{
		// stop
		m_Recorder.stop();
	}
}

void ofApp::mouseMoved(int x, int y)
{

}

void ofApp::mouseDragged(int x, int y, int button)
{

}

void ofApp::mousePressed(int x, int y, int button)
{

}

void ofApp::mouseReleased(int x, int y, int button)
{

}

void ofApp::mouseEntered(int x, int y)
{

}

void ofApp::mouseExited(int x, int y)
{

}

void ofApp::windowResized(int w, int h)
{

}

void ofApp::gotMessage(ofMessage msg)
{

}

void ofApp::dragEvent(ofDragInfo dragInfo)
{

}

void ofApp::exit()
{
	m_Grabber.close();
}
