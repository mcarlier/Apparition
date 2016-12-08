#include "text.h"

void text::setup(string count){

   myfont.load("unna.ttf", 32);
   pleasesitJPN.load("text/staystilljpn.png");
   userJPN.load("text/usersJPN.png");
   youwereJPN.load("text/youwereJPN.png");
   participationJPN.load("text/participation.png");
   user = count;
   numberOfUser = stoi(user);

   gui.setup(); // most of the time you don't need a name
   gui.add(a.setup("a", 380, 0, 1000));
   gui.add(b.setup("b", 385, 0, 1000));
   gui.add(c.setup("c", 425, 0, 1000));
   gui.add(d.setup("d", 470, 0, 1000));
   gui.add(e.setup("e", 485, 0, 1000));
   gui.add(f.setup("f", 435, 0, 1000));
   gui.add(g.setup("g", 450, 0, 1000));
   gui.add(h.setup("h", 515, 0, 1000));
   gui.add(i.setup("i", 620, 0, 1000));
   gui.add(j.setup("j", 560, 0, 1000));
   gui.add(k.setup("k", 660, 0, 1000));
   gui.add(l.setup("l", 518, 0, 1000));


}
void text::update(string count){
  user = count;
  numberOfUser = stoi(user);

}
void text::draw(Boolean waitToGo, Boolean end, int statSusu){
  ofSetColor(ofColor(255,255,255,255));
  if(waitToGo){
  myfont.drawString("Thank you for your participation", 380,385);
  participationJPN.draw(425,470);
    myfont.drawString("You were the "+user+" user", 485,435);
    if(numberOfUser<10){
      youwereJPN.draw(450,515);
      myfont.drawString(user,620,560);
      userJPN.draw(625,518);
    }
    else if(numberOfUser<100){
      youwereJPN.draw(450,515);
      myfont.drawString(user,620,560);
      userJPN.draw(640,518);
    }
    else{
      youwereJPN.draw(450,515);
      myfont.drawString(user,620,560);
      userJPN.draw(k,518);
    }
  }
  else if(statSusu==1){
    myfont.drawString("Please sit and stay still", 490,455);
    pleasesitJPN.draw(460, 450);

 }

 //gui.draw();
}
