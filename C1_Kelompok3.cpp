#include <iostream>  //header file untuk menginput dan untun output seperti cout dan cin
#include <string>    // agar fungsi string bisa digunakan
#include <ctime>     //mendeklarasikan waktu
#include <iomanip>   // Diperlukan untuk mengatur format output
#include <queue>     // agar fungsi waktu dantanggal bisa digunakan dalam program
#include <limits>    // untuk mengatur limit suatu tipe data
#include <thread>    // File header thread berisi deklarasi untuk kelas thread, yang dapat digunakan untuk membuat dan mengelola thread
#include <chrono>    // deklarasi untuk kelas chrono, yang dapat digunakan untuk mengukur dan mengelola waktu
using namespace std; // untuk  menyimpan banyak elemen-elemen dasar, seperti cin, cout, string, vector dan lainnya

string getCurrentTime() // membuat fungsi getCurrentTime() adalah fungsi untuk mendapatkan waktu saat ini dalam format YYYY-MM-DD HH:MM:SS
{
    time_t now = time(0);                                // Mendapatkan waktu saat ini dalam format time_t menggunakan fungsi time(0)
    struct tm tstruct;                                   // Mengkonversi waktu dalam format time_t ke struktur waktu tm menggunakan fungsi localtime()
    char buf[80];                                        // buf berisi 80 karakter
    tstruct = *localtime(&now);                          // Memformat waktu dalam struktur tm ke string menggunakan fungsi strftime()
    strftime(buf, sizeof(buf), "%Y-%m-%d %X", &tstruct); // Mengembalikan string yang berisi waktu saat ini dalam format YYYY-MM-DD HH:MM:SS
    return buf;
}

struct RegistrationHistory // membuat fungsi RegistrationHistory yang berisi data yang menyimpan informasi tentang registrasi pengguna
{
    string username;         // Nama pengguna yang melakukan registrasi
    string registrationTime; // Waktu registrasi pengguna
};

queue<RegistrationHistory> registrationHistoryQueue; // Inisialisasi queue history registrasi

// Definisi struct untuk merepresentasikan barang dalam keranjang
struct Barang
{
    int kodeProduk;
    string nama;
    int jumlah;
    double harga;
};

// Deklarasi struktur untuk barang dalam keranjang
struct KeranjangNode
{
    Barang barang;       // Barang sebagai data yang diambil dari struct Barang dang barang sebagai objek baru yang dibuat untuk KeranjangNode
    KeranjangNode *next; // pointer yang menunjukkkan ke node berikutnya agar terhubung secara berurutan, membentuk sebuah linked list satu sama lain
    KeranjangNode *prev; // pointer yang merujuk ke node sebelumnya
};

// mendeklarasikan pointer dari struct KeranjangNode agar awal dari sebuah liked list itu kosong
KeranjangNode *keranjangHead = nullptr;
KeranjangNode *keranjangTail = nullptr;

// Struktur untuk menyimpan data produk kosmetik
struct ProdukKosmetik
{
    int kode;
    string nama;
    string merek;
    int harga;
    int stok;
};

// mendeklarasikan struct node dari data struct ProdukKosmetik
struct Node
{
    ProdukKosmetik data; // Data yang akan disimpan dalam node (dalam konteks ini, data produk kosmetik)
    Node *next;          // Pointer ke node berikutnya dalam linked list
    Node *prev;          // Pointer ke node sebelumnya dalam linked list (diperlukan dalam double linked list)
};

// membuat Fungsi untuk mengurangi stok barang berdasarkan kode produk
void kurangiStok(Node *head, int kodeProduk, int jumlah) // paramenter head adalah pointer ke node pertama di linked list , kodeProduk adalahkode produk yang akan dikurangi stoknya dan jumlah adalah jumlah stok yang akan dikurangi
{
    Node *current = head;      // mendeklarasi variabel current. Variabel ini digunakan untuk menyimpan pointer ke node saat ini
    while (current != nullptr) // melakukan Iterasi perulangan while-loop ini untuk menjalankan pointer current yang menunjuk ke node yang valid
    {
        if (current->data.kode == kodeProduk) // Kondisi if-else ini digunakan untuk memeriksa apakah node saat ini memiliki kode produk yang sesuai.
        {
            // Temukan barang berdasarkan kode
            if (current->data.stok >= jumlah) // untuk memeriksa apakah stok barang mencukupi untuk transaksi
            {
                // Jika stok mencukupi untuk transaksi
                current->data.stok -= jumlah;
            }
            else
            {
                cout << "Stok tidak mencukupi untuk transaksi." << endl;
            }
            return; // Keluar dari loop setelah penanganan produk
        }
        current = current->next; // membuat pointer yang menunjuk ke node berikutnya dan mengambil alamat dari node berikutnya yang ditunjuk oleh pointer current dan menyimpannya ke dalam variabel current
    }
    cout << "Produk dengan kode " << kodeProduk << " tidak ditemukan." << endl;
}

// Fungsi untuk menampilkan data produk
void tampilkanProduk(Node *head) // parameter head digunakan sebagai pointer ke node pertama di linked list
{
    cout << "Daftar Produk Kosmetik:" << endl;
    Node *current = head; // mendeklarasikan bahwa variabel current. Variabel ini digunakan untuk menyimpan pointer ke node saat ini
    while (current != nullptr)
    {
        ProdukKosmetik produk = current->data; // menunjukkan bahwa variabel current digunakan untuk menyimpan pointer ke node saat ini
        // menampikan informasi produk
        cout << "-----------------------------" << endl;
        cout << "Kode  : " << produk.kode << endl;
        cout << "Nama  : " << produk.nama << endl;
        cout << "Merek : " << produk.merek << endl;
        cout << "Harga : Rp" << produk.harga << endl;
        cout << "stok  : " << produk.stok << " unit" << endl;
        cout << "-----------------------------" << endl;
        current = current->next; // memindahkan pointer current ke node berikutnya
    }
}

// Fungsi untuk menampilkan data produk secara Forward (Data dari head ke Tail)
void tampilkanProdukForward(Node *head) // membuat fungsi tampilkanProdukForward dengan parameter head sebagai pointer ke node pertama di linked list
{
    cout << "Daftar Produk Kosmetik (Forward):" << endl; // menampilkan judul daftar produk kosmetik
    Node *current = head;                                // mendeklarasikan bahwa variabel current. Variabel ini digunakan untuk menyimpan pointer ke node saat ini
    while (current != nullptr)                           // melakukan perulangan yang akan berjalan selama pointer current masih menunjuk ke node yang valid.
    {
        ProdukKosmetik produk = current->data; // ProdukKosmetik mengambil data dari node saat ini dan menyimpannya ke dalam variabel produk
        cout << "-----------------------------" << endl;
        cout << "Kode  : " << produk.kode << endl;
        cout << "Nama  : " << produk.nama << endl;
        cout << "Merek : " << produk.merek << endl;
        cout << "Harga : Rp" << produk.harga << endl;
        cout << "Stok  : " << produk.stok << " unit" << endl;
        cout << "-----------------------------" << endl;
        current = current->next; // Bergeser ke node sebelumnya
    }
}

// Fungsi untuk menampilkan data produk secara Backward (Data dari Tail ke Head)
void tampilkanProdukBackward(Node *tail) // fungsi tampilkanProdukBackward(). Fungsi ini memiliki parameter tail yaitu pointer ke node terakhir di linked list
{

    cout << "Daftar Produk Kosmetik (Backward):" << endl;
    Node *current = tail; // mendeklarasi variabel current. Variabel ini digunakan untuk menyimpan pointer ke node saat ini.

    while (current != nullptr) // membuat perulangan agar perulangan ini berjalan selama pointer current masih menunjukkan ke node yang valid
    {
        ProdukKosmetik produk = current->data; // produkkosmetik mengambil data dari node saat ini dan menyimpannya ke dalam variabel produk.
        cout << "------------------------------" << endl;
        cout << "Kode   : " << produk.kode << endl;
        cout << "Nama   : " << produk.nama << endl;
        cout << "Merek  : " << produk.merek << endl;
        cout << "Harga  : Rp" << produk.harga << endl;
        cout << "Stok   : " << produk.stok << " unit" << endl;
        cout << "------------------------------" << endl;

        current = current->prev; // Bergeser ke node sebelumnya
    }
}

