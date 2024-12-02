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

    cout << " > Masukan Nama                               : "; getline(cin,nama);
    cout << " > Masukan NIK                                : "; getline(cin,nik);
    cout << " > Masukan Umur                               : "; getline(cin,umur);
    cout << " > Masukan Jenis Kelamin [L/P]                : "; getline(cin,jenis_kelamin);
    cout << " > Masukan Tempat Tanggal Lahir [DD/~MM/YYYY] : "; getline(cin,ttl);

}


void  menu_utama() {
    int ketik;
        cout<<endl;
        cout<<"      DAFTAR POLI YANG TERSEDIA "<<endl;
        cout<<"____________________________________"<<endl;
        cout<<endl;
        cout<<" (1) POLI JANTUNG     "<<endl;
        cout<<" (2) POLI KULIT       "<<endl;
        cout<<" (3) POLI THT         (dalam tahap pengembangan)"<<endl;
        cout<<" (4) POLI MATA        (dalam tahap pengembangan)"<<endl;
        cout<<" (5) POLI BEDAH       (dalam tahap pengembangan)"<<endl;
        cout<<endl;  
        cout<<"ketik '0' untuk BERHENTI"<<endl;
        cout<<endl;
}


void polijantung(bool kembali){
    int jadwal, Kunjungan, dokter,ketik, pilih;
        do
        {
        cout << "---- SELAMAT DATANG DI POLI JANTUNG ----" << endl;
        cout<<endl;
        cout << " (1) Lihat Jadwal Perawatan" << endl;
        cout << " (2) Lihat Dokter" << endl;
        cout << " (3) Lihat Tindakan" << endl;
        cout<<endl;
        cout << "ketik '0' untuk kembali" << endl;
        cout << "_____________________________________"<<endl;
        cout << " > Pilih: ";cin >> pilih;
        cout<<endl;
        

        switch (pilih)
        {
            case 1:
                do
                {
                    cout << "JADWAL PERAWATAN" << endl;
                    cout << "------------------" << endl;
                    cout << " (1) Senin   : 08.00 - 12.00" << endl;
                    cout << " (2) Selasa  : 13.00 - 17.00" << endl;
                    cout << " (3) Rabu    : 08.00 - 12.00" << endl;
                    cout << " (4) Kamis   : 13.00 - 17.00" << endl;
                    cout << " (5) Jumat   : 08.00 - 12.00" << endl;
                    cout<<endl;
                    cout << "ketik '0' untuk kembali" << endl;
                    cout<<"___________________________"<<endl;
                    cout << " > PILIH : ";cin>>ketik;
                    cout<<endl;
                    
                    if (ketik>=1&&ketik<=5)
                    {
                        cout<<" Hari berhasil dipilih\n";
                        cout<<" Jadwal perawatan hari ini adalah "<<endl;
                        switch (ketik)
                        {
                            case 1:
                                cout<<" Senin   : 08.00 - 12.00"<<endl;
                                break;
                            case 2:
                                cout<<" Selasa  : 13.00 - 17.00"<<endl;
                                break;
                            case 3:
                                cout<<" Rabu    : 08.00 - 12.00"<<endl;
                                break;
                            case 4:
                                cout<<" Kamis   : 13.00 - 17.00"<<endl;
                                break;
                            case 5:
                                cout<<" Jumat   : 08.00 - 12.00"<<endl;
                                break;
                        }
                        cout<<endl;
                        break;
                    }
                    else
                    {
                        cout<<"PILIHAN TIDAK VALID !\n";
                    }     
                } while(ketik != 0); //ke menu
                break;

            case 2:
                do
                {
                    cout << "DAFTAR DOKTER" << endl;
                    cout << "__________________" << endl;
                    cout << " (1) Senin   : Dr. Handoko Sujatmiko Mrs" << endl;
                    cout << " (2) Selasa  : Dr. Rizky Fauzi" << endl;
                    cout << " (3) Rabu    : Dr. Rizky Fauzi" << endl;
                    cout << " (4) Kamis   : Dr. Handoko Sujatmiko Mrs" << endl;
                    cout << " (5) Jumat   : Dr. Rizky Fauzi" << endl;
                    cout<<endl;
                    cout << "ketik '0' untuk kembali" << endl;
                    cout<<"___________________________"<<endl;
                    cout << " > PILIH : ";cin >> ketik;
                    cout<<endl;
                    
                } while(ketik != 0);  //ke menu
                break;

            case 3:
                do
                {
                    cout << "DAFTAR TINDAKAN & PENANGANAN" << endl;
                    cout << "__________________" << endl;
                    cout << " "
                } while();

            case 0:
                kembali = true;
                cout<<" Kembali ke Menu"<<endl;
                break;

        default:
            cout<<endl;
            cout<<" ========================"<<endl;
            cout<<" |   pilihan tidak ada   |"<<endl;
            cout<<" | SILAKAN ULANG KEMBALI |"<<endl;
            cout<<" ========================"<<endl;
            cout<<endl;
            break;
        }
        } while(!kembali); // ke menu utama


        /*switch (PG)
        //{
            case 1:
                cout<<"          POLI GIGI "<<endl;
                cout<<" =========================="<<endl;
                cout<<" Ketik 1 = Jadwal Perawatan"<<endl;
                cout<<" Ketik 2 = Daftar Dokter"<<endl;
                //cout<<" ketik 3 = "
                cout<<" ========================== "<<endl;
                cout<<"SILAKAN PILIH POLI YANG DIINGINKAN =  ";cin>>ketik;
                
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
                        cout<<" - Senin   : Dr. Handoko Sujatmiko Mrs "<<endl;
                        cout<<" - Selasa  :  Dr. Rizky Fauzi "<<endl;
                        cout<<" - Rabu    :  Dr. Rizky Fauzi "<<endl;
                        cout<<" - Kamis   :  Dr. Handoko Sujatmiko Mrs "<<endl;
                        cout<<" - Jumat   :  Dr. Rizky Fauzi "<<endl;
                        break;
                    }
            break;
        //default:
            cout<<" SILAKAN ULANG KEMBALI "<<endl;
            break;
        }*/
}

