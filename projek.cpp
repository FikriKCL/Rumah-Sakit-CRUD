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

const string fileJSON = "data.json";

void menu() {
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

json loadData() {
    std::ifstream file(fileJSON);

    // Check if the file can be opened
    if (!file.is_open()) {
        cerr << "Error: Could not open the file." << endl;
        return json{}; // Return an empty JSON object
    }
    
    // Check if the file is empty
    if (file.peek() == std::ifstream::traits_type::eof()) {
        cout << "File is empty, initializing with empty JSON." << endl;
        return json{};
    }

    json data;
    try {
        file >> data; // Parse the JSON data
    } catch (const json::parse_error& e) {
        cerr << "Parse error: " << e.what() << endl;
        return json{}; // Return an empty JSON object on parse failure
    }

    file.close(); // Close the file
    return data;
}

void saveData(const json& data) {
    std::ofstream file(fileJSON);

    // Check if the file can be opened
    if (!file.is_open()) {
        cerr << "Error: Could not open the file for saving." << endl;
        return;
    }

    try {
        file << data.dump(4); // Pretty-print JSON with 4 spaces indentation
    } catch (const std::exception& e) {
        cerr << "Error while writing to the file: " << e.what() << endl;
    }

    file.close(); // Close the file
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
    menu();
    pendaftaran();
    pemilihanPoli();
}
