#include <bits/stdc++.h>
using namespace std;

// Struktur produk
struct Produk
{
    int id;
    string nama;
    string kategori;
    int harga;
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

    int pilihan;

    do
    {
        system("cls");
        cout << "\n=== Aplikasi Toko Online Fantastic Five ===" << endl;
        cout << "1. Tampilkan Semua Produk" << endl;
        cout << "2. Menu Sortir Produk" << endl;
        cout << "3. Tambah Produk ke Keranjang" << endl;
        cout << "4. Mencari Produk Berdasarkan ID" << endl;
        cout << "5. Tampilkan Keranjang Belanja" << endl;
        cout << "6. Menghapus Barang di Keranjang" << endl;
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
        case 0:
            break;
        default:
            cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
            break;
        }
    } while (pilihan != 0);

    return 0;
}
