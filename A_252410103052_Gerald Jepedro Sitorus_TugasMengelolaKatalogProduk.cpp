/*
NAMA              : GERALD JEPEDRO SITORUS
PROGRAM STUDI     : INFORMATIKA
MATA KULIAH       : PRAKTIKUM BAHASA PEMROGRAMAN
KELAS             : A
KETERANGAN        : OLEH-OLEH TERAKHIR
SOAL NO.          : 4 (EMPAT)
*/


#include <iostream> // merupakan library cpp untuk menggunakan fungsi cout dan cin.
#include <fstream> // untuk ifstream dan ofstream yang gunanya membaca data dari file dan menulisnya.
#include <vector> // untuk menyediakan array yang ukurannya bisa berubah saat prograamnya berjalan.
#include <string> // untuk menggunakan tipe data string.
#include <sstream> // untuk memecah-mecah data string.
#include <iomanip> // untuk memformat output cout biar rapi.
#include <chrono> // tambahan aja ya mas/mbak. Biar programnya gak terlalu kaku.
#include <thread> // jadi library yang dua ini gunanya untuk animasi aja. Tidak akan saya jelaskan ya mas/mbak karena cuma topping.

using namespace std; // Kalau ini biar program gak cape ngetik standard atau std.

/*
Selanjutnya saya buat variabel 'konstan' yang artinya nilai dari si NAMA_FILE tidak bisa diubah, saya input .csv, maka akan-
seterusnya .csv. Bisa diubah, tapi hanya di baris kode ini saja.
Mengapa saya deklarasikan fungsinya sebagai fungsi global? Biar fungsinya bisa diakses oleh fungsi lainnya di bawah nanti.
Dari sumber YouTube yang saya tonton, variabel const lebih baik ditulis huruf besar biar mudah dikenali.
*/

const string NAMA_FILE = "katalog_produk.csv";

/*
Selanjutnya, saya buat tipe data buatan dengan struct biar kedepannya tidak ribet.
Tentunya saya deklarasikan global biar bisa dipanggil di fungsi lain.
Sama seperti di pertemuan praktikum ke-2 yang membahas tentang struct, struct ini sangat berguna supaya programmer itu-
lebih enak ngodingnya.
*/

struct Produk {
    string sku; // klarif, sku ini adalah Stock Keeping Unit, sebagai ID unik produk
    string nama;
    string kategori;
    int harga;
};

/*
Selanjutnya di bagian paling penting yang bisa kita anggap seperti database utama dari memori.
Seperti yang saya jelaskan di awal, library vector fungsinya untuk array yang dinamis.
Karena program ini nantinya akan bisa ditambah dan dihapus produknya, maka ini perlu.
Dengan fungsi ini, maka program akan berjalan dengan baik.
Saya deklarasikan global agar semua fungsi itu bisa saling solid seperti Fasilkom angkatan 25.
*/

vector<Produk> katalog;

/**
Selanjutnya, saya buat fungsi void untuk memuat data dari file csv ke vector katalog yang diatas saat program dimuali pertama kali.
 */

void muatData() {
    katalog.clear(); // mengosongkan vector katalog. Gunanya mencegah duplikat.
    ifstream file(NAMA_FILE); // membuat objek ifstream yang bernama file.
    string baris, kata;

    if (file.is_open()) {

        while (getline(file, baris)) {
            stringstream ss(baris); // Seperti di bagian header, ini gunanya untuk memecah nila string baris di atas.
            Produk p;

            // Membaca setiap atribut dipisahkan koma
            getline(ss, p.sku, ',');
            getline(ss, p.nama, ',');
            getline(ss, p.kategori, ',');
            getline(ss, kata, ',');
            p.harga = stoi(kata); // Ubah string harga menjadi integer

            katalog.push_back(p);
        }
        file.close(); // Tutup!!!!!!
    } else {
        // Jika file belum ada, tidak masalah. 
        // File akan dibuat saat 'simpanData' dipanggil.
        cout << "Info: File 'katalog_produk.csv' tidak ditemukan. File baru akan dibuat saat menyimpan.\n\n";
    }
}

/*
Selanjutnya, saya buat fungsi void lagi yang gunanya nanti untuk menyalin data dari si vector katalog kembali ke csv.
Kebalikan dari yang di atas.
*/

void simpanData() {
    ofstream file(NAMA_FILE);

    if (file.is_open()) {
        for (const auto& p : katalog) {
            file << p.sku << ","
                 << p.nama << ","
                 << p.kategori << ","
                 << p.harga << "\n";
        }
        file.close();
    } else {
        cout << "Error: Tidak bisa membuka file untuk menyimpan data!\n";
    }
}

