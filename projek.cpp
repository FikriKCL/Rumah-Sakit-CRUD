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
json pasien;
const char* GREEN = "\033[32m";
const char* RED = "\033[31m";
const char* RESET = "\033[0m";
struct Obat{
    string namaObat;
    long long int hargaObat;
};

struct Tindakan{
    string namaTindakan;
    long long int hargaTindakan;
};


// Load data from JSON file
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

    file.close(); // Close the file
    return data;
}


// Save data ke JSON
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


// Mencetak Pembatas
void pembatas(){
    cout << GREEN << string(100, '=') << RESET <<endl;
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
pembatas();
cout << GREEN << judul << endl;
pembatas();
}

// Error handling String ke Integer
// Proseduer Cek Input Integer digunakan untuk mengecek apakah input yang dimasukan oleh user adalah angka
// Memilki parameter const string& prompt digunakan untuk menggantikan variable prompt di dalam fungsi ex: cekInputInteger("Masukan ID Pasien : ");
// "Masukan ID Pasien" akan menggantikan variable prompt
int cekInputInteger(const string& prompt) {
    int input;
    while (true) {
        cout << GREEN << prompt << RESET;
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

// Error handling Empty Input
// Prosedur Cek Input String digunakan untuk mengecek apakah input yang dimasukan oleh user tidak kosong
// Memilki parameter const string& prompt digunakan untuk menggantikan variable prompt di dalam fungsi ex: cekInputString("Masukan ID Pasien : ");
// "Masukan ID Pasien" akan menggantikan variable prompt
string cekInputString(const string& prompt) {
    string input;
    while (true) {
        cout << GREEN << prompt << RESET;
        getline(cin, input);
//Mengecek apakah input kosong
        if (input.empty()) {
//Apabila kosong akan mencetak pesan            
            cout << RED << "Input harus diisi dengan huruf/kalimat\n" << RESET;
        } else {
//Apabila tidak kosong akan mengembalikan nilai input            
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
        cout << GREEN << prompt << RESET;
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

// Error Mengecek BPJS apakah diisi dengan Y (True) dan N (False)
// Prosedur CekBPJS digunakan untuk mengecek BPJS true atau false
// Memilki parameter const string& prompt digunakan untuk menggantikan variable prompt di dalam fungsi ex: cekBPJS("Apakah anda pengguna BPJS : ");
// "Apakah anda pengguna BPJS : " akan menggantikan variable prompt
bool cekBPJS(const string& prompt) {
    string input;
    while (true) {
        cout << GREEN << prompt << RESET;
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

//Prosedur BPJS pada tahap penentuan biaya
// Memilki parameter bool bpjs, string tindakan, int biaya
bool bpjs(bool bpjs, const Tindakan &tindakan) {
//Apabila user pengguna BPJS maka biaya akan menjadi 0 lalu mencetak pesan dan mengembalikan true    
    if(bpjs) {
        int biaya = 0;
        cout << GREEN << "Biaya tindakan dan konsultasi ditanggung BPJS" << RESET << endl;
        cout << GREEN << "Biaya menjadi Rp- " << biaya << RESET << endl;
        return true;    
    } else {
//Apabila user tidak terdaftar bpjs maka biaya akan tetap sama lalu mencetak pesan dan mengembalikan false         
        cout << RED << "BPJS Tidak Terdaftar. Biaya akan dikenakan secara mandiri." << RESET << endl;
        cout << GREEN << "Biaya " << tindakan.namaTindakan <<  "  menjadi Rp- " << tindakan.hargaTindakan << RESET << endl;
        return false;
    }
}

// Fungsi Pendaftaran
void pendaftaran() {
//Memuat data dari File melalui prosedur loadData()
    json data = loadData();
    
    if (!data.contains("Pasien") || !data["Pasien"].is_array()) {
        data["Pasien"] = json::array();
    }

    int id = cekInputInteger("Masukan ID Pasien : ");
    int long nik = cekInputInteger("Masukan NIK Pasien : ");
    int umur = cekInputInteger("Masukan Umur Pasien : ");
    string nama = cekInputString("Masukan Nama Pasien : ");
    string jenis_kelamin = cekInputKelamin("Masukan Jenis Kelamin [L/P] : ");
    bool bpjs = cekBPJS("Apakah Anda Pengguna BPJS? [Y/N] : ");
    string ttl = cekInputString("Masukan Tempat Tanggal Lahir [DD/MM/YYYY] : ");

    //Mendeklarasikan data ke dalam variabel yang akan di simpan di file JSON yang telah dibuat
    data["Pasien"] = {{"id", id}, {"nama", nama}, {"nik", nik}, {"umur", umur}, {"jenis_kelamin", jenis_kelamin}, {"ttl", ttl}, {"BPJS", bpjs}};

    //Save data yang telat diinput kedalam file
    saveData(data);
    pembatas();
}

//Sebuah prosedur yang berisi switch case untuk memilih tindakan berdasarkan id_tindakan, akan dipanggil di fungsi Poliklinik masing-masing
void pilihTindakan(int id_tindakan, string keluhan){
    int biaya;
    json data = loadData();
    bool done = false;
    string tindakan;
    bool bpjsStatus = pasien["BPJS"];

    if(id_tindakan == 1){
        cout << GREEN <<"Tindakan untuk Poli Gigi\n" << RESET;
    //Mengecek Input pilih_tindakan apakah itu angka atau tidak 
    if (id_tindakan == 1) {
        cout << GREEN << "Tindakan untuk Poli Gigi\n" << RESET;

        Tindakan tindakanGigi[] = {
            {"Scaling Karang Gigi", 500000}, 
            {"Pembersihan Gigi", 250000}, 
            {"Penggantian Gigi", 150000}, 
            {"Tambal Gigi", 200000}, 
            {"Behel Gigi", 200000}
        };
        do {
            int pilih_tindakan = cekInputInteger("Silahkan Pilih Tindakan\n1. Scaling Karang Gigi\n2. Pembersihan Gigi\n3. Penggantian Gigi\n4. Tambal Gigi\n5. Behel Gigi\n6. Selesai\n");

            if (pilih_tindakan >= 1 && pilih_tindakan <= 5) {
                int index = pilih_tindakan - 1;
                cout << tindakanGigi[index].namaTindakan << endl;
                cout << "Harga: " << tindakanGigi[index].hargaTindakan << endl;

                // Call the BPJS function and save tindakan
                bpjs(data["Pasien"]["BPJS"], tindakanGigi[index]);
                data["Pasien"]["tindakan"].push_back({
                    {"namaTindakan", tindakanGigi[index].namaTindakan},
                    {"hargaTindakan", tindakanGigi[index].hargaTindakan}
                });
                cout << "Tindakan berhasil disimpan.\n";
            } else if (pilih_tindakan == 6) {
                cout << "Selesai dengan Poli Gigi.\n";
                done = true;
            } else {
                cout << "Pilihan tidak valid, coba lagi.\n";
            }
        } while (!done);
    } else {
        cout << "Poliklinik yang dipilih tidak tersedia.\n";
    }

    saveData(data); // Save the data after actions
    }else if(id_tindakan == 2){
        cout << GREEN <<  "Tindakan untuk Poli Umum\n" << RESET;
        Tindakan tindakanUmum[] = {{"Pemeriksaan Umum", 80000},{"Pemeriksaan Kesehatan", 100000}};
        do{
            int tindakan = cekInputInteger("Silahkan Pilih Tindakan\n 1. Pemeriksaan Umum\n 2. Pemeriksaan Kesehatan");
            switch(tindakan){
            case 1: 
            cout << tindakanUmum[0].namaTindakan << endl;
            cout << tindakanUmum[0].hargaTindakan << endl;   
            bpjs(bpjsStatus, tindakanUmum[1]);

            data["Pasien"]["tindakan"].push_back({"namaTindakan", tindakanUmum[1].namaTindakan, "hargaTindakan", tindakanUmum[1].hargaTindakan});
            break;
            case 2:
            cout << tindakanUmum[1].namaTindakan << endl;
            cout << tindakanUmum[1].hargaTindakan << endl;   
            bpjs(bpjsStatus, tindakanUmum[1]);

            data["Pasien"]["tindakan"].push_back({"namaTindakan", tindakanUmum[1].namaTindakan, "hargaTindakan", tindakanUmum[1].hargaTindakan});
            break;
            default:
            cout << "3.Tindakan belum ada!\n"; 
            }
        }while(!done);
    }else if(id_tindakan == 3){
        cout << GREEN << "Tindakan untuk Poli Orthopedi\n" << RESET;
        Tindakan tindakanOrthopedi[] = {{"Operasi Lutut", 30000000},{"Operasi Paha", 35000000},{"Operasi Kaki", 40000000},{"Operasi Punggung", 33000000},{"Fisioterapi", 250000}};
        do{
        int tindakan = cekInputInteger("Silahkan Pilih Tindakan\n 1. Operasi Lutut\n 2. Operasi Paha\n 3. Operasi Kaki\n 4. Operasi Punggung\n 5. Fisioterapi");
        switch(tindakan){
            case 1: 
            cout << tindakanOrthopedi[0].namaTindakan << endl;
            cout << tindakanOrthopedi[0].hargaTindakan << endl;   
            bpjs(bpjsStatus, tindakanOrthopedi[0]);

            data["Pasien"]["tindakan"].push_back({"namaTindakan", tindakanOrthopedi[0].namaTindakan, "hargaTindakan", tindakanOrthopedi[0].hargaTindakan});
            break;
            case 2:
            cout << tindakanOrthopedi[1].namaTindakan << endl;
            cout << tindakanOrthopedi[1].hargaTindakan << endl;   
            bpjs(bpjsStatus, tindakanOrthopedi[1]);

            data["Pasien"]["tindakan"].push_back({"namaTindakan", tindakanOrthopedi[1].namaTindakan, "hargaTindakan", tindakanOrthopedi[1].hargaTindakan});
            break;
            case 3:
            cout << tindakanOrthopedi[2].namaTindakan << endl;
            cout << tindakanOrthopedi[2].hargaTindakan << endl;   
            bpjs(bpjsStatus, tindakanOrthopedi[2]);

            data["Pasien"]["tindakan"].push_back({"namaTindakan", tindakanOrthopedi[2].namaTindakan, "hargaTindakan", tindakanOrthopedi[2].hargaTindakan});
            break;
            case 4:
            cout << tindakanOrthopedi[3].namaTindakan << endl;
            cout << tindakanOrthopedi[3].hargaTindakan << endl;   
            bpjs(bpjsStatus, tindakanOrthopedi[3]);

            data["Pasien"]["tindakan"].push_back({"namaTindakan", tindakanOrthopedi[3].namaTindakan, "hargaTindakan", tindakanOrthopedi[3].hargaTindakan});
            break;
            case 5:
            cout << tindakanOrthopedi[4].namaTindakan << endl;
            cout << tindakanOrthopedi[4].hargaTindakan << endl;   
            bpjs(bpjsStatus, tindakanOrthopedi[4]);

            data["Pasien"]["tindakan"].push_back({"namaTindakan", tindakanOrthopedi[4].namaTindakan, "hargaTindakan", tindakanOrthopedi[4].hargaTindakan});
            break;
            default:
            cout << "Tindakan belum ada!";    
            };
        }while(!done);
    }else if(id_tindakan == 4){
        cout << GREEN << "Tindakan untuk Poli Anak\n" << RESET;
        int tindakan = cekInputInteger("Silahkan Pilih Tindakan\n");
        switch(tindakan){
            case 1: 
            cout << "1.Pemeriksaan Kesehatan\n";
            break;
            case 2:
            cout << "2.Konsultasi Gizi & Tumbuh Kembang \n";
            break;
            default:
            cout << "Tindakan belum ada!";    
        };
    }else if(id_tindakan == 5){
        cout << GREEN << "Tindakan untuk Poli Kejiwaan\n" << RESET;
        int tindakan = cekInputInteger("Silahkan Pilih Tindakan\n");
        switch(tindakan){
            case 1:
            cout << "1.Sesi Terapi Kejiwaan\n";
            break;
            default:
            cout << "Tindakan belum ada!";
        }
    }
    saveData(data);
}

void pembayaran(string obat[5][2]) {
    string arrayObat[5][2];
    json data = loadData();
    int pembayaran;
    int id = pasien["id"];

    for(int i = 0; i < 5; i++){
        cout << "\n" << arrayObat[i][0] << " Rp." << arrayObat[i][1] << endl;
    }

    cout << "Pembayaran\n1.Cash\n2.Kredit\n";
    pembayaran = cekInputInteger("Silahkan Pilih Pembayaran\n");

    data["Pasien"] = {{"tipe_bayar", pembayaran}};

    saveData(data);
}

// Fungsi Poliklinik
void poliGigi() {

     Obat obatPoliGigi[] = {
        {"Penghilang Nyeri Gigi", 5000},
        {"Obat Gusi Bengkak", 10000},
        {"Antibiotik Gigi", 8000},
        {"Obat Kumur Antiseptik", 15000},
        {"Obat Luka Dalam Mulut", 20000}
    };

    string keluhan;
    int tindakan;
    cout << GREEN << "Anda di Poli Gigi!" << RESET << endl;
    cout << GREEN << "Silahkan Konsultasi ke Dokter!\nJelaskan Keluhan Anda!\n" << RESET;
    getline(cin, keluhan);
    pilihTindakan(1, keluhan);
    // pembayaran(obatPoliGigi);
    
}

void poliUmum() {
    string obatPoliUmum[5][2] = {
        {"Penurun Demam", "5000"},
        {"Obat Sakit Kepala", "7000"},
        {"Vitamin untuk Daya Tahan Tubuh", "10000"},
        {"Obat Maag", "8000"},
        {"Penghilang Nyeri Otot", "12000"}
    };
   
    string keluhan;
    cout << GREEN << "Anda di Poli Umum!" << RESET << endl;
    pilihTindakan(2,keluhan);

}

void poliOrthopedi() {
    string obatPoliOrthopedi[5][2] = {
        {"Obat Nyeri Sendi", "15000"},
        {"Obat Penguat Tulang", "20000"},
        {"Obat Anti Radang Sendi", "10000"},
        {"Vitamin Tulang", "25000"},
        {"Krim Penghilang Pegal", "12000"}
    };
    string keluhan;
    cout << GREEN << "Anda di Poli Orthopedi!" << RESET;
    pilihTindakan(3,keluhan);

}

void poliAnak() {
    string obatPoliAnak[5][2] = {
        {"Obat Penurun Demam Anak", "5000"},
        {"Vitamin Anak", "7000"},
        {"Obat Batuk Anak", "8000"},
        {"Obat Pilek Anak", "6000"},
        {"Obat Nyeri Tumbuh Gigi Anak", "10000"}
    };
    string keluhan;
    cout << GREEN << "Anda di Poli Anak!" << RESET;
    pilihTindakan(4,keluhan);
}

void poliKejiwaan() {
    string obatPoliKejiwaan[5][2] = {
        {"Obat Tidur", "15000"},
        {"Obat Penenang", "20000"},
        {"Obat Anti Cemas", "10000"},
        {"Vitamin Otak", "12000"},
        {"Obat Stres", "25000"}
    };
    string keluhan;
    cout << GREEN << "Anda di Poli Kejiwaan!" << RESET;
    pilihTindakan(5,keluhan);
}

void pemilihanPoli() {
    int poli = 0;
    char ch;
    cout << GREEN <<"Pilih Poliklinik\n1.Poliklinik Gigi\n2.Poliklinik Umum\n3.Poliklinik Kejiwaan\n4.Poliklinik Anak\n5.Poliklinik Orthopedi\n";

    ch = _getch();
    cout << endl;
    if (ch >= '1' && ch <= '5') {
        poli = ch - '0';
    } else {
        cout << "Poliklinik Belum Ada!" << endl;
        return;
    }
    pembatas();

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


int main() {
    menu();
    pendaftaran();
    pemilihanPoli();
    // pembayaran();
}