// Fungsi untuk menambahkan data produk ke dalam linked list sesuai dengan posisi yang dipilih
void tambahProduk(Node *&head, Node *&tail, int &jumlahProduk) // membuat fungsi tambahProduk() untuk menambahkan produk baru ke dalam daftar produk , Mendeklarasikan variabel newNode dari tipe Node untuk menyimpan data produk baru, Mengisi variabel newNode dengan data produk baru yang dimasukkan oleh pengguna
{

    if (jumlahProduk >= 100) // Memeriksa apakah kode produk sudah ada dalam daftar
    {
        cout << "Maaf, jumlah produk sudah mencapai batas maksimal." << endl; // Jika sudah, maka fungsi akan menampilkan pesan kesalahan dan menghapus node yang sudah dibuat.
        return;
    }

    Node *newNode = new Node; // Menampilkan menu pilihan untuk menentukan posisi produk baru
    ProdukKosmetik newProduk; // Menambahkan node baru ke dalam daftar sesuai dengan pilihan posisi.

    cout << "Masukkan Kode Produk: ";
    cin >> newProduk.kode; // membaca input dari pengguna dan menyimpannya ke dalam variabel newProduk.kode

    // Periksa apakah kode produk sudah ada dalam daftar
    Node *current = head;      // Inisialisasi pointer ke node saat ini dengan node pertama dalam daftar
    while (current != nullptr) // Lakukan perulangan melalui daftar untuk memeriksa keberadaan kode produk yang sama
    {
        if (current->data.kode == newProduk.kode) //// Periksa apakah kode produk sudah ada
        {
            cout << "Kode produk sudah ada. Silakan masukkan kode produk yang berbeda." << endl; //// Jika kode produk sudah ada, tampilkan pesan dan batalkan penambahan node baru
            delete newNode;                                                                      // Hapus node yang sudah dibuat mencegah kebocoran memori
            return;                                                                              // Keluar dari fungsi karena penambahan produk dibatalkan
        }
        current = current->next; //// Pindah ke node berikutnya dalam daftar
    }
    cin.ignore(); // Bersihkan buffer input sebelum membaca string
    // Meminta input dari pengguna untuk atribut lain dari produk baru
    cout << "Masukkan Nama Produk: ";
    getline(cin, newProduk.nama);
    cout << "Masukkan Merek Produk: ";
    getline(cin, newProduk.merek);
    cout << "Masukkan Harga Produk (Rp): ";
    cin >> newProduk.harga;
    cout << "Masukkan Stok Produk: ";
    cin >> newProduk.stok;

    newNode->data = newProduk; // Attribut dari node baru diisi dengan data produk baru

    int pilihanPosisi; // Input untuk pilihan posisi penambahan produk
    cout << "==============================\n";
    cout << "| Tambah Produk - Pilih Opsi |\n";
    cout << "==============================\n";
    cout << "|1. Tambah ke Awal           |\n";
    cout << "|2. Tambah ke Akhir          |\n";
    cout << "|3. Tambah di Tengah         |\n";
    cout << "|4. Kembali                  |\n";
    cout << "==============================\n";
    cout << "Pilihan Anda: ";

    // Memastikan input adalah angka
    while (!(cin >> pilihanPosisi) || pilihanPosisi < 1 || pilihanPosisi > 4)
    {
        cin.clear(); // Menghapus error flag

        // Membersihkan buffer input untuk menghindari masukan yang salah
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        // Menampilkan pesan kesalahan jika input tidak valid
        cout << "Masukkan tidak valid. Silakan masukkan angka antara 1 dan 4: ";
    }

    // Switch untuk menentukan posisi penambahan produk
    switch (pilihanPosisi)
    {
    case 1:
        // Tambah ke awal
        newNode->next = head;  // Menyambungkan node baru dengan node yang sebelumnya adalah head (node pertama saat ini)
        newNode->prev = nullptr;  //Mengatur prev (node sebelumnya) dari node baru menjadi nullptr karena node baru akan menjadi node pertama dan tidak memiliki node sebelumnya.
        if (head == nullptr)  //Memeriksa apakah linked list masih kosong
        {
            tail = newNode; //(ekor) diatur menjadi node baru karena ini adalah satu-satunya node dalam linked list
        }
        else  //Jika linked list tidak kosong, maka head->prev (prev dari node yang sebelumnya adalah head) diatur menjadi node baru
        {
            head->prev = newNode;
        }
        head = newNode;  //penyesuaian prev, head diupdate menjadi node baru karena node baru sekarang menjadi node pertama dalam linked list
        break;
    case 2:
        // Tambah ke akhir
        newNode->next = nullptr;  //Menyatakan bahwa node baru akan menjadi node terakhir, sehingga next dari node baru diatur menjadi nullptr
        newNode->prev = tail;  //Mengatur prev (node sebelumnya) dari node baru menjadi tail (ekor saat ini)
        if (tail == nullptr) //Memeriksa apakah linked list masih kosong. Jika ya, maka head (kepala) diatur menjadi node baru karena ini adalah satu-satunya node dalam linked list
        {
            head = newNode;
        }
        else  //Jika linked list tidak kosong, maka tail->next (next dari node yang sebelumnya adalah tail) diatur menjadi node baru
        {
            tail->next = newNode;
        }
        tail = newNode;  // penyesuaian next, tail diupdate menjadi node baru karena node baru sekarang menjadi node terakhir dalam linked list
        break;
    case 3:
        // Tambah di tengah
        int posisi;  // Mendeklarasikan variabel posisi untuk menyimpan posisi yang dimasukkan oleh pengguna
        cout << "Masukkan posisi (0 sampai " << jumlahProduk << "): ";  //Menampilkan pesan untuk meminta pengguna memasukkan posisi. jumlahProduk di sini adalah jumlah produk saat ini di dalam linked list
        cin >> posisi;  //Mengambil input posisi dari pengguna

        if (posisi < 0 || posisi > jumlahProduk)  //Memeriksa apakah posisi yang dimasukkan valid. Jika tidak valid, program memberikan pesan dan mengembalikan kontrol
        {
            cout << "Posisi yang dimasukkan tidak valid." << endl;
            return;
        }

        if (posisi == 0)  //Jika posisi == 0: Node baru ditambahkan di awal linked list
        {
            newNode->next = head;  //Mengatur pointer next dari node baru (newNode) untuk menunjuk ke node yang sebelumnya berada di awal linked list (head)
            newNode->prev = nullptr;  //Karena node baru ditambahkan di awal, pointer prev diatur menjadi nullptr karena tidak ada node sebelumnya
            if (head == nullptr)  //Memeriksa apakah linked list awalnya kosong
            {
                tail = newNode;  //diatur untuk menunjuk ke node baru, karena node baru akan menjadi satu-satunya node dalam linked list
            }
            else  //Jika tidak (head tidak nullptr), artinya linked list tidak kosong, maka head->prev (pointer prev dari node yang sebelumnya berada di awal linked list) diatur untuk menunjuk ke node baru (newNode)
            {
                head->prev = newNode;  //head->prev (pointer prev dari node yang sebelumnya berada di awal linked list) diatur untuk menunjuk ke node baru (newNode)
            }
            head = newNode;  //Pointer head diatur untuk menunjuk ke node baru, sehingga node baru sekarang menjadi node pertama dalam linked list
        }
        else if (posisi == jumlahProduk)  //ika posisi == jumlahProduk: Node baru ditambahkan di akhir linked list
        {
            newNode->next = nullptr;  //Mengatur pointer next dari node baru (newNode) menjadi nullptr karena node baru akan menjadi node terakhir
            newNode->prev = tail;  //Mengatur pointer prev dari node baru untuk menunjuk ke node yang sebelumnya berada di akhir linked list (tail)
            if (tail == nullptr)
            {
                head = newNode;  //linked list kosong, maka head (kepala) linked list diatur untuk menunjuk ke node baru, karena node baru akan menjadi satu-satunya node dalam linked list
            }
            else
            {
                tail->next = newNode;  //tail->next (pointer next dari node yang sebelumnya berada di akhir linked list) diatur untuk menunjuk ke node baru (newNode)
            }
            tail = newNode;  //Pointer tail diatur untuk menunjuk ke node baru, sehingga node baru sekarang menjadi node terakhir dalam linked list.
        }
        else
        {
            Node *current = head;  //Membuat pointer current dan menginisialisasinya dengan alamat node pertama (head) untuk memulai iterasi melalui linked list
            for (int i = 0; i < posisi - 1; i++)  //Melakukan iterasi melalui linked list hingga mencapai node sebelum posisi yang dimasukkan (posisi - 1), karena kita ingin menambahkan node baru setelah node tersebut
            {
                current = current->next;  //Mengatur pointer next dari node baru (newNode) untuk menunjuk ke node yang awalnya berada setelah current dalam linked list
            }
            newNode->next = current->next;
            newNode->prev = current;  //Mengatur pointer prev dari node baru untuk menunjuk ke current, karena newNode akan ditempatkan setelah current
            current->next->prev = newNode;  //Mengatur pointer prev dari node yang awalnya berada setelah current untuk menunjuk ke newNode
            current->next = newNode;  //Mengatur pointer next dari current untuk menunjuk ke newNode, sehingga newNode ditambahkan di antara current dan node yang awalnya berada setelah current
        }
        break;  //Mengakhiri switch statement karena kita sudah menangani semua kasus
    default:
        cout << "Pilihan posisi tidak valid." << endl;
        return;
    }

    jumlahProduk++;  //jumlahProduk++;: Setelah penambahan, jumlah produk ditingkatkan
    cout << "Produk berhasil ditambahkan!" << endl;
}

