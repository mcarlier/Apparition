#include "jsonManager.h"

//Open the Json file.
void jsonManager::setup(){
  Boolean open=counterUser.open("counterUser.json");
  if(open){
    std::cout << "the json file is open" << '\n';
  }
}
//Increment the number of users.
void jsonManager::increment(){
  std::cout << "increment" << '\n';
  int a = getInt()+1;
  stringstream ss;
  ss << a;
  counterUser["counterUser"] = ss.str();
  counterUser.save("counterUser.json",false);
}

//Return the number of user as an int
int jsonManager::getInt(){
  return stoi(counterUser["counterUser"].asString());
}

//Return the number of user as a string
string jsonManager::getString(){
  return counterUser["counterUser"].asString();
}
