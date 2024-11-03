#include <iostream>
#include <string>
#include <iomanip>  
#include <thread>
#include <vector>

using namespace std;

void menu() {
    cout << "                                        Selamat Datang" << endl;
    this_thread::sleep_for(2000ms);

    std::string judul = R"(
  _____                           _        _____         _     _  _     _    _  _____  _____ 
 |  __ \                         | |      / ____|       | |   (_)| |   | |  | ||  __ \|_   _|
 | |__) |_   _  _ __ ___    __ _ | |__   | (___    __ _ | | __ _ | |_  | |  | || |__) | | |  
 |  _  /| | | || '_ ` _ \  / _` || '_ \   \___ \  / _` || |/ /| || __| | |  | ||  ___/  | |  
 | | \ \| |_| || | | | | || (_| || | | |  ____) || (_| ||   < | || |_  | |__| || |     _| |_ 
 |_|  \_\\__,_||_| |_| |_| \__,_||_| |_| |_____/  \__,_||_|\_\|_| \__|  \____/ |_|    |_____|
 )";

    for(int i = 0; i <= 200; i++){
        if(i == 100){
            for (char ch : judul) {
                cout << ch ;                     
                cout.flush();                    
                this_thread::sleep_for(1ms);    
            }
        }else if( i == 200){
            cout << endl;
        } else {
            cout << "=";
        }
        this_thread::sleep_for(1ms);
    }

  
}

void pendaftaran() {
    string nama, nik, umur, jenis_kelamin, ttl;

    cout << " Masukan Nama : "; getline(cin,nama);
    cout << " Masukan NIK : "; getline(cin,nik);
    cout << " Masukan Umur : "; getline(cin,umur);
    cout << " Masukan Jenis Kelamin : "; getline(cin,jenis_kelamin);
    cout << " Masukan Tempat Tanggal Lahir [DD/~MM/YYYY] : "; getline(cin,ttl);

}

void poliGigi(){

}

void pembayaran(){
    
}


int main() {
    menu();
    pendaftaran();
    // for(int i = 0;){

    // }
}
