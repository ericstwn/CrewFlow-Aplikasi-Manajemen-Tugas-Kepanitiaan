#include "Searching.h"
#include "Sorting.h"     // bubbleSort dipakai untuk mengurutkan data sebelum Binary Search
#include "utils.h"
#include <iostream>
using namespace std;

static bool mengandung(const string &teks, const string &kunci) {
    return toLower(teks).find(toLower(kunci)) != string::npos;
}

static void tampilAnggota(const vector<Anggota> &v) {
    if (v.empty()) { cout << "Data tidak ditemukan.\n"; return; }
    cetakHeaderAnggota();
    for (const Anggota &a : v) cetakBarisAnggota(a);
    cout << v.size() << " data ditemukan.\n";
}

static void tampilTugas(const vector<Tugas> &v, const DaftarAnggota &da) {
    if (v.empty()) { cout << "Data tidak ditemukan.\n"; return; }
    cetakHeaderTugas();
    for (const Tugas &t : v) cetakBarisTugas(t, da);
    cout << v.size() << " data ditemukan.\n";
}

// ---------- Pencarian ----------

static void menuPencarian(const DaftarAnggota &da, const DaftarTugas &dt) {
    while (true) {
        cout << "\n--- PENCARIAN ---\n"
             << "1. Cari anggota berdasarkan NIM (Linear Search)\n"
             << "2. Cari anggota berdasarkan nama (Linear Search)\n"
             << "3. Cari anggota berdasarkan ID (Binary Search)\n"
             << "4. Cari tugas berdasarkan ID (Binary Search)\n"
             << "5. Cari tugas berdasarkan nama/judul (Linear Search)\n"
             << "0. Kembali\n";
        int p = bacaInt("Pilih: ", 0, 5);
        if (p == 0) return;

        vector<Anggota> va = da.keVector();
        vector<Tugas> vt = dt.keVector();

        if (p == 1) {
            string kunci = bacaString("NIM (boleh sebagian): ");
            vector<int> idx = linearSearch(va, [&](const Anggota &a) { return mengandung(a.nim, kunci); });
            vector<Anggota> hasil;
            for (int i : idx) hasil.push_back(va[i]);
            tampilAnggota(hasil);

        } else if (p == 2) {
            string kunci = bacaString("Nama (boleh sebagian): ");
            vector<int> idx = linearSearch(va, [&](const Anggota &a) { return mengandung(a.nama, kunci); });
            vector<Anggota> hasil;
            for (int i : idx) hasil.push_back(va[i]);
            tampilAnggota(hasil);

        } else if (p == 3) {
            int id = bacaInt("ID anggota: ", 1, 1000000);
            bubbleSort(va, [](const Anggota &a, const Anggota &b) { return a.id < b.id; });  // syarat Binary Search
            int i = binarySearchId(va, id);
            if (i < 0) cout << "Anggota dengan ID " << id << " tidak ditemukan.\n";
            else tampilAnggota({va[i]});

        } else if (p == 4) {
            int id = bacaInt("ID tugas: ", 1, 1000000);
            bubbleSort(vt, [](const Tugas &a, const Tugas &b) { return a.id < b.id; });
            int i = binarySearchId(vt, id);
            if (i < 0) cout << "Tugas dengan ID " << id << " tidak ditemukan.\n";
            else tampilTugas({vt[i]}, da);

        } else if (p == 5) {
            string kunci = bacaString("Nama/judul tugas (boleh sebagian): ");
            vector<int> idx = linearSearch(vt, [&](const Tugas &t) { return mengandung(t.judul, kunci); });
            vector<Tugas> hasil;
            for (int i : idx) hasil.push_back(vt[i]);
            tampilTugas(hasil, da);
        }
    }
}

// ---------- Filter ----------

static void menuFilter(const DaftarAnggota &da, const DaftarTugas &dt) {
    while (true) {
        cout << "\n--- FILTER ---\n"
             << "1. Tugas berdasarkan status\n"
             << "2. Tugas berdasarkan prioritas\n"
             << "3. Tugas berdasarkan penanggung jawab\n"
             << "4. Anggota yang tersedia\n"
             << "5. Anggota yang tidak tersedia\n"
             << "0. Kembali\n";
        int p = bacaInt("Pilih: ", 0, 5);
        if (p == 0) return;

        if (p == 1) {
            string st = statusDariKode(bacaInt("Status (1=Belum 2=Proses 3=Selesai): ", 1, 3));
            tampilTugas(saring(dt.keVector(), [&](const Tugas &t) { return t.status == st; }), da);
        } else if (p == 2) {
            int pr = bacaInt("Prioritas (3=Tinggi 2=Sedang 1=Rendah): ", 1, 3);
            tampilTugas(saring(dt.keVector(), [&](const Tugas &t) { return t.prioritas == pr; }), da);
        } else if (p == 3) {
            da.tampilSemua();
            int id = bacaInt("ID penanggung jawab: ", 1, 1000000);
            tampilTugas(saring(dt.keVector(), [&](const Tugas &t) { return t.idPJ == id; }), da);
        } else if (p == 4) {
            tampilAnggota(saring(da.keVector(), [](const Anggota &a) { return a.tersedia; }));
        } else if (p == 5) {
            tampilAnggota(saring(da.keVector(), [](const Anggota &a) { return !a.tersedia; }));
        }
    }
}

void menuPencarianFilter(const DaftarAnggota &da, const DaftarTugas &dt) {
    while (true) {
        cout << "\n=== PENCARIAN & FILTER ===\n1. Pencarian\n2. Filter\n0. Kembali\n";
        int p = bacaInt("Pilih: ", 0, 2);
        if (p == 0) return;
        if (p == 1) menuPencarian(da, dt);
        else menuFilter(da, dt);
    }
}