// Fungsi untuk menambahkan barang ke keranjang
void tambahBarangKeKeranjang(const Barang &newBarang)
{
    // Membuat node baru untuk barang dalam keranjang
    KeranjangNode *newNode = new KeranjangNode;

    // Mengisi data barang pada node baru
    newNode->barang = newBarang;

    // Mengatur pointer next ke nullptr dan pointer prev ke keranjangTail
    newNode->next = nullptr;
    newNode->prev = keranjangTail;

    // Jika keranjang kosong, atur head dan tail ke node baru
    if (keranjangTail == nullptr)
    {
        keranjangHead = newNode;
        keranjangTail = newNode;
    }
    else
    {
        // Jika keranjang tidak kosong, hubungkan node baru ke tail dan update tail
        keranjangTail->next = newNode;
        keranjangTail = newNode;
    }
}

// Fungsi untuk menampilkan isi keranjang belanja
void tampilkanKeranjangBelanja()
{
    // Pengecekan apakah keranjang belanja kosong
    if (keranjangHead == nullptr)
    {
        cout << "Keranjang belanja kosong." << endl;
    }
    else
    {
        // Menampilkan judul isi keranjang belanja
        cout << "Isi Keranjang Belanja:\n";

        // Pointer ke node pertama dalam keranjang
        KeranjangNode *current = keranjangHead;

        // Nomor urut untuk barang dalam keranjang
        int nomorBarang = 1;

        // Iterasi melalui setiap node dalam keranjang
        while (current != nullptr)
        {
            // Mendapatkan data barang dari node saat ini
            Barang barang = current->barang;

            // Menampilkan informasi barang
            cout << nomorBarang << ". " << setw(20) << left << barang.nama;
            cout << " = " << setw(5) << right << barang.jumlah;
            cout << "     Rp " << setw(10) << fixed << setprecision(2) << barang.harga << "\n";

            // Pindah ke node berikutnya dalam keranjang
            current = current->next;

            // Meningkatkan nomor barang
            nomorBarang++;
        }

        // Baris kosong setelah menampilkan seluruh isi keranjang belanja
        cout << "\n";
    }
}

double hargaTotal;  //mendeklarasikan hatga total bertipe data double
int hari_ini;  //mendeklarasikan bahwa variable hariini adalah integer
int waktu_sekarang;  //mendeklarasikan waktu_sekarang adlah integer

// Fungsi untuk menghitung total harga dari barang-barang dalam keranjang
void hitungTotalHarga(KeranjangNode *keranjangHead, double &totalHarga)
{
    totalHarga = 0.0;                       // Inisialisasi totalHarga ke 0
    KeranjangNode *current = keranjangHead; // Pointer ke elemen pertama di keranjang
    while (current != nullptr)              // Selama masih ada barang di keranjang
    {
        // Menambahkan harga barang saat ini ke totalHarga
        totalHarga += current->barang.harga * current->barang.jumlah;
        current = current->next; // Pindah ke barang berikutnya di keranjang
    }
}

// Fungsi untuk mencetak struk pembayaran
void cetakStruk(const string &namaPelanggan, KeranjangNode *keranjangHead, double totalPembayaran, const string &metodePembayaran)
{
    // Mendapatkan waktu saat ini
    time_t now = time(0);
    tm *timeInfo = localtime(&now);
    char buffer[80];
    strftime(buffer, 80, "%Y-%m-%d %H:%M:%S", timeInfo);
    string tanggalWaktu(buffer);

    // Mencetak struk pembayaran
    cout << "======================================================================\n";
    cout << "|                           STRUK PEMBAYARAN                         |\n";
    cout << "======================================================================\n";
    cout << "|                    Tanggal: " << tanggalWaktu << "                    |\n";
    cout << "======================================================================\n";

    cout << "Nama Pelanggan: " << namaPelanggan << "\n\n";

    cout << "Daftar Barang yang Dipesan:\n";
    int nomorBarang = 1;
    KeranjangNode *current = keranjangHead; // Pointer ke elemen pertama di keranjang
    while (current != nullptr)              // Selama masih ada barang di keranjang
    {
        cout << nomorBarang << ". " << setw(20) << left << current->barang.nama;
        cout << " = " << setw(5) << right << current->barang.jumlah;
        cout << "     Rp " << setw(10) << fixed << setprecision(2) << current->barang.harga << "\n";
        current = current->next; // Pindah ke barang berikutnya di keranjang
        nomorBarang++;
    }
    cout << "\n";

    cout << "======================================================================\n";
    cout << "Total Pembayaran:        Rp " << setw(10) << fixed << setprecision(2) << totalPembayaran << "\n";
    cout << "======================================================================\n";

    cout << "Metode Pembayaran: " << metodePembayaran << "\n\n";

    // Meminta konfirmasi untuk melakukan pembayaran
    cout << "Apakah Anda ingin melakukan pembayaran? (Y/N): ";
    char konfirmasi;
    cin >> konfirmasi;

    if (konfirmasi == 'Y' || konfirmasi == 'y') // Jika pengguna ingin melanjutkan pembayaran
    {
        cout << "Pembayaran berhasil dilakukan. Terima kasih atas pesanan Anda!\n";
    }
    else
    {
        cout << "Pembayaran dibatalkan. Silakan datang kembali.\n";
    }

    cout << "======================================================================\n";
}

// Fungsi untuk menghapus barang dari keranjang berdasarkan nomor barang
void hapusBarangDariKeranjang(int nomorBarang)
{
    if (nomorBarang >= 1)
    {
        KeranjangNode *nodeToDelete = keranjangHead;

        // Iterasi untuk menemukan node yang sesuai dengan nomor barang
        for (int i = 1; i < nomorBarang; i++)
        {
            if (nodeToDelete != nullptr)
            {
                nodeToDelete = nodeToDelete->next;
            }
        }

        // Jika node yang sesuai ditemukan
        if (nodeToDelete != nullptr)
        {
            // Hapus node dari linked list
            if (nodeToDelete->prev)
            {
                nodeToDelete->prev->next = nodeToDelete->next;
            }
            else
            {
                keranjangHead = nodeToDelete->next;
            }

            if (nodeToDelete->next)
            {
                nodeToDelete->next->prev = nodeToDelete->prev;
            }
            else
            {
                keranjangTail = nodeToDelete->prev;
            }

            // Hapus node yang sesuai
            delete nodeToDelete;
        }
        else
        {
            cout << "Nomor barang tidak valid." << endl;
        }
    }
}

