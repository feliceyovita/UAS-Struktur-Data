#include <bits/stdc++.h>
#define ii pair<int, int>
using namespace std;


struct Produk
{
    int id;
    string nama;
    string kategori;
    int harga;
};

struct KeranjangItem
{
    Produk produk;
    int jumlah;
};

struct RiwayatPembayaran {
    int id;
    string nama;
    int jumlahBarang; 
    int total;      
    string waktuPembayaran; 
    vector<KeranjangItem> barangDibeli; 
};


class HashTable
{
private:
    static const int size = 10;
    list<Produk> table[size];

    int hashFunction(const string &kategori)
    {
        int hash = 0;
        for (char ch : kategori)
        {
            hash += ch;
        }
        return hash % size;
    }

public:
    void insert(const Produk &produk)
    {
        int index = hashFunction(produk.kategori);
        table[index].push_back(produk);
    }

    list<Produk> getProdukByKategori(const string &kategori)
    {
        int index = hashFunction(kategori);
        list<Produk> hasil;

        for (const auto &produk : table[index])
        {
            if (produk.kategori == kategori)
            {
                hasil.push_back(produk);
            }
        }
        return hasil;
    }
};

// Fungsi untuk menampilkan daftar produk
void tampilkanProduk(const vector<Produk> &produk)
{
    cout << "\n========================= Daftar Produk ============================" << endl;
    cout << left << setw(5) << "ID"
         << setw(30) << "Nama Produk"
         << setw(20) << "Kategori"
         << setw(15) << "Harga (Rp)" << endl;

    for (const auto &p : produk)
    {
        cout << left << setw(5) << p.id
             << setw(30) << p.nama
             << setw(20) << p.kategori
             << setw(15) << p.harga << endl;
    }
    cout << "====================================================================";
}

// Fungsi untuk menampilkan menu dalam menu 1
void menuTampilkanProduk(const vector<Produk> &produk)
{
    int pilihanMenu1;
    do
    {
        tampilkanProduk(produk);
        cout << "\n1. Kembali ke Menu Utama" << endl;
        cout << "Masukkan pilihan: ";
        cin >> pilihanMenu1;

        if (pilihanMenu1 != 1)
        {
            cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
        }
    } while (pilihanMenu1 != 1);
}

// Fungsi untuk mengurutkan produk berdasarkan harga menggunakan Bubble Sort
void bubbleSort(vector<Produk> &produk)
{
    int n = produk.size();
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - 1 - i; j++)
        {
            if (produk[j].harga > produk[j + 1].harga)
            {
                swap(produk[j], produk[j + 1]);
            }
        }
    }
}

// Fungsi untuk sortir berdasarkan kategori
void sortirBerdasarkanKategori(vector<Produk> &produk, const string &kategori)
{
    HashTable hashTable;

    for (const auto &p : produk)
    {
        hashTable.insert(p);
    }

    list<Produk> hasil = hashTable.getProdukByKategori(kategori);

    if (!hasil.empty())
    {
        vector<Produk> hasilVec(hasil.begin(), hasil.end());
        tampilkanProduk(hasilVec);
    }
    else
    {
        cout << "Tidak ada produk dalam kategori " << kategori << endl;
    }
}

// Fungsi untuk menu sortir (harga atau kategori)
void menuSortirProduk(vector<Produk> &produk)
{
    int pilihanSortir;
    do
    {
        cout << "\n=== Menu Sortir Produk ===" << endl;
        cout << "1. Sortir Berdasarkan Harga" << endl;
        cout << "2. Sortir Berdasarkan Kategori" << endl;
        cout << "0. Kembali ke Menu Utama" << endl;
        cout << "Masukkan pilihan: ";
        cin >> pilihanSortir;

        switch (pilihanSortir)
        {
        case 1:
            system("cls");
            bubbleSort(produk);
            tampilkanProduk(produk);
            break;
        case 2:
        {
            system("cls");
            string kategori;
            cout << "Masukkan kategori (Elektronik/Fitness/Kecantikan/Konsumsi): ";
            cin >> kategori;
            sortirBerdasarkanKategori(produk, kategori);
            break;
        }
        case 0:
            break;
        default:
            cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
            break;
        }
    } while (pilihanSortir != 0);
}

