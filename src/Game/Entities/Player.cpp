#include "Player.h"

Player::Player(int x, int y, int width, int height, ofImage sprite, EntityManager* em) : Entity(x, y, width, height, sprite){

    vector<ofImage> chefAnimframes;
    ofImage temp;
    this->burger = new Burger(ofGetWidth()-110, 100, 100, 50);
    temp.cropFrom(sprite, 30,3,66,120);
    chefAnimframes.push_back(temp);
    temp.cropFrom(sprite, 159,3,66,120);
    chefAnimframes.push_back(temp);
    temp.cropFrom(sprite, 287, 3,67,120);
    chefAnimframes.push_back(temp);
    temp.cropFrom(sprite, 31,129,66,120);
    chefAnimframes.push_back(temp);
    this->chefAnim = new Animation(50, chefAnimframes);
    this->entityManager = em;
    
}
void Player::tick(){
    chefAnim->tick();
    if(facing == "left"){
        x-=speed;
    }else if(facing == "right"){
        x+=speed;
    }
    if(x <= 0){
        facing = "right";
    }else if(x + width >= ofGetWidth()){
        facing = "left";
    }
    if(startTimer){ //while timer is on, count ticks
        this->cookTimer++;
    }
}

void Player::render(){
    BaseCounter* ac = getActiveCounter();
    StoveCounter* stoveAc = dynamic_cast<StoveCounter*>(ac);
    if(stoveAc != nullptr){
        if(this->cookTimer > 160){
            stoveAc->setBurgerIsCooked(true);
        }
        stoveAc->displayIcon();
    }
    else if(ac != nullptr){
        ac->showItem();
    }
    ofSetColor(256,256,256);
    ofImage currentFrame = chefAnim->getCurrentFrame();
   if(facing == "left"){
       currentFrame.mirror(false, true);
    }
   currentFrame.draw(x, y, width, height);
   burger->render();
}

void Player::keyPressed(int key){
    if(key == 'e'){
        BaseCounter* ac = getActiveCounter();
        StoveCounter* stoveAc = dynamic_cast<StoveCounter*>(ac);
        //if timer if off turn it on, while timer is less than 160 ticks, don't give item
        if(stoveAc != nullptr && this->cookTimer <= 160){ 
            startTimer = true;
        }
        else if(ac != nullptr){
            Item* item = ac->getItem();
            if(item != nullptr){
                burger->addIngredient(item);
            }
            if(stoveAc != nullptr){
                //this means we took the item from the stove so stop and reset the timer
                stoveAc->setBurgerIsCooked(false);
                startTimer = false;
                cookTimer = 0;
            }
        }
    }else if(key == 'u'){
        this->burger->removeIngredient();
    }
}
BaseCounter* Player::getActiveCounter(){
    for(Entity* e:entityManager->entities){
        BaseCounter* c = dynamic_cast<BaseCounter*>(e);
        if(x + e->getWidth()/2 >= e->getX() && x +e->getWidth()/2 <e->getX() + e->getWidth()){
            return c;
        }
    }
    return nullptr;
}
void Player::keyReleased(int key){
}
void Player::mousePressed(int x, int y, int button){

}

void Player::setFacing(string facing){
    this->facing = facing;
}