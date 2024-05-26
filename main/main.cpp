#include <iostream>
#include <iomanip>
#include <conio.h>
#include <fstream>
#include <chrono>
#include <sstream>
#include <limits>

using namespace std;
const int max_user = 50;
const int MAX_BUKU = 50; 
int current_selection = 0;
string current_username;


const string RED = "\033[31m";
const string GREEN = "\033[32m";
const string YELLOW = "\033[33m";
const string BLUE = "\033[34m";
const string MAGENTA = "\033[35m";
const string CYAN = "\033[36m";
const string WHITE = "\033[37m";
const string RESET = "\033[0m"; 

void tampilan_menu(string header, string desc_opt[], int num_opt);
void login_admin();
void tambahbuku();
void update_buku();
void lihat_buku_semua_pinjaman();
void pinjam_buku();
void menu();
void menuadmin();
void login_user();
void username_password(string& username, string& password);
void anggota();
void menu_anggota();
void login_pengunjung();
void lihat_semua_buku();
void lihat_pinjam();
void hapus();
void tamu();
void tamu_menu();
void lihat_judul();
void lihat_penulis();
void lihat_tahun();
void lihat_genre();
string kapitalisasi();
void cari_buku();
void lihat_anggota();
void lihat_tamu();
bool sudah_di_pinjam();
string huruf_lower();
void lihat_buku_csv();
void kelompok();
void eror(string teks);
void suscess(string* teks);
void lihat_Buku_Yang_dipinjamUser();

fstream Data;
fstream dataAnggota;

// Struktur buku
struct buku {
    string judul;
    string penulis;
    int tahun_terbit;
    string genre;
};

struct Pinjaman {
    string username;
    string judul;
    string penulis;
    string tahun;
    string genre;
    string waktu_pinjaman;
    string durasi;
    string selesai_pinjam;
};

struct ID {
    string username;
    string password;
};

void kelompok() {
    // Print the header with green color
    cout << GREEN << "+----------------------------------------------------------+" << RESET << endl;
    cout << GREEN << "| " << RESET << BLUE << "       PROGRAM DIBUAT OLEH KELOMPOK 1 KELAS C2" << RESET << GREEN << "           |" << RESET << endl;
    // Print the team members with cyan color
    cout << GREEN << "|----------------------------------------------------------|" << RESET << endl;
    cout << GREEN << "| " << RESET << "2309106130\tAlif Rifai" << setw(32) << " " << GREEN << " |" << RESET << endl;
    cout << GREEN << "| " << RESET << "2309106132\tAlvito Gabbriel Saputra" << setw(19) << " " << GREEN << " |" << RESET << endl;
    cout << GREEN << "| " << RESET << "2309106136\tYuyun Nabilawati Rumbia" << setw(19) << " " << GREEN << " |" << RESET << endl;
    cout << GREEN << "| " << RESET << "2309106137\tAde Fajar Kurniawan" << setw(23) << " " << GREEN << " |" << RESET << endl;
    cout << GREEN << "+----------------------------------------------------------+" << RESET << endl;
}

int panjangdata() 
{
    int total = 0;
    string tmp;
    Data.open("Databuku.csv", ios::in);
    while (getline(Data, tmp)) {
        total++;
    }
    Data.close();
    return total;
}

string kapitalisasi(string str) 
    {
    istringstream iss(str);
    string word;
    string result;  
    while (iss >> word) {  
        word[0] = toupper(word[0]);
        result += word + " ";
    }
    return result;
}

void eror(string teks) {
    cout <<RED<< teks<<RESET<< endl;
}

void suscess(string* teks){
    cout << GREEN << *teks << RESET << endl;
}

void username_password(string& username, string& password) {
    while (true) {
        cout << "Masukkan username: ";
        if (!getline(cin, username)) {  
            if (cin.eof()) {
                eror("\nInput dibatalkan.\n");
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }
        }
        if (username.empty()) {
            eror("Username tidak boleh kosong!");
           
        } else {
            break;  
        }
    }

    while (true) {
        cout << "Masukkan password: ";
        char ch;
        password.clear();  
        while (true) {
            ch = _getch();
            if (ch == 13) {  // Enter
                break;
            } else if (ch == 26) {  // Ctrl+Z
                eror("\nInput dibatalkan.\n");
                continue;  // Keluar dari program
            } else if (ch == 8) {  // Backspace
                if (!password.empty()) {
                    cout << "\b \b";  // Menghapus karakter dari konsol
                }
            } else {
                password.push_back(ch);
                cout << '*';
            }
        }
        cout << endl;
        if (password.empty()) {
            eror("Password Tidak Boleh Kosong! Silakan Coba Lagi.");
        } else {
            break;  // Keluar dari loop jika input valid
        }
    }
}

void login_admin() {
    system("cls");
    string username, password;
    cout << YELLOW<<"+-----------------------------------------------------------+" << endl;
    cout << "|                      LOGIN ADMIN                          |" << endl;
    cout << "+-----------------------------------------------------------+" <<RESET<< endl;
    username_password(username, password);
    if (username == "admin" && password == "admin") {
        string pesan = "Login Berhasil!";
        suscess(&pesan);
        system("pause");
        menuadmin();
    } else {
        eror("Login Gagal. Username atau Password Salah.");
        system("pause");
        menu();
    }
}

void menu_anggota() {
    int opsi = 4;
    string header =  "MENU ANGGOTA";
    string desc_menu[4] = {"Lihat Buku", "Pinjam Buku", "Lihat Buku Yang Dipinjam", "Kembali"};
    tampilan_menu(header, desc_menu, opsi);

    if (current_selection == 0) {
        lihat_semua_buku();
        menu_anggota();
    } else if (current_selection == 1) {
        pinjam_buku();
    } else if (current_selection == 2) {
        lihat_Buku_Yang_dipinjamUser();
    } else if (current_selection == 3) {
        anggota();
    }
}