// Fungsi untuk menambahkan produk ke keranjang
void tambahKeKeranjang(const vector<Produk> &produk, vector<KeranjangItem> &keranjang, int &jumlahKeranjang, const int maxKeranjang)
{
    system("cls");
    if (jumlahKeranjang >= maxKeranjang)
    {
        cout << "Keranjang penuh! Tidak dapat menambahkan produk lagi." << endl;
        return;
    }

    int idProduk;
    cout << "Masukkan ID produk yang ingin ditambahkan ke keranjang: ";
    cin >> idProduk;

    bool ditemukan = false;
    for (const auto &p : produk)
    {
        if (p.id == idProduk)
        {
            int kuantitas;
            cout << "Kuantitas yang ingin ditambah: ";
            cin >> kuantitas;

            if (kuantitas <= 0)
            {
                cout << "Kuantitas tidak valid. Tidak ada produk yang ditambahkan." << endl;
            }
            else
            {
                bool sudahAda = false;
                for (auto &item : keranjang)
                {
                    if (item.produk.id == p.id)
                    {
                        item.jumlah += kuantitas;
                        sudahAda = true;
                        break;
                    }
                }

                if (!sudahAda && jumlahKeranjang < maxKeranjang)
                {
                    keranjang.push_back({p, kuantitas});
                    jumlahKeranjang++;
                }

                cout << "\nProduk " << p.nama << " berhasil ditambahkan ke keranjang sebanyak "
                     << kuantitas << " unit!" << endl;
            }

            ditemukan = true;
            break;
        }
    }

    if (!ditemukan)
    {
        cout << "\nProduk dengan ID " << idProduk << " tidak ditemukan." << endl;
    }

    int pilihanMenu1;
    do
    {
        cout << "\n==========================================================================" << endl;
        cout << "1. Tambah produk lain ke keranjang" << endl;
        cout << "2. Kembali ke Menu Utama" << endl;
        cout << "Masukkan pilihan: ";
        cin >> pilihanMenu1;

        if (pilihanMenu1 == 1)
        {
            tambahKeKeranjang(produk, keranjang, jumlahKeranjang, maxKeranjang);
            break;
        }
        else if (pilihanMenu1 == 2)
        {
            break;
        }
        else
        {
            cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
        }
    } while (pilihanMenu1 != 1 && pilihanMenu1 != 2);
}

//Fungsi untuk mencari peroduk berdasarkan id
void cariProdukByID(const vector<Produk> &produk)
{
    int idProduk;
    cout << "Masukkan ID produk yang ingin dicari: ";
    cin >> idProduk;

    unordered_map<int, Produk> produkMap;

    for (const auto &p : produk)
    {
        produkMap[p.id] = p; 
    }

    if (produkMap.find(idProduk) != produkMap.end())
    {
        Produk p = produkMap[idProduk];
        cout << "\n======================= Produk Ditemukan ========================" << endl;
        cout << left << setw(5) << "ID"
             << setw(30) << "Nama Produk"
             << setw(20) << "Kategori"
             << setw(15) << "Harga (Rp)" << endl;
        cout << "-----------------------------------------------------------------" << endl;
        cout << left << setw(5) << p.id
             << setw(30) << p.nama
             << setw(20) << p.kategori
             << setw(15) << p.harga << endl;
        cout << "==================================================================" << endl;
    }
    else
    {
        cout << "\nProduk dengan ID " << idProduk << " tidak ditemukan." << endl;
    }

    int pilihanMenu1;
    do
    {
        cout << "\n1. Kembali ke Menu Utama" << endl;
        cout << "Masukkan pilihan: ";
        cin >> pilihanMenu1;

        if (pilihanMenu1 != 1)
        {
            cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
        }
    } while (pilihanMenu1 != 1);
}