void polikulit(bool kembali){
        int jadwal, Kunjungan, dokter,ketik, pilih;
        do
        {
        cout << "---- SELAMAT DATANG DI POLI KULIT ----" << endl;
        cout<<endl;
        cout << " (1) Lihat Jadwal Perawatan" << endl;
        cout << " (2) Lihat Dokter" << endl;
        cout<<endl;
        cout << "ketik '0' untuk kembali" << endl;
        cout << "_____________________________________"<<endl;
        cout << " > Pilih: ";cin >> pilih;
        cout<<endl;


        switch (pilih)
        {
            case 1:
                do
                {
                    cout << "JADWAL PERAWATAN" << endl;
                    cout << "------------------" << endl;
                    cout << " (1) Senin   : 08.00 - 12.00" << endl;
                    cout << " (2) Selasa  : 13.00 - 17.00" << endl;
                    cout << " (3) Rabu    : 08.00 - 12.00" << endl;
                    cout << " (4) Kamis   : 13.00 - 17.00" << endl;
                    cout << " (5) Jumat   : 08.00 - 12.00" << endl;
                    cout<<endl;
                    cout << "ketik '0' untuk kembali" << endl;
                    cout<<"___________________________"<<endl;
                    cout << " > PILIH : ";cin>>ketik;
                    cout<<endl;
                    
                    if (ketik>=1&&ketik<=5)
                    {
                        cout<<" Hari berhasil dipilih\n";
                        cout<<" Jadwal perawatan hari ini adalah "<<endl;
                        switch (ketik)
                        {
                            case 1:
                                cout<<" Senin   : 08.00 - 12.00"<<endl;
                                break;
                            case 2:
                                cout<<" Selasa  : 13.00 - 17.00"<<endl;
                                break;
                            case 3:
                                cout<<" Rabu    : 08.00 - 12.00"<<endl;
                                break;
                            case 4:
                                cout<<" Kamis   : 13.00 - 17.00"<<endl;
                                break;
                            case 5:
                                cout<<" Jumat   : 08.00 - 12.00"<<endl;
                                break;
                        }
                        cout<<endl;
                        break;
                    }
                    else
                    {
                        cout<<"PILIHAN TIDAK VALID\n";
                    }

                } while(ketik != 0); //ke menu
                break;

            case 2:
                do
                {
                    cout << "DAFTAR DOKTER" << endl;
                    cout << "__________________" << endl;
                    cout << " (1) Senin   : Dr. Handoko Sujatmiko Mrs" << endl;
                    cout << " (2) Selasa  : Dr. Rizky Fauzi" << endl;
                    cout << " (3) Rabu    : Dr. Rizky Fauzi" << endl;
                    cout << " (4) Kamis   : Dr. Handoko Sujatmiko Mrs" << endl;
                    cout << " (5) Jumat   : Dr. Rizky Fauzi" << endl;
                    cout<<endl;
                    cout << "ketik '0' untuk kembali" << endl;
                    cout<<"___________________________"<<endl;
                    cout << " > PILIH : ";cin >> ketik;
                    cout<<endl;
                    
                } while(ketik != 0);  //ke menu
                break;

            case 0:
                kembali = true;
                cout<<" Kembali ke Menu"<<endl;
                break;

        default:
            cout<<endl;
            cout<<" ========================"<<endl;
            cout<<" |   pilihan tidak ada   |"<<endl;
            cout<<" | SILAKAN ULANG KEMBALI |"<<endl;
            cout<<" ========================"<<endl;
            cout<<endl;
            break;
        }
        } while(!kembali); // ke menu utama
}