void hapusProduk(Node *&head, Node *&tail, int &jumlahProduk, int pilihan, int kode)
{
    if (pilihan == 1)
    {
        // Hapus dari awal
        if (head == nullptr)
        {
            cout << "Daftar produk kosong." << endl;
            return;
        }

        // Simpan alamat node awal
        Node *temp = head;

        // Pindahkan head ke node berikutnya
        head = head->next;

        // Jika masih ada node setelah head, atur prev-nya menjadi nullptr
        if (head != nullptr)
        {
            head->prev = nullptr;
        }
        else
        {
            // Jika tidak ada node lagi, tail diset menjadi nullptr
            tail = nullptr;
        }

        // Hapus node awal dan kurangi jumlah produk
        delete temp;
        jumlahProduk--;

        cout << "Produk pertama berhasil dihapus." << endl;
    }
    else if (pilihan == 2)
    {
        // Hapus dari akhir
        if (head == nullptr)
        {
            cout << "Daftar produk kosong." << endl;
            return;
        }

        // Jika hanya ada satu node, hapus node tersebut
        if (head == tail)
        {
            delete head;
            head = nullptr;
            tail = nullptr;
        }
        else
        {
            // Simpan alamat node terakhir
            Node *temp = tail;

            // Pindahkan tail ke node sebelumnya
            tail = tail->prev;

            // Putuskan hubungan dengan node terakhir
            tail->next = nullptr;

            // Hapus node terakhir
            delete temp;
        }

        // Kurangi jumlah produk
        jumlahProduk--;

        cout << "Produk terakhir berhasil dihapus." << endl;
    }
    else if (pilihan == 3)
    {
        // Hapus di tengah
        if (head == nullptr)
        {
            cout << "Daftar produk kosong." << endl;
            return;
        }

        // Iterasi melalui daftar produk untuk mencari node dengan kode yang sesuai
        Node *current = head;
        while (current != nullptr)
        {
            if (current->data.kode == kode)
            {
                // Jika node yang sesuai berada di awal
                if (current == head)
                {
                    head = current->next;

                    // Jika masih ada node setelah head, atur prev-nya menjadi nullptr
                    if (head != nullptr)
                    {
                        head->prev = nullptr;
                    }
                }
                else
                {
                    // Jika node yang sesuai berada di tengah atau akhir
                    current->prev->next = current->next;

                    // Jika masih ada node setelah node yang dihapus, atur prev-nya
                    if (current->next != nullptr)
                    {
                        current->next->prev = current->prev;
                    }

                    // Jika node yang dihapus berada di akhir, atur tail ke node sebelumnya
                    if (current == tail)
                    {
                        tail = current->prev;
                    }
                }

                // Hapus node yang ditemukan dan kurangi jumlah produk
                delete current;
                jumlahProduk--;

                cout << "Produk dengan Kode " << kode << " berhasil dihapus." << endl;
                return;
            }
            // Lanjut ke node berikutnya
            current = current->next;
        }

        // Jika tidak ada node dengan kode yang sesuai
        cout << "Produk dengan Kode " << kode << " tidak ditemukan." << endl;
    }
}

// Fungsi untuk mengubah data produk berdasarkan kode
void ubahProdukDiPosisi(Node *head, int posisi) // membuat fungsi ubahProdukDiPosisi dan menambahkan dua parameter, yaitu pointer ke node pertama dari daftar produk dan posisi produk yang ingin diubah
{
    Node *current = head; // Inisialisasi pointer current ke node pertama dari daftar produk
    int currentIndex = 0; // Inisialisasi variabel currentIndex ke 0

    // mencari node yang berada di posisi posisi. Jika current tidak sama dengan nullptr dan currentIndex kurang dari posisi, maka pindahkan pointer current ke node berikutnya
    while (current != nullptr && currentIndex < posisi)
    {
        current = current->next;
        currentIndex++; // menambahkan nilai 1 ke variabel currentIndex
    }

    if (current != nullptr) // memeriksa apakah current tidak sama dengan nullptr
    {
        cout << "Masukkan data baru untuk Produk di posisi " << posisi << endl;

        // ID Produk tidak dapat diubah
        cout << "ID Produk: " << current->data.kode << endl; // digunakan untuk menampilkan kode produk yang tidak dapat diubah

        cin.ignore(); // digunakan untuk mengabaikan karakter newline yang ada di buffer input
        cout << "Nama Produk: ";
        getline(cin, current->data.nama); // digunakan untuk membaca nama produk dari pengguna
        cout << "Merek Produk: ";
        getline(cin, current->data.merek); // digunakan untuk membaca merek produk dari pengguna
        cout << "Harga Produk (Rp): ";
        cin >> current->data.harga; // digunakan untuk membaca harga produk dari pengguna
        cout << "Stok Produk: ";
        cin >> current->data.stok; // digunakan untuk membaca stok produk dari pengguna
        cout << "Data Produk pada posisi " << posisi << " berhasil diubah!" << endl;
    }
    else // jika posisi yang dipilih admin tidak ditemukan
    {
        cout << "Produk pada posisi " << posisi << " tidak ditemukan." << endl;
    }
}

// Fungsi untuk menemukan pertengahan linked list
// Fungsi untuk mencari tengah dari linked list
Node *findMiddle(Node *head)
{
    // Pengecekan apakah linked list kosong atau hanya terdiri dari satu node
    if (head == nullptr || head->next == nullptr)
    {
        return head; // Jika kosong atau hanya satu node, maka node itu adalah pertengahan
    }

    // Inisialisasi dua pointer, slow dan fast
    Node *slow = head;
    Node *fast = head->next;

    // Iterasi hingga fast mencapai akhir atau nullptr
    while (fast != nullptr && fast->next != nullptr)
    {
        slow = slow->next;       // Pindahkan slow satu node per iterasi
        fast = fast->next->next; // Pindahkan fast dua node per iterasi
    }

    return slow; // Node slow adalah pertengahan linked list
}

// Fungsi Merge untuk Merge Sort
Node *merge(Node *left, Node *right, int ProdukKosmetik::*field)
{
    Node *result = nullptr;

    // Pengecekan jika salah satu linked list kosong, langsung kembalikan yang tidak kosong
    if (left == nullptr)
    {
        return right;
    }
    if (right == nullptr)
    {
        return left;
    }

    // Membandingkan berdasarkan harga (atau bidang yang Anda inginkan)
    if ((left->data.*field) <= (right->data.*field))
    {
        result = left;
        result->next = merge(left->next, right, field); // Rekursif untuk sisa linked list
    }
    else
    {
        result = right;
        result->next = merge(left, right->next, field); // Rekursif untuk sisa linked list
    }

    return result; // Mengembalikan hasil penggabungan yang terurut
}

// Fungsi Merge Sort untuk linked list berdasarkan bidang tertentu
Node *mergeSort(Node *head, int ProdukKosmetik::*field)
{
    // Basis rekursi: jika linked list kosong atau hanya terdiri dari satu node
    if (head == nullptr || head->next == nullptr)
    {
        return head;
    }

    // Temukan node tengah linked list
    Node *middle = findMiddle(head);

    // Pisahkan linked list menjadi dua bagian
    Node *left = head;
    Node *right = middle->next;
    middle->next = nullptr;

    // Rekursif: Urutkan kedua bagian linked list
    left = mergeSort(left, field);   // Urutkan bagian kiri
    right = mergeSort(right, field); // Urutkan bagian kanan

    // Gabungkan dua bagian yang telah diurutkan
    return merge(left, right, field);
}

// Fungsi untuk mengurutkan linked list berdasarkan harga secara ascending
void mergeSortAscending(Node *&head)
{
    head = mergeSort(head, &ProdukKosmetik::harga);
}

// Fungsi untuk mengurutkan linked list berdasarkan harga secara descending
void mergeSortDescending(Node *&head)
{
    // Urutkan linked list berdasarkan harga secara ascending
    head = mergeSort(head, &ProdukKosmetik::harga);

    // Membalikkan urutan setelah pengurutan ascending
    Node *prev = nullptr;
    Node *current = head;
    Node *next = nullptr;

    while (current != nullptr)
    {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }

    head = prev; // Head sekarang adalah node terakhir yang sebelumnya adalah yang pertama
}

// Fungsi untuk mengurutkan linked list berdasarkan stok secara ascending
void mergeSortStokAscending(Node *&head)
{
    head = mergeSort(head, &ProdukKosmetik::stok);
}

// Fungsi untuk mengurutkan linked list berdasarkan stok secara descending
void mergeSortStokDescending(Node *&head)
{
    // Urutkan linked list berdasarkan stok secara ascending
    head = mergeSort(head, &ProdukKosmetik::stok);

    // Membalikkan urutan setelah pengurutan ascending
    Node *prev = nullptr;
    Node *current = head;
    Node *next = nullptr;

    while (current != nullptr)
    {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }

    head = prev; // Head sekarang adalah node terakhir yang sebelumnya adalah yang pertama
}