void anggota() {
    int opsi = 3;
    string header = "MENU LOGIN ANGGOTA";
    string desc_menu[3] = {"Daftar Sebagai Anggota", "Login Sebagai Anggota", "Kembali"};
    tampilan_menu(header, desc_menu, opsi);
    system("cls");

    if (current_selection == 0) {
        cout <<GREEN<< "+-----------------------------------------------------------------------------------------+\n";
        cout << "|                                REGISTRASI Anggota                                       |\n";
        cout << "+-----------------------------------------------------------------------------------------+\n"<<RESET;
        string username, password;
        username_password(username, password);
        ifstream fileRead("Data_Anggota.csv");
        bool user_terpakai = false;
        if (fileRead.is_open()) {
            string line;
            while (getline(fileRead, line)) {
                stringstream ss(line);
                string user_used;
                getline(ss, user_used, ',');
                if (user_used == username) {
                    eror("Username Sudah Digunakan. Silakan Pilih Username Lain.");
                    system("pause");
                    user_terpakai = true;
                    break;
                }
            }
            fileRead.close();
        }

        if (!user_terpakai) {
            ID anggotaID;
            anggotaID.username = username;
            anggotaID.password = password;
            ofstream fileWrite("Data_Anggota.csv", ios::app);
            if (fileWrite.is_open()) {
                fileWrite << anggotaID.username << "," << anggotaID.password << "\n";
                string pesan = "Pendaftaran Anggota berhasil!";
                suscess(&pesan);
                fileWrite.close();
                system("pause");
                anggota();
            }
        } else {
            anggota();
        }
    } else if (current_selection == 1) {
        cout <<YELLOW<< "+-----------------------------------------------------------------------------------------+\n";
        cout << "|                                    Login Anggota                                        |\n";
        cout << "+-----------------------------------------------------------------------------------------+\n"<<RESET;
        string username, password;
        username_password(username, password);

        ifstream fileRead("Data_Anggota.csv");
        bool login_berhasil = false;
        string line;

        if (fileRead.is_open()) {
            while (getline(fileRead, line)) {
                stringstream ss(line);
                string file_username, file_password;
                getline(ss, file_username, ',');
                getline(ss, file_password);

                if (file_username == username && file_password == password) {
                    string pesan = "Login berhasil";
                    suscess(&pesan);
                    current_username = username;
                    login_berhasil = true;
                    fileRead.close();
                    system("pause");
                    menu_anggota();
                    return;
                }
            }
            fileRead.close();
        }

        if (!login_berhasil) {
            eror("Username atau password salah. Silakan Coba Lagi");
            system("pause");
            anggota();
        }
    } else if (current_selection == 2) {
        login_pengunjung();
    }
}

void tamu_menu() {
    system("cls");
    int opsi = 2;
    string header = "MENU TAMU";
    string desc_menu[2] = {"Lihat Buku", "Kembali"};
    tampilan_menu(header, desc_menu, opsi);
    if (current_selection == 0) {
        lihat_semua_buku();
        tamu_menu();
    } else if (current_selection == 1) {
        login_pengunjung();
    }
}

void tamu() {
    system("cls");
    cout << "+-----------------------------------------------------------+" << endl;
    cout << "|                      LOGIN TAMU                           |" << endl;
    cout << "+-----------------------------------------------------------+" << endl;

    string username;
    while (true) {
        cout << "Masukkan Username: ";
        if (!getline(cin, username)) {
            if (cin.eof()) {
                eror("Inputan tidak bisa diterima");
                cin.clear();  // Membersihkan flag error
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Membersihkan buffer input
                continue;
            }
        }

        if (username.empty()) {
            eror("Username tidak boleh kosong!");
            continue;  // Meminta input username lagi
        } else {
            break;  // Keluar dari loop jika input valid
        }
    }

    ofstream fileWrite("Data_Pengunjung_Tamu.csv", ios::app);
    if (fileWrite.is_open()) {
        auto waktu_sekarang = chrono::system_clock::to_time_t(chrono::system_clock::now());

        // Menggunakan std::put_time untuk memformat waktu
        fileWrite << username << ", " << put_time(localtime(&waktu_sekarang), "%d-%m-%Y %H:%M:%S") << endl;
        cout << GREEN << "Login berhasil pada " << put_time(localtime(&waktu_sekarang), "%d-%m-%Y %H:%M:%S") << RESET << endl;
        fileWrite.close();
        system("pause");
        tamu_menu();
        return;
    } else {
        eror("Gagal Membuka File Untuk Menulis.");
        return;
    }
}

void login_pengunjung() {
    system("cls");
    int opsi = 3;
    string header = "MENU LOGIN PENGUNJUNG";
    string desc_menu[3] = {"Anggota", "Tamu", "Kembali"};
    tampilan_menu(header, desc_menu, opsi);

    if (current_selection == 0) {
        anggota();
    } else if (current_selection == 1) {
        tamu();
    } else if (current_selection == 2) {
        menu();
    }
}

void menuadmin() {
    int opsi = 9;
    string header = "MENU ADMIN";
    string desc_menu[9] = {"Tambah Buku", "Update Buku", "Hapus Buku", "Lihat Buku", "Lihat Daftar Anggota", "Lihat Daftar Tamu", "Cari Buku","Lihat Buku Yang di Pinjam", "Kembali"};
    tampilan_menu(header, desc_menu, opsi);
    if (current_selection == 0) {
        tambahbuku();
    } else if (current_selection == 1) 
    {
        update_buku();
        system("pause");
    } else if (current_selection == 2) 
    {
        hapus();
    } else if (current_selection == 3) 
    {
        lihat_semua_buku();
        menuadmin(); // Kembali ke menu admin setelah melihat buku
    } else if (current_selection == 4) 
    {
         lihat_anggota();
         menu_anggota();
    } else if (current_selection == 5)
    {
        lihat_tamu();
        menuadmin();
    } 
    else if (current_selection== 6)
    {
       cari_buku();
    }
    else if(current_selection == 7)
    {
        lihat_buku_semua_pinjaman();
    }
    else if(current_selection == 8)
    {
        menu();
    }
}

void lihat_buku_semua_pinjaman() {
    system("cls");
    ifstream file("Data_Pinjam.csv");
    if (!file) {
        eror("File Data_Pinjam.csv Tidak Ditemukan.");
        return;
    }

    cout << "Data Buku yang Dipinjam:" << endl;
    cout << GREEN<<"-----------------------------------------------------------------------------"<<RESET << endl;

    string line;
    int nomor = 1;
    while (getline(file, line)) {
        stringstream ss(line);
        Pinjaman pinjaman;
        getline(ss, pinjaman.username, ',');
        getline(ss, pinjaman.judul, ',');
        getline(ss, pinjaman.penulis, ',');
        getline(ss, pinjaman.tahun, ',');
        getline(ss, pinjaman.genre, ',');
        getline(ss, pinjaman.waktu_pinjaman, ',');
        getline(ss, pinjaman.durasi, ',');
        getline(ss, pinjaman.selesai_pinjam, ',');

        cout << nomor << "." << endl;
        cout << "Username        : " << pinjaman.username << endl;
        cout << "Judul Buku      : " << pinjaman.judul << endl;
        cout << "Penulis         : " << pinjaman.penulis << endl;
        cout << "Tahun           : " << pinjaman.tahun << endl;
        cout << "Genre           : " << pinjaman.genre << endl;
        cout << "Tanggal Pinjam  : " << pinjaman.waktu_pinjaman << endl;
        cout << "Durasi Pinjam   : " << pinjaman.durasi << " hari" << endl; // Menampilkan durasi pinjam dari file
        cout << "Tanggal Kembali : " << pinjaman.selesai_pinjam << endl;
        cout << GREEN<<"-----------------------------------------------------------------------------"<< RESET << endl;
        nomor++;
    }
    file.close();
    system("pause");
    menuadmin();
}

