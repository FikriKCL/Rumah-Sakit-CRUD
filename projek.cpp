#include <iostream>
#include <string>
#include <iomanip>
#include <thread>
#include <vector>
#include <fstream>
#include "json.hpp"
#include <conio.h>
#include <cctype>

const char* GREEN = "\033[32m";
const char* RED = "\033[31m";
const char* YELLOW = "\033[33m";
const char* RESET = "\033[0m";

using json = nlohmann::json;
using namespace std;

const string fileJSON = "data.json";
json pasien = json::array();
struct Obat{
    string namaObat;
    long long int hargaObat;
};

struct Tindakan{
    string namaTindakan;
    long long int hargaTindakan;
};

//function prototypes
void pembayaran();
void pemilihanPoli();
void poliGigi();
void poliUmum();
void poliOrthopedi();
void poliAnak();
void poliKejiwaan();
void pilihDokter(int id_poli);
void pilihTindakan(int id_tindakan, string keluhan);
void pemilihanObat(Obat obat[], int jumlahObat);
void pembayaran();

// Mencetak Pembatas
void pembatas(){
    cout << GREEN << string(100, '=') << RESET <<endl;
}

// Error handling String ke Integer
// Proseduer Cek Input Integer digunakan untuk mengecek apakah input yang dimasukan oleh user adalah angka
// Memilki parameter const string& prompt digunakan untuk menggantikan variable prompt di dalam fungsi ex: cekInputInteger("Masukan ID Pasien : ");
// "Masukan ID Pasien" akan menggantikan variable prompt
int cekInputInteger(const string& prompt) {
    int input;
    while (true) {
        cout << GREEN << prompt << YELLOW;
        cin >> input;

// Apabila input bukan angka maka akan muncul pesan setelah itu diclear
        if (cin.fail()) {
            cin.clear();
// Lalu diignore semua input selanjutnya sampai newline
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
// Memunculkan pesan             
            cout << RED << "Input harus Diisi dengan Angka dan Tidak Boleh Kosong\n" << RESET;
        } else {
// Apabila input adalah angka maka akan mengembalikan nilai input            
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return input;
        }
    }
}

int cekInputUmur(const string &prompt){
    int input;
    while (true) {
        cout << GREEN << prompt << YELLOW;
        cin >> input;
// Apabila input bukan angka maka akan muncul pesan setelah itu diclear
        if (cin.fail()) {
            cin.clear();
// Lalu diignore semua input selanjutnya sampai newline
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
// Memunculkan pesan             
            cout << RED << "Input harus Diisi dengan Angka dan Tidak Boleh Kosong\n" << RESET;
        }else if(input > 100 || input <= 0){
            cout << RED << "Input terlalu tinggi atau terlalu rendah!\n" << RESET;
        } else {
// Apabila input adalah angka maka akan mengembalikan nilai input            
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return input;
        }
    }
    
}
// Error handling menginput selain huruf
// Prosedur Cek Input String digunakan untuk mengecek apakah input yang dimasukan oleh user tidak kosong
// Memilki parameter const string& prompt digunakan untuk menggantikan variable prompt di dalam fungsi ex: cekInputString("Masukan ID Pasien : ");
// "Masukan ID Pasien" akan menggantikan variable prompt
string cekInputString(const string &prompt) {
    string input;
    while (true) {
        cout << GREEN << prompt << YELLOW;
        getline(cin, input);
        // Check if input is empty or contains invalid characters
        bool valid = true;

        //Mengiterasi setiap karakter pada input untuk mengecek apakah ada angka
        //range based for loop (for each)
        for (char ch : input) {
            if (!isalpha(ch) && !isspace(ch)) { 
                valid = false;
                break;
            }
        }
        //Apabila tidak diisi/kosong maka akan mencetak pesan
        if (input.empty()) {
            cout << RED << "Input tidak boleh kosong. Coba lagi.\n" << RESET;
        //Apabila terdapat angka maka akan mencetak pesan
        } else if (!valid) {
            cout << RED << "Input harus berupa huruf/kalimat tanpa angka atau simbol. Coba lagi.\n" << RESET;
        } else {
        //Mengembalikan Input apabila sudah benar
            return input;        
        }
    }
}

// Error Handling Jenis Kelamin apabila bukan diisi oleh L/P
// Prosedur Cek Input String digunakan untuk mengecek apakah input yang dimasukan oleh user tidak kosong
// Memilki parameter const string& prompt digunakan untuk menggantikan variable prompt di dalam fungsi ex: cekInputKelamin("Masukkan Jenis Kelamin [L/P] : ");
// "Masukan Jenis Kelamin[l/P]" akan menggantikan variable prompt
string cekInputKelamin(const string& prompt) {
    string input;
    while (true) {                
        cout << GREEN << prompt << YELLOW;
        getline(cin, input);
// membuat input menjadi kapital       
        transform(input.begin(), input.end(), input.begin(), ::toupper);
// Mengecek apakah input itu L/P apabila bukan akan mencetak pesan
        if (input != "L" && input != "P") {
            cout << RED << "Input Kelamin Hanya Dapat Diisi Dengan L/P" << RESET << endl;
        } else {
// Mengembalikan Input            
            return input;
        }
    }
}