// Implementasi fungsi pencarian Boyer-Moore
int searchBoyerMoore(const string &text, const string &pattern)
{
    int n = text.length();
    int m = pattern.length();
    if (m == 0)
    {
        return 0; // Pencocokan langsung di posisi 0 jika pola kosong
    }

    // Inisialisasi array right untuk menyimpan informasi kemunculan terakhir setiap karakter dalam pola
    vector<int> right(256, -1);
    for (int i = 0; i < m; i++)
    {
        right[pattern[i]] = i;
    }

    int skip;
    for (int i = 0; i <= n - m; i += skip)
    {
        skip = 0;
        for (int j = m - 1; j >= 0; j--)
        {
            if (pattern[j] != text[i + j])
            {
                // Hitung pergeseran berdasarkan karakter yang tidak cocok di pola
                skip = max(1, j - right[text[i + j]]);
                break;
            }
        }
        if (skip == 0)
        {
            return i; // Pencocokan ditemukan di posisi i
        }
    }

    return -1; // Pencocokan tidak ditemukan
}

// Fungsi untuk mencari produk berdasarkan stok dengan metode linear search
Node *cariProdukBerdasarkanStok(Node *head, int stok)
{
    Node *current = head;
    while (current != nullptr)
    {
        if (current->data.stok == stok)
        {
            return current; // Produk ditemukan, mengembalikan node yang cocok
        }
        current = current->next;
    }
    return nullptr; // Produk tidak ditemukan, mengembalikan nullptr
}

// Fungsi untuk mencari produk berdasarkan nama dengan metode Boyer-Moore Search
Node *cariProdukBerdasarkanNamaBoyerMoore(Node *head, const string &nama)
{
    Node *current = head;
    Node *hasilPencarian = nullptr;

    while (current != nullptr)
    {
        if (current->data.nama.find(nama) != string::npos)
        {
            // Produk ditemukan, simpan hasil pencarian dan lanjutkan pencarian
            Node *temp = new Node;
            temp->data = current->data;
            temp->next = hasilPencarian;
            hasilPencarian = temp;
        }
        current = current->next;
    }

    return hasilPencarian; // Mengembalikan node-node yang cocok dengan pencarian Boyer-Moore
}

// LOGIN ADMIN USERNAME AND PASSWORD
string username = "subasic";
string password = "123";

// Struktur data untuk pengguna / user
struct User
{
    string username;
    string password;
    User *next;
    User *prev;
};

// Fungsi untuk membuat node pengguna baru
User *createUserNode(string username, string password)
{
    // Mengalokasikan memori untuk node baru dan menginisialisasi nilainya
    User *newNode = new User();
    newNode->username = username;
    newNode->password = password;
    newNode->next = nullptr;
    newNode->prev = nullptr;
    return newNode;
}

// Fungsi untuk memeriksa ketersediaan username
bool checkUsernameAvailability(User *head, string username);

// Fungsi untuk menambahkan pengguna ke dalam double linked list
bool addUser(User *&head, string username, string password)
{
    // Validasi username agar unik
    if (!checkUsernameAvailability(head, username))
    {
        cout << "Username sudah digunakan. Silakan pilih username lain." << endl;
        return false; // Registrasi gagal
    }

    // Menambahkan pengguna ke sistem
    User *newUser = createUserNode(username, password);
    if (head == nullptr)
    {
        head = newUser; // Jika linked list kosong, pengguna baru menjadi head
    }
    else
    {
        User *temp = head;
        while (temp->next != nullptr)
        {
            temp = temp->next;
        }
        temp->next = newUser;
        newUser->prev = temp; // Menghubungkan node baru dengan node sebelumnya
    }

    // Menambahkan data registrasi pengguna ke dalam antrian (queue)
    RegistrationHistory historyEntry;
    historyEntry.username = username;
    historyEntry.registrationTime = getCurrentTime();
    // Antrian menggunakan struktur data FIFO, data baru ditambahkan di bagian belakang
    registrationHistoryQueue.push(historyEntry);

    cout << "Registrasi berhasil! Silahkan pilih menu login user untuk berbelanja *><*" << endl;

    return true; // Registrasi berhasil
}

// Fungsi untuk menghapus data registrasi pengguna per satu data sesuai terapan fungsi LIFO
void deleteOldestRegistrationHistory(queue<RegistrationHistory> &registrationHistoryQueue)
{
    while (registrationHistoryQueue.size() > 2)
    {
        registrationHistoryQueue.pop(); // Hapus data registrasi yang paling tua hingga menyisakan 2 data terbaru
    }
}

// Fungsi untuk memeriksa ketersediaan username
bool checkUsernameAvailability(User *head, string username)
{
    User *temp = head;
    while (temp != nullptr)
    {
        if (temp->username == username)
        {
            return false; // Username sudah digunakan
        }
        temp = temp->next;
    }
    return true; // Username tersedia
}

// Variabel jumlah percobaan login yang gagal, dideklarasikan di tingkat global
int failedLoginAttempts = 0;

// Fungsi untuk memeriksa login user
bool checkLogin(User *head, string username, string password)
{
    User *temp = head;
    while (temp != nullptr)
    {
        if (temp->username == username && temp->password == password)
        {
            // Reset jumlah percobaan login jika login berhasil
            failedLoginAttempts = 0;
            return true; // Login berhasil
        }
        temp = temp->next;
    }

    // Tambahkan jumlah percobaan login yang gagal
    failedLoginAttempts++;

    // Tunggu 5 detik setelah 3 kali percobaan login yang gagal
    if (failedLoginAttempts >= 3)
    {
        cout << "Anda telah gagal login sebanyak 3 kali. Silakan coba lagi dalam 5 detik." << endl;
        std::this_thread::sleep_for(std::chrono::seconds(5));
        failedLoginAttempts = 0; // Reset jumlah percobaan login
    }

    return false; // Login gagal
}

int failedAdminLoginAttempts = 0; // Deklarasi variabel di tingkat global

// Fungsi untuk memeriksa login admin
bool checkAdminLogin(string username, string password)
{
    if (username == "subasic" && password == "123")
    {
        // Reset jumlah percobaan login jika login berhasil
        failedAdminLoginAttempts = 0;
        return true; // Login berhasil
    }

    // Tambahkan jumlah percobaan login yang gagal
    failedAdminLoginAttempts++;

    // Tunggu 5 detik setelah 3 kali percobaan login yang gagal
    if (failedAdminLoginAttempts == 5)
    {
        cout << "Anda telah gagal login sebanyak 3 kali. Silakan coba lagi dalam 5 detik." << endl;
        this_thread::sleep_for(chrono::seconds(5));
        failedAdminLoginAttempts = 0; // Reset jumlah percobaan login
    }

    return false; // Login gagal
}
vector<Barang> daftarBarang; // Pindahkan deklarasi ke luar dari blok switch

