#include "StoveCounter.h"

StoveCounter::StoveCounter(int x, int y, int width, int height, Item* item, ofImage sprite): BaseCounter(x,y,width,height,item,sprite){
    ofImage idleImg("images/iconToEdit.png");
    this->notCookingImg.cropFrom(idleImg,0,4,50,46);
}
void StoveCounter::displayIcon(){
    if(this->burgerIsCooked){
        BaseCounter::showItem();
    }else{
        this->notCookingImg.draw(x+width/2 -25, y-30, 50, 30);
    }
}