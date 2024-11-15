#include <iostream>
#include <string>
#include <iomanip>  
#include <thread>
#include <vector>
#include <fstream>
#include "json.hpp"
#include <conio.h>

using json = nlohmann::json;
using namespace std;

int main() {
cout <<"                                        Selamat Datang" << endl;

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
                // this_thread::sleep_for(1ms);    
            }
        }else if( i == 200){
            cout << endl;
        } else {
            cout << "=";
        }
        // this_thread::sleep_for(1ms);
    }
  
}

void pendaftaran() {
    json data = loadData();
    string id, nama, nik, umur, jenis_kelamin, ttl;

    cout << " Masukan ID : "; getline(cin,id);
    cout << " Masukan Nama : "; getline(cin,nama);
    cout << " Masukan NIK : "; getline(cin,nik);
    cout << " Masukan Umur : "; getline(cin,umur);
    cout << " Masukan Jenis Kelamin [L/P] : "; getline(cin,jenis_kelamin);
    transform(jenis_kelamin.begin(), jenis_kelamin.end(), jenis_kelamin.begin(), ::toupper);
    cout << " Masukan Tempat Tanggal Lahir [DD/MM/YYYY] : "; getline(cin,ttl);

    data[id] = {{"nama",nama},{"nik",nik},{"umur",umur},{"jenis_kelamin",jenis_kelamin},{"ttl",ttl}};

    saveData(data);

}

void poliGigi(){
    cout << " Anda di Poli Gigi!";

}

void pemilihanPoli(){
    int poli = 0;
    char ch;
    cout << string(100, '=') << endl;
    cout << " Pilih Poliklinik\n 1.Poliklinik Gigi\n 2.Poliklinik Umum\n ";

     ch = _getch(); 
    cout << endl;
    
    if (ch >= '1' && ch <= '2') {
        poli = ch - '0';
    } else {
        cout << "Poliklinik Belum Ada!" << endl;
        return; 
    }

    switch(poli){
    case 1:
        poliGigi();
    default:
        break;
    }   

}

void pembayaran(){
    
}

int main() {
    // menu();
    // pendaftaran();
    pemilihanPoli();
}
