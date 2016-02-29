// Brian Malloy        Game Construction
#include "manager.h"
#include <string>
int main(int, char*[]) {


/*      Manager *manager =  new Manager();
   try {
      string ret;
      string seq="first";
      while(true){
      if(seq=="first"){
        ret = manager->play();
        seq="second";
      } 
      if(ret=="r"){
        delete manager;
        manager = new Manager();
        seq="first";
      }
      std::cout<<ret;
      if(ret=="e") break;
       
   }*/

try {
 Manager manager;
  manager.play();
 }
   catch (const string& msg) { std::cout << msg << std::endl; }
   catch (...) {
      std::cout << "Oops, someone threw an exception!" << std::endl;
   }
   return 0;
}