//Prosedur BPJS pada tahap penentuan biaya
// Memilki parameter bool bpjs, struct tindakan, int biaya
bool bpjs(bool bpjs, Tindakan &tindakan) {
//Apabila user pengguna BPJS maka biaya akan menjadi 0 lalu mencetak pesan dan mengembalikan true    
    if(bpjs) {
        tindakan.hargaTindakan = 0;
        cout << GREEN << "Biaya tindakan dan konsultasi ditanggung BPJS" << RESET << endl;
        cout << GREEN << "Biaya menjadi (Rp- " << tindakan.hargaTindakan << ")" << RESET << endl;
        pembatas();
        return true;    
    } else {
//Apabila user tidak terdaftar bpjs maka biaya akan tetap sama lalu mencetak pesan dan mengembalikan false         
        cout << RED << "BPJS Tidak Terdaftar. Biaya akan dikenakan secara mandiri." << RESET << endl;
        cout << GREEN << "Biaya " << tindakan.namaTindakan <<  " menjadi (Rp-" << tindakan.hargaTindakan << ")" << RESET << endl;
        pembatas();
        return false;
    }

}
// Error Mengecek BPJS apakah diisi dengan Y (True) dan N (False)
// Prosedur CekBPJS digunakan untuk mengecek BPJS true atau false
// Memilki parameter const string& prompt digunakan untuk menggantikan variable prompt di dalam fungsi ex: cekBPJS("Apakah anda pengguna BPJS : ");
// "Apakah anda pengguna BPJS : " akan menggantikan variable prompt"
bool cekBPJS(const string& prompt) {
    string input;
    while (true) {
        cout << GREEN << prompt << YELLOW;
        getline(cin, input);
        transform(input.begin(), input.end(), input.begin(), ::toupper);
// Apabila Input bukan Y/N maka akan mencetak pesan
        if (input != "Y" && input != "N") {            
            cout << RED << "Input BPJS Hanya Dapat Diisi Dengan Y/N" << RESET << endl;
        } else {
// Selain itu mengembalikan input "Y" atau true            
            return input == "Y";
        }
    }
}
// Error cek Input tanggal
string cekInputDate(const string& prompt){
    struct tm date = {};
    string input;
    while(true){
        cout << GREEN << prompt << YELLOW;
        getline(cin, input);

        stringstream ss(input);
        char delimiter;
        if(ss >> date.tm_mday >> delimiter >> date.tm_mon >> delimiter >> date.tm_year && delimiter == '/') {
            date.tm_mon -= 1;
            date.tm_year -= 1900;
            if (mktime(&date) != -1) {
                return input;
            }else{
                cout << RED << "Tanggal Salah. Silahkan isi kembali!" << RESET << endl;
            }
        }else{
            cout << RED << "Format Tanggal Salah. Silahkan isi kembali!" << RESET << endl;
        }
    }
}
// hidden input
int hiddenInput(char maxChoice) {
    char ch;
    int choice = 0;

    ch = _getch(); // Membaca satu karakter tanpa echo ke console

    if (ch >= '0' && ch <= maxChoice) {
        choice = ch - '0'; //konvert char ke integer
        return choice;
    }else if (ch == '\n'){
        cout << "Tidak Boleh Kosong!" << endl;  
        return -1;
    } else {
        cout << RED << "Pilihan tidak valid!" << endl;
        pembatas();
        return -1; 
    }
}
// Cek Input Nik
string cekInputNIK(const string &prompt) {
    string input;
    while (true) {
        cout << GREEN << prompt << YELLOW;
        getline(cin, input);
        // Cek apakah input kosong?
        if (input.empty()) {
            cout << RED << "Input tidak boleh kosong. Coba lagi.\n" << RESET;
        }else if(input.size() <= 16 || input.size() > 16){
            cout << RED << "Input NIK tidak valid. Harus 16 Angka!\n" << RESET;
        }
        // Cek apakah input hanya mengandung angka
        else {
            bool isNumeric = true;
            for (char ch : input) {
                if (!isdigit(ch)) {
                    isNumeric = false;
                    break;
                }
            }
            if (!isNumeric) {
                cout << RED << "Input harus angka. Coba Lagi!.\n";
            } 
            // Return valid input
            else {
                return input;        
            }
        }
    }
}
// Load data dari json
json loadData() {
    std::ifstream file(fileJSON);

    // Cek Apakah file dapat dibuka
    if (!file.is_open()) {
        cerr << "Error: Could not open the file." << endl;
        return json{}; // Mengembalikan JSoN
    }
    
    // Cek apakah file kosong
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

    file.close(); // Tutup File
    return data;
}
// Save data ke JSON
void saveData(const json& data) {
    std::ofstream file(fileJSON);

    // cek apakah file dapat dibuka
    if (!file.is_open()) {
        cerr << "Error: Could not open the file for saving." << endl;
        return;
    }

    try {
        file << data.dump(4); // Pretty-print JSON with 4 spaces indentation
    } catch (const std::exception& e) {
        cerr << "Error while writing to the file: " << e.what() << endl;
    }

    file.close(); // Tutup file
}
// Read Item
void readItems() {
    json data = loadData();

    if (data["Pasien"].empty()) {
        cout << RED << "Tidak ada data pasien!" << RESET << endl;
        return;
    }
    cout << GREEN << string(40, '-') << endl; 
    cout << GREEN << "Data Pasien:" << RESET << endl;
    for (const auto& pasien : data["Pasien"]) {
        cout << GREEN << "ID: " << pasien["id"] << endl;
        cout << GREEN << "Nama: " << pasien["nama"] << endl;
        cout << GREEN << "NIK: " << pasien["nik"] << endl;
        cout << GREEN << "Jenis Kelamin: " << pasien["jenis_kelamin"] << endl;
        cout << GREEN << "Tanggal Lahir: " << pasien["ttl"] << endl;
        cout << GREEN << "Umur: " << pasien["umur"] << endl;
        cout << GREEN << "Poli: " << pasien["poli"] << endl;
        cout << GREEN << "Dokter: " << pasien["dokter"] << endl;
        cout << GREEN << "BPJS: " << (pasien["BPJS"] ? "Ya" : "Tidak") << endl;
        cout << GREEN << "Tipe Bayar: " << pasien["tipeBayar"] << endl;

        cout << GREEN << "Obat:" << endl;
        for (const auto& obat : pasien["obat"]) {
            cout << GREEN << "  - " << obat["namaObat"] << " (Rp " << obat["hargaObat"] << ")" << endl;
        }

        cout << "Tindakan:" << endl;
        for (const auto& tindakan : pasien["tindakan"]) {
            cout << GREEN << "  - " << tindakan["namaTindakan"] << " (Rp " << tindakan["hargaTindakan"] << ")" << endl;
        }

        cout << "Total Biaya: Rp " << GREEN << pasien["totalBiaya"] << endl;
        cout << GREEN << string(40, '-') << endl; 
    }
}
// Update Item
void updateItem() {
    json data = loadData();
    //Cek apakah data pasien kosong
    if (data["Pasien"].empty()) {
        cout << RED << "Data pasien kosong! Tidak ada yang bisa diperbarui." << RESET << endl;
        return;
    }

    //Meminta id dari pasien yang ingin diupdate
    int id;
    cout << "Masukan ID Pasien yang ingin diupdate: ";
    cin >> id;

    bool found = false;

    //Menginterasi data pasien, dan penggunaan dereference untuk berinteraksi dengan data secara langsung
    for (auto& pasien : data["Pasien"]) {
        if (pasien["id"] == id) {
            found = true;
            cout << GREEN << "Data pasien ditemukan!" << RESET << endl;

            cout << "Nama lama: " << pasien["nama"] << ". Masukkan nama baru (kosongkan untuk tidak mengubah): ";
            cin.ignore();
            string namaBaru;
            getline(cin, namaBaru);
            if (!namaBaru.empty()) {
                pasien["nama"] = namaBaru;
            }

            cout << "NIK lama: " << pasien["nik"] << ". Masukkan NIK baru (kosongkan untuk tidak mengubah): ";
            string nikBaru;
            getline(cin, nikBaru);
            if (!nikBaru.empty()) {
                pasien["nik"] = nikBaru;
            }

            cout << "Jenis kelamin lama: " << pasien["jenis_kelamin"] << ". Masukkan jenis kelamin baru (kosongkan untuk tidak mengubah): ";
            string jkBaru;
            getline(cin, jkBaru);
            if (!jkBaru.empty()) {
                pasien["jenis_kelamin"] = jkBaru;
            }

            cout << "Tanggal lahir lama: " << pasien["ttl"] << ". Masukkan tanggal lahir baru (kosongkan untuk tidak mengubah): ";
            string ttlBaru;
            getline(cin, ttlBaru);
            if (!ttlBaru.empty()) {
                pasien["ttl"] = ttlBaru;
            }

            cout << "Umur lama: " << pasien["umur"] << ". Masukkan umur baru (kosongkan untuk tidak mengubah): ";
            string umurBaru;
            getline(cin, umurBaru);
            if (!umurBaru.empty()) {
                pasien["umur"] = stoi(umurBaru);
            }

            cout << "Poli lama: " << pasien["poli"] << ". Masukkan poli baru (kosongkan untuk tidak mengubah): ";
            string poliBaru;
            getline(cin, poliBaru);
            if (!poliBaru.empty()) {
                pasien["poli"] = poliBaru;
            }

            cout << "Dokter lama: " << pasien["dokter"] << ". Masukkan dokter baru (kosongkan untuk tidak mengubah): ";
            string dokterBaru;
            getline(cin, dokterBaru);
            if (!dokterBaru.empty()) {
                pasien["dokter"] = dokterBaru;
            }

            saveData(data);
            cout << GREEN << "Data pasien berhasil diperbarui!" << RESET << endl;
            break;
        }
    }

    if (!found) {
        cout << RED << "Pasien dengan ID tersebut tidak ditemukan." << RESET << endl;
    }
}
// Delete Item
void deleteItem() {
    json data = loadData();
    string id;

    cout << RED << "Masukkan Id Pasien yang ingin dihapus: ";
    cin >> id;

    bool found = false;

    for (size_t i = 0; i < data["Pasien"].size(); ++i) {
        if (to_string(data["Pasien"][i]["id"]) == id) {
            data["Pasien"].erase(i);
            saveData(data);
            cout << GREEN << "Pasien berhasil dihapus!" << RESET << endl;
            found = true;
            break;
        }
    }

    if (!found) {
        cout << RED << "Pasien tidak ditemukan!" << RESET << endl;
    }
}
// Menunjukan menu
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
pembatas();
cout << GREEN << judul << endl;
pembatas();
}
// Fungsi Pendaftaran
void pendaftaran() {
//Memuat data dari File melalui prosedur loadData()
    json data = loadData();
    
    if (!data.contains("Pasien") || !data["Pasien"].is_array()) {
        data["Pasien"] = json::array();
    }

    int id = data["Pasien"].size() + 1;
    string nik = cekInputNIK("Masukan NIK Pasien : ");
    int umur = cekInputUmur("Masukan Umur Pasien : ");
    string nama = cekInputString("Masukan Nama Pasien : ");
    string jenis_kelamin = cekInputKelamin("Masukan Jenis Kelamin [L/P] : ");
    bool bpjs = cekBPJS("Apakah Anda Pengguna BPJS? [Y/N] : ");
    string ttl = cekInputDate("Masukan Tempat Tanggal Lahir [DD/MM/YYYY] : ");

    //Mendeklarasikan data ke dalam variabel yang akan di simpan di file JSON yang telah dibuat
     pasien = {{"id", id}, {"nama", nama}, {"nik", nik}, {"umur", umur}, {"jenis_kelamin", jenis_kelamin}, {"ttl", ttl}, {"BPJS", bpjs}};

     data["Pasien"].push_back(pasien);    
   
    //Save data yang telah diinput kedalam file
    saveData(data);
    pembatas();
}
// Pilih Poli
void pemilihanPoli() {
    json data = loadData();  
    bool done = false;       
    string poliName;

    while (!done) {
        cout << GREEN 
             << "Pilih Poliklinik\n"
                "1. Poliklinik Gigi\n"
                "2. Poliklinik Umum\n"
                "3. Poliklinik Orthopedi\n"
                "4. Poliklinik Anak\n"
                "5. Poliklinik Kejiwaan\n"
                "6. Selesai\n" 
             << RESET;
                pembatas();
        int poli = hiddenInput('6');  

        switch (poli) {
            case 1:
                poliName = "Poliklinik Gigi";
                done = true;
                break;
            case 2:
                poliName = "Poliklinik Umum";
                done = true;
                break;
            case 3:
                poliName = "Poliklinik Orthopedi";
                done = true;
                break;
            case 4:
                poliName = "Poliklinik Anak";
                done = true;
                break;
            case 5:
                poliName = "Poliklinik Kejiwaan";
                done = true; 
                break;
            case 6:
                cout << GREEN << "Terima kasih telah menggunakan layanan kami!" << RESET << endl;
                return; 
            default:
                cout << RED << "Pilihan tidak valid! Silakan coba lagi.\n" << RESET;
                break;
        }
    }

    if (!data["Pasien"].empty()) {  
        data["Pasien"].back()["poli"] = poliName;
        saveData(data);
        cout << GREEN << "Data berhasil disimpan!\n" << RESET;
    } else {
        cout << RED << "Tidak ada data pasien untuk diperbarui!\n" << RESET;
    }

    if (poliName == "Poliklinik Gigi") poliGigi();
    else if (poliName == "Poliklinik Umum") poliUmum();
    else if (poliName == "Poliklinik Orthopedi") poliOrthopedi();
    else if (poliName == "Poliklinik Anak") poliAnak();
    else if (poliName == "Poliklinik Kejiwaan") poliKejiwaan();
}
// Fungsi Poliklinik
void poliGigi() {
    cout << GREEN <<"Salah Pilih Poli ? Tekan 0 untuk kembali memilih poli atau tekan 1 untuk lanjut\n";
    pembatas();
    int choice = hiddenInput('1');
    if(choice == 0){
        pemilihanPoli();
        return;
    }else if(choice == 1){
        pembatas(); 
        Obat obatGigi[] = {{"Penghilang Nyeri Gigi", 5000},{"Obat Gusi Bengkak", 10000},{"Antibiotik Gigi", 8000},{"Obat Kumur Antiseptik", 15000},{"Obat Luka Dalam Mulut", 20000}};
        int jumlahObat = sizeof(obatGigi) / sizeof (obatGigi[0]);
        cout << GREEN << "Anda di Poli Gigi!" << RESET << endl;
        pilihDokter(1);
        cout << GREEN << "Silahkan Konsultasi ke Dokter!\nJelaskan Keluhan Anda!\n" << YELLOW;
        string keluhan = cekInputString("Apa Keluhan Anda?\n");
        pilihTindakan(1, keluhan);
        pemilihanObat(obatGigi, jumlahObat);
        pembayaran();
    } 

}
// Pilih poliGigi
void poliUmum() {
    cout << GREEN << "Salah Pilih Poli ? Tekan 0 untuk kembali memilih poli atau tekan 1 untuk lanjut\n";
    pembatas();
    int choice = hiddenInput('1');
    if(choice == 0){
        pemilihanPoli();
        return;
    }else if(choice == 1){
        Obat obatUmum[] = {{"Penurun Demam", 5000},{"Obat Sakit Kepala", 5000},{"Vitamin untuk Daya Tahan Tubuh", 7000},{"Obat Maag", 8000},{"Penghilang Nyeri Otot", 12000}};
        int jumlahObat = sizeof(obatUmum) / sizeof (obatUmum[0]);
        cout << GREEN << "Anda di Poli Umum!" << RESET << endl;
        pilihDokter(2);
        cout << GREEN << "Silahkan Konsultasi ke Dokter!\nJelaskan Keluhan Anda!\n" << YELLOW;
        string keluhan = cekInputString("Apa Keluhan Anda?\n");
        pilihTindakan(2,keluhan);
        pemilihanObat(obatUmum, jumlahObat);
        pembayaran();
    } 
    
}   
// Pilih poliOrthopedi
void poliOrthopedi() {
    cout << GREEN << "Salah Pilih Poli ? Tekan 0 untuk kembali memilih poli atau tekan 1 untuk lanjut\n";
    pembatas();
    int choice = hiddenInput('1');
    if(choice == 0){
        pemilihanPoli();
        return;
    }else if(choice == 1){
        Obat obatOrthopedi[] = {{"Obat Penguat Tulang", 20000},{"Obat Nyeri Sendi", 15000},{"Obat Anti Radang Sendi", 10000},{"Vitamin Tulang", 25000},{"Krim Penghilang Pegal", 12000}};
        int jumlahObat = sizeof(obatOrthopedi) / sizeof (obatOrthopedi[0]); //Mengambil size dari array output : 5
        cout << GREEN << "Anda di Poli Orthopedi!" << RESET << endl;
        pilihDokter(3);
        cout << GREEN << "Silahkan Konsultasi ke Dokter!\nJelaskan Keluhan Anda!\n" << YELLOW;
        string keluhan = cekInputString("Apa Keluhan Anda?\n");
        pilihTindakan(3, keluhan);
        pemilihanObat(obatOrthopedi, jumlahObat);
        pembayaran();
    } 
    
}
// Pilih P
void poliAnak() {
    cout << GREEN << "Salah Pilih Poli ? Tekan 0 untuk kembali memilih poli atau tekan 1 untuk lanjut\n";
    pembatas();
    int choice = hiddenInput('1');
    if(choice == 0){
        pemilihanPoli();
        return;
    }else if(choice == 1){    
        Obat obatAnak[] = {{"Obat Penurun Demam Anak", 5000},{"Vitamin Anak", 7000},{"Obat Batuk Anak", 8000},{"Obat Pilek Anak", 6000},{"Obat Nyeri Tumbuh Gigi Anak", 10000}};  
        int jumlahObat = sizeof(obatAnak) / sizeof (obatAnak[0]); //Mengambil size dari array output : 5
        cout << GREEN << "Anda di Poli Anak!" << RESET << endl;
        pilihDokter(4);
        cout << GREEN << "Silahkan Konsultasi ke Dokter!\nJelaskan Keluhan Anda!\n" << YELLOW;
        string keluhan = cekInputString("Apa Keluhan Anda?\n");
        pilihTindakan(4,keluhan);
        pemilihanObat(obatAnak, jumlahObat);
        pembayaran();
    } 
    
}