/*
Sesuai nama variabelnya, ini adalah fungsi void  yang nanti menampilkan data di vector katalog ke layar dengan rapi.
*/

void tampilkanProduk() {
    if (katalog.empty()) {
        cout << "Katalog produk masih kosong.\n";
        return;
    }

/*
Di bagian bawah saya meminta bantuan ChatGPT tercinta untuk merapikan tampilan katalognya.
Karena saya tidak tahu bagaimana penggunaan library iomanip, jadi saya jujur saja, Mas/Mbak😊👌.
*/

    cout << "==================================================================\n";
    cout << "                DAFTAR KATALOG PRODUK\n";
    cout << "==================================================================\n";
    // setw = set width (mengatur lebar kolom).
    cout << left << setw(10) << "SKU"
         << left << setw(25) << "Nama Produk"
         << left << setw(20) << "Kategori"
         << right << setw(10) << "Harga" << endl;
    cout << "------------------------------------------------------------------\n";

    for (const auto& p : katalog) {
        cout << left << setw(10) << p.sku
             << left << setw(25) << p.nama
             << left << setw(20) << p.kategori
             << right << setw(10) << p.harga << endl;
    }
    cout << "==================================================================\n";
}

/*
Selanjutnya, saya buat fungsi untuk menambahkan produk nanti ke katalog.
Intinya, nanti program meminta kita untuk menambahkan produk, yang nanti produknya tersimpan di csv.
*/

void tambahProduk() {
    Produk p;
    cout << "Tambah Produk Baru\n";
    cout << "Masukkan SKU: ";
    cin.ignore(); // cin.ignore ini gunanya untuk mengabaikan enter sebelumnya. ini berguna saat kita menginput menu nanti.
    getline(cin, p.sku);
    cout << "Masukkan Nama Produk: ";
    getline(cin, p.nama);
    cout << "Masukkan Kategori: ";
    getline(cin, p.kategori);
    cout << "Masukkan Harga: ";
    cin >> p.harga;

    katalog.push_back(p); // tambah ke vector.
    simpanData(); // simpan perubahan ke file.
    cout << "Produk baru berhasil ditambahkan!\n";
}

/*
Selanjutnya saya buat fungsi untuk mencari index produk berdasarkan SKU-nya.
Ini adalah fungsi bantuan untuk 'ubah' dan 'hapus'
*/

int cariProduk(const string& sku) {
    for (int i = 0; i < katalog.size(); ++i) {
        if (katalog[i].sku == sku) {
            return i; // mengembalikan index jika ditemukan.
        }
    }
    return -1; // mengembalikan -1 jika tidak ditemukan. Baru saja dipelajari ini minggu lalu, hehe.
}

/*
Selanjutnya saya buat fungsi untuk mengubah data produk yang sudah ada atau yang sudah dimasukkan.
Sesuai dengan Menu: "Ubah data produk".
*/

void ubahProduk() {
    string sku;
    cout << "Ubah Data Produk\n"; // ini cari produk yang mau diubah dengan SKU.
    cout << "Masukkan SKU produk yang ingin diubah: ";
    cin.ignore();
    getline(cin, sku);

    int index = cariProduk(sku); // laporan posisinya berdasarkan index dan -1.

    if (index != -1) { // ini jika dia laporan bukan -1, maka produk ada dan ditemukan.
        cout << "Produk ditemukan. Masukkan data baru:\n"; // bagian ini dan seterusnya untuk mengubah produk lama.
        cout << "Nama Produk saat ini: " << katalog[index].nama << "\n";
        cout << "Nama Produk baru (kosongkan jika tidak mau diubah ya): ";
        string namaBaru;
        getline(cin, namaBaru);
        if (!namaBaru.empty()) {
            katalog[index].nama = namaBaru;
        }

        cout << "Kategori saat ini: " << katalog[index].kategori << "\n";
        cout << "Kategori baru (kosongkan jika tidak mau diubah ya): ";
        string kategoriBaru;
        getline(cin, kategoriBaru);
        if (!kategoriBaru.empty()) {
            katalog[index].kategori = kategoriBaru;
        }

        cout << "Harga saat ini: " << katalog[index].harga << "\n";
        cout << "Harga baru (masukkan 0 jika tidak diubah): "; // kenapa 0? karena integer hahahaha (stress dikit).
        int hargaBaru;
        cin >> hargaBaru;
        if (hargaBaru != 0) {
            katalog[index].harga = hargaBaru;
        }

        simpanData(); // menyimpan perubahan ke csv.
        cout << "Data produk berhasil diubah!\n";
    } else {
        cout << "Produk dengan SKU '" << sku << "' tidak ditemukan.\n"; // no wayyyyy.
    }
}

