#include "MenuState.h"

MenuState::MenuState() {
	startButton = new Button(ofGetWidth()/2, ofGetHeight()/2, 64, 50, "Start");
	startScreen.load("images/titleToEdit.jpg");
}
void MenuState::tick() {
	startButton->tick();
	if(startButton->wasPressed()){
		setNextState("Game");
		setFinished(true);

	}
}
void MenuState::render() {
	ofSetColor(256,256,256); //this prevents the screen from being completely black
	this->startScreen.draw(0, 0, ofGetWidth(), ofGetHeight());
	ofSetBackgroundColor(230, 230, 250);
	startButton->render();
	//display instructions/controls
	ofDrawBitmapString("Instructions:\nPress 'e' to pick up ingredients\nPress 's' to serve burger\nPress 'u' to remove the last added ingredient\nPress '1' to calm clients (costs $15)\nPress 'c' to control the chef's movement\nPress 'd' to move the chef to the right once you have control of the chef\nPress 'a' to move the chef to the left once you have control of the chef",(ofGetWidth()/2)*0.2,(ofGetHeight()/2)*1.6);
}

void MenuState::keyPressed(int key){
	
}

void MenuState::mousePressed(int x, int y, int button){
	startButton->mousePressed(x, y);
}

void MenuState::reset(){
	setFinished(false);
	setNextState("");
	startButton->reset();
}