string huruf_lower(string str) {
    for (size_t i = 0; i < str.length(); ++i) {
        str[i] = tolower(str[i]);
    }
    return str;
}

void lihat_judul_cari(string& kata_kunci) {
    // Fungsi untuk melihat judul buku yang mengandung kata_kunci
    ifstream file("Databuku.csv");
    string line;
    bool found = false;
    while (getline(file, line)) {
        stringstream ss(line);
        string judul, penulis, tahun, genre;
        getline(ss, judul, ',');
        getline(ss, penulis, ',');
        getline(ss, tahun, ',');
        getline(ss, genre, '\n');

        // Konversi judul dan kata_kunci ke huruf kecil untuk pencarian case-insensitive
        string judul_lower = judul;
        string kata_kunci_lower = kata_kunci;
        huruf_lower(judul_lower);
        huruf_lower(kata_kunci_lower);

        if (judul_lower.find(kata_kunci_lower) != string::npos) {
            cout << "Judul: " << judul << "\n";
            cout << "Penulis: " << penulis << "\n";
            cout << "Tahun: " << tahun << "\n";
            cout << "Genre: " << genre << "\n";
            cout << GREEN <<"+-----------------------------------------------------------+\n"<<RESET;
            found = true;
        }
    }
    file.close();
    if (!found) {
        eror("Buku Tidak Ditemukan");
    }
}

void cari_buku() {
    system("cls");
    string header = "+-----------------------------------------------------------+\n"
                    "|                        CARI BUKU                          |\n"
                    "+-----------------------------------------------------------+\n";
    cout <<YELLOW<< header<<RESET;
    cout << "Masukkan Judul Buku:\n";

    string kata_kunci = "";
    char ch;

    while (true) {
        ch = _getch();
        if (ch == '\r') // Jika tombol 'q' ditekan, keluar dari loop
            menuadmin();
        else if (ch == '\b') { // Jika tombol Backspace ditekan
            if (!kata_kunci.empty()) { 
                kata_kunci.erase(kata_kunci.size() - 1);// Hanya hapus jika kata kunci tidak kosong
            }
        } else if (isprint(ch)) { // Jika karakter yang dicetak
            kata_kunci += ch;
        }
        system("cls"); // Bersihkan layar
        cout <<YELLOW<< header<<RESET;
        cout << "Judul Buku Pencarian: " << kata_kunci << endl;
        cout<< GREEN<<"-------------------------------------------------------------"<<RESET<<endl;
        lihat_judul_cari(kata_kunci); // Menampilkan hasil pencarian berdasarkan kata kunci
        cout << "Masukkan Judul Buku Untuk Pencarian (Tekan [Enter] Untuk keluar):\n";
    }
}

void tambahbuku() {
    system("cls");
    cout << YELLOW<<"+-----------------------------------------------------------+" << endl;
    cout << "|                   MENU TAMBAH BUKU                        |" << endl;
    cout << "+-----------------------------------------------------------+"<<RESET << endl;
    cout << endl;
    buku bk;
    
    while (true) {
        cout << "Masukkan Judul Buku: ";
        if (!getline(cin >> ws, bk.judul)) {  
            if (cin.eof()) {
                eror("Inputan Tidak Valid. Silakan Coba Lagi");
            } else {
                eror("Inputan Tidak Valid. Silakan Coba Lagi");
            }
            cin.clear(); // Mengatur ulang (clear) status kesalahan cin
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Membersihkan buffer input
            continue;
        }
        if (bk.judul.empty()) {
            eror("Judul Buku Tidak Boleh Kosong");
            continue;
        }

        bool valid = true;
        for (size_t i = 0; i < bk.judul.size(); ++i) {
            if (!isalnum(bk.judul[i]) && !isspace(bk.judul[i])) { // Membolehkan spasi
                valid = false;
                break;
            }
        }

        if (!valid) {
            eror("Inputan Tidak Valid. Silakan Coba Lagi");
            continue;
        }

        bk.judul = kapitalisasi(bk.judul);

        ifstream Data;
        Data.open("Databuku.csv", ios::in);
        bool judul_terpakai = false;
        string line;
        while (getline(Data, line)) {
            stringstream ss(line);
            string judul_existing;
            getline(ss, judul_existing, ',');
            if (judul_existing == bk.judul) {
                judul_terpakai = true;
                break;
            }
        }
        Data.close();

        if (judul_terpakai) {
            eror("Judul Buku Sudah Ada. Silakan Masukkan Judul Lain");
            continue;
        }

        break;  
    }


    while (true) {
        cout << "Masukkan Penulis Buku: ";
        if (!getline(cin >> ws, bk.penulis)) { 
             eror("Inputan Tidak Valid. Silakan Coba Lagi");
            cin.clear();  
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  
            continue;
        }
        if (bk.penulis.empty()) {
            eror("Nama Penulis Tidak Boleh Kosong");
            continue;
        }
        bk.penulis = kapitalisasi(bk.penulis);
        break;  
    }

    while (true) {
        cout << "Masukkan Tahun Terbit Buku (YYYY): ";
        if (!(cin >> bk.tahun_terbit) || cin.peek() != '\n') { 
            eror("Tahun terbit Harus Berupa Angka 4 Digit");
            cin.clear();  
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  
            continue;
        }
        if (bk.tahun_terbit < 1000 || bk.tahun_terbit > 9999) { 
            eror("Tahun terbit Harus Berupa Angka 4 Digit");
            continue;
        }
        break;  
    }

    system("cls");
    int opsi = 7;
    string desc_menu[7] = {"Horor","Pelajaran", "Science", "Comedy", "Novel remaja", "Romance", "Fantasy"};
    tampilan_menu("Pilih Genre",desc_menu,opsi);
    if (current_selection == 0)
    {   bk.genre = "Horor";
    }else if(current_selection == 1)
    {    bk.genre = "Pelajaran";
    }else if(current_selection == 2){
        bk.genre = "Science";
    }else if(current_selection == 3){
        bk.genre = "Comedy";
    }else if(current_selection == 4){
        bk.genre = "Novel remaja";
    }else if(current_selection == 5){
        bk.genre = "Romance";
    }else if(current_selection == 6){
        bk.genre = "Fantasy";
    }

    system("cls");
    cout << "Konfirmasi\n";
    cout << GREEN<<"-----------------------------------------------------------"<<RESET<<endl;
    cout << "Judul Buku: " << bk.judul << endl;
    cout << "Penulis: " << bk.penulis << endl;
    cout << "Tahun Terbit: " << bk.tahun_terbit << endl;
    cout << "Genre: " << bk.genre << endl;
    cout << GREEN<<"-----------------------------------------------------------"<<RESET<<endl;
    cout << "Apakah Anda yakin ingin menambahkan buku ini? (y/n): ";
    char konfirmasi;
    cin >> konfirmasi;
    if (konfirmasi != 'y' && konfirmasi != 'Y') {
        eror("Buku tidak ditambahkan");
        system("pause");
        menuadmin();
        return;
    } 

    ofstream Data;
    Data.open("Databuku.csv", ios::out | ios::app);
    Data << bk.judul << "," << bk.penulis << "," << bk.tahun_terbit << "," << bk.genre << endl;
    Data.close();
    string pesan = "Buku  Berhasil Ditambahkan";
    suscess(&pesan);
    system("pause");
    menuadmin();
}
 
