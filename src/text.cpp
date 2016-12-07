#include "text.h"

void text::setup(string count){
  //myfont.load("华文仿宋.ttf", 32);
   myfont.load("unna.ttf", 32);
  numberOfuser = count;
}
void text::update(string count){
  numberOfuser = count;

}
void text::draw(Boolean waitToGo, Boolean end, int statSusu){
  ofSetColor(ofColor(255,255,255,255));
  if(waitToGo){
    myfont.drawString("You were the "+numberOfuser+" user", 450,500);
    myfont.drawString("Thank you for your participation", 350,450);
  }
  else if(statSusu==1){
    myfont.drawString("Please sit and stay still", 450,450);
    // myfont.drawString("aaa座って静かにしてください", 450,500);
  }



}
