#include "ofApp.h"
#include "Images.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetWindowTitle("C++ Game Box");
	//States
	menuState = new MenuState();
	gameState = new GameState();
	loseState = new LoseState();
	winState = new WinState();
	// Initial State
	currentState = menuState;

	//----------------(music)--------------------
	gameMusic.load("music/gameMusicWithFade.mp3");
	gameMusic.setLoop(true);
	gameMusic.play();
	loseMusic.load("music/loseMusic.mp3");
	loseMusic.setVolume(0.6);
	loseMusic.setLoop(true);
	winMusic.load("music/winMusic.mp3");
}

//--------------------------------------------------------------
void ofApp::update(){
	if (currentState != nullptr){
		currentState->tick();
		if(currentState->hasFinished()){
			if(currentState->getNextState() == "Menu"){
				currentState = menuState;
			}else if(currentState->getNextState() == "Game" && dynamic_cast<MenuState*>(currentState)){
				//if we were in the menu, switch to the gameState
				currentState = gameState;
			}else if(currentState->getNextState() == "Game" && dynamic_cast<LoseState*>(currentState)){
				//if we restarted from a game over then reset the game first
				gameState->resetRestaurant();
				currentState = gameState;
				playCorrectMusic();
			}else if(currentState->getNextState() == "Game" && dynamic_cast<WinState*>(currentState)){
				//if we restarted from WinState then reset the game first
				gameState->resetRestaurant();
				currentState = gameState;
				playCorrectMusic();
			}else if(currentState->getNextState() == "Lose"){
				//Enter "lose" state
				currentState = loseState;
				playCorrectMusic();
			}
			else if(currentState->getNextState() == "Win"){
				//Enter "Win" state
				currentState = winState;
				playCorrectMusic();
			}
			currentState->reset();
		}
	}
		
}

//--------------------------------------------------------------
void ofApp::draw(){
	if (currentState != nullptr)
		currentState->render();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (currentState != nullptr)
		currentState->keyPressed(key);

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	if (currentState != nullptr)
			currentState->keyReleased(key);
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
	if (currentState != nullptr)
		currentState->mouseMoved(x, y);
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
	if (currentState != nullptr)
		currentState->mouseDragged(x, y, button);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	if (currentState != nullptr)
		currentState->mousePressed(x, y, button);
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
	if (currentState != nullptr)
		currentState->mouseReleased(x, y, button);
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){
	if (currentState != nullptr)
			currentState->mouseEntered(x, y);
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){
	if (currentState != nullptr)
		currentState->mouseExited(x, y);
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
	if (currentState != nullptr)
			currentState->windowResized(w, h);
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
	if (currentState != nullptr)
		currentState->gotMessage(msg);
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 
	if (currentState != nullptr)
		currentState->dragEvent(dragInfo);
}

//--------------------------------------------------------------
void ofApp::playCorrectMusic(){
	//stops all music then plays the correct one
	gameMusic.stop();
	loseMusic.stop();
	winMusic.stop();
	if(dynamic_cast<WinState*>(currentState)){
		winMusic.play();
	}else if(dynamic_cast<LoseState*>(currentState)){
		loseMusic.play();
	}else{
		gameMusic.play();
	}
}