void update_buku() {
    lihat_buku_csv();
    int total = panjangdata();
    int index;
    cout << "\nNomor Buku Yang Ingin Diupdate: ";
    cin >> index;
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (index > 0 && index <= total) {
        system("pause");
        buku updated_buku;
        system("cls");
        cout <<YELLOW<< "+-----------------------------------------------------------+" << endl;
        cout << "|                   MENU UPDATE BUKU                        |" << endl;
        cout << "+-----------------------------------------------------------+"<<RESET << endl;
        cout << endl;

        // Input Judul Buku Baru
        while (true) {
            cout << "Masukkan Judul Buku Baru: ";
            if (!getline(cin >> ws, updated_buku.judul)) {
                eror("Inputan Tidak Valid. Silakan Coba Lagi");
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }
            updated_buku.judul = kapitalisasi(updated_buku.judul);
            if (updated_buku.judul.empty()) {
                eror("Judul Buku Tidak Boleh Kosong");
                continue;
            }
            
           
            ifstream Data("Databuku.csv");
            bool judul_terpakai = false;
            string line;
            int currentLine = 1;
            while (getline(Data, line)) {
                if (currentLine != index) {
                    stringstream ss(line);
                    string judul_existing;
                    getline(ss, judul_existing, ',');
                    if (judul_existing == updated_buku.judul) {
                        judul_terpakai = true;
                        break;
                    }
                }
                currentLine++;
            }
            Data.close();

            if (judul_terpakai) {
                eror("Judul Buku Sudah Ada. Silakan Masukkan Judul Lain");
                continue;
            }
            break;
        }

        // Input Penulis Buku Baru
        while (true) {
            cout << "Masukkan Penulis Buku Baru: ";
            if (!getline(cin >> ws, updated_buku.penulis)) {
                eror("Inputan Tidak Valid. Silakan Coba Lagi");
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }
            updated_buku.penulis = kapitalisasi(updated_buku.penulis);
            if (updated_buku.penulis.empty()) {
                eror("Nama Penulis Buku Tidak Boleh Kosong");
                continue;
            }
            break;
        }

        // Input Tahun Terbit Buku Baru
        while (true) {
            cout << "Masukkan Tahun Terbit Buku Baru (YYYY): ";
            if (!(cin >> updated_buku.tahun_terbit) || cin.peek() != '\n') {
                eror("Tahun terbit Harus Berupa Angka 4 Digit");
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }
            if (updated_buku.tahun_terbit < 1000 || updated_buku.tahun_terbit > 9999) {
                eror("Tahun terbit Harus Berupa Angka 4 Digit");
                continue;
            }
            break;
        }
        

        
        int opsi = 7;
        string desc_menu[7] = {"Horor","Pelajaran", "Science", "Comedy", "Novel remaja", "Romance", "Fantasy"};
        tampilan_menu("Pilih Genre Buku", desc_menu, opsi);

        switch (current_selection) {
            case 0: updated_buku.genre = "Horor"; break;
            case 1: updated_buku.genre = "Pelajaran"; break;
            case 2: updated_buku.genre = "Science"; break;
            case 3: updated_buku.genre = "Comedy"; break;
            case 4: updated_buku.genre = "Novel remaja"; break;
            case 5: updated_buku.genre = "Romance"; break;
            case 6: updated_buku.genre = "Fantasy"; break;
            default: updated_buku.genre = "Unknown"; break;
        }

        ifstream inputFile("Databuku.csv");
        if (!inputFile.is_open()) {
            eror("Tidak Dapat Membuka File");
            return;
        }

        stringstream buffer;
        buffer << inputFile.rdbuf();
        inputFile.close();

        ofstream outputFile("Databuku_temp.csv");
        if (!outputFile.is_open()) {
            eror("Tidak Dapat Membuka File");
            return;
        }

        string line;
        int currentLine = 1;
        while (getline(buffer, line)) {
            if (currentLine == index) {
                outputFile << updated_buku.judul << "," << updated_buku.penulis << "," 
                           << updated_buku.tahun_terbit << "," << updated_buku.genre << "\n";
            } else {
                outputFile << line << "\n";
            }
            currentLine++;
        }

        outputFile.close();
        remove("Databuku.csv");
        rename("Databuku_temp.csv", "Databuku.csv");
        string pesan = "Buku Berhasil Diupdate";
        suscess(&pesan);
    } else {
        eror("Nomor Buku Tidak Valid!");
    }
    system("pause");
    menuadmin();
}

