#include "text.h"

void text::setup(string count){

   myfont.load("unna.ttf", 32);
   pleasesitJPN.load("text/staystilljpn.png");
   userJPN.load("text/usersJPN.png");
   youwereJPN.load("text/youwereJPN.png");
   participationJPN.load("text/participation.png");
   bonTravailJPN.load("text/bontravail.png");
   user = count;
   numberOfUser = stoi(user);

   gui.setup(); // most of the time you don't need a name
   gui.add(a.setup("a", 480, 0, 1000));
   gui.add(b.setup("b", 585, 0, 1000));
   gui.add(c.setup("c", 490, 0, 1000));
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
    string particule = getParticle();
    myfont.drawString("You were the "+user+particule+" user", 470,435);
    youwereJPN.draw(420,490);
    if(numberOfUser<10){
      myfont.drawString(user,570,545);
    }
    else if(numberOfUser<100){
      myfont.drawString(user,570,545);
    }
    else{
      myfont.drawString(user,555,545);
    }
    userJPN.draw(595,490);
    bonTravailJPN.draw(535,535);
  }
  else if(statSusu==1){
    myfont.drawString("Please sit and stay still", 490,455);
    pleasesitJPN.draw(340, 450);
 }

 //gui.draw();
}

string text::getParticle(){
  if(numberOfUser%100==11||numberOfUser%100==12||numberOfUser%100==13){
    return "th";
  }
  else if(numberOfUser%10==1){
    return "st";
  }
  else if(numberOfUser%10==2){
    return "nd";
  }
  else if(numberOfUser%10==3){
    return "rd";
  }
  return "th";
}