int main()
{
    queue<RegistrationHistory> registrationHistoryQueue; // variabel yang disimpan untuk queue yang digunakan untuk menyimpan daftar riwayat registrasi pengguna
    string namaPelanggan = "Nama Pelanggan";             // mendeklarsikan nama pelanggan
    double subtotal = 0.0;                               // Variabel subtotal digunakan untuk menyimpan subtotal belanjaan pelanggan
    string metodePembayaran = "Tunai";                   // digunakan untuk menyimpan metode pembayaran pelanggan

    Node *head = nullptr; // digunakan untuk menyimpan head linked list untuk menyimpan daftar produk
    Node *tail = nullptr; // digunakan untuk menyimpan tail linked list untuk menyimpan daftar produk
    int jumlahProduk = 0; // digunakan untuk menyimpan jumlah produk di dalam linked list

    cout << "===================================================\n";
    cout << "|    *       *        *        *       *     *    |\n";
    cout << "| *     * SELAMAT DATANG DI TOKO KOSMETIK *     * |\n";
    cout << "|    *       *        *        *       *     *    |\n";
    cout << "===================================================\n";

    cout << "===================================================\n";
    cout << "|          Silahkan Login Terlebih Dahulu         |\n";
    cout << "===================================================\n";

    int choice;            // mendeklarasikan choice untuk menyimpan pilihan pengguna
    User *users = nullptr; // untuk menyimpan head dari linked list yang digunakan untuk menyimpan daftar pengguna

    do // perulangan untuk mengecek statement yang benar
    {
        cout << "===================================================\n";
        cout << "|  +         +          +         +           +   |\n";
        cout << "|      +       MENU DI TOKO KOSMETIK     +        |\n";
        cout << "|  +         +          +         +           +   |\n";
        cout << "===================================================\n";
        cout << "|1. | Register                                    |\n";
        cout << "===================================================\n";
        cout << "|2. | Login User                                  |\n";
        cout << "===================================================\n";
        cout << "|3. | Login Admin                                 |\n";
        cout << "===================================================\n";
        cout << "|4. | Exit                                        |\n";
        cout << "===================================================\n";
        cout << "Pilihan Anda: ";
        // Validasi input
        if (!(cin >> choice)) // Mengembalikan status input ke normal
        {
            cin.clear();                                         // Mengembalikan status input ke normal                             // Mengembalikan status input ke normal
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Membersihkan buffer input
            cout << "Masukkan tidak valid. Silakan masukkan angka (1-4) sebagai pilihan." << endl;
            continue; // Mengulangi loop
        }

        switch (choice) // untuk menangani pilihan user an memeriksa apakah pilihan tersebut true atau false
        {
        case 1:
        {
            string username, password; // mendeklarasikan username dan password sebagai string
            cout << "Masukkan username: ";
            cin >> username; // menampilkan username yang dimasukkan user
            cout << "Masukkan password: ";
            cin >> password;                    // menampilkan password yang dimasukkan user
            addUser(users, username, password); // memanggil fungsi addusser dan parameternya

            // Menambahkan data registrasi pengguna ke queue
            RegistrationHistory historyEntry;                 // menambahkan data registrasi pengguna ke queue
            historyEntry.username = username;                 // menyimpan informasi username
            historyEntry.registrationTime = getCurrentTime(); // Waktu registrasi pengguna
            registrationHistoryQueue.push(historyEntry);      // memasukkan data menggunakan antrian
            break;                                            // berhentikan pengecekan
        }
        case 2:
        {
            string username, password; // mendeklarasikan username dan password sebagai string
            cout << "Masukkan username: ";
            cin >> username; // menampilkan username yang dimasukkan user
            cout << "Masukkan password: ";
            cin >> password;                           // menampilkan password yang dimasukkan user
            if (checkLogin(users, username, password)) // melakukan perulangan dengan memanggil fungsi checklogin dan parameternya
            {
                // Reset jumlah percobaan login jika login berhasil
                failedLoginAttempts = 0;
                // Menyimpan nama pengguna ke variabel namaPelanggan
                namaPelanggan = username; // Menyimpan nama pengguna ke variabel namaPelanggan
                cout << "Login User Berhasil!!!" << endl;

                // Implementasi menu keranjang belanja
                int pilihanUser; // mendeklarasikan pilihan user sebagai integer
                do
                {
                    cout << "============================================================================\n";
                    cout << "|                 ******* MENU USER DI TOKO KOSMETIK *******               |\n";
                    cout << "============================================================================\n";
                    cout << "|1. | Lihat Barang                                                         |\n";
                    cout << "============================================================================\n";
                    cout << "|2. | Cari Barang                                                          |\n";
                    cout << "============================================================================\n";
                    cout << "|3. | Tambah Barang ke Keranjang                                           |\n";
                    cout << "============================================================================\n";
                    cout << "|4. | Hapus Barang dari Keranjang                                          |\n";
                    cout << "============================================================================\n";
                    cout << "|5. | Melihat keranjang                                                    |\n";
                    cout << "============================================================================\n";
                    cout << "|6. | Transaksi Pembayaran dan Struk                                       |\n";
                    cout << "============================================================================\n";
                    cout << "|7. | Kembali ke Menu Utama                                                |\n";
                    cout << "============================================================================\n";
                    cout << "Pilihan Anda: "; // menampilkan nomor pilhan user

                    // Memastikan input adalah angka dan berada dalam rentang antara 1 hingga 7
                    while (!(cin >> pilihanUser) || pilihanUser < 1 || pilihanUser > 7)
                    {
                        cin.clear(); // Menghapus error flag

                        // Membersihkan buffer untuk menghindari masukan yang salah
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');

                        // Menampilkan pesan kesalahan jika input tidak valid
                        cout << "Masukkan tidak valid. Silakan masukkan angka antara 1-7: ";
                    }

                    switch (pilihanUser) // melakukan perulangan switch dengan fungsi pilihan user dana user dapat memilih nomor dalam menu dari 1 sampai 7
                    {
                    case 1:
                        // Implementasi untuk menampilkan produk di toko kosmetik
                        tampilkanProduk(head); // memanggil fungsi tampilkanProduk(head)
                        break;                 // memberhentikan perulangan
                    case 2:
                        // Implementasi untuk mencari produk berdasarkan nama produk
                        {
                            string nama;  // mendeklarsikan nama sebagai string
                            cin.ignore(); // Membersihkan buffer input menggunakan fungsi
                            cout << "Masukkan Nama Produk yang akan dicari: ";
                            getline(cin, nama);                                                     // Mengambil input dari pengguna
                            Node *hasilPencarian = cariProdukBerdasarkanNamaBoyerMoore(head, nama); // Memanggil fungsi cariProdukBerdasarkanNamaBoyerMoore() untuk mencari produk dengan nama yang dimasukkan oleh pengguna
                            if (hasilPencarian != nullptr)                                          // memeriksa hasil pencarian tidak sama dengan nullptr
                            {
                                tampilkanProduk(hasilPencarian); // memanggil fungsi tampilkanProduk(hasilPencarian) dan parameternya
                            }
                            else // jika hasil pencarian tidak ditemukan maka program akan mencetak pesan "Produk dengan Nama "" << nama << "" tidak ditemukan
                            {
                                cout << "Produk dengan Nama \"" << nama << "\" tidak ditemukan." << endl;
                            }
                            break; // memberhentikan perulangan
                        }
                        break;
                    case 3:
                    {
                        // Memasukkan nama produk dan jumlah produk yang dibeli
                        string namaProduk; // mendeklarasikan namaProduk sebagai tipe data string
                        int jumlah;        // mendeklarasikan jumlah sebagai integer

                        cout << "Masukkan Nama Produk: ";
                        cin.ignore(); // Untuk membersihkan newline character dari input sebelumnya
                        getline(cin, namaProduk);

                        cout << "Masukkan Jumlah Produk: ";
                        cin >> jumlah; // menampilkan jumlah yang bertipe data integer

                        // Mencari produk dengan nama yang sesuai di dalam daftar produk
                        Node *current = head;      // memanggil pointer bernama current yang menunjuk ke node pertama dari sebuah linked list
                        while (current != nullptr) // melakukan perulangan selama current != nullptr, yang berarti masih ada node yang tersisa di dalam daftar produk
                        {
                            if (current->data.nama == namaProduk)
                            {
                                // Temukan produk berdasarkan nama, sekarang tambahkan produk ke keranjang
                                if (current->data.stok >= jumlah) // memeriksa apakah produk dengan kode kodeProduk ditemukan di dalam daftar produk
                                {
                                    // Jika stok mencukupi untuk transaksi
                                    Barang newBarang;                          // mendeklarasikan sebuah objek baru dari struct Barang
                                    newBarang.kodeProduk = current->data.kode; // digunakan untuk mengisi field kode dari objek newBarang dengan nilai kodeProduk
                                    newBarang.nama = current->data.nama;       // digunakan untuk mengisi field nama dari objek newBarang dengan nilai dari field nama dari objek current
                                    newBarang.jumlah = jumlah;                 // digunakan untuk mengisi field jumlah dari objek newBarang dengan nilai jumlah
                                    newBarang.harga = current->data.harga;     // digunakan untuk mengisi field harga dari objek newBarang dengan nilai dari field harga dari objek current

                                    // Tambahkan produk ke keranjang
                                    tambahBarangKeKeranjang(newBarang); // memanggil fungsi tambahBarangKeKeranjang dan newbarang untuk menampilkan isi keranjang
                                    cout << "Produk telah ditambahkan ke keranjang.\n";
                                    current->data.stok -= jumlah; // digunakan jika sudah menambahkan ke keranjang maka stok akan berkurang
                                }
                                else
                                {
                                    cout << "Stok tidak mencukupi untuk transaksi." << endl;
                                }
                                break; // memberhentikan pengecekan
                            }
                            current = current->next;
                        }

                        if (current == nullptr) // mengecek apakah pointer current menunjuk ke node yang valid
                        {
                            cout << "Produk dengan nama \"" << namaProduk << "\" tidak ditemukan." << endl; // jika tidak akan menampilkan output Produk dengan kode " << kodeProduk << " tidak ditemukan.
                        }
                        break; // memberhentikan pengecekan
                    }
                    case 4:
                    {
                        if (keranjangHead == nullptr) // mengecek apakah keranjang belanja kosong
                        {
                            cout << "Keranjang belanja kosong." << endl;
                        }
                        else // jika tidak kosong atau sudah menambahkan belanjaan maka akan menampilkan isis kernjang
                        {
                            // Menampilkan isi keranjang belanja
                            tampilkanKeranjangBelanja();
                            int nomorBarangHapus; // mendeklarasikan nomorbaranghapus bertipe data integer
                            cout << "Masukkan nomor barang yang ingin dihapus: ";
                            cin >> nomorBarangHapus; // menampilkan nomor barang yang ingin dihapus

                            hapusBarangDariKeranjang(nomorBarangHapus); // lalu memanggi fungsi hapus barang dari keranjang
                        }
                        cout << "Barang Berhasil Dihapus!" << endl;
                        break;
                    }
                    case 5:
                        tampilkanKeranjangBelanja(); // memanggil fungsi tampilkanKeranjangBelanja()
                        break;
                    case 6:
                    {
                        double hargaTotal = 0.0;                                                // Inisialisasi variabel hargaTotal ke 0
                        hitungTotalHarga(keranjangHead, hargaTotal);                            // Memanggil fungsi hitungTotalHarga untuk menghitung total harga belanja
                        cetakStruk(namaPelanggan, keranjangHead, hargaTotal, metodePembayaran); // Mencetak struk pembayaran dengan data yang diperlukan
                        break;                                                                  // Keluar dari blok case 6
                    }
                    case 7: // jika user memilih nomor 7 maka program akan kemvbali ke nmenu login
                        cout << "Terima kasih telah berkunjung di toko kami *><*" << endl;
                        break;
                    default: // selain memilih nomor 1-7 maka output yang dipilih Pilihan tidak tersedia. Silakan pilih lagi.
                        cout << "Pilihan tidak tersedia. Silakan pilih lagi." << endl;
                        break;
                    }

                } while (pilihanUser != 7);
            }
            else
            {
                cout << "Login gagal. Username atau password salah." << endl;
            }
            break;
        }
        case 3:
        {
            string username, password; // untuk menyimpan username dan password admin yang dimasukkan oleh admin
            // Mengecek apakah admin telah gagal login sebanyak 3 kali
            if (failedAdminLoginAttempts == 5)
            {
                cout << "Anda telah gagal login sebanyak 3 kali. Silakan coba lagi dalam 5 detik." << endl;
                this_thread::sleep_for(chrono::seconds(5));
                failedAdminLoginAttempts = 0; // Reset jumlah percobaan login
            }

            cout << "Masukkan username admin: ";
            cin >> username; // menampilkan username yang diinput dengan tipe data string
            cout << "Masukkan password admin: ";
            cin >> password; // menampilkan password yang diinput dengan tipe data string

            if (checkAdminLogin(username, password)) //  fungsi checkAdminLogin() untuk memeriksa apakah username dan password admin yang dimasukkan benar dari string username dan passwor yang sudah dideklarasikan
            {
                // Reset jumlah percobaan login jika login berhasil
                failedAdminLoginAttempts = 0;
                cout << "Login Admin Berhasil!!!" << endl;

                int pilihan; // digunakan untuk menyimpan pilihan pengguna
                do
                {
                    cout << "============================================================================\n";
                    cout << "|                ******* MENU ADMIN DI TOKO KOSMETIK *******               |\n";
                    cout << "============================================================================\n";
                    cout << "|1. | Tampilkan Produk                                                     |\n";
                    cout << "============================================================================\n";
                    cout << "|2. | Tambah Produk                                                        |\n";
                    cout << "============================================================================\n";
                    cout << "|3. | Hapus Produk                                                         |\n";
                    cout << "============================================================================\n";
                    cout << "|4. | Ubah Produk                                                          |\n";
                    cout << "============================================================================\n";
                    cout << "|5. | Urutkan Produk berdasarkan Harga (Ascending)                         |\n";
                    cout << "============================================================================\n";
                    cout << "|6. | Urutkan Produk berdasarkan Harga (Descending)                         |\n";
                    cout << "============================================================================\n";
                    cout << "|7. | Urutkan Produk berdasarkan Stok (Ascending)                           |\n";
                    cout << "============================================================================\n";
                    cout << "|8. | Urutkan Produk berdasarkan Stok (Descending)                          |\n";
                    cout << "============================================================================\n";
                    cout << "|9. | Cari Produk berdasarkan Stok Barang                                   |\n";
                    cout << "============================================================================\n";
                    cout << "|10.| Cari Produk berdasarkan Nama Barang                                  |\n";
                    cout << "============================================================================\n";
                    cout << "|11.| Menampilkan Data Produk Secara Forward (Data dari head ke Tail)      |\n";
                    cout << "============================================================================\n";
                    cout << "|12.| Menampilkan Data Produk Secara  Backward (Data dari Tail ke Head)    |\n";
                    cout << "============================================================================\n";
                    cout << "|13.| History Data Registrasi User                                         |\n";
                    cout << "============================================================================\n";
                    cout << "|14.| Kembali ke Menu Utama                                                |\n";
                    cout << "============================================================================\n";
                    cout << "Pilihan Anda: "; // menampilkan nomor pilihan admin

                    // Memastikan input adalah angka dan berada dalam rentang antara 1 hingga 14
                    while (!(cin >> pilihan) || pilihan < 1 || pilihan > 14)
                    {
                        cin.clear(); // Menghapus error flag

                        // Membersihkan buffer untuk menghindari masukan yang salah
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');

                        // Menampilkan pesan kesalahan jika input tidak valid
                        cout << "Masukkan tidak valid. Silakan masukkan angka antara 1-14: ";
                    }

                    // Inisialisasi variabel historyEntry di luar semua case statement
                    RegistrationHistory historyEntry;

                    switch (pilihan) // melakukan pergantian untuk memilih berdasarkan user memilih nomor dari program
                    {
                    case 1:                    // menampilkan produk yang tersedia
                        tampilkanProduk(head); // memanggil fungsi tampilkanProduk(head)
                        break;                 // menghentikan loop
                    case 2:
                    {
                        // Pilihan untuk menambah produk
                        tambahProduk(head, tail, jumlahProduk); // memanggil void tambahproduk dan parameternya
                        break;                                  // menghentikan loop
                    }
                    case 3:
                    {
                        int pilihanHapus; // digunakan untuk menyimpan pilihan
                        do                // untuk mengulang proses pemilihan kode produk hingga admin memilih opsi Kembali
                        {
                            cout << "=============================\n";
                            cout << "| Hapus Produk - Pilih Opsi |\n";
                            cout << "=============================\n";
                            cout << "|1. Hapus dari Awal         |\n";
                            cout << "|2. Hapus dari Akhir        |\n";
                            cout << "|3. Hapus di Tengah         |\n";
                            cout << "|4. Kembali                 |\n";
                            cout << "=============================\n";
                            cout << "Pilihan Anda: "; // menampilkan pilihan dari admin

                            // Memastikan input adalah angka
                            while (!(cin >> pilihanHapus) || pilihanHapus < 1 || pilihanHapus > 4)
                            {
                                cin.clear(); // Menghapus error flag

                                // Membersihkan buffer untuk menghindari masukan yang salah
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                                // Menampilkan pesan kesalahan jika input tidak valid
                                cout << "Masukkan tidak valid. Silakan masukkan angka antara 1-4: ";
                            }

                            if (pilihanHapus == 1 || pilihanHapus == 2 || pilihanHapus == 3) // admin hanya bisa memilih pilihan no 1, 2, dan 3
                            {
                                if (pilihanHapus != 4)
                                {
                                    int kode; // mendeklarasikan bahwa kode bertipe data integer
                                    cout << "Masukkan Kode Produk yang akan dihapus: ";
                                    cin >> kode; // menampilkan kode yang telah dimasukkan
                                    hapusProduk(head, tail, jumlahProduk, pilihanHapus, kode);
                                }
                            }
                            else if (pilihanHapus != 4) // jika admin memasukkan nomor selai nomor 1 sampai 3 maka akan menampilkan error handling "Pilihan tidak valid. Silakan pilih kembali
                            {
                                cout << "Pilihan tidak valid. Silakan pilih kembali." << endl;
                            }
                        } while (pilihanHapus != 4);

                        break; // menghentikan loop
                    }
                    case 4:
                    {
                        int posisi; // mendeklarasikan posisi bertipe data integer
                        cout << "Masukkan posisi Produk yang akan diubah: ";
                        cin >> posisi;                    // menampilkan posisi yang dipilih admin
                        ubahProdukDiPosisi(head, posisi); // memanggil fungsi ubahProdukDiPosisi dan paramternya
                        break;                            // menghentikan loop
                    }
                    case 5:
                        mergeSortAscending(head); // memanggil fungsi mergeSortAscending(head)
                        cout << "Produk berhasil diurutkan berdasarkan harga secara ascending!\n";
                        break; // menghentikan loop
                    case 6:
                        mergeSortDescending(head); // memanggil fungsi mergeSortDescending(head)
                        cout << "Produk berhasil diurutkan berdasarkan harga secara descending!\n";
                        break; // menghentikan loop
                    case 7:
                        mergeSortStokAscending(head); // memanggil fungsi mergeSortStokAscending(head)
                        cout << "Produk berhasil diurutkan berdasarkan stok secara ascending!\n";
                        break; // menghentikan loop
                    case 8:
                        mergeSortStokDescending(head); // memanggil fungsi mergeSortStokDescending(head)
                        cout << "Produk berhasil diurutkan berdasarkan stok secara descending!\n";
                        break; // menghentikan loop
                    case 9:    // Cari Produk berdasarkan Stok Barang
                    {
                        int stokCari; // mendeklarasikan stokcari bertipe data integer
                        cout << "Masukkan stok yang ingin dicari: ";
                        cin >> stokCari; // memasukkan stok yang ingin dicari

                        Node *hasilPencarian = cariProdukBerdasarkanStok(head, stokCari); // Memanggil fungsi cariProdukBerdasarkanStok() untuk mencari produk tersebut

                        if (hasilPencarian != nullptr) // memeriksa hasil pencarian bernilai nullptr atau tidak
                        {
                            // melakukan perulangan jika stok yang dicari user itu ditemukan
                            cout << "Produk dengan stok " << stokCari << " ditemukan:" << endl;
                            cout << "Nama: " << hasilPencarian->data.nama << endl;
                            cout << "Merek: " << hasilPencarian->data.merek << endl;
                            cout << "Harga: " << hasilPencarian->data.harga << endl;
                            cout << "Stok: " << hasilPencarian->data.stok << endl;
                        }
                        else
                        {
                            cout << "Produk dengan stok " << stokCari << " tidak ditemukan." << endl;
                        }
                        break;
                    }
                    case 10:
                    {
                        string nama;  // mendeklarasikan bahawa nama bertipe data string
                        cin.ignore(); // mengosongkan buffer input cin
                        cout << "Masukkan Nama Produk yang akan dicari: ";
                        getline(cin, nama);                                                     // digunakan untuk membaca satu baris dari input pengguna dan menyimpannya ke dalam variabel nama
                        Node *hasilPencarian = cariProdukBerdasarkanNamaBoyerMoore(head, nama); // Memanggil fungsi cariProdukBerdasarkanNamaBoyerMoore() untuk mencari produk tersebut
                        if (hasilPencarian != nullptr)                                          // perulangan untuk menampilkan hasil pencarian
                        {
                            tampilkanProduk(hasilPencarian); // menampilkan fungsi tampilkanproduk untuk admin
                        }
                        else
                        {
                            cout << "Produk dengan Nama \"" << nama << "\" tidak ditemukan." << endl;
                        }
                        break; // memberhentikan perulangan
                    }
                    case 11:
                        tampilkanProdukForward(head); // memanggil fungsi tampilkanProdukForward(head) dan parameternya
                        cout << "Produk berhasil ditampilkan secara Forward (Data dari Head ke Tail)!\n";
                        break; // berhentikan perulangan
                    case 12:
                        tampilkanProdukBackward(tail); // memanggil fungsi tampilkanProdukBackward(tail) dan parameternya
                        cout << "Produk berhasil ditampilkan secara Backward (Data dari Tail ke Head)!\n";
                        break; // berhentikan perulangan

                    case 13: // Menu history registrasi pengguna
                    {
                        // Implementasi untuk menampilkan history registrasi pengguna

                        // Memeriksa apakah antrian history registrasi pengguna kosong
                        if (registrationHistoryQueue.empty())
                        {
                            cout << "Tidak ada history registrasi pengguna." << endl;
                        }
                        else
                        {
                            // Menampilkan judul "History Registrasi Pengguna"
                            cout << "=== History Registrasi Pengguna ===" << endl;

                            // Menampilkan header tabel
                            cout << "+-----------+---------------------+" << endl;
                            cout << "| Username  | Waktu Registrasi    |" << endl;
                            cout << "+-----------+---------------------+" << endl;

                            // Salin antrian history registrasi ke antrian sementara untuk iterasi
                            queue<RegistrationHistory> tempQueue = registrationHistoryQueue;

                            // Iterasi melalui antrian sementara untuk menampilkan history
                            while (!tempQueue.empty())
                            {
                                // Mengambil data history registrasi dari antrian sementara
                                const RegistrationHistory &history = tempQueue.front();

                                // Menampilkan data history registrasi dalam bentuk tabel
                                cout << "| " << setw(10) << history.username << " | " << setw(19) << history.registrationTime << " |" << endl;

                                // Menghapus data histori yang sudah di-iterasi
                                tempQueue.pop();
                            }

                            // Menampilkan footer tabel
                            cout << "+-----------+---------------------+" << endl;

                            // Hapus data histori registrasi pengguna yang sudah di-iterasi
                            deleteOldestRegistrationHistory(registrationHistoryQueue);
                        }
                    }
                    case 14: // keluar dari menu admin
                        cout << "Terima kasih Admin *><*\n";
                        break; // menghentikan loop

                    default: // digunakan jika admin memasukkan nomor yang tidak tersedia di menu admin
                        cout << "Pilihan tidak tersedia. Silakan pilih lagi.\n";
                        break; // menghentikan loop
                    }
                } while (pilihan != 14);
            }
            else // jika admin memasukkan password atau username yang salah maka output yang dihasilkan Login admin gagal. Username atau password salah
            {
                // Tambahkan jumlah percobaan login yang gagal
                failedAdminLoginAttempts++;
                cout << "Login admin gagal. Username atau password salah." << endl;
            }
            break;
        }

        case 4: // jika user memilih no 4 maka program akan kembali ke menu login
            cout << "=======================================================================" << endl;
            cout << "|  +       +       +       +       +       +       +       +       +  |" << endl;
            cout << "|   *Terima kasih telah berkunjung di toko kami, Sampai jumpa lagi*   |" << endl;
            cout << "|  +       +       +       +       +       +       +       +       +  |" << endl;
            cout << "=======================================================================" << endl;
            break;
        default:                                                           // jika admin memasukkan nomor selain nomor 1-4 maka output yang dihasilkan Pilihan tidak tersedia. Silakan pilih lagi
            cout << "Pilihan tidak tersedia. Silakan pilih lagi." << endl; // jika user memilih pilihan selain no 1-4 maka akan menampilkan error handling Pilihan tidak tersedia. Silakan pilih lagi
            break;
        }

    } while (choice != 4); // loop atau perulangan akan berhenti jika user memilih no 4

    // node ini digunakan untuk menghapus semua node dalam linked list
    Node *current = head;      // digunakan membuat pointer current menunjuk ke node pertama di linked list.
    while (current != nullptr) // perulangan untuk mengecek bahwa pointer current tersebut menunjukkan ke node yang benar
    {
        Node *next = current->next; // menyimpan pointer ke node berikutnya di linked list ke dalam variabel next
        delete current;             // menghapus node yang saat ini ditunjuk oleh pointer current
        current = next;             // memindahkan pointer current ke node berikutnya
    }
    return 0; // untuk menghentikan program
}