void poliKejiwaan() {
    cout << GREEN << "Salah Pilih Poli ? Tekan 0 untuk kembali memilih poli atau tekan 1 untuk lanjut\n";
    pembatas();
    int choice = hiddenInput('1');
    if(choice == 0){
        pemilihanPoli();
    }else if(choice == 1){
        Obat obatKejiwaan[] = {{"Obat Penenang", 20000},{"Obat Anti Cemas", 10000},{"Vitamin Otak", 12000},{"Obat Stres", 25000},{"Obat Tidur", 15000}};
        int jumlahObat = sizeof(obatKejiwaan) / sizeof (obatKejiwaan[0]);
        cout << GREEN << "Anda di Poli Kejiwaan!\n" << RESET;
        pilihDokter(5);
        cout << GREEN << "Silahkan Konsultasi ke Dokter!\nJelaskan Keluhan Anda!\n" << YELLOW;
        string keluhan = cekInputString("Apa Keluhan Anda?\n");
        pilihTindakan(5,keluhan);
        pemilihanObat(obatKejiwaan, jumlahObat);
        pembayaran();
    } 
    
}

void pilihDokter(int id_poli) {
    json data = loadData();
    int id_dokter = 0;
    string dokterName;
    bool pasienAvailable = !data["Pasien"].empty();

    if (!pasienAvailable) {
        cout << RED << "Pasien belum ada. Silakan tambahkan pasien terlebih dahulu!" << RESET << endl;
        return;
    }

    while (true) {   
        pembatas();
        switch (id_poli) {
            case 1: {
                cout << GREEN << "Dokter Gigi\n" << RESET;
                pembatas();
                cout << GREEN 
                     << "1. Drg. Asep (Spesialis Gigi)\n"
                        "2. Drg. Budi (Spesialis Gigi)\n"
                        "3. Drg. Anugrah (Spesialis Gigi)\n"
                        "4. Drg. Bisma (Spesialis Gigi)\n"
                        "5. Drg. Vivi (Spesialis Gigi)\n" << RESET;
                id_dokter = hiddenInput('5');
                if (id_dokter >= 1 && id_dokter <= 5) {
                    string dokterGigi[] = {"Drg. Asep (Spesialis Gigi)", "Drg. Budi (Spesialis Gigi)", 
                                           "Drg. Anugrah (Spesialis Gigi)", "Drg. Bisma (Spesialis Gigi)", 
                                           "Drg. Vivi (Spesialis Gigi)"};
                    dokterName = dokterGigi[id_dokter - 1];
                } else {
                    cout << RED << "Pilihan tidak valid, silakan coba lagi.\n" << RESET;
                    continue;
                }
                break;
            }
            case 2: {
                cout << GREEN << "Dokter Umum\n" << RESET;
                pembatas();
                cout << GREEN 
                     << "1. Dr. Rahman (Spesialis Umum)\n"
                        "2. Dr. Siti (Spesialis Umum)\n"
                        "3. Dr. Indra (Spesialis Umum)\n"
                        "4. Dr. Fajar (Spesialis Umum)\n"
                        "5. Dr. Lala (Spesialis Umum)\n" << RESET;
                id_dokter = hiddenInput('5');
                if (id_dokter >= 1 && id_dokter <= 5) {
                    string dokterUmum[] = {"Dr. Rahman (Spesialis Umum)", "Dr. Siti (Spesialis Umum)", 
                                           "Dr. Indra (Spesialis Umum)", "Dr. Fajar (Spesialis Umum)", 
                                           "Dr. Lala (Spesialis Umum)"};
                    dokterName = dokterUmum[id_dokter - 1];
                } else {
                    cout << RED << "Pilihan tidak valid, silakan coba lagi.\n" << RESET;
                    continue;
                }
                break;
            }
            case 3: {
                cout << GREEN << "Dokter Orthopedi\n" << RESET;
                pembatas();
                cout << GREEN 
                     << "1. Dr. Seno (Spesialis Orthopedi)\n"
                        "2. Dr. Lestari (Spesialis Orthopedi)\n"
                        "3. Dr. Prasetyo (Spesialis Orthopedi)\n"
                        "4. Dr. Rina (Spesialis Orthopedi)\n"
                        "5. Dr. Arya (Spesialis Orthopedi)\n" << RESET;
                id_dokter = hiddenInput('5');
                if (id_dokter >= 1 && id_dokter <= 5) {
                    string dokterOrthopedi[] = {"Dr. Seno (Spesialis Orthopedi)", "Dr. Lestari (Spesialis Orthopedi)", 
                                                "Dr. Prasetyo (Spesialis Orthopedi)", "Dr. Rina (Spesialis Orthopedi)", 
                                                "Dr. Arya (Spesialis Orthopedi)"};
                    dokterName = dokterOrthopedi[id_dokter - 1];
                } else {
                    cout << RED << "Pilihan tidak valid, silakan coba lagi.\n" << RESET;
                    continue;
                }
                break;
            } 
            case 4:
            {
                cout << GREEN << "Dokter Anak\n" << RESET;
                pembatas();
                cout << GREEN 
                     << "1. Dr. Andi (Spesialis Anak)\n"
                        "2. Dr. Maya (Spesialis Anak)\n"
                        "3. Dr. Fitri (Spesialis Anak)\n"
                        "4. Dr. Wawan (Spesialis Anak)\n"
                        "5. Dr. Nina (Spesialis Anak)\n" << RESET;
                id_dokter = hiddenInput('5');
                if (id_dokter >= 1 && id_dokter <= 5) {
                    string dokterAnak[] = {"Dr. Andi (Spesialis Anak)", "Dr. Maya (Spesialis Anak)", 
                                           "Dr. Fitri (Spesialis Anak)", "Dr. Wawan (Spesialis Anak)", 
                                           "Dr. Nina (Spesialis Anak)"};
                    dokterName = dokterAnak[id_dokter - 1];
                } else {
                    cout << RED << "Pilihan tidak valid, silakan coba lagi.\n" << RESET;
                    continue;
                }
                break;
            }
            case 5: {
                cout << GREEN << "Dokter Kejiwaan\n" << RESET;
                pembatas();
                cout << GREEN 
                     << "1. Dr. Hasan (Spesialis Kejiwaan)\n"
                        "2. Dr. Sari (Spesialis Kejiwaan)\n"
                        "3. Dr. Devi (Spesialis Kejiwaan)\n"
                        "4. Dr. Eko (Spesialis Kejiwaan)\n"
                        "5. Dr. Rizky (Spesialis Kejiwaan)\n" << RESET;
                id_dokter = hiddenInput('5');
                if (id_dokter >= 1 && id_dokter <= 5) {
                    string dokterKejiwaan[] = {"Dr. Hasan (Spesialis Kejiwaan)", "Dr. Sari (Spesialis Kejiwaan)", 
                                               "Dr. Devi (Spesialis Kejiwaan)", "Dr. Eko (Spesialis Kejiwaan)", 
                                               "Dr. Rizky (Spesialis Kejiwaan)"};
                    dokterName = dokterKejiwaan[id_dokter - 1];
                } else {
                    cout << RED << "Pilihan tidak valid, silakan coba lagi.\n" << RESET;
                    continue;
                }
                break;
            }
        
            case 6: {
                cout << GREEN << "Terima kasih telah menggunakan layanan kami!" << RESET << endl;
                return;
                
            }
            default: {
                cout << RED << "Poliklinik tidak valid, silakan coba lagi." << RESET << endl;
                continue;
            } 
        }

        cout << GREEN << "Anda telah memilih: " << dokterName << RESET << endl;
        pembatas();
        cout << GREEN << "Salah Pilih Dokter ? Tekan 0 untuk kembali memilih dokter atau tekan 1 untuk lanjut\n";
        pembatas();
        int choice = hiddenInput('1');

        if (choice == 0) {
            cout << GREEN << "Silakan pilih dokter kembali." << RESET << endl;
            continue;
        } else if (choice == 1) {
            data["Pasien"].back()["dokter"] = dokterName;
            saveData(data);
            cout << GREEN << "Dokter anda : " << dokterName << RESET << endl;
            break;
        } else {
            cout << RED << "Pilihan tidak valid, silakan coba lagi.\n" << RESET;
            continue;
        }
    }
}
//Sebuah prosedur yang berisi if else untuk memilih tindakan berdasarkan id_tindakan, akan dipanggil di fungsi Poliklinik masing-masing
    //Alasan menggunakan if else agar  memasukan data ke json dapat dalam satu block. Tidak dimasing-masing switch case ditambahkan algoritma untuk menambahkan data
