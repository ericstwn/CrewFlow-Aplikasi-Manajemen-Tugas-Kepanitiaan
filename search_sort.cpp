#include "search_sort.h"
#include "utils.h"
#include <iostream>
using namespace std;

string namaAlgoritma(int algo) {
    if (algo == 1) return "Bubble Sort";
    if (algo == 2) return "Selection Sort";
    if (algo == 3) return "Insertion Sort";
    return "Merge Sort";
}

static bool mengandung(const string &teks, const string &kunci) {
    return toLower(teks).find(toLower(kunci)) != string::npos;
}

static void tampilAnggota(const vector<Anggota> &v) {
    if (v.empty()) { cout << "Tidak ada data yang cocok.\n"; return; }
    cetakHeaderAnggota();
    for (const Anggota &a : v) cetakBarisAnggota(a);
    cout << v.size() << " data.\n";
}

static void tampilTugas(const vector<Tugas> &v, const DaftarAnggota &da) {
    if (v.empty()) { cout << "Tidak ada data yang cocok.\n"; return; }
    cetakHeaderTugas();
    for (const Tugas &t : v) cetakBarisTugas(t, da);
    cout << v.size() << " data.\n";
}

// ---------- Pencarian ----------

static void menuPencarian(const DaftarAnggota &da, const DaftarTugas &dt) {
    while (true) {
        cout << "\n--- PENCARIAN ---\n"
             << "1. Cari anggota berdasarkan nama (Linear Search)\n"
             << "2. Cari anggota berdasarkan ID (Binary Search)\n"
             << "3. Cari tugas berdasarkan judul (Linear Search)\n"
             << "4. Cari tugas berdasarkan ID (Binary Search)\n"
             << "0. Kembali\n";
        int p = bacaInt("Pilih: ", 0, 4);
        if (p == 0) return;

        vector<Anggota> va = da.keVector();
        vector<Tugas> vt = dt.keVector();

        if (p == 1) {
            string kunci = bacaString("Kata kunci nama: ");
            vector<int> idx = linearSearch(va, [&](const Anggota &a) { return mengandung(a.nama, kunci); });
            vector<Anggota> hasil;
            for (int i : idx) hasil.push_back(va[i]);
            tampilAnggota(hasil);

        } else if (p == 2) {
            int id = bacaInt("ID anggota: ", 1, 1000000);
            mergeSort(va, [](const Anggota &a, const Anggota &b) { return a.id < b.id; });  // syarat binary search
            int i = binarySearchId(va, id);
            if (i < 0) cout << "Anggota dengan ID " << id << " tidak ditemukan.\n";
            else tampilAnggota({va[i]});

        } else if (p == 3) {
            string kunci = bacaString("Kata kunci judul: ");
            vector<int> idx = linearSearch(vt, [&](const Tugas &t) { return mengandung(t.judul, kunci); });
            vector<Tugas> hasil;
            for (int i : idx) hasil.push_back(vt[i]);
            tampilTugas(hasil, da);

        } else if (p == 4) {
            int id = bacaInt("ID tugas: ", 1, 1000000);
            mergeSort(vt, [](const Tugas &a, const Tugas &b) { return a.id < b.id; });
            int i = binarySearchId(vt, id);
            if (i < 0) cout << "Tugas dengan ID " << id << " tidak ditemukan.\n";
            else tampilTugas({vt[i]}, da);
        }
    }
}

// ---------- Sorting ----------

static void menuSorting(const DaftarAnggota &da, const DaftarTugas &dt) {
    while (true) {
        cout << "\n--- SORTING ---\n"
             << "Anggota:\n  1. Nama A-Z\n  2. Nama Z-A\n  3. ID\n"
             << "Tugas:\n  4. Prioritas (Tinggi dulu)\n  5. Deadline (terdekat dulu)\n"
             << "  6. Status (Belum > Proses > Selesai)\n  7. Judul A-Z\n"
             << "0. Kembali\n";
        int p = bacaInt("Pilih: ", 0, 7);
        if (p == 0) return;

        int algo = bacaInt("Algoritma (1=Bubble 2=Selection 3=Insertion 4=Merge): ", 1, 4);
        cout << "Diurutkan dengan " << namaAlgoritma(algo) << ":\n";

        if (p <= 3) {
            vector<Anggota> v = da.keVector();
            if (p == 1)
                urutkan(v, algo, [](const Anggota &a, const Anggota &b) { return toLower(a.nama) < toLower(b.nama); });
            else if (p == 2)
                urutkan(v, algo, [](const Anggota &a, const Anggota &b) { return toLower(a.nama) > toLower(b.nama); });
            else
                urutkan(v, algo, [](const Anggota &a, const Anggota &b) { return a.id < b.id; });
            tampilAnggota(v);
        } else {
            vector<Tugas> v = dt.keVector();
            if (p == 4)
                urutkan(v, algo, [](const Tugas &a, const Tugas &b) { return a.prioritas < b.prioritas; });
            else if (p == 5)
                urutkan(v, algo, [](const Tugas &a, const Tugas &b) { return a.deadline < b.deadline; });
            else if (p == 6)
                urutkan(v, algo, [](const Tugas &a, const Tugas &b) {
                    return kodeDariStatus(a.status) < kodeDariStatus(b.status);
                });
            else
                urutkan(v, algo, [](const Tugas &a, const Tugas &b) { return toLower(a.judul) < toLower(b.judul); });
            tampilTugas(v, da);
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
            int pr = bacaInt("Prioritas (1=Tinggi 2=Sedang 3=Rendah): ", 1, 3);
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

void menuCariSortFilter(const DaftarAnggota &da, const DaftarTugas &dt) {
    while (true) {
        cout << "\n=== PENCARIAN, SORTING & FILTER ===\n"
             << "1. Pencarian\n2. Sorting\n3. Filter\n0. Kembali\n";
        int p = bacaInt("Pilih: ", 0, 3);
        if (p == 0) return;
        if (p == 1) menuPencarian(da, dt);
        else if (p == 2) menuSorting(da, dt);
        else menuFilter(da, dt);
    }
}
