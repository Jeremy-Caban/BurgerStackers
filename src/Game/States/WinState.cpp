#include "WinState.h"

WinState::WinState(){
    WinStateImg.load("images/winner.jpg");
}

void WinState::tick(){
    
}

void WinState::render(){
    ofSetColor(256,256,256); //make it the normal image coloration
    WinStateImg.draw(0, 0, ofGetWidth(), ofGetHeight());
    ofSetColor(0,0,0); //Black color for displaying winner message.
    ofDrawBitmapString("You Won!!! You reached a 100 dollars! Congratulations.",(ofGetWidth()/2)-200, 30);
    ofDrawBitmapString("To play again press your Space Bar.",(ofGetWidth()/2)-140, 45);
}

void WinState::keyPressed(int key){
    //allows players to restart by pressing "space"
    if(key == ' '){ 
        setNextState("Game");
        setFinished(true);
    }
}

void WinState::mousePressed(int x, int y, int button){

}

void WinState::reset(){
    setFinished(false);
    setNextState("");
}