void pilihTindakan(int id_tindakan, string keluhan) {
    json data = loadData(); // Memuat data
    int id = data["Pasien"].back()["id"]; // Mengambil ID Pasien terakhir
    bool done = false;
    bool bpjsStatus = data["Pasien"].back()["BPJS"]; // Mengambil data bpjs
    pembatas();

    if (id_tindakan == 1) {
        cout << GREEN << "Tindakan untuk Poli Gigi\n" << RESET;

        // Struct berisi tindakan yang terdapat di poli gigi
        Tindakan tindakanGigi[] = {
            {"Scaling Karang Gigi", 500000},
            {"Pembersihan Gigi", 250000},
            {"Penggantian Gigi", 150000},
            {"Tambal Gigi", 200000},
            {"Behel Gigi", 200000}
        };

        do {
            cout << GREEN << "Silahkan Pilih Tindakan\n1. Scaling Karang Gigi\n2. Pembersihan Gigi\n3. Penggantian Gigi\n4. Tambal Gigi\n5. Behel Gigi\n6. Selesai\n";
            int pilih_tindakan = hiddenInput('6');
            if (pilih_tindakan >= 1 && pilih_tindakan <= 5) {
                cout << GREEN << "Nama Tindakan : " << tindakanGigi[pilih_tindakan - 1].namaTindakan << endl;

                bpjs(bpjsStatus, tindakanGigi[pilih_tindakan - 1]);

                // Menambahkan data ke "tindakan"
                if (!data["Pasien"].empty()) {  // cek apakah pasien ada
                    // Membuat objek baru
                    json newTindakan = {
                        {"namaTindakan", tindakanGigi[pilih_tindakan - 1].namaTindakan},
                        {"hargaTindakan", tindakanGigi[pilih_tindakan - 1].hargaTindakan}
                    };

                    // Memasukan data ke tindakan
                    data["Pasien"].back()["tindakan"].push_back(newTindakan);

                    saveData(data);
                    cout << GREEN << "Data berhasil disimpan!\n" << RESET;
                } else {
                    cout << RED << "Tidak ada data pasien untuk diperbarui!\n" << RESET;
                }
            } else if (pilih_tindakan == 6) {
                cout << GREEN << "Terima kasih telah menggunakan layanan kami!\n";
                done = true;
            } else {
                cout << RED << "Pilihan tidak valid! Silahkan pilih ulang.\n";
            }
        } while (!done);
    } else if (id_tindakan == 2) {
        cout << GREEN << "Tindakan untuk Poli Umum\n" << RESET;

        Tindakan tindakanUmum[] = {
            {"Pemeriksaan Umum", 80000},
            {"Pemeriksaan Kesehatan", 100000}
        };

        do {
            cout << GREEN << "Silahkan Pilih Tindakan\n1. Pemeriksaan Umum\n2. Pemeriksaan Kesehatan\n3. Selesai\n";
            int pilih_tindakan = hiddenInput('3');
            if (pilih_tindakan >= 1 && pilih_tindakan <= 2) {
                cout << GREEN << "Nama Tindakan : "<< tindakanUmum[pilih_tindakan - 1].namaTindakan << endl;

                bpjs(bpjsStatus, tindakanUmum[pilih_tindakan - 1]);

                // cek apakah data pasien kosong
                if (!data["Pasien"].empty()) {  
                    // Membuat objek tindakan
                    json newTindakan = {
                        {"namaTindakan", tindakanUmum[pilih_tindakan - 1].namaTindakan},
                        {"hargaTindakan", tindakanUmum[pilih_tindakan - 1].hargaTindakan}
                    };

                    // memasukan data ke objek
                    data["Pasien"].back()["tindakan"].push_back(newTindakan);

                    saveData(data);
                    cout << GREEN << "Data berhasil disimpan!\n" << RESET;
                } else {
                    cout << RED << "Tidak ada data pasien untuk diperbarui!\n" << RESET;
                }
            } else if (pilih_tindakan == 3) {
                cout << GREEN << "Terima kasih telah menggunakan layanan kami!\n";
                pembatas();
                done = true;
            } else {
                cout << RED << "Pilihan tidak valid! Silahkan pilih ulang.\n";
                pembatas();
            }
        } while (!done);
    } else if (id_tindakan == 3) {
        cout << GREEN << "Tindakan untuk Poli Orthopedi\n" << RESET;
        Tindakan tindakanOrthopedi[] = {{"Operasi Lutut", 3000000}, {"Operasi Punggung", 37000000},{"Operasi Paha", 25000000}};

        do {
            cout << GREEN << "Silahkan Pilih Tindakan\n1. Operasi Lutut\n2. Operasi Punggung\n3. Operasi Paha\n4. Selesai\n";
            int pilih_tindakan = hiddenInput('4');
            if (pilih_tindakan >= 1 && pilih_tindakan <= 3) {
                cout << GREEN << "Nama Tindakan : " << tindakanOrthopedi[pilih_tindakan - 1].namaTindakan << endl;

                bpjs(bpjsStatus, tindakanOrthopedi[pilih_tindakan - 1]);

                // Menambhkan tindakan ke JSON
                if (!data["Pasien"].empty()) {  //cek apakah data pasien ada
                    // Membuat object baru untuk menyimpan tindakan yang dipilih
                    json newTindakan = {
                        {"namaTindakan", tindakanOrthopedi[pilih_tindakan - 1].namaTindakan},
                        {"hargaTindakan", tindakanOrthopedi[pilih_tindakan - 1].hargaTindakan}
                    };

                    // menambahkan data ke objek tersebut
                    data["Pasien"].back()["tindakan"].push_back(newTindakan);

                    saveData(data);
                    cout << GREEN << "Data berhasil disimpan!\n" << RESET;
                } else {
                    cout << RED << "Tidak ada data pasien untuk diperbarui!\n" << RESET;
                }
            } else if (pilih_tindakan == 4) {
                cout << GREEN << "Terima kasih telah menggunakan layanan kami!\n";
                done = true;
                pembatas();
            } else {
                cout << RED << "Pilihan tidak valid! Silahkan pilih ulang.\n";
            }
        } while (!done);
    }else if (id_tindakan == 4){
        cout << GREEN << "Tindakan untuk Poli Anak\n" << RESET;
        Tindakan tindakanAnak[] = {{"Pemeriksaan Kesehatan", 80000}, {"Konsultasi Gizi dan Tumbuh Kembang", 200000}};
        do {
            cout << GREEN << "Silahkan Pilih Tindakan\n1. Pemeriksaan Kesehatan\n2. Konsultasi Gizi dan Tumbuh Kembang\n3. Selesai\n";
            int pilih_tindakan = hiddenInput('3');
            if (pilih_tindakan >= 1 && pilih_tindakan <= 2) {
                cout << GREEN << "Nama Tindakan : " << tindakanAnak[pilih_tindakan - 1].namaTindakan << endl;

                bpjs(bpjsStatus, tindakanAnak[pilih_tindakan - 1]);

                // Menambhkan tindakan ke JSON
                if (!data["Pasien"].empty()) {  //cek apakah data pasien ada
                    // Membuat object baru untuk menyimpan tindakan yang dipilih
                    json newTindakan = {
                        {"namaTindakan", tindakanAnak[pilih_tindakan - 1].namaTindakan},
                        {"hargaTindakan", tindakanAnak[pilih_tindakan - 1].hargaTindakan}
                    };

                    // menambahkan data ke objek tersebut
                    data["Pasien"].back()["tindakan"].push_back(newTindakan);

                    saveData(data);
                    cout << GREEN << "Data berhasil disimpan!\n" << RESET;
                } else {
                    cout << RED << "Tidak ada data pasien untuk diperbarui!\n" << RESET;
                }
            } else if (pilih_tindakan == 3) {
                cout << GREEN << "Terima kasih telah menggunakan layanan kami!\n";
                done = true;
                pembatas();
            } else {
                cout << RED << "Pilihan tidak valid! Silahkan pilih ulang.\n";
            }
        } while (!done);   
    } else if (id_tindakan == 5) {
        cout << GREEN << "Tindakan untuk Poli Kejiwaan\n" << RESET;
        pembatas();
        Tindakan tindakanKejiwaan[] = {{"Konseling Individu", 300000}, {"Terapi Kognitif Perilaku (CBT)", 450000},
                                       {"Psikoedukasi", 250000}, {"Psikoterapi", 500000}, {"Terapi Keluarga", 600000},
                                       {"Pemeriksaan Psikologi", 400000}, {"Evaluasi Psikiatri", 550000},
                                       {"Medikasi Psikiatri", 350000}, {"Manajemen Stres", 300000},
                                       {"Terapi Relaksasi", 250000}};

        do {
            cout << GREEN << "Silahkan Pilih Tindakan\n1. Konseling Individu\n2. Terapi Kognitif Perilaku (CBT)\n3. Psikoedukasi\n4. Psikoterapi\n5. Terapi Keluarga\n6. Pemeriksaan Psikologi\n7. Evaluasi Psikiatri\n8. Medikasi Psikiatri\n9. Selesai\n";
            int pilih_tindakan = hiddenInput('9');
            if (pilih_tindakan >= 1 && pilih_tindakan <= 8) {
                cout << GREEN << "Nama Tindakan : " << tindakanKejiwaan[pilih_tindakan - 1].namaTindakan << endl;

                bpjs(bpjsStatus, tindakanKejiwaan[pilih_tindakan - 1]);

                if (!data["Pasien"].empty()) {  
                    json newTindakan = {
                        {"namaTindakan", tindakanKejiwaan[pilih_tindakan - 1].namaTindakan},
                        {"hargaTindakan", tindakanKejiwaan[pilih_tindakan - 1].hargaTindakan}
                    };
                    data["Pasien"].back()["tindakan"].push_back(newTindakan);

                    saveData(data);
                    cout << GREEN << "Data berhasil disimpan!\n" << RESET;
                } else {
                    cout << RED << "Tidak ada data pasien untuk diperbarui!\n" << RESET;
                }
            } else if (pilih_tindakan == 9) {
                cout << GREEN << "Terima kasih telah menggunakan layanan kami!\n";
                done = true;
                pembatas();
            } else {
                cout << RED << "Pilihan tidak valid! Silahkan pilih ulang.\n";
            }
        } while (!done);
    }
}