void lihat_buku_UntukAnggota() {
    system("cls");
    cout << "+----------------------------------------------------------------------------------------------------------------+" << endl;
    cout << "|                                                   DAFTAR BUKU                                                  |" << endl;
    cout << "+----------------------------------------------------------------------------------------------------------------+" << endl;

    ifstream fileRead("Databuku.csv");
    if (!fileRead.is_open()) {
        cout << "Gagal membuka file Databuku.csv.\n";
        return;
    }

    string line;
    int nomor = 1;
    cout << left << "| " << setw(3) << "NO" 
         << "| " << setw(38) << "JUDUL BUKU" 
         << "| " << setw(28) << "PENULIS" 
         << "| " << setw(8) << "TAHUN" 
         << "| " << setw(26) << "GENRE" 
         << "|" << endl;
    cout << "+----------------------------------------------------------------------------------------------------------------+" << endl;

    while (getline(fileRead, line)) {
        stringstream ss(line);
        string judulBuku, penulis, tahun, genre;
        getline(ss, judulBuku, ',');
        getline(ss, penulis, ',');
        getline(ss, tahun, ',');
        getline(ss, genre);

        cout << left << "| " << setw(3) << nomor 
             << "| " << setw(38) << judulBuku 
             << "| " << setw(28) << penulis 
             << "| " << setw(8) << tahun 
             << "| " << setw(26) << genre 
             << "|" << endl;
        nomor++;
    }
    cout << "+----------------------------------------------------------------------------------------------------------------+" << endl;
    fileRead.close();
}

void lihat_Buku_Yang_dipinjamUser() {
   system("cls");
    string line;
    cout <<YELLOW<< "+-----------------------------------------------------------------------------------------+\n";
    cout << "|                                    Buku yang Dipinjam                                   |\n";
    cout << "+-----------------------------------------------------------------------------------------+\n"<<RESET;
   
    ifstream fileRead("Data_Pinjam.csv");
    int no = 1;
    bool any_book_found = false;

    cout << "Buku yang dipinjam oleh: " << current_username << endl ;
    cout << GREEN<< "-------------------------------------------------------------------------------------------"<<RESET<<endl;
    while (getline(fileRead, line)) {
        stringstream ss(line);
        string username, judul_buku, penulis, tahun, genre, tanggal_pinjam, durasi_pinjam, tanggal_kembali;
        getline(ss, username, ',');
        getline(ss, judul_buku, ',');
        getline(ss, penulis, ',');
        getline(ss, tahun, ',');
        getline(ss, genre, ',');
        getline(ss, tanggal_pinjam, ',');
        getline(ss, durasi_pinjam, ',');
        getline(ss, tanggal_kembali, ',');

        if (username == current_username) {
            cout << no << ". Username        : " << username << "\n";
            cout << "   Judul Buku      : " << judul_buku << "\n";
            cout << "   Penulis         : " << penulis << "\n";
            cout << "   Tahun           : " << tahun << "\n";
            cout << "   Genre           : " << genre << "\n";
            cout << "   Tanggal Pinjam  : " << tanggal_pinjam << "\n";
            cout << "   Durasi Pinjam   : " << durasi_pinjam << " hari\n";
            cout << "   Tanggal Kembali : " << tanggal_kembali << "\n";
            cout <<GREEN<< "+-----------------------------------------------------------------------------------------+\n"<<RESET;
            no++;
            any_book_found = true;
        }
    }

    fileRead.close();

    if (!any_book_found) {
        cout <<RED<< "                               Tidak Ada Buku Yang Dipinjam                             \n"<<RESET;
        
    }

    system("pause");
    menu_anggota();
}


bool sudah_dipinjam(string username, string judul) {
    ifstream Data_Pinjam("Data_Pinjam.csv");
    if (!Data_Pinjam.is_open()) {
        eror("Gagal Membuka File");
        return false;
    }
    string line;
    while (getline(Data_Pinjam, line)) {
        stringstream ss(line);
        string user, book_title;
        getline(ss, user, ',');
        getline(ss, book_title, ',');
        if (user == username && book_title == judul) {
            return true;
        }
    }
    return false;
}

void pinjam_buku() {
    lihat_buku_UntukAnggota();
    int total = panjangdata();
    int index;

    while (true) {
        cout << "Nomor Buku Yang Ingin Dipinjam: ";
        cin >> index;
        cin.clear(); 
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 

        if (cin.fail()) {
            eror("Input Tidak Valid, Masukkan Nomor Buku yang Benar");
            cout << "Tekan Enter untuk melanjutkan...";
            cin.get();
            menu_anggota();
        } else {
            if (index > 0 && index <= total) {
                break;
            } else {
                eror("Nomor Buku Tidak Valid!");
                cout << "Tekan Enter untuk melanjutkan...";
                cin.get();
                menu_anggota();
            }
        }
    }

    int i = 1;
    string judul, penulis, tahun, genre, buku, temp;
    ifstream Data("Databuku.csv");
    if (!Data.is_open()) {
        eror("Gagal membuka file");
        return;
    }

    while (getline(Data, buku)) {
        if (i == index) {
            stringstream line(buku);
            getline(line, judul, ',');
            getline(line, penulis, ',');
            getline(line, tahun, ',');
            getline(line, genre, '\n');
            temp = judul + "," + penulis + "," + tahun + "," + genre;
            break;
        }
        i++;
    }
    Data.close();

    // Cek apakah buku sudah dipinjam
    if (sudah_dipinjam(current_username, judul)) {
        eror("Anda Sudah Meminjam Buku Ini Sebelumnya");
        cout << "Tekan Enter untuk melanjutkan...";
        cin.get();
        menu_anggota();
        return;
    }

    ofstream fileWrite("Data_Pinjam.csv", ios::app);
    if (!fileWrite.is_open()) {
        eror("Gagal membuka file");
        return;
    }

    // Menggunakan chrono untuk mendapatkan waktu saat ini dan memformatnya
    auto now = chrono::system_clock::now();
    time_t now_time = chrono::system_clock::to_time_t(now);
    stringstream datetime;
    datetime << put_time(localtime(&now_time), "%Y-%m-%d %H:%M:%S");

    // Input durasi peminjaman
    int durasi_pinjam;
    cout << "Masukkan durasi peminjaman dalam hari: ";
    cin >> durasi_pinjam;
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (cin.fail() || durasi_pinjam <= 0) {
        eror("Durasi Peminjaman Tidak Valid");
        cout << "Tekan Enter untuk melanjutkan...";
        cin.get();
        menu_anggota();
        return;
    }

    // Menghitung tanggal kembali
    auto kembali_time = now + chrono::hours(durasi_pinjam * 24);
    time_t kembali_time_t = chrono::system_clock::to_time_t(kembali_time);
    stringstream kembali_datetime;
    kembali_datetime << put_time(localtime(&kembali_time_t), "%Y-%m-%d %H:%M:%S");

    fileWrite << current_username << "," << temp << "," << datetime.str() << "," << durasi_pinjam << "," << kembali_datetime.str() << "\n";
    fileWrite.close();

    cout << GREEN << "Buku berhasil dipinjam pada " << datetime.str() << " untuk " << durasi_pinjam << " hari. Tanggal kembali: " << kembali_datetime.str() << RESET << '\n';
    cout << "Tekan Enter untuk melanjutkan...";
    cin.get();
    menu_anggota();
}

