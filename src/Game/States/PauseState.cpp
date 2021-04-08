#include "PauseState.h"

PauseState::PauseState() {
	resumeButton = new Button(ofGetWidth()/2, ofGetHeight()/2, 64, 50, "Resume");
    quitButton = new Button (ofGetWidth()/2, (ofGetHeight()/2)+50, 64, 50, "Quit");
	
	

}
void PauseState::tick() {
	resumeButton->tick();
    quitButton->tick();

	if(resumeButton->wasPressed()){
		setNextState("Game");
		setFinished(true);

	}
    else if (quitButton->wasPressed()){
		isPaused = false;
        setNextState("Menu");
        setFinished(true);
    }
}
void PauseState::render() {
	ofDrawBitmapString("Pause", ofGetWidth()/2, ofGetHeight()/2-300, 50);
	ofSetBackgroundColor(0, 0, 0);
	ofSetColor(256, 256, 256);
	resumeButton->render();
    quitButton->render();


}

void PauseState::keyPressed(int key){
	
}

void PauseState::mousePressed(int x, int y, int button){
    resumeButton->mousePressed(x, y);
    quitButton->mousePressed(x,y);
}

void PauseState::reset(){
	setFinished(false);
	setNextState("Game");
	resumeButton->reset();
    quitButton->reset();
}

PauseState::~PauseState(){
	delete resumeButton;
    delete quitButton;
	
}