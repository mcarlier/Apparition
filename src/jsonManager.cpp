#include "jsonManager.h"

void jsonManager::setup(){
  Boolean open=counterUser.open("counterUser.json");
  if(open){
    std::cout << "le ficier json est ouvert" << '\n';
  }
}

int jsonManager::getInt(){
  return stoi(counterUser["counterUser"].asString());
}
string jsonManager::getString(){
  return counterUser["counterUser"].asString();
}

void jsonManager::increment(){
  std::cout << "increment" << '\n';
  int a = getInt()+1;
  stringstream ss;
  ss << a;
  counterUser["counterUser"] = ss.str();
  counterUser.save("counterUser.json",false);
}
