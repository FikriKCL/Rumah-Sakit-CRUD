#include <iostream>
#include <string>
#include <iomanip>  
#include <thread>
#include <vector>

using namespace std;

int main() {
cout <<"                                       SELAMAT DATANG" << endl;

this_thread::sleep_for(2000ms);
std::string judul = R"(
  _____                           _           _____         _     _  _        _    _  _____  _____ 
 |  __ \                         | |         / ____|       | |   (_)| |      | |  | ||  __ \|_   _|
 | |__) |_   _  _ __ ___    __ _ | |__      | (___    __ _ | | __ _ | |_     | |  | || |__) | | |  
 |  _  /| | | || '_ ` _ \  / _` || '_ \      \___ \  / _` || |/ /| || __|    | |  | ||  ___/  | |  
 | | \ \| |_| || | | | | || (_| || | | |     ____) || (_| ||   < | || |_     | |__| || |     _| |_ 
 |_|  \_\\__,_||_| |_| |_| \__,_||_| |_|    |_____/  \__,_||_|\_\|_| \__|     \____/ |_|    |_____|                                                               
)";

    for(int i = 0; i <= 200; i++){

    if(i == 100){
        cout << judul;
    }else{
        cout << "=";
     }
    }

    vector <string> penyakit = {"Demam Berdarah", "HIV"};
    // for(int i = 0;){

    // }
}