// Fungsi untuk menampilkan keranjang belanja
void tampilkanKeranjang(const vector<KeranjangItem> &keranjang)
{
    if (keranjang.empty())
    {
        cout << "Keranjang belanja kosong." << endl;
        int pilihanMenu1;
        do
        {
            cout << "\n1. Kembali ke Menu Utama" << endl;
            cout << "Masukkan pilihan: ";
            cin >> pilihanMenu1;

            if (pilihanMenu1 != 1)
            {
                cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
            }
        }
        while (pilihanMenu1 != 1);
        return;
    }

    cout << "\n========================= Keranjang Belanja =========================" << endl;
    cout << left << setw(5) << "ID"
         << setw(30) << "Nama Produk"
         << setw(15) << "Jumlah"
         << setw(15) << "Harga Total (Rp)" << endl;

    int grandTotal = 0;

    for (const auto &item : keranjang)
    {
        int totalHarga = item.produk.harga * item.jumlah;

        cout << left << setw(5) << item.produk.id
             << setw(30) << item.produk.nama
             << setw(15) << item.jumlah
             << setw(15) << totalHarga << endl;

        grandTotal += totalHarga;
    }

    cout << "=====================================================================" << endl;
    cout << "Total Belanja: Rp " << grandTotal << endl;

    int pilihanMenu1;
    do
    {
        cout << "\n1. Kembali ke Menu Utama" << endl;
        cout << "Masukkan pilihan: ";
        cin >> pilihanMenu1;

        if (pilihanMenu1 != 1)
        {
            cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
        }
    } while (pilihanMenu1 != 1);
}

// Fungsi untuk menghapus barang dari keranjang belanja berdasarkan ID
void hapusDariKeranjang(vector<KeranjangItem> &keranjang)
{
    int idProduk;
    cout << "Masukkan ID produk yang ingin dihapus dari keranjang belanja: ";
    cin >> idProduk;

    auto it = keranjang.begin();
    bool ditemukan = false;
    while (it != keranjang.end())
    {
        if (it->produk.id == idProduk)
        {
            keranjang.erase(it);
            cout << "Produk dengan ID " << idProduk << " berhasil dihapus dari keranjang belanja." << endl;
            ditemukan = true;
            break;
        }
        ++it;
    }

    if (!ditemukan)
    {
        cout << "Produk dengan ID " << idProduk << " tidak ditemukan di keranjang belanja." << endl;
    }

    int pilihanMenu1;
    do
    {
        cout << "\n1. Kembali ke Menu Utama" << endl;
        cout << "Masukkan pilihan: ";
        cin >> pilihanMenu1;

        if (pilihanMenu1 != 1)
        {
            cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
        }
    } while (pilihanMenu1 != 1);
}

int hitungBiayaPengiriman(int biayaPengiriman) {
    int tujuan;
    while (true) {
        system("cls");
        cout << "Masukkan titik tujuan (1-9): ";
        cin >> tujuan;
        if (tujuan >= 1 && tujuan <= 9) {
            break;
        } else {
            cout << "Input salah! Masukkan titik tujuan antara 1 sampai 9." << endl;
        }
    }

    int n = 10; 
    int m = 13; 
    vector<vector<ii>> adj(n);

    adj[0].push_back({3, 4});
    adj[0].push_back({6, 4});
    adj[0].push_back({2, 7});
    adj[0].push_back({8, 5});
    adj[6].push_back({1, 4});
    adj[6].push_back({4, 2});
    adj[6].push_back({5, 11});
    adj[2].push_back({1, 5});
    adj[8].push_back({5, 10});
    adj[4].push_back({7, 7});
    adj[5].push_back({4, 9});
    adj[5].push_back({7, 8});
    adj[5].push_back({9, 3});
    adj[9].push_back({7, 4});

    vector<int> dist(n, INT_MAX); 
    vector<bool> visited(n, false);
    vector<int> pred(n, -1);
    priority_queue<ii, vector<ii>, greater<ii>> pq;
    dist[0] = 0;
    pq.push({0, 0});

    while (!pq.empty()) {
        ii currItem = pq.top(); pq.pop();
        int currDist = currItem.first;
        int currNode = currItem.second;

        if (!visited[currNode]) {
            visited[currNode] = true;

            for (ii it : adj[currNode]) {
                int v = it.first;
                int w = it.second;
                if (dist[currNode] + w < dist[v]) {
                    dist[v] = dist[currNode] + w;
                    pred[v] = currNode;
                    pq.push({dist[v], v});
                }
            }
        }
    }

    biayaPengiriman = dist[tujuan] * 3000;
    cout << "Biaya pengiriman dari supermarket ke titik " << tujuan << " : Rp." << biayaPengiriman << endl;

    int pilihan;
    while (true) {  
        cout << "\n1. Memperbarui tujuan\n";
        cout << "2. Simpan tujuan dan kembali ke ke menu utama\n";
        cout << "Masukkan pilihan: ";
        cin >> pilihan;

        if (pilihan == 1) {
            return hitungBiayaPengiriman(biayaPengiriman);
        } else if (pilihan == 2) {
            return biayaPengiriman;
        } else {
            cout << "Pilihan tidak valid!\n Silakan masukkan pilihan yang benar.\n";
        }
    }
}

