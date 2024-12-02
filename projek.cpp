#include <iostream>
#include <string>
#include <iomanip>
#include <thread>
#include <vector>
#include <fstream>
#include "json.hpp"
#include <conio.h>
#include <cctype>

using json = nlohmann::json;
using namespace std;

const string fileJSON = "data.json";
json pasien = json::array();
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

string cekInputTanggal(const string &prompt){
    string input;
    while(true){
        cout << GREEN << prompt << RESET;
        getline(cin,input);

    }
}
// Error handling menginput selain huruf
// Prosedur Cek Input String digunakan untuk mengecek apakah input yang dimasukan oleh user tidak kosong
// Memilki parameter const string& prompt digunakan untuk menggantikan variable prompt di dalam fungsi ex: cekInputString("Masukan ID Pasien : ");
// "Masukan ID Pasien" akan menggantikan variable prompt
string cekInputString(const string &prompt) {
    string input;
    while (true) {
        cout << GREEN << prompt << RESET;
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
            return input;         }
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

int hiddenInput(char maxChoice) {
    char ch;
    int choice = 0;

    ch = _getch(); // Membaca satu karakter tanpa echo ke console
    cout << endl;

    if (ch >= '1' && ch <= maxChoice) {
        choice = ch - '0'; //konvert char ke integer
        return choice;
    }else if (ch == '\n'){
        cout << "Tidak Boleh Kosong!" << endl;  
        return -1;
    } else {
        cout << "Pilihan tidak valid!" << endl;
        return -1; 
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

    // loop untuk mencari ddata pasien
    for (size_t i = 0; i < data["Pasien"].size(); ++i) {
        if (data["Pasien"][i]["id"] == id) {  // cek apakah id pasien sama dengan id terkini yang diambil
            found = true;
            
            cout << GREEN << "Struk Pembayaran\n";

            // Print setiap data tindakan dan menjumlahkan totalnya
            cout << GREEN << "Tindakan:\n";
            for (size_t j = 0; j < data["Pasien"][i]["tindakan"].size(); ++j) {
                int hargaTindakan = data["Pasien"][i]["tindakan"][j]["hargaTindakan"].get<int>();  // mengambil value integer dari hargaTindakan
                cout << "  - " << data["Pasien"][i]["tindakan"][j]["namaTindakan"] 
                     << " (Rp-" << hargaTindakan << ")\n";
                totalBiaya += hargaTindakan;  // menambahkan harga ke total biaya
            }

            // Print setiap data obat
            cout << GREEN << "Obat:\n";
            for (size_t j = 0; j < data["Pasien"][i]["obat"].size(); ++j) {
                int hargaObat = data["Pasien"][i]["obat"][j]["hargaObat"].get<int>();  // mengambil value integer dari hargaTindakan
                cout << "  - " << data["Pasien"][i]["obat"][j]["namaObat"] 
                     << " (Rp-" << hargaObat << ")\n";
                totalBiaya += hargaObat;  // menambahkan ke total biaya
            }

            // mencetak total biaya
            cout << GREEN << "Total Biaya Obat & Tindakan adalah Rp-" << totalBiaya << endl;

            break;  // Keluar loop ketika id ketemu
        }
    }

    //Apabila tidak id tidak ketemu akan mencetak pesan
    if (!found) {
        cout << RED << "Pasien dengan ID " << id << " tidak ditemukan.\n";
        return;
    }

    if (!bpjsStatus) {
        // Kalau BPJS tidak aktif maka akan melanjutkan pembayaran
        cout << "Pembayaran\n1. Cash\n2. Kredit\n";
        pembayaran = cekInputInteger("Silahkan Pilih Pembayaran\n"); 

        // Apabila memilih Kredit maka tidak harus memasukan nominal 
        if (pembayaran == 2) {
            bool done = false;
            do{
            uang = cekInputInteger("Masukan Jumlah uang di kredit anda : ");
            if(uang > totalBiaya){
                cout << GREEN << "Pembayaran Kredit berhasil, terima kasih!\n";
                cout << GREEN << "Sisa uang di kredit anda : " << uang - totalBiaya;
                done = true;
            }else if (uang == totalBiaya){
                 cout << GREEN << "Pembayaran Kredit berhasil, terima kasih!\n";   
                 done = true;
            }else{
                cout << RED << "Pembayaran gagal. Saldo tidak cukup!";
            }
            }while(!done);
        //Apabila memilih 1. Cash maka akan meminta memasukan jumlah uang        
        } else if (pembayaran == 1) {
            bool done = false;
            do {
                uang = cekInputInteger("Silahkan Masukan Jumlah Uang\n"); //Mengambil jumlah dari user
                if (uang < totalBiaya) {
                    cout << RED << "Uang kurang, silahkan ulangi!\n";
                } else if(uang = totalBiaya){ 
                    cout << GREEN << "Pembayaran berhasil, terima kasih!\n";
                    done = true; // Kalau sesuai maka loop berhenti
                } else {
                    cout << GREEN << "Pembayaran berhasil, terima kasih!\n";
                    cout << GREEN << "Kembalian anda : " << uang - totalBiaya << endl;
                    done = true;
                }
            } while (!done); // Terus nge loop apabila uang masih kurang.
        } else {
            cout << RED << "Pilihan tidak valid!\n";
        }

        // Menambahkan data jenis pembayaran ke dalam JSON
        bool paymentUpdated = false;
        for (size_t i = 0; i < data["Pasien"].size(); ++i) {
            if (data["Pasien"][i]["id"] == id) {
                data["Pasien"][i]["tipe_bayar"] = pembayaran;
                paymentUpdated = true;
                break;
            }
        }

        if (paymentUpdated) {
            saveData(data); // Save data
        } else {
            cout << RED << "Pasien tidak ditemukan.\n";
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
        cout << GREEN << "Biaya menjadi Rp- " << tindakan.hargaTindakan << RESET << endl;
        pembatas();
        return true;    
    } else {
//Apabila user tidak terdaftar bpjs maka biaya akan tetap sama lalu mencetak pesan dan mengembalikan false         
        cout << RED << "BPJS Tidak Terdaftar. Biaya akan dikenakan secara mandiri." << RESET << endl;
        cout << GREEN << "Biaya " << tindakan.namaTindakan <<  "  menjadi Rp- " << tindakan.hargaTindakan << RESET << endl;
        pembatas();
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

    int id = data["Pasien"].size() + 1;
    long long int nik = cekInputInteger("Masukan NIK Pasien : ");
    int umur = cekInputInteger("Masukan Umur Pasien : ");
    string nama = cekInputString("Masukan Nama Pasien : ");
    string jenis_kelamin = cekInputKelamin("Masukan Jenis Kelamin [L/P] : ");
    bool bpjs = cekBPJS("Apakah Anda Pengguna BPJS? [Y/N] : ");
    string ttl = cekInputString("Masukan Tempat Tanggal Lahir [DD/MM/YYYY] : ");

    //Mendeklarasikan data ke dalam variabel yang akan di simpan di file JSON yang telah dibuat
     pasien = {{"id", id}, {"nama", nama}, {"nik", nik}, {"umur", umur}, {"jenis_kelamin", jenis_kelamin}, {"ttl", ttl}, {"BPJS", bpjs}};

     data["Pasien"].push_back(pasien);    
   
    //Save data yang telah diinput kedalam file
    saveData(data);
    pembatas();
}

    //Sebuah prosedur yang berisi if else untuk memilih tindakan berdasarkan id_tindakan, akan dipanggil di fungsi Poliklinik masing-masing
    //Alasan menggunakan if else agar  memasukan data ke json dapat dalam satu block. Tidak dimasing-masing switch case ditambahkan algoritma untuk menambahkan data
void pilihTindakan(int id_tindakan, string keluhan) {
    json data = loadData(); // Memuat data
    int id = data["Pasien"].back()["id"]; // Mengambil ID Pasien terakhir
    bool done = false;
    bool bpjsStatus = data["Pasien"].back()["BPJS"]; // Mengambil data bpjs
    string tindakan;
    pembatas();
    
    if (id_tindakan == 1) {
        cout << GREEN << "Tindakan untuk Poli Gigi\n" << RESET;

        //Struct berisi tindakan yang terdapat di poli gigi
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
            // Memilih tindakan dan mencetak tindakan yang dipilih berdasarkan angka
            if (pilih_tindakan >= 1 && pilih_tindakan <= 5) {
                cout << GREEN << tindakanGigi[pilih_tindakan - 1].namaTindakan << endl;
                cout << GREEN << tindakanGigi[pilih_tindakan - 1].hargaTindakan << endl;

                bpjs(bpjsStatus, tindakanGigi[pilih_tindakan - 1]);

                // Menambahkan data tindakan ke data pasien
                for (size_t i = 0; i < data["Pasien"].size(); ++i) {
                    if (data["Pasien"][i]["id"] == id) {
                        data["Pasien"][i]["tindakan"].push_back({
                            {"namaTindakan", tindakanGigi[pilih_tindakan - 1].namaTindakan},
                            {"hargaTindakan", tindakanGigi[pilih_tindakan - 1].hargaTindakan}
                        });
                    }
                }
                //Apabila memilih opsi enam maka akan berakhir/lanjut ke selanjutnya 
            } else if (pilih_tindakan == 6) {
                cout << GREEN << "Terima kasih telah menggunakan layanan kami!\n";
                done = true;
            } else {
                //apabila tidak valid akan mencetak pesan untuk memilih ulang
                cout << RED <<"Pilihan tidak valid! Silahkan pilih ulang.\n";
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
                cout << GREEN << tindakanUmum[pilih_tindakan - 1].namaTindakan << endl;
                cout << GREEN << tindakanUmum[pilih_tindakan - 1].hargaTindakan << endl;

                bpjs(bpjsStatus, tindakanUmum[pilih_tindakan - 1]);

                // Add tindakan
                for (size_t i = 0; i < data["Pasien"].size(); ++i) {
                    if (data["Pasien"][i]["id"] == id) {
                        data["Pasien"][i]["tindakan"].push_back({
                            {"namaTindakan", tindakanUmum[pilih_tindakan - 1].namaTindakan},
                            {"hargaTindakan", tindakanUmum[pilih_tindakan - 1].hargaTindakan}
                        });
                    }
                }
            } else if (pilih_tindakan == 3) {
                cout << GREEN << "Terima kasih telah menggunakan layanan kami!\n";
                done = true;
                pembatas();
            } else {
                cout << RED << "Pilihan tidak valid! Silahkan pilih ulang.\n";
            }
        } while (!done);
    } else if (id_tindakan == 3) {
        cout << GREEN << "Tindakan untuk Poli Orthopedi\n" << RESET;
        Tindakan tindakanOrthopedi[] = {
            {"Operasi Lutut", 3000000},
            {"Operasi Paha", 3500000},
            {"Operasi Kaki", 4000000},
            {"Operasi Punggung", 3300000},
            {"Fisioterapi", 250000}
        };

        do {
            cout << GREEN << "Silahkan Pilih Tindakan\n1. Operasi Lutut\n2. Operasi Paha\n3. Operasi Kaki\n4. Operasi Punggung\n5. Fisioterapi\n6. Selesai\n";
            int pilih_tindakan = hiddenInput('6');
            if (pilih_tindakan >= 1 && pilih_tindakan <= 5) {
                cout << GREEN << tindakanOrthopedi[pilih_tindakan - 1].namaTindakan << endl;
                cout << GREEN << tindakanOrthopedi[pilih_tindakan - 1].hargaTindakan << endl;

                bpjs(bpjsStatus, tindakanOrthopedi[pilih_tindakan - 1]);

                // Add tindakan
                for (size_t i = 0; i < data["Pasien"].size(); ++i) {
                    if (data["Pasien"][i]["id"] == id) {
                        data["Pasien"][i]["tindakan"].push_back({
                            {"namaTindakan", tindakanOrthopedi[pilih_tindakan - 1].namaTindakan},
                            {"hargaTindakan", tindakanOrthopedi[pilih_tindakan - 1].hargaTindakan}
                        });
                    }
                }
            } else if (pilih_tindakan == 6) {
                cout << GREEN << "Terima kasih telah menggunakan layanan kami!\n";
                done = true;
                pembatas();
            } else {
                cout << RED << "Pilihan tidak valid! Silahkan pilih ulang.\n";
            }
        } while (!done);
    }else if(id_tindakan == 4){
            cout << GREEN << "Tindakan untuk Poli Orthopedi\n" << RESET;
            Tindakan tindakanAnak[] = {{"Pemeriksaan Kesehatan", 80000},{"Konsultasi Gizi dan Tumbuh Kembang", 200000}};

            do {
                cout << GREEN << "Silahkan Pilih Tindakan\n1. Pemeriksaan Kesehatan\n2. Konsultasi Gizi dan Tumbuh Kembang\n3. Selesai\n";
                int pilih_tindakan = hiddenInput('3');
                if (pilih_tindakan >= 1 && pilih_tindakan <= 2) {
                    cout << GREEN << tindakanAnak[pilih_tindakan - 1].namaTindakan << endl;
                    cout << GREEN << tindakanAnak[pilih_tindakan - 1].hargaTindakan << endl;

                    bpjs(bpjsStatus, tindakanAnak[pilih_tindakan - 1]);

                    // Add tindakan
                    for (size_t i = 0; i < data["Pasien"].size(); ++i) {
                        if (data["Pasien"][i]["id"] == id) {
                            data["Pasien"][i]["tindakan"].push_back({
                                {"namaTindakan", tindakanAnak[pilih_tindakan - 1].namaTindakan},
                                {"hargaTindakan", tindakanAnak[pilih_tindakan - 1].hargaTindakan}
                            });
                        }
                    }
                } else if (pilih_tindakan == 3) {
                    cout << GREEN << "Terima kasih telah menggunakan layanan kami!\n";
                    done = true;
                    pembatas();
                } else {
                    cout << RED << "Pilihan tidak valid! Silahkan pilih ulang.\n";
                }
            } while (!done);
        }else if(id_tindakan == 5){
            cout << GREEN << "Tindakan untuk Poli Orthopedi\n" << RESET;
            Tindakan tindakanKejiwaan[] = {{"Konseling Individu", 300000},{"Terapi Kognitif Perilaku (CBT)", 450000},{"Psikoedukasi", 250000},{"Psikoterapi", 500000},{"Terapi Keluarga", 600000},{"Pemeriksaan Psikologi", 400000},{"Evaluasi Psikiatri", 550000},{"Medikasi Psikiatri", 350000},{"Manajemen Stres", 300000},{"Terapi Relaksasi", 250000}};
            do {  
                cout << GREEN << "Silahkan Pilih Tindakan\n1. Konseling Individu\n2. Terapi Kognitif Perilaku (CBT)\n3. Psikoedukasi\n4. Psikoterapi\n5. Terapi Keluarga\n6. Pemeriksaan Psikologi\n7. Evaluasi Psikiatri\n8. Medikasi Psikiatri\n9. Selesai\n";
                int pilih_tindakan = hiddenInput('9');   
                if (pilih_tindakan >= 1 && pilih_tindakan <= 10) {
                    cout << GREEN << tindakanKejiwaan[pilih_tindakan - 1].namaTindakan << endl;
                    cout << GREEN << tindakanKejiwaan[pilih_tindakan - 1].hargaTindakan << endl;

                    bpjs(bpjsStatus, tindakanKejiwaan[pilih_tindakan - 1]);

                    // Add tindakan
                    for (size_t i = 0; i < data["Pasien"].size(); ++i) {
                        if (data["Pasien"][i]["id"] == id) {
                            data["Pasien"][i]["tindakan"].push_back({
                                {"namaTindakan", tindakanKejiwaan[pilih_tindakan - 1].namaTindakan},
                                {"hargaTindakan", tindakanKejiwaan[pilih_tindakan - 1].hargaTindakan}
                            });
                        }
                    }
                } else if (pilih_tindakan == 11) {
                    cout << GREEN << "Terima kasih telah menggunakan layanan kami!\n";
                    done = true;
                    pembatas();
                } else {
                    cout << RED <<"Pilihan tidak valid! Silahkan pilih ulang.\n";
                }
            } while (!done);
        }
        saveData(data);
    }

void pemilihanObat(Obat obat[], int jumlahObat) {
    pembatas();
    json data = loadData();
    int id = data["Pasien"].back()["id"];
    bool bpjsStatus = data["Pasien"].back()["BPJS"]; // Mengambil data BPJS

    srand(0);
    // Random jumlah obat diberikan
    int quantityObat = 1 + rand() % jumlahObat;

    if (!bpjsStatus) {  
        for (int i = 0; i <= quantityObat; i++) {
            int random = rand() % jumlahObat; 
            cout << GREEN << obat[random].namaObat << endl;
            cout << GREEN << "Rp-" << obat[random].hargaObat << RESET << endl;

            // Append the obat data to the corresponding patient
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

// Fungsi Poliklinik
void poliGigi() {
    pembatas();
    Obat obatGigi[] = {{"Penghilang Nyeri Gigi", 5000},{"Obat Gusi Bengkak", 10000},{"Antibiotik Gigi", 8000},{"Obat Kumur Antiseptik", 15000},{"Obat Luka Dalam Mulut", 20000}};
    string keluhan;
    cout << GREEN << "Anda di Poli Gigi!" << RESET << endl;
    cout << GREEN << "Silahkan Konsultasi ke Dokter!\nJelaskan Keluhan Anda!\n" << RESET;
    getline(cin, keluhan);
    pilihTindakan(1, keluhan);

    int jumlahObat = sizeof(obatGigi) / sizeof (obatGigi[0]);

    // cout << "Jumlah Obat adalah : " <<  jumlahObat;

    pemilihanObat(obatGigi, jumlahObat);
    pembayaran();

}

void poliUmum() {
    pembatas();
    Obat obatUmum[] = {{"Penurun Demam", 5000},{"Obat Sakit Kepala", 5000},{"Vitamin untuk Daya Tahan Tubuh", 7000},{"Obat Maag", 8000},{"Penghilang Nyeri Otot", 12000}};
    string keluhan;
    int jumlahObat = sizeof(obatUmum) / sizeof (obatUmum[0]);

    cout << GREEN << "Anda di Poli Umum!" << RESET << endl;
    pilihTindakan(2,keluhan);
    pemilihanObat(obatUmum, jumlahObat);
    pembayaran();
}   

void poliOrthopedi() {
    pembatas();
    Obat obatOrthopedi[] = {{"Obat Penguat Tulang", 20000},{"Obat Nyeri Sendi", 15000},{"Obat Anti Radang Sendi", 10000},{"Vitamin Tulang", 25000},{"Krim Penghilang Pegal", 12000}};
    string keluhan;
    int jumlahObat = sizeof(obatOrthopedi) / sizeof (obatOrthopedi[0]);

    cout << GREEN << "Anda di Poli Orthopedi!" << RESET;
    pilihTindakan(3,keluhan);
    pemilihanObat(obatOrthopedi, jumlahObat);
    pembayaran();
}

void poliAnak() {
    pembatas();
    Obat obatAnak[] = {{"Obat Penurun Demam Anak", 5000},{"Vitamin Anak", 7000},{"Obat Batuk Anak", 8000},{"Obat Pilek Anak", 6000},{"Obat Nyeri Tumbuh Gigi Anak", 10000}};  
    string keluhan;
    cout << GREEN << "Anda di Poli Anak!" << RESET;
    int jumlahObat = sizeof(obatAnak) / sizeof (obatAnak[0]);
    pilihTindakan(4,keluhan);
    pemilihanObat(obatAnak, jumlahObat);
    pembayaran();
}

void poliKejiwaan() {
    pembatas();
    Obat obatKejiwaan[] = {{"Obat Penenang", 20000},{"Obat Anti Cemas", 10000},{"Vitamin Otak", 12000},{"Obat Stres", 25000},{"Obat Tidur", 15000}};
    string keluhan;
    int jumlahObat = sizeof(obatKejiwaan) / sizeof (obatKejiwaan[0]);
    cout << GREEN << "Anda di Poli Kejiwaan!" << RESET;
    pilihTindakan(5,keluhan);
    pemilihanObat(obatKejiwaan, jumlahObat);
    pembayaran();
}

void pemilihanPoli() {
    int poli = 0;
    char ch;
    bool done = false;

    do{   
        cout << GREEN <<"Pilih Poliklinik\n1.Poliklinik Gigi\n2.Poliklinik Umum\n3.Poliklinik Kejiwaan\n4.Poliklinik Anak\n5.Poliklinik Orthopedi\n";

        ch = _getch();
        cout << endl;
        if (ch >= '1' && ch <= '6') {
            poli = ch - '0';
        } else {
            cout << "Poliklinik Belum Ada!" << endl;
            continue;
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
            case 6:
                cout << GREEN << "Terima kasih telah menggunakan layanan kami!" << RESET << endl;
                done = true; 
            break;
            default:
                cout << " Poliklinik Belum Ada!" << endl;
                break;
        }
    }while(!done);
    
}

int main() {
    menu();
    pendaftaran();
    pemilihanPoli();
}