/*
Yesss. Tinggal terakhir. Saya buat fungsi untuk menghapus produk dari katalog.
Sesuai dengan Menu: "Hapus produk dari katalog" yang sesuai dengan ketentuan programnya.
*/

void hapusProduk() {
    string sku;
    cout << "Hapus Produk\n";
    cout << "Masukkan SKU produk yang ingin dihapus: ";
    cin.ignore();
    getline(cin, sku);

    int index = cariProduk(sku);

    if (index != -1) {
        // saya buat konfirmasi sebelum menghapus biar keren dikit hehe.
        cout << "Anda yakin ingin menghapus '" << katalog[index].nama << "' (SKU: " << sku << ")? (y/n): ";
        char konfirmasi;
        cin >> konfirmasi;

        if (konfirmasi == 'y' || konfirmasi == 'Y') { // jaga2 buat yang keyboardnya auto capital.
            katalog.erase(katalog.begin() + index); // hapus dari vector.
            simpanData(); // simpan perubahan ke file.
            cout << "Produk berhasil dihapus.\n";
        } else {
            cout << "Penghapusan dibatalkan.\n";
        }
    } else {
        cout << "Produk dengan SKU '" << sku << "' tidak ditemukan.\n";
    }
}

/*
Selanjutnya, mas Fahmi eh maksudnya Pemeran Utama untuk tampil.
Ya, tentunya di main lah yang pertama tampil untuk pengguna menggunakan programnya.
Nanti muncul beberapa menu dan bisa dilihat langsung di bawah.
*/

int main() {
    muatData();

    int pilihan = 0;
    while (pilihan != 5) {
        cout << "PROGRAM MANAJEMEN KATALOG\n";
        cout << "1. Tampilkan Semua Produk\n";
        cout << "2. Tambah Produk Baru\n";
        cout << "3. Ubah Data Produk\n";
        cout << "4. Hapus Produk\n";
        cout << "5. Keluar\n";
        cout << "------------------------------------\n";
        cout << "Masukkan pilihan: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                tampilkanProduk();
                break;
            case 2:
                tambahProduk();
                break;
            case 3:
                ubahProduk();
                break;
            case 4:
                hapusProduk();
                break;
            case 5: // Nah, di case 5 saya pakai library chrono dan thread tadi. Tidak perlu dijelaskan ya karena cuma topping.
                cout << "Menutup program";
                cout.flush();

                std::this_thread::sleep_for(std::chrono::milliseconds(500));

                cout << ".";
                cout.flush();
                std::this_thread::sleep_for(std::chrono::milliseconds(500));

                cout << ".";
                cout.flush();
                std::this_thread::sleep_for(std::chrono::milliseconds(500));

                cout << "." << endl;
                
                std::this_thread::sleep_for(std::chrono::milliseconds(300)); 

                cout << "\nAnda telah berhasil keluar. Semoga hari Anda menyenangkan\n";
                break;
            default:
                cout << "Pilihan tidak valid. Silakan coba lagi.\n";
                // mengatasi input non-angka yang bisa menyebabkan loop tak terbatas.
                if (cin.fail()) {
                    cin.clear(); // hapus status error.
                    cin.ignore(10000, '\n'); // Buang input buruk
                }
                break;
        }
    }

    return 0;
}

/*
PENJELESAN FINAL

Baris-baris kode di atas adalah program yang setelah dijalankan akan menghasilkan program untuk mengelola data produk yang-
berupa katalog.
Program ini sangat berguna bagi seorang pekerja di bidang usaha produk-produk yang akan membantunya dalam berbagai hal.
Seperti,
  1. Untuk mengetahui daftar produk
  2. Mengetahui harga tiap produk
  3. Mengetahui jenis tiap produk
  4. Membantu dalam perubahan daftar produk
  5. Dan masih banyak lainnya.

Memang program ini adalah program yang sederhana. Tetapi, dengan program ini kita seorang programmer bisa belajar banyak hal-
bahwa semuanya itu butuh proses. Manusia tidak akan pernah bisa mencapai tujuannya tanpa mengandalkan bantuan.
Dengan program ini, memudahkan manusia untuk menjadi seorang pekerja di bidang usaha produk, tanpa perlu lelah-
mencatat dengan tangan di buku tulis daftar tiap produk.

Ke kota Bandung membeli pepaya
Bersama mbak Kamel dan mas Fahmi
Sekian saja dari saya
Kurang lebihnya, jangan lupa kabari
*/