// Fungsi untuk menyimpan riwayat pembayaran
void simpanRiwayatPembayaran(vector<RiwayatPembayaran>& riwayat, int id, const string& nama, const vector<KeranjangItem>& barangDibeli, int total, const string& waktuPembayaran) {
    // Membuat riwayat baru dan menyimpannya ke dalam vector riwayat
    RiwayatPembayaran riwayatBaru = {id, nama, static_cast<int>(barangDibeli.size()), total, waktuPembayaran, barangDibeli};
    riwayat.push_back(riwayatBaru);

    // Menampilkan pesan bahwa penyimpanan riwayat pembayaran berhasil
    cout << "Riwayat pembayaran berhasil disimpan untuk nama pembeli: " << nama << endl;
    cout << "Jumlah produk yang dibeli: " << barangDibeli.size() << endl;
    cout << "Total pembayaran: Rp " << total << endl;
    cout << "Waktu Pembayaran: " << waktuPembayaran << endl;
}

void prosesPembayaran(vector<KeranjangItem> &keranjang, vector<RiwayatPembayaran> &riwayat, int biayaPengiriman, int &indeksPembayaran) {
    if (keranjang.empty()) {
        cout << "Keranjang kosong, tidak ada pembayaran yang perlu dilakukan." << endl;
        return;
    }

    // Jika biaya pengiriman belum dihitung, hitung biaya pengiriman
    if (biayaPengiriman == 0) {
        biayaPengiriman = hitungBiayaPengiriman(biayaPengiriman);
    }

    int totalPembayaran = 0;
    cout << "\nProses Pembayaran: " << endl;
    cout << left << setw(5) << "ID"
         << setw(30) << "Nama Produk"
         << setw(15) << "Jumlah"
         << setw(15) << "Subtotal (Rp)" << endl;
    cout << string(65, '-') << endl;

    for (const auto& item : keranjang) {
        int subtotal = item.produk.harga * item.jumlah;
        totalPembayaran += subtotal;

        cout << left << setw(5) << item.produk.id
             << setw(30) << item.produk.nama
             << setw(15) << item.jumlah
             << setw(15) << subtotal << endl;
    }

    totalPembayaran += biayaPengiriman;
    cout << right << setw(50) << "Biaya Pengiriman: Rp" << biayaPengiriman << endl;
    cout << right << setw(50) << "Total Pembayaran: Rp" << totalPembayaran << endl;
    cout << string(65, '-') << endl;

    string namaPembeli;
    cout << "Masukkan Nama Pembeli: ";
    cin.ignore();
    getline(cin, namaPembeli);

    int pilihan;
    cout << "\n1. Bayar" << endl;
    cout << "2. Kembali ke menu utama" << endl;
    cout << "Masukkan pilihan: ";
    cin >> pilihan;

    if (pilihan == 1) {
        time_t sekarang = time(0);
        char* dt = ctime(&sekarang);
        string waktuPembayaran = dt;

        simpanRiwayatPembayaran(riwayat, indeksPembayaran++, namaPembeli, keranjang, totalPembayaran, waktuPembayaran);

        cout << "\nPembayaran berhasil! Total Pembayaran: Rp" << totalPembayaran << endl;

        keranjang.clear();

        int pilihanMenu1;
        do {
            cout << "\n1. Kembali ke Menu Utama" << endl;
            cout << "Masukkan pilihan: ";
            cin >> pilihanMenu1;

            if (pilihanMenu1 != 1) {
                cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
            }
        } while (pilihanMenu1 != 1);
    } else if (pilihan == 2) {
        return;
    } else {
        cout << "\nPilihan tidak valid, coba lagi.\n";
    }
}