void politht(bool kembali){
    int jadwal, Kunjungan, dokter,ketik, pilih;
        do
        {
        cout << "---- SELAMAT DATANG DI POLI THT ----" << endl;
        cout<<endl;
        cout << " (1) Lihat Jadwal Perawatan" << endl;
        cout << " (2) Lihat Dokter" << endl;
        cout<<endl;
        cout << "ketik '0' untuk kembali" << endl;
        cout << "_____________________________________"<<endl;
        cout << " > Pilih: ";cin >> pilih;
        cout<<endl;
        

        switch (pilih)
        {
            case 1:
                do
                {
                    cout << "JADWAL PERAWATAN" << endl;
                    cout << "------------------" << endl;
                    cout << " (1) Senin   : 08.00 - 12.00" << endl;
                    cout << " (2) Selasa  : 13.00 - 17.00" << endl;
                    cout << " (3) Rabu    : 08.00 - 12.00" << endl;
                    cout << " (4) Kamis   : 13.00 - 17.00" << endl;
                    cout << " (5) Jumat   : 08.00 - 12.00" << endl;
                    cout<<endl;
                    cout << "ketik '0' untuk kembali" << endl;
                    cout<<"___________________________"<<endl;
                    cout << " > PILIH : ";cin>>ketik;
                    cout<<endl;
                    
                    if (ketik>=1&&ketik<=5)
                    {
                        cout<<" Hari berhasil dipilih\n";
                        cout<<" Jadwal perawatan hari ini adalah "<<endl;
                        switch (ketik)
                        {
                            case 1:
                                cout<<" Senin   : 08.00 - 12.00"<<endl;
                                break;
                            case 2:
                                cout<<" Selasa  : 13.00 - 17.00"<<endl;
                                break;
                            case 3:
                                cout<<" Rabu    : 08.00 - 12.00"<<endl;
                                break;
                            case 4:
                                cout<<" Kamis   : 13.00 - 17.00"<<endl;
                                break;
                            case 5:
                                cout<<" Jumat   : 08.00 - 12.00"<<endl;
                                break;
                        }
                        cout<<endl;
                        break;
                    }
                    else
                    {
                        cout<<"PILIHAN TIDAK VALID\n";
                    }

                } while(ketik != 0); //ke menu
                  break;

            case 2:
                do
                {
                    cout << "DAFTAR DOKTER" << endl;
                    cout << "__________________" << endl;
                    cout << " (1) Senin   : Dr. Handoko Sujatmiko Mrs" << endl;
                    cout << " (2) Selasa  : Dr. Rizky Fauzi" << endl;
                    cout << " (3) Rabu    : Dr. Rizky Fauzi" << endl;
                    cout << " (4) Kamis   : Dr. Handoko Sujatmiko Mrs" << endl;
                    cout << " (5) Jumat   : Dr. Rizky Fauzi" << endl;
                    cout<<endl;
                    cout << "ketik '0' untuk kembali" << endl;
                    cout<<"___________________________"<<endl;
                    cout << " > PILIH : ";cin >> ketik;
                    cout<<endl;
                    
                } while(ketik != 0);  //ke menu
                  break;

            case 0:
                kembali = true;
                cout<<" Kembali ke Menu"<<endl;
                break;

        default:
            cout<<endl;
            cout<<" ========================"<<endl;
            cout<<" |   pilihan tidak ada   |"<<endl;
            cout<<" | SILAKAN ULANG KEMBALI |"<<endl;
            cout<<" ========================"<<endl;
            cout<<endl;
            break;
        }
        } while(!kembali); // ke menu utama
}
void polimata(bool kembali){
    int jadwal, Kunjungan, dokter,ketik, pilih;
        do
        {
        cout << "---- SELAMAT DATANG DI POLI MATA ----" << endl;
        cout<<endl;
        cout << " (1) Lihat Jadwal Perawatan" << endl;
        cout << " (2) Lihat Dokter" << endl;
        cout<<endl;
        cout << "ketik '0' untuk kembali" << endl;
        cout << "_____________________________________"<<endl;
        cout << " > Pilih: ";cin >> pilih;
        cout<<endl;
        

        switch (pilih)
        {
            case 1:
                do
                {
                    cout << "JADWAL PERAWATAN" << endl;
                    cout << "------------------" << endl;
                    cout << " (1) Senin   : 08.00 - 12.00" << endl;
                    cout << " (2) Selasa  : 13.00 - 17.00" << endl;
                    cout << " (3) Rabu    : 08.00 - 12.00" << endl;
                    cout << " (4) Kamis   : 13.00 - 17.00" << endl;
                    cout << " (5) Jumat   : 08.00 - 12.00" << endl;
                    cout<<endl;
                    cout << "ketik '0' untuk kembali" << endl;
                    cout<<"___________________________"<<endl;
                    cout << " > PILIH : ";cin>>ketik;
                    cout<<endl;
                    
                    if (ketik>=1&&ketik<=5)
                    {
                        cout<<" Hari berhasil dipilih\n";
                        cout<<" Jadwal perawatan hari ini adalah "<<endl;
                        switch (ketik)
                        {
                            case 1:
                                cout<<" Senin   : 08.00 - 12.00"<<endl;
                                break;
                            case 2:
                                cout<<" Selasa  : 13.00 - 17.00"<<endl;
                                break;
                            case 3:
                                cout<<" Rabu    : 08.00 - 12.00"<<endl;
                                break;
                            case 4:
                                cout<<" Kamis   : 13.00 - 17.00"<<endl;
                                break;
                            case 5:
                                cout<<" Jumat   : 08.00 - 12.00"<<endl;
                                break;
                        }
                        cout<<endl;
                        break;
                    }
                    else
                    {
                        cout<<"PILIHAN TIDAK VALID\n";
                    }

                } while(ketik != 0); //ke menu
                break;

            case 2:
                do
                {
                    cout << "DAFTAR DOKTER" << endl;
                    cout << "__________________" << endl;
                    cout << " (1) Senin   : Dr. Handoko Sujatmiko Mrs" << endl;
                    cout << " (2) Selasa  : Dr. Rizky Fauzi" << endl;
                    cout << " (3) Rabu    : Dr. Rizky Fauzi" << endl;
                    cout << " (4) Kamis   : Dr. Handoko Sujatmiko Mrs" << endl;
                    cout << " (5) Jumat   : Dr. Rizky Fauzi" << endl;
                    cout<<endl;
                    cout << "ketik '0' untuk kembali" << endl;
                    cout<<"___________________________"<<endl;
                    cout << " > PILIH : ";cin >> ketik;
                    cout<<endl;
                    
                } while(ketik != 0);  //ke menu
                break;

            case 0:
                kembali = true;
                cout<<" Kembali ke Menu"<<endl;
                break;

        default:
            cout<<endl;
            cout<<" ========================"<<endl;
            cout<<" |   pilihan tidak ada   |"<<endl;
            cout<<" | SILAKAN ULANG KEMBALI |"<<endl;
            cout<<" ========================"<<endl;
            cout<<endl;
            break;
        }
        } while(!kembali); // ke menu utama
}

