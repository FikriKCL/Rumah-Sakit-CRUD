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
const char* GREEN = "\033[32m";
const char* RED = "\033[31m";
const char* RESET = "\033[0m";

// Load data from JSON file
json loadData() {
    ifstream file(fileJSON);

    if (!file) {
        cerr << "Error: Could not open the file." << endl;
        return json{};
    }

    if (file.peek() == ifstream::traits_type::eof()) {
        return json{};
    }

    json data;
    try {
        file >> data;
    } catch (const json::parse_error& e) {
        cerr << "Parse error: " << e.what() << endl;
    }

    file.close();
    return data;
}

// Save data to JSON file
void saveData(const json& data) {
    ofstream file(fileJSON);
    if (file.is_open()) {
        file << data.dump(4);
        file.close();
    }
}

// Display the welcome menu
void menu() {
    cout << GREEN << "                                        Selamat Datang" << endl;

    string judul = R"(
  _____                           _        _____         _     _  _     _    _  _____  _____ 
 |  __ \                         | |      / ____|       | |   (_)| |   | |  | ||  __ \|_   _|
 | |__) |_   _  _ __ ___    __ _ | |__   | (___    __ _ | | __ _ | |_  | |  | || |__) | | |  
 |  _  /| | | || '_ ` _ \  / _` || '_ \   \___ \  / _` || |/ /| || __| | |  | ||  ___/  | |  
 | | \ \| |_| || | | | | || (_| || | | |  ____) || (_| ||   < | || |_  | |__| || |     _| |_ 
 |_|  \_\\__,_||_| |_| |_| \__,_||_| |_| |_____/  \__,_||_|\_\|_| \__|  \____/ |_|    |_____|
 )";

    for (int i = 0; i <= 200; i++) {
        if (i == 100) {
            for (char ch : judul) {
                cout << GREEN << ch;
                cout.flush();
            }
        } else if (i == 200) {
            cout << endl;
        } else {
            cout << "=";
        }
    }
}

// Error handling String ke Integer
int cekInputInteger(const string& prompt) {
    int input;
    while (true) {
        cout << GREEN << prompt << RESET;
        cin >> input;

        if (cin.fail()) {
            // Clear the error flag on cin
            cin.clear();
            // Ignore the rest of the input line to avoid issues
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << RED << " Input harus Diisi dengan Angka dan Tidak Boleh Kosong\n" << RESET;
        } else {
            // Consume the newline character left by cin
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return input;
        }
    }
}

// Error handling Empty Input
string cekInputString(const string& prompt) {
    string input;
    while (true) {
        cout << GREEN << prompt << RESET;
        getline(cin, input);

        if (input.empty()) {
            cout << RED << " Input harus diisi dengan huruf/kalimat\n" << RESET;
        } else {
            return input;
        }
    }
}

// Fungsi Pendaftaran
void pendaftaran() {
    json data = loadData();
    string penyakit;

    int id = cekInputInteger(" Masukan ID Pasien : ");
    int nik = cekInputInteger(" Masukan NIK Pasien : ");
    int umur = cekInputInteger(" Masukan Umur Pasien : ");
    string nama = cekInputString(" Masukan Nama Pasien : ");
    string jenis_kelamin = cekInputString(" Masukan Jenis Kelamin [L/P] : ");
    transform(jenis_kelamin.begin(), jenis_kelamin.end(), jenis_kelamin.begin(), ::toupper);
    string ttl = cekInputString(" Masukan Tempat Tanggal Lahir [DD/MM/YYYY] : ");

    data[id] = {{"nama", nama}, {"nik", nik}, {"umur", umur}, {"jenis_kelamin", jenis_kelamin}, {"ttl", ttl}, {"penyakit", penyakit}};

    saveData(data);
}

// Fungsi Poliklinik
void poliGigi() {
    cout << GREEN << string(100, '=')<<endl;
    cout << " Anda di Poli Gigi!\n";
    cout << " Silahkan Konsultasi ke Dokter";
}

void poliUmum() {
    cout << GREEN << string(100, '=')<<endl;
    cout << " Anda di Poli Umum!";
}

void poliOrthopedi() {
    cout << GREEN << string(100, '=')<<endl;
    cout << " Anda di Poli Orthopedi!";
}

void poliAnak() {
    cout << GREEN << string(100, '=');
    cout << " Anda di Poli Anak!";
}

void poliKejiwaan() {
    cout << GREEN << string(100, '=')<<endl;
    cout << " Anda di Poli Kejiwaan!";
}

void pemilihanPoli() {
    int poli = 0;
    char ch;
    cout << GREEN << string(100, '=') << endl;
    cout << GREEN <<" Pilih Poliklinik\n 1.Poliklinik Gigi\n 2.Poliklinik Umum\n 3.Poliklinik Kejiwaan\n 4.Poliklinik Anak\n 5.Poliklinik Orthopedi\n";

    ch = _getch();
    cout << endl;
    if (ch >= '1' && ch <= '5') {
        poli = ch - '0';
    } else {
        cout << "Poliklinik Belum Ada!" << endl;
        return;
    }

    switch (poli) {
        case 1:
            poliGigi();
            break;
        case 2:
            poliUmum();
            break;
        case 3:
            poliKejiwaan();
            break;
        case 4:
            poliAnak();
            break;
        case 5:
            poliOrthopedi();
            break;
        default:
            cout << " Poliklinik Belum Ada!" << endl;
            break;
    }
}

void pembayaran() {

}

int main() {
    menu();
    pendaftaran();
    pemilihanPoli();
}