void tampilkanRiwayatPembayaran(const vector<RiwayatPembayaran>& riwayat) {
    // Menampilkan header
    cout << left << setw(5) << "ID"
         << setw(30) << "Nama Pembeli"
         << setw(15) << "Jumlah Barang"
         << setw(15) << "Total Pembayaran"
         << setw(20) << "Waktu Pembayaran" << endl;
    cout << string(85, '-') << endl;

    // Menampilkan setiap riwayat pembayaran
    for (const auto& pembayaran : riwayat) {
        cout << left << setw(5) << pembayaran.id
             << setw(30) << pembayaran.nama
             << setw(15) << pembayaran.jumlahBarang
             << setw(15) << pembayaran.total
             << setw(20) << pembayaran.waktuPembayaran << endl;
    }

    int pilihanMenu1;
    do
    {
        cout << "\n1. Kembali ke Menu Utama" << endl;
        cout << "Masukkan pilihan: ";
        cin >> pilihanMenu1;

        if (pilihanMenu1 != 1)
        {
            cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
        }
    } while (pilihanMenu1 != 1);
}

void tampilkanDetailRiwayatPembayaran(const vector<RiwayatPembayaran>& riwayat) {
    if (riwayat.empty()) {
        cout << "Tidak ada riwayat pembayaran untuk ditampilkan." << endl;
        return;
    }

    cout << "Masukkan ID riwayat pembayaran yang ingin ditampilkan: ";
    int index;
    cin >> index;
    index -= 1;

    if (index < 0 || index >= riwayat.size()) {
        cout << "ID tidak valid. Silakan coba lagi." << endl;
        return;
    }

    const RiwayatPembayaran& pembayaran = riwayat[index];

    // Membuat hash berdasarkan beberapa atribut
    string hashInput = to_string(pembayaran.id) + pembayaran.nama + pembayaran.waktuPembayaran;
    std::hash<string> hashFunction;
    size_t hashValue = hashFunction(hashInput);

    cout << "ID Pembayaran: " << pembayaran.id << endl;
    cout << "Nama Pembeli: " << pembayaran.nama << endl;
    cout << "Jumlah Barang: " << pembayaran.jumlahBarang << endl;
    cout << "Total Pembayaran: " << pembayaran.total << endl;
    cout << "Waktu Pembayaran: " << pembayaran.waktuPembayaran << endl;
    cout << "Token Transaksi: " << hashValue << endl; // Menampilkan hash transaksi

    cout << "\nDaftar Barang yang Dibeli: " << endl;
    for (const auto& item : pembayaran.barangDibeli) {
        cout << "Produk: " << item.produk.nama
             << " Jumlah: " << item.jumlah
             << " Harga: Rp" << item.produk.harga << endl;
    }

    int pilihanMenu1;
    do {
        cout << "\n1. Kembali ke Menu Utama" << endl;
        cout << "Masukkan pilihan: ";
        cin >> pilihanMenu1;

        if (pilihanMenu1 != 1) {
            cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
        }
    } while (pilihanMenu1 != 1);
}