void  polibedah(bool kembali){
    int jadwal, Kunjungan, dokter,ketik, pilih;
        do
        {
        cout << "---- SELAMAT DATANG DI POLI BEDAH ----" << endl;
        cout<<endl;
        cout << " (1) Lihat Jadwal Perawatan" << endl;
        cout << " (2) Lihat Dokter" << endl;
        cout << " (3) Lihat Tindakan" << endl;
        cout<<endl;
        cout << "ketik '0' untuk kembali" << endl;
        cout << "_____________________________________"<<endl;
        cout << " > Pilih: ";cin >> pilih;
        cout<<endl;
        

        switch (pilih)
        {
            case 1:
                do
                {
                    cout << "JADWAL PERAWATAN" << endl;
                    cout << "------------------" << endl;
                    cout << " (1) Senin   : 08.00 - 12.00" << endl;
                    cout << " (2) Selasa  : 13.00 - 17.00" << endl;
                    cout << " (3) Rabu    : 08.00 - 12.00" << endl;
                    cout << " (4) Kamis   : 13.00 - 17.00" << endl;
                    cout << " (5) Jumat   : 08.00 - 12.00" << endl;
                    cout<<endl;
                    cout << "ketik '0' untuk kembali" << endl;
                    cout<<"___________________________"<<endl;
                    cout << " > PILIH : ";cin>>ketik;
                    cout<<endl;
                    
                    if (ketik>=1&&ketik<=5)
                    {
                        cout<<" Hari berhasil dipilih\n";
                        cout<<" Jadwal perawatan hari ini adalah "<<endl;
                        switch (ketik)
                        {
                            case 1:
                                cout<<" Senin   : 08.00 - 12.00"<<endl;
                                break;
                            case 2:
                                cout<<" Selasa  : 13.00 - 17.00"<<endl;
                                break;
                            case 3:
                                cout<<" Rabu    : 08.00 - 12.00"<<endl;
                                break;
                            case 4:
                                cout<<" Kamis   : 13.00 - 17.00"<<endl;
                                break;
                            case 5:
                                cout<<" Jumat   : 08.00 - 12.00"<<endl;
                                break;
                        }
                        cout<<endl;
                        break;
                    }
                    else
                    {
                        cout<<"PILIHAN TIDAK VALID\n";
                    }

                } while(ketik != 0); //ke menu
                break;

            case 2:
                do
                {
                    cout << "DAFTAR DOKTER" << endl;
                    cout << "__________________" << endl;
                    cout << " (1) Senin   : Dr. Handoko Sujatmiko Mrs" << endl;
                    cout << " (2) Selasa  : Dr. Rizky Fauzi" << endl;
                    cout << " (3) Rabu    : Dr. Rizky Fauzi" << endl;
                    cout << " (4) Kamis   : Dr. Handoko Sujatmiko Mrs" << endl;
                    cout << " (5) Jumat   : Dr. Rizky Fauzi" << endl;
                    cout<<endl;
                    cout << "ketik '0' untuk kembali" << endl;
                    cout<<"___________________________"<<endl;
                    cout << " > PILIH : ";cin >> ketik;
                    cout<<endl;
                    
                } while(ketik != 0);  //ke menu
                break;

            case 

            case 0:
                kembali = true;
                cout<<" Kembali ke Menu"<<endl;
                break;

        default:
            cout<<endl;
            cout<<" ========================"<<endl;
            cout<<" |   pilihan tidak ada   |"<<endl;
            cout<<" | SILAKAN ULANG KEMBALI |"<<endl;
            cout<<" ========================"<<endl;
            cout<<endl;
            break;
        }
        } while(!kembali); // ke menu utama
}

