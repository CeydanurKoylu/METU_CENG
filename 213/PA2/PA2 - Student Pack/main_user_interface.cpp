#include <iostream>
#include "user_interface.h"
using namespace std;
int main(void){
    Movie KFP("KungFuPanda",2009,9.9);
    Movie Turkiye("Turkiye",2023,3.3);
    Movie VFV("VForVandetta",2002,7.9);
    Movie HTTYD("HTTYD",2010,10.0);
    Movie AbdulBari("AbdulBari",2024,5.5);
    Movie Erastour("Erastour",2023,13.13);
    Movie GTF("GraveOfTheFrieflies",2004,7.5);
    Movie BD("BeynimDurdu",1999,1.1);
    UserInterface mytest;
      mytest.addUser("5abcdef");
      mytest.addUser("abcgef");
      mytest.addUser("bcef");
      mytest.addUser("xabc");
      mytest.addUser("abc123");
      mytest.addUser("defabcghi");
      mytest.addUser("a1c123");
      mytest.addUser("abfbcf");
      mytest.addUser("act");
      mytest.addUser("eaxbcdlf");
      mytest.addUser("abcmnop");
      mytest.addUser("dcefghijkl");
      mytest.addUser("user1");
      mytest.addUser("abcdef123");
      mytest.addUser("ghabcdef123");
      mytest.addUser("12345ac");
      mytest.addUser("1345ac");
      mytest.addUser("xyzzfzf");
      mytest.addUser("xyzzzf");
      mytest.addUser("aaaaaabbbbbcccccabcdefghi");
      mytest.addUser("CeydanurKoylu");
      mytest.addUser("TahaKarageldi");         
      mytest.addUser("ZeynepPektas");
      mytest.addUser("ZeynepOzbek");
      mytest.addUser("SudemFeyzaUdul");
    mytest.addWatchedMovie("CeydanurKoylu",KFP);
    mytest.addWatchedMovie("CeydanurKoylu",AbdulBari);
    mytest.addWatchedMovie("CeydanurKoylu",VFV);
    mytest.addWatchedMovie("CeydanurKoylu",HTTYD);
    mytest.addWatchedMovie("CeydanurKoylu",GTF);
    mytest.addWatchedMovie("CeydanurKoylu",BD);
    mytest.addWatchedMovie("ZeynepPektas",Erastour);
    mytest.addWatchedMovie("ZeynepPektas",KFP);
    mytest.addWatchedMovie("ZeynepPektas",AbdulBari);
    mytest.addWatchedMovie("ZeynepOzbek",AbdulBari);
    mytest.addWatchedMovie("ZeynepOzbek",Erastour);
    mytest.addWatchedMovie("ZeynepOzbek",BD);
     mytest.addWatchedMovie("SudemFeyzaUdul",VFV);
     mytest.addWatchedMovie("SudemFeyzaUdul",AbdulBari);
     mytest.addWatchedMovie("SudemFeyzaUdul",GTF);   
     mytest.addWatchedMovie("TahaKarageldi",Turkiye);
     mytest.addWatchedMovie("TahaKarageldi",BD);
    
    mytest.printUsers();
    cout << endl;
    BST<Movie>* obj;
    obj = mytest.mergeWatchedMovies("ZeynepOzbek", "SudemFeyzaUdul");
    (*obj).print();
    cout << endl;
    obj = mytest.intersectionWatchedMovies("CeydanurKoylu", "ZeynepPektas");
    (*obj).print();
    /*
   vector<User*> foundUsersContains;
   mytest.findUsersContains("e????????*???????",foundUsersContains);
   while(!foundUsersContains.empty()){
    cout << *(foundUsersContains[0]) << endl;
    foundUsersContains.erase(foundUsersContains.begin());
   }*/
    return 0;
}