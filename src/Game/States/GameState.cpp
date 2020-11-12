#include "GameState.h"

GameState::GameState() {
    this->restaurant = new Restaurant();
}
void GameState::tick() {
	restaurant->countAngryClients(); //count clients that left
	restaurant->tick();
	if(restaurant->getClientsThatLeft() >= 10){ //ends game when 10 (or more) clients leave
		setFinished(true);
		setNextState("Lose");
	}
	if(restaurant->getMoney() >= 100){ //When reached $100 player has won.
		setFinished(true);
		setNextState("Win");
	}
}
void GameState::render() {
	restaurant->render();
}

void GameState::keyPressed(int key){
	restaurant->keyPressed(key);
}

void GameState::mousePressed(int x, int y, int button){
}

void GameState::keyReleased(int key){
}

void GameState::resetRestaurant(){
	//this will remove the old restaurant and make a new one
	//essentially restarting the game
	delete restaurant;
	this->restaurant = new Restaurant();
}

void GameState::reset(){
	setFinished(false);
	setNextState("");
}