int main()
{
    vector<Produk> produk = {
        {1, "Smartphone Samsung Galaxy S23", "Elektronik", 12000000},
        {2, "Laptop ASUS ROG Zephyrus G14", "Elektronik", 25000000},
        {3, "TV LED LG 43 Inch", "Elektronik", 6500000},
        {4, "Earbuds Apple AirPods Pro", "Elektronik", 3500000},
        {5, "Kamera DSLR Canon EOS 90D", "Elektronik", 17000000},
        {6, "Sepeda MTB Polygon", "Fitness", 5000000},
        {7, "Dumbbell 5kg", "Fitness", 200000},
        {8, "Matras Yoga", "Fitness", 250000},
        {9, "Mesin Elliptical", "Fitness", 7500000},
        {10, "Resistance Band", "Fitness", 100000},
        {11, "Serum Wajah Vitamin C", "Kecantikan", 150000},
        {12, "Masker Wajah Aloe Vera", "Kecantikan", 75000},
        {13, "Lipstik Matte L'Oreal", "Kecantikan", 120000},
        {14, "Parfum Chanel", "Kecantikan", 2500000},
        {15, "Sabun Cuci Muka Himalaya", "Kecantikan", 35000},
        {16, "Roti Tawar Serba Roti", "Konsumsi", 15000},
        {17, "Kopi Arabica 100g", "Konsumsi", 50000},
        {18, "Mie Instan", "Konsumsi", 5000},
        {19, "Susu UHT Indomilk 1 Liter", "Konsumsi", 18000},
        {20, "Teh Kotak Sosro 500ml", "Konsumsi", 7500}};

    vector<KeranjangItem> keranjang;
    int jumlahKeranjang = 0;
    const int maxKeranjang = 100;
    int biayaPengiriman = 0;
    vector<RiwayatPembayaran> riwayat;
    int indeksPembayaran = 1;

    int pilihan;

    do
    {
        system("cls");
        cout << "\n=== Aplikasi Toko Online Fantastic Five ===" << endl;
        cout << "1. Tampilkan Semua Produk" << endl;
        cout << "2. Menu Sortir Produk" << endl;
        cout << "3. Tambah Produk ke Keranjang Belanja" << endl;
        cout << "4. Mencari Produk Berdasarkan ID" << endl;
        cout << "5. Tampilkan Keranjang Belanja" << endl;
        cout << "6. Menghapus Barang di Keranjang Belanja" << endl;
        cout << "7. Menghitung Biaya Pengiriman Berdasarkan Jarak" << endl;
        cout << "8. Melakukan Pembayaran dan Menyimpan Riwayat Pembayaran" << endl;
        cout << "9. Melihat Riwayat Pembayaran" << endl;
        cout << "10. Melihat Detail Setiap Transaksi pada Riwayat Pembayaran" << endl;
        cout << "0. Keluar" << endl;
        cout << "Masukkan pilihan: ";
        cin >> pilihan;

        switch (pilihan)
        {
        case 1:
            system("cls");
            menuTampilkanProduk(produk);
            break;
        case 2:
            system("cls");
            menuSortirProduk(produk);
            break;
        case 3:
            system("cls");
            tambahKeKeranjang(produk, keranjang, jumlahKeranjang, maxKeranjang);
            break;
        case 4:
            system("cls");
            cariProdukByID(produk);
            break;
        case 5:
            system("cls");
            tampilkanKeranjang(keranjang);
            break;
        case 6:
            system("cls");
            hapusDariKeranjang(keranjang);
            break;
        case 7:
            system("cls");
            biayaPengiriman = hitungBiayaPengiriman(biayaPengiriman);
            break;
        case 8:
            system("cls");
            prosesPembayaran(keranjang, riwayat, biayaPengiriman, indeksPembayaran);
            break;
        case 9:
            system("cls");
            if (riwayat.empty()) {
                cout << "Tidak ada riwayat pembayaran." << endl;
                cin.ignore();
                cin.get();    
            } else {
                tampilkanRiwayatPembayaran(riwayat);
            }

            break;
        case 10:
            system("cls");
            if (riwayat.empty()) {
                cout << "Tidak ada riwayat pembayaran." << endl;
                cin.ignore(); 
                cin.get();  
                tampilkanDetailRiwayatPembayaran(riwayat); 
            }
        case 0:
            break;
        default:
            cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
            break;
        }
    } while (pilihan != 0);

    return 0;
};