void pemilihanObat(Obat obat[], int jumlahObat) {
    json data = loadData();
    int id = data["Pasien"].back()["id"];
    bool bpjsStatus = data["Pasien"].back()["BPJS"]; // Mengambil data BPJS
    // Random jumlah obat diberikan
    srand(time(0));
    int quantityObat = 1 + rand() % jumlahObat;

    if (!bpjsStatus) {  
        for (int i = 0; i <= quantityObat; i++) {
            int random = rand() % jumlahObat; 
            cout << GREEN << " - " << obat[random].namaObat;
            cout << GREEN << " (Rp-" << obat[random].hargaObat << ")" << RESET << endl;

            // Menambahkan data ke pasien tersebut
            for (size_t j = 0; j < data["Pasien"].size(); ++j) {
                if (data["Pasien"][j]["id"] == id) {
                    data["Pasien"][j]["obat"].push_back({
                        {"namaObat", obat[random].namaObat},
                        {"hargaObat", obat[random].hargaObat}
                    });
                }
            }
        }
        saveData(data); // Save data 
    } else {
        // Semua harga obat jadi 0
        for (int i = 0; i <= quantityObat; i++) {
            int random = rand() % jumlahObat; // Generate random index
            cout << GREEN << obat[random].namaObat << endl;
            cout << GREEN << "Rp-0" << RESET << endl;

            // Memasukan data obat ke dalam JSON data
            for (size_t j = 0; j < data["Pasien"].size(); ++j) {
                if (data["Pasien"][j]["id"] == id) {
                    data["Pasien"][j]["obat"].push_back({
                        {"namaObat", obat[random].namaObat},
                        {"hargaObat", 0}
                    });
                }
            }
        }
        saveData(data); // Save data 
    }
}