void lihat_buku_csv() {
    system("cls");
    
    cout <<YELLOW<< "                                                   DAFTAR BUKU                                                  " <<RESET<< endl;
    cout << "+----------------------------------------------------------------------------------------------------------------+" << endl;

    ifstream fileRead("Databuku.csv");
    if (!fileRead.is_open()) {
        cout << "Gagal membuka file Databuku.csv.\n";
        return;
    }

    string line;
    int nomor = 1;
    cout << left << "| " << setw(3) << "NO" 
         << "| " << setw(38) << "JUDUL BUKU" 
         << "| " << setw(28) << "PENULIS" 
         << "| " << setw(8) << "TAHUN" 
         << "| " << setw(26) << "GENRE" 
         << "|" << endl;
    cout << "+----------------------------------------------------------------------------------------------------------------+" << endl;

    while (getline(fileRead, line)) {
        stringstream ss(line);
        string judulBuku, penulis, tahun, genre;
        getline(ss, judulBuku, ',');
        getline(ss, penulis, ',');
        getline(ss, tahun, ',');
        getline(ss, genre);

        cout << left << "| " << setw(3) << nomor 
             << "| " << setw(38) << judulBuku 
             << "| " << setw(28) << penulis 
             << "| " << setw(8) << tahun 
             << "| " << setw(26) << genre 
             << "|" << endl;
        nomor++;
    }
    cout << "+----------------------------------------------------------------------------------------------------------------+" << endl;
    fileRead.close();
}

void lihat_semua_buku() {
    string header =  "DATA BUKU";
    int opsi =4;
    string desc_menu[4] = {"Berdasarkan Judul (A-Z)", "Berdasarkan Penulis (A-Z)", "Berdasarkan Tahun (1000-9999)", "Berdasarkan Genre", };
    tampilan_menu(header,desc_menu, opsi);
    if(current_selection == 0)
    {
        lihat_judul();
        system("pause");
        return;
    } 
    else if (current_selection == 1)
    {
        lihat_penulis();
        system("pause");
        return;
        
        
    }
    else if (current_selection == 2)
    {
        lihat_tahun();
        system("pause");
        return;
    }
    else if (current_selection == 3)
    {
        lihat_genre();
        system("pause");
        return;
    }
}

void lihat_genre() {
    system("cls");
    int opsi = 7;
    string desc_menu[7]= {"Horor", "Pelajaran", "Science", "Comedy", "Novel remaja", "Romance", "Fantasy" };
    tampilan_menu("Pilih Genre Buku", desc_menu, opsi);

    string genre_terpilih = desc_menu[current_selection]; // Mengambil genre yang dipilih

    system("cls");

    // Membuka file CSV untuk memeriksa apakah ada buku dalam genre yang dipilih
    ifstream dataRead("Databuku.csv");
    string line;
    bool ada_buku = false;

    while (getline(dataRead, line)) {
        stringstream ss(line);
        string judul, penulis, tahun_terbit, genre;
        getline(ss, judul, ',');
        getline(ss, penulis, ',');
        getline(ss, tahun_terbit, ',');
        getline(ss, genre);

        // Jika genre pada data sama dengan genre yang dipilih, set ada_buku menjadi true dan keluar dari loop
        if (genre == genre_terpilih) {
            ada_buku = true;
            break;
        }
    }
    dataRead.close();

    // Jika tidak ada buku dalam genre yang dipilih, tampilkan pesan dan keluar dari fungsi
    if (!ada_buku) {
        cout << "Tidak Ada Buku Dengan Genre "<< genre_terpilih << endl;
        return;
    }

    // Jika ada buku dalam genre yang dipilih, tampilkan tabel buku
    cout <<YELLOW<< "                      Daftar Buku dengan Genre: " << setw(20) << left << genre_terpilih << RESET << endl;
    cout << "=====================================================================================" << endl;
    cout << "| No |                 Judul                 |        Penulis               | Tahun |" << endl;                       
    cout << "=====================================================================================" << endl;

    // Membuka kembali file CSV untuk menampilkan buku dalam genre yang dipilih
    ifstream dataRead2("Databuku.csv");
    int nomor = 0;
    bool is_empty = true;

    while (getline(dataRead2, line)) {
        stringstream ss(line);
        string judul, penulis, tahun_terbit, genre;
        getline(ss, judul, ',');
        getline(ss, penulis, ',');
        getline(ss, tahun_terbit, ',');
        getline(ss, genre);

        // Jika genre pada data sama dengan genre yang dipilih, cetak informasi buku
        if (genre == genre_terpilih) {
            is_empty = false; // Set is_empty menjadi false karena ada buku yang akan ditampilkan
            // Mengatur lebar setiap kolom sesuai dengan panjang maksimum dari data yang akan ditampilkan
            int max_judul = 37;   // Lebar maksimum untuk judul buku
            int max_penulis = 29; // Lebar maksimum untuk nama penulis
            int max_tahun = 6;

            // Memformat output untuk menampilkan dalam bentuk tabel
            cout << "| " << setw(2) << nomor + 1 << " | " << setw(max_judul) << left << judul.substr(0, max_judul) << " | " << setw(max_penulis) << left << penulis.substr(0, max_penulis) <<"|"<<setw(max_tahun)<<left<<tahun_terbit.substr(0, max_tahun)<< " |" << endl;
            nomor++;
        }
    }
    dataRead2.close();

    // Jika tidak ada buku yang ditampilkan, tampilkan pesan bahwa tidak ada buku dalam genre yang dipilih
    if (is_empty) {
        cout << RED <<"                                  Tidak Ada Buku Dalam Genre Tersebut                                " << RESET<< endl;
    }

    cout << "=====================================================================================" << endl;

}

