#include "text.h"

void text::setup(string count){
  myfont.load("Times.ttf", 32);
  numberOfuser = count;
}
void text::update(string count){
  numberOfuser = count;

}
void text::draw(Boolean waitToGo, Boolean end, int statSusu){
  ofSetColor(ofColor(55,55,55,255));
  if(waitToGo){
    myfont.drawString("You are the"+numberOfuser+" user", 450,500);
    myfont.drawString("The experimentation is over", 450,550);
  }
  else if(statSusu==1){
    myfont.drawString("Please come and seat", 450,450);
      myfont.drawString("Stay still", 450,500);
  }



}