void pembayaran() {
    pembatas();
    json data = loadData();
    int pembayaran, uang;
    bool bpjsStatus = data["Pasien"].back()["BPJS"];
    int id = data["Pasien"].back()["id"];
    bool found = false;  // cek apakah id pasien ketemu
    int totalBiaya = 0;  // untuk jumlah biaya total

    // loop untuk mencari data pasien
    for (size_t i = 0; i < data["Pasien"].size(); ++i) {
        if (data["Pasien"][i]["id"] == id) {  // csek apakah id pasien sama dengan id terkini yang diambil
            found = true;
            
            cout << GREEN << "Struk Pembayaran\n";

            // Print setiap data tindakan dan menjumlahkan totalnya
            cout << GREEN << "Tindakan:\n";
            for (size_t j = 0; j < data["Pasien"][i]["tindakan"].size(); ++j) {
                // Debug print to check if the data is accessed properly
                cout << " - " << "Nama Tindakan: " << data["Pasien"][i]["tindakan"][j]["namaTindakan"];
                cout << " (Rp-" << data["Pasien"][i]["tindakan"][j]["hargaTindakan"] << ")"<< endl;
                
                int hargaTindakan = data["Pasien"][i]["tindakan"][j].contains("hargaTindakan") ?
                                    data["Pasien"][i]["tindakan"][j]["hargaTindakan"].get<int>() : 0;
                totalBiaya += hargaTindakan;  // menambahkan harga ke total biaya
            }

            // Print setiap data obat
            cout << GREEN << "Obat:\n";
            for (size_t j = 0; j < data["Pasien"][i]["obat"].size(); ++j) {
                int hargaObat = data["Pasien"][i]["obat"][j]["hargaObat"].get<int>();
                cout << "  - " << data["Pasien"][i]["obat"][j]["namaObat"] 
                     << " (Rp-" << hargaObat << ")\n";
                totalBiaya += hargaObat;  // menambahkan ke total biaya
            }

            // mencetak total biaya
            cout << GREEN << "Total Biaya Obat & Tindakan adalah Rp-" << totalBiaya << endl;

            break;  // Keluar loop ketika id ketemu
        }
    }

    // Memasukan Total Biaya Ke Json
    if (!data["Pasien"].empty()) { 
        data["Pasien"].back()["totalBiaya"] = totalBiaya;
        saveData(data);
        cout << GREEN << "Data berhasil disimpan!\n" << RESET;
    } else {
        cout << RED << "Tidak ada data pasien untuk diperbarui!\n" << RESET;
    }

    if(bpjsStatus){
        data["Pasien"].back()["tipeBayar"] = "BPJS";
        saveData(data);
    }

    // Pembayaran
    if (!bpjsStatus) {
        cout << GREEN << "Pembayaran\n1. Kredit\n2. Cash\n";
        pembayaran = hiddenInput('2');
        pembatas();
        
        if (!data["Pasien"].empty()) {
            if(pembayaran == 1){
                data["Pasien"].back()["tipeBayar"] = "Umum/Kredit";
                saveData(data);
            }else if(pembayaran == 2){
                data["Pasien"].back()["tipeBayar"] = "Umum/Cash";
                saveData(data);
            }else{
                cout << RED << "Pilihan pembayaran tidak valid!\n" << RESET;
            }
            
        } else {
            cout << RED << "Tidak ada data pasien untuk disimpan!" << RESET << endl;
        }
        
        // Kredit
        if (pembayaran == 1) {
            bool done = false;
            do {
                uang = cekInputInteger("Masukan Jumlah uang di kredit anda : ");
                if (uang > totalBiaya) {
                    cout << GREEN << "Pembayaran Kredit berhasil, terima kasih!\n";
                    cout << GREEN << "Sisa uang di kredit anda : " << uang - totalBiaya << endl;
                    done = true;
                } else if (uang == totalBiaya) {
                    cout << GREEN << "Pembayaran Kredit berhasil, terima kasih!\n";
                    done = true;
                } else {
                    cout << RED << "Pembayaran gagal. Saldo tidak cukup!\n";
                }
            } while (!done);
        } else if (pembayaran == 2) {
            bool done = false;
            do {
                uang = cekInputInteger("Silahkan Masukan Jumlah Uang\n");
                if (uang < totalBiaya) {
                    cout << RED << "Uang kurang, silahkan ulangi!\n";
                } else if (uang == totalBiaya) {
                    cout << GREEN << "Pembayaran berhasil, terima kasih!\n";
                    done = true;
                } else if (uang > totalBiaya) {
                    cout << GREEN << "Pembayaran berhasil, terima kasih!\n";
                    cout << GREEN << "Kembalian anda : " << uang - totalBiaya << endl;
                    done = true;
                }
            } while (!done);
        } else {
            cout << RED << "Pilihan tidak valid!\n";
        }
    }
}

int main() {
    int pilihan;

    while (true) {
        pembatas();
        cout << GREEN << "CRUD" << endl;
        cout << "1. Tampilkan Pasien\n2. Tambahkan Pasien\n3. Delete Pasien\n4. Update Pasien\n5. Keluar\n";
        pilihan = cekInputInteger("Masukan Pilihan ! : ");
        pembatas();

        switch(pilihan) {
            case 1:
                readItems();
                break;
            case 2:
                menu();
                pendaftaran();
                pemilihanPoli();
                break;
            case 3:
                deleteItem();
                break;
            case 4:
                updateItem();
                break;
            case 5:
                cout << GREEN << "Terima kasih! Program selesai.\n";
                return 0; 
            default:
                cout << "Pilihan tidak ditemukan!\n";
                break;


        }
    }
}