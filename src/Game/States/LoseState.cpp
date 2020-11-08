#include "LoseState.h"

LoseState::LoseState(){
    gameOverImg.load("images/game-over-image.jpg");
}

void LoseState::tick(){
    
}

void LoseState::render(){
    ofSetColor(256,256,256); //make it the normal image coloration
    gameOverImg.draw(0, 0, ofGetWidth(), ofGetHeight());
}

void LoseState::keyPressed(int key){
    //allows players to restart by pressing "space"
    if(key == ' '){ 
        setNextState("Game");
        setFinished(true);
    }
}

void LoseState::mousePressed(int x, int y, int button){

}

void LoseState::reset(){
    setFinished(false);
    setNextState("");
}