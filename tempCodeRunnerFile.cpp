// Fungsi untuk menyimpan riwayat pembayaran
void simpanRiwayatPembayaran(vector<RiwayatPembayaran>& riwayat, int id, const string& nama, const vector<KeranjangItem>& barangDibeli, int total, const string& waktuPembayaran) {
    // Membuat riwayat baru dan menyimpannya ke dalam vector riwayat
    RiwayatPembayaran riwayatBaru = {id, nama, static_cast<int>(barangDibeli.size()), total, waktuPembayaran, barangDibeli};
    riwayat.push_back(riwayatBaru);
}

// Fungsi untuk melakukan pembayaran
void prosesPembayaran(vector<KeranjangItem> &keranjang, vector<RiwayatPembayaran> &riwayat, int biayaPengiriman) {
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

    // Menampilkan informasi produk dalam keranjang dan menghitung total
    for (const auto& item : keranjang) {
        int subtotal = item.produk.harga * item.jumlah;
        totalPembayaran += subtotal;

        cout << left << setw(5) << item.produk.id
             << setw(30) << item.produk.nama
             << setw(15) << item.jumlah
             << setw(15) << subtotal << endl;
    }

    // Menambahkan biaya pengiriman ke total pembayaran
    totalPembayaran += biayaPengiriman;
    cout << right << setw(50) << "Biaya Pengiriman: Rp" << biayaPengiriman << endl;
    cout << right << setw(50) << "Total Pembayaran: Rp" << totalPembayaran << endl;
    cout << string(65, '-') << endl;

    // Proses pembayaran
    int pilihan;
    cout << "\n1. Bayar" << endl;
    cout << "2. Kembali ke menu utama" << endl;
    cout << "Masukkan pilihan: ";
    cin >> pilihan;

    if (pilihan == 1) {
        // Mendapatkan waktu saat ini
        time_t sekarang = time(0);
        char* dt = ctime(&sekarang);
        string waktuPembayaran = dt;

        // Menyimpan riwayat pembayaran dan menghitung ulang total pembayaran
        simpanRiwayatPembayaran(riwayat, 1, "Nama Pembeli", keranjang, totalPembayaran, waktuPembayaran);

        cout << "\nPembayaran berhasil! Total Pembayaran: Rp" << totalPembayaran + biayaPengiriman << endl;

        // Hapus produk dari keranjang setelah pembayaran berhasil
        keranjang.clear();

        // Pilihan untuk kembali ke menu utama setelah pembayaran
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
    cout << left << setw(5) << "ID"
         << setw(30) << "Nama"
         << setw(15) << "Jumlah Barang"
         << setw(15) << "Total Pembayaran"
         << setw(20) << "Waktu Pembayaran" << endl;
    cout << string(85, '-') << endl;

    for (const auto& item : riwayat) {
        cout << left << setw(5) << item.id
             << setw(30) << item.nama
             << setw(15) << item.jumlahBarang
             << setw(15) << item.total
             << setw(20) << item.waktuPembayaran << endl;
    }
}


// Fungsi untuk menampilkan detail riwayat pembayaran
void tampilkanDetailRiwayatPembayaran(const vector<RiwayatPembayaran>& riwayat) {
    int index;
    cout << "Masukkan index riwayat pembayaran yang ingin ditampilkan: ";
    cin >> index;

    if (index >= 0 && index < riwayat.size()) {
        const RiwayatPembayaran& pembayaran = riwayat[index];
        cout << "ID Pembayaran: " << pembayaran.id << endl;
        cout << "Nama Pembeli: " << pembayaran.nama << endl;
        cout << "Jumlah Barang: " << pembayaran.jumlahBarang << endl;
        cout << "Total Pembayaran: " << pembayaran.total << endl;
        cout << "Waktu Pembayaran: " << pembayaran.waktuPembayaran << endl;

        cout << "\nDaftar Barang yang Dibeli: " << endl;
        for (const auto& item : pembayaran.barangDibeli) {
            cout << "Produk: " << item.produk.nama
                 << " Jumlah: " << item.jumlah
                 << " Harga: Rp" << item.produk.harga << endl;
        }
    } else {
        cout << "Index riwayat tidak valid." << endl;
    }
}