void pembayaran(){
    int jadwal, pembayaran;
}

void kesalahan(){
        cout<<endl;
        cout<<" ========================"<<endl;
        cout<<" |   pilihan tidak ada   |"<<endl;
        cout<<" | SILAKAN ULANG KEMBALI |"<<endl;
        cout<<" ========================"<<endl;
        cout<<endl;
}

int main() {
    int ketik,kembali;
    menu();
    pendaftaran();
    
        do
        {
            menu_utama();
            cout<<"*PERHATIKAN : ketik angka didepan nama poli untuk memilih"<<endl;
            cout<<"========================================================="<<endl;
            cout<<"SILAKAN PILIH POLI YANG DIINGINKAN = ";cin>>ketik;
            cout<<endl;

            kembali=false;
            
        switch (ketik)
        {
            case 1:
            polijantung(kembali);
            if (ketik==1)
            
            break;

            case 2:
            polikulit(kembali);
            break;

            case 3:
            politht(kembali);
            break;

            case 4:
            polimata(kembali);
            break;

            case 5:
            polibedah(kembali);
            break;

            case 0:
                cout<<"      PROGRAM BERHENTI"<<endl;
                cout<<"============================"<<endl;
                cout<<"TERIMAKASIH TELAH BERKUNJUNG"<<endl;
                cout<<endl;
                break;
           

        default:
            kesalahan();
            break;
        }
        } 
        while(ketik !=0);
}

