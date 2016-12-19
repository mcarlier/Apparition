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
   gui.add(a.setup("a", 570, 0, 1000));
   gui.add(b.setup("b", 515, 0, 1000));
   gui.add(c.setup("c", 620, 0, 1000));
   gui.add(d.setup("d", 560, 0, 1000));
   gui.add(e.setup("e", 625, 0, 1000));
   gui.add(f.setup("f", 518, 0, 1000));
   gui.add(g.setup("g", 425, 0, 1000));
   gui.add(h.setup("h", 470, 0, 1000));
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
  participationJPN.draw(445,445);
    myfont.drawString("You were the "+user+" user", 485,435);
    if(numberOfUser<10){
      youwereJPN.draw(420,490);
      myfont.drawString(user,570,545);
      userJPN.draw(595,490);
    }
    else if(numberOfUser<100){
      youwereJPN.draw(420,490);
      myfont.drawString(user,570,545);
      userJPN.draw(595,490);
    }
    else{
      youwereJPN.draw(420,490);
      myfont.drawString(user,555,545);
      userJPN.draw(595,490);
    }
  }
  else if(statSusu==1){
    myfont.drawString("Please sit and stay still", 490,455);
    pleasesitJPN.draw(340, 450);

 }

 //gui.draw();
}
