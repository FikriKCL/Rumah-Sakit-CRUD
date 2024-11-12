#include <iostream>
#include <string>
#include <iomanip>  
#include <thread>
#include <vector>
#include <fstream>
//#include <nlohmann/json.hpp>
//using json = nlohmann::json;

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

    //for(int i = 0; i <= 200; i++){
    //    if(i == 100){
    //        for (char ch : judul) {
    //            cout << ch ;                     
    //            cout.flush();                    
    //            this_thread::sleep_for(1ms);    
    //        }
    //    }else if( i == 200){
    //        cout << endl;
    //    } else {
    //        cout << "=";
    //    }
    //    this_thread::sleep_for(1ms);
    //}
  
}

void pendaftaran() {
    string nama, nik, umur, jenis_kelamin, ttl;

    cout << " Masukan Nama                               : "; getline(cin,nama);
    cout << " Masukan NIK                                : "; getline(cin,nik);
    cout << " Masukan Umur                               : "; getline(cin,umur);
    cout << " Masukan Jenis Kelamin                      : "; getline(cin,jenis_kelamin);
    cout << " Masukan Tempat Tanggal Lahir [DD/~MM/YYYY] : "; getline(cin,ttl);

}

void poliGigi(int PG){
    int jadwal, Kunjungan, dokter,ketik;
        switch (PG)
        {
            case 1:
                cout<<" POLI GIGI "<<endl;
                cout<<"==========="<<endl;
                cout<<" Ketik 1 = Jadwal Perawatan"<<endl;
                cout<<" Ketik 2 = Daftar Dokter"<<endl;
                //cout<<" ketik 3 = "
                cout<<" ========================== "<<endl;
                cout<<" PILIH :  ";cin>>ketik;
                
                    if (ketik==1)
                    {
                        cout<<" JADWAL PERAWATAN  "<<endl;
                        cout<<"=================="<<endl;
                        cout<<" - Senin   : 08.00 - 12.00 "<<endl;
                        cout<<" - Selasa  : 13.00 - 17.00 "<<endl;
                        cout<<" - Rabu    : 08.00 - 12.00 "<<endl;
                        cout<<" - Kamis   : 13.00 - 17.00 "<<endl;
                        cout<<" - Jumat   : 08.00 - 12.00 "<<endl;
                        break;
                    }
                    else if (ketik==2)
                    {
                        cout<<" - Senin   : Dr. Hamdoko Sujatmiko Mrs "<<endl;
                        break;
                    }
            break;
        default:
            cout<<" SILAKAN ULANG KEMBALI "<<endl;
            break;
        }
}

void pembayaran(){
    int jadwal, pembayaran;
}


int main() {
    int PG,ketik;
    menu();
    pendaftaran();

            cout<<" SILAKAN PILIH POLI YANG DIINGINKAN "<<endl;
        cout<<"===================================="<<endl;
        cout<<" - POLI GIGI    = 1 "<<endl;
        cout<<" - POLI ANAK    = 2  "<<endl;
        cout<<" - POLI JANTUNG = 3 "<<endl;

        cout<<"PILIH = ";cin>>PG;
        if (PG)
        {
           poliGigi(PG); 
        }
        else
        {
            
        }
        
    // for(int i = 0;){

    // }
}