void bubbleSort(string arr[], int n) {
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

void bubbleSortTahun(buku arr[], int n) {
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (arr[j].tahun_terbit > arr[j + 1].tahun_terbit) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

void lihat_tahun() {
    system("cls");

    buku daftarBuku[MAX_BUKU];
    int jumlah_buku = 0;

    // Simpan semua data buku dalam array struktur
    ifstream dataRead("Databuku.csv");
    if (!dataRead) {
        eror("Tidak Dapat Membuka File");
        system("pause");
        return;
    }

    string line;
    while (getline(dataRead, line) && jumlah_buku < MAX_BUKU) {
        stringstream ss(line);
        getline(ss, daftarBuku[jumlah_buku].judul, ',');
        getline(ss, daftarBuku[jumlah_buku].penulis, ',');
        ss >> daftarBuku[jumlah_buku].tahun_terbit;
        getline(ss >> ws, daftarBuku[jumlah_buku].genre);
        if (!daftarBuku[jumlah_buku].genre.empty() && daftarBuku[jumlah_buku].genre[0] == ',') {
        daftarBuku[jumlah_buku].genre = daftarBuku[jumlah_buku].genre.substr(1); // Menghapus karakter koma di awal
        }
        
        jumlah_buku++;
    }
    dataRead.close();

    if (jumlah_buku == 0) {
        eror("Buku TIdak Ada Yang Tersedia");
        system("pause");
        return;
    }

    // Mengurutkan buku berdasarkan tahun terbit secara ascending menggunakan bubble sort
    bubbleSortTahun(daftarBuku, jumlah_buku);

    // Menampilkan daftar buku yang sudah diurutkan berdasarkan tahun
    cout << YELLOW<<"                               Daftar Buku yang Tersedia                                "<<RESET << endl;
    cout << "+--------------------------------------------------------------------------------------------+" << endl;
    cout << "| No |                    Judul                 |      Penulis     | Tahun |      Genre      |" << endl;
    cout << "+--------------------------------------------------------------------------------------------+" << endl;

    for (int i = 0; i < jumlah_buku; ++i) {
        // Mengatur lebar setiap kolom sesuai dengan panjang maksimum dari data yang akan ditampilkan
        int max_judul = 40;   // Lebar maksimum untuk judul buku
        int max_penulis = 16; // Lebar maksimum untuk nama penulis
        int max_genre = 15;   // Lebar maksimum untuk genre buku

        // Memformat output untuk menampilkan dalam bentuk tabel
        cout << "| " << setw(2) << i + 1 << " | " << left << setw(max_judul) << daftarBuku[i].judul.substr(0, max_judul) << " | "
             << left << setw(max_penulis) << daftarBuku[i].penulis.substr(0, max_penulis) << " | "
             << setw(5) << daftarBuku[i].tahun_terbit << " | "
             << left << setw(max_genre) << daftarBuku[i].genre.substr(0, max_genre) << " |" << endl;
    }
    cout << "+--------------------------------------------------------------------------------------------+" << endl;
}

void lihat_penulis() {
    system("cls");

    string line;
    
    string penulis_buku[MAX_BUKU];
    int nomor = 0;

    // Simpan semua penulis buku dalam array
    ifstream dataRead("Databuku.csv");
    if (!dataRead) {
        eror("Tidak Dapat Membuka File");
        system("pause");
        return;
    }

    while (getline(dataRead, line) && nomor < MAX_BUKU) {
        stringstream ss(line);
        string judul, penulis, tahun_terbit, genre;
        getline(ss, judul, ',');
        getline(ss, penulis, ',');
        getline(ss, tahun_terbit, ',');
        getline(ss, genre);

        // Memasukkan penulis buku ke dalam array
        penulis_buku[nomor] = penulis;
        nomor++;
    }
    dataRead.close();

    if (nomor == 0) {
        eror("Buku TIdak Ada Yang Tersedia");
        system("pause");
        return;
    }

    // Mengurutkan penulis buku secara ascending menggunakan bubble sort
    bubbleSort(penulis_buku, nomor);

    // Menampilkan daftar buku yang sudah diurutkan berdasarkan penulis
    cout <<YELLOW<< "                               Daftar Buku yang Tersedia                                "<<RESET << endl;
    cout << "+--------------------------------------------------------------------------------------------+" << endl;
    cout << "| No |                    Judul                 |      Penulis     | Tahun |      Genre      |" << endl;
    cout << "+--------------------------------------------------------------------------------------------+" << endl;

    for (int i = 0; i < nomor; ++i) {
        // Cari data buku berdasarkan penulis yang sudah diurutkan
        ifstream dataRead("Databuku.csv");
        while (getline(dataRead, line)) {
            stringstream ss(line);
            string judul, penulis, tahun_terbit, genre;
            getline(ss, judul, ',');
            getline(ss, penulis, ',');
            getline(ss, tahun_terbit, ',');
            getline(ss, genre);

            // Jika penulis pada data sama dengan penulis pada array penulis_buku, cetak informasi buku
            if (penulis == penulis_buku[i]) {
                // Mengatur lebar setiap kolom sesuai dengan panjang maksimum dari data yang akan ditampilkan
                int max_judul = 40;   // Lebar maksimum untuk judul buku
                int max_penulis = 16; // Lebar maksimum untuk nama penulis
                int max_genre = 15;   // Lebar maksimum untuk genre buku

                // Memformat output untuk menampilkan dalam bentuk tabel
                cout << "| " << setw(2) << i + 1 << " | " << left << setw(max_judul) << judul.substr(0, max_judul) << " | "
                     << left << setw(max_penulis) << penulis.substr(0, max_penulis) << " | "
                     << setw(5) << tahun_terbit << " | "
                     << left << setw(max_genre) << genre.substr(0, max_genre) << " |" << endl;
                break;
            }
        }
        dataRead.close();
    }
    cout << "+--------------------------------------------------------------------------------------------+" << endl;

}

void lihat_judul() {
    system("cls");

    string line;
   
    string judul_buku[MAX_BUKU];
    int nomor = 0;

    // Simpan semua judul buku dalam array
    ifstream dataRead("Databuku.csv");
    if (!dataRead) {
        eror("Tidak Dapat Membuka File");
        return;
    }

    while (getline(dataRead, line)) {
        stringstream ss(line);
        string judul, penulis, tahun_terbit, genre;
        getline(ss, judul, ',');
        judul_buku[nomor] = judul;
        nomor++;
    }
    dataRead.close();

    if (nomor == 0) {
        eror("Buku TIdak Ada Yang Tersedia");
        return;
    }

    // Mengurutkan judul buku secara ascending
    bubbleSort(judul_buku, nomor);

    // Menampilkan daftar buku yang sudah diurutkan berdasarkan judul
    cout << YELLOW<<"                               Daftar Buku yang Tersedia                                      "<<RESET << endl;
    cout << "+--------------------------------------------------------------------------------------------+" << endl;
    cout << "| No |                    Judul                 |      Penulis     | Tahun |      Genre      |" << endl;
    cout << "+--------------------------------------------------------------------------------------------+" << endl;

    for (int i = 0; i < nomor; ++i) {
        // Cari data buku berdasarkan judul yang sudah diurutkan
        ifstream dataRead("Databuku.csv");
        while (getline(dataRead, line)) {
            stringstream ss(line);
            string judul, penulis, tahun_terbit, genre;
            getline(ss, judul, ',');
            getline(ss, penulis, ',');
            getline(ss, tahun_terbit, ',');
            getline(ss, genre);

            // Jika judul pada data sama dengan judul pada array judul_buku, cetak informasi buku
            if (judul == judul_buku[i]) {
                // Mengatur lebar setiap kolom sesuai dengan panjang maksimum dari data yang akan ditampilkan
                int max_judul = 40;   // Lebar maksimum untuk judul buku
                int max_penulis = 16; // Lebar maksimum untuk nama penulis
                int max_genre = 15;   // Lebar maksimum untuk genre buku

                // Memformat output untuk menampilkan dalam bentuk tabel
                cout << "| " << setw(2) << i + 1 << " | " << left << setw(max_judul) << judul.substr(0, max_judul) << " | "
                     << left << setw(max_penulis) << penulis.substr(0, max_penulis) << " | "
                     << setw(5) << tahun_terbit << " | "
                     << left << setw(max_genre) << genre.substr(0, max_genre) << " |" << endl;
                break;
            }
        }
        dataRead.close();
    }
    cout << "+--------------------------------------------------------------------------------------------+" << endl;

   
}

void hapus() {
    lihat_buku_csv();
    int total = panjangdata();

    if (total == 0) {
        system("cls");
        eror("Buku TIdak Ada Yang Tersedia");
        system("pause");
        menuadmin(); // Kembali ke menu admin
        return;
    }
    int index;
    cout << "Nomor Buku Yang Di Hapus : "; 
    cin >> index;
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (index != 0 && index <= total) {
        int i = 1;
        string judul, penulis, tahun, genre, buku;
        string temp;
        ifstream Data("Databuku.csv", ios::in); // Membuka file untuk dibaca
        while (getline(Data, buku)) {
            if (i != index) {
                stringstream line(buku);
                getline(line, judul, ',');
                getline(line, penulis, ',');
                getline(line, tahun, ',');
                getline(line, genre, '\n');
                temp += judul + "," + penulis + "," + tahun + "," + genre + "\n";
            }
            i++;
        }
        Data.close();
        ofstream DataOut("Databuku.csv", ios::out | ios::trunc); // Membuka file untuk ditulis ulang
        DataOut << temp;
        DataOut.close();
        string pesan = "Buku Berhasil Dihapus";
        suscess(&pesan);
    } else {
        eror("Nomor Buku Tidak Ditemukan");
    }

    system("pause");
    menuadmin(); 
}

void lihat_anggota() {
    system("cls");
    cout << YELLOW << "+-----------------------------------------------------------+" << endl;
    cout << "|                      DAFTAR ANGGOTA                       |" << endl;
    cout << "+-----------------------------------------------------------+" << RESET << endl;

    ifstream fileRead("Data_Anggota.csv");
    if (!fileRead.is_open()) {
        eror("Gagal Membuka File");
        return;
    }

    string line;
    int nomor = 1;
    cout << GREEN << "-------------------------------------------------------------" << RESET << endl;
    cout << left << setw(5) << "NO" << setw(20) << "USERNAME" << endl;
    cout << GREEN << "-------------------------------------------------------------" << RESET << endl;

    while (getline(fileRead, line)) {
        stringstream ss(line);
        string username, password;
        getline(ss, username, ',');
        getline(ss, password);

        cout << left << setw(5) << nomor << setw(20) << username << endl;
        nomor++;
    }
    cout << GREEN << "--------------------------------------------------------------" << RESET << endl;
    fileRead.close();
    system("pause");
    menuadmin();
}

void lihat_tamu(){
    system("cls");
    cout <<YELLOW<< "+-----------------------------------------------------------+" << endl;
    cout << "|                       DAFTAR TAMU                         |" << endl;
    cout << "+-----------------------------------------------------------+"<<RESET << endl;

    ifstream fileRead("Data_Pengunjung_Tamu.csv");
    if (!fileRead.is_open()) {
        cout << "Gagal membuka file Data_Pengunjung_Tamu.csv.\n";
        return;
    }

    string line;
    int nomor = 1;
    cout << GREEN << "-------------------------------------------------------------" << RESET << endl;
    cout << left << setw(5) << "NO" << setw(20) << "USERNAME" << endl;
    cout << GREEN << "-------------------------------------------------------------" << RESET << endl;

    while (getline(fileRead, line)) {
        stringstream ss(line);
        string username, password;
        getline(ss, username, ',');
        getline(ss, password);

        cout << left << setw(5) << nomor << setw(20) << username<< endl;
        nomor++;
    }
    cout << GREEN << "--------------------------------------------------------------" << RESET << endl;
    fileRead.close();
    system("pause");
    menuadmin();
}

void tampilan_menu(string header, string desc_opt[], int num_opt) {
    bool aktif = true;
    while (aktif) {
        system("cls");
        cout << YELLOW << "                    " << header << RESET << endl;
        cout << GREEN << "+----------------------------------------------------------+" << RESET << endl;
        for (int i = 0; i < num_opt; i++) {
            if (i == current_selection) {
                cout << GREEN << "| > " << CYAN << left << setw(55) << desc_opt[i] << GREEN << "|" << RESET << endl;
            } else {
                cout << GREEN << "| " << RESET  << left << setw(57) << desc_opt[i] << GREEN << "|" << RESET << endl;
            }
        }
        cout << GREEN << "+----------------------------------------------------------+" << RESET << endl;

        switch (_getch()) {
        case 72: // arrow up
            current_selection = (current_selection == 0 ? num_opt - 1 : current_selection - 1);
            break;
        case 80: // arrow down
            current_selection = (current_selection == num_opt - 1 ? 0 : current_selection + 1);
            break;
        case 13: // enter
            aktif = false;
            break;
        }
    }
}

void menu() {
    int opsi = 3;
    string header = "MENU UTAMA";
    string desc_menu[3] = { "Login Admin", "Login Pengunjung", "Keluar" };
    tampilan_menu(header, desc_menu, opsi);
    if (current_selection == 0) {
        login_admin();
    } else if (current_selection == 1) {
        login_pengunjung();
    } else if (current_selection == 2) {
        system("cls");
        kelompok();
        exit(0);
    }
}

int main() {
    menu();
    return 0;
}