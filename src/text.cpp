#include "text.h"

void text::setup(){
  myfont.load("Times.ttf", 32);
}
void text::update(){

}
void text::draw(){
  ofSetColor(ofColor(255,255,255,255));
  myfont.drawString("Please come and seat", 450,450);
  myfont.drawString("Thank you for your participation", 450,500);
  myfont.drawString("The experimentation is over", 450,550);

}
