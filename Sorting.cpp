#include "Sorting.h"
#include "utils.h"
#include <iostream>
using namespace std;

string namaAlgoritma(int algo) {
    if (algo == 1) return "Bubble Sort";
    if (algo == 2) return "Selection Sort";
    if (algo == 3) return "Insertion Sort";
    return "Merge Sort";
}

static void tampilAnggota(const vector<Anggota> &v) {
    if (v.empty()) { cout << "Tidak ada data anggota.\n"; return; }
    cetakHeaderAnggota();
    for (const Anggota &a : v) cetakBarisAnggota(a);
    cout << v.size() << " data.\n";
}

static void tampilTugas(const vector<Tugas> &v, const DaftarAnggota &da) {
    if (v.empty()) { cout << "Tidak ada data tugas.\n"; return; }
    cetakHeaderTugas();
    for (const Tugas &t : v) cetakBarisTugas(t, da);
    cout << v.size() << " data.\n";
}

// NIM berupa angka: bandingkan panjangnya dulu, baru isinya (supaya sama dengan membandingkan angka)
static bool nimLebihBesar(const string &a, const string &b) {
    if (a.size() != b.size()) return a.size() > b.size();
    return a > b;
}

// Urutan status: Selesai (3) > Proses (2) > Belum (1)
void menuSorting(const DaftarAnggota &da, const DaftarTugas &dt) {
    while (true) {
        cout << "\n=== SORTING (BESAR KE KECIL) ===\n"
             << "Anggota:\n"
             << "  1. Nama (Z -> A)\n"
             << "  2. NIM (terbesar -> terkecil)\n"
             << "  3. ID (terbesar -> terkecil)\n"
             << "Tugas:\n"
             << "  4. Prioritas (Tinggi -> Rendah)\n"
             << "  5. Status (Selesai -> Proses -> Belum)\n"
             << "  6. Deadline (terbaru -> terlama)\n"
             << "  7. Judul (Z -> A)\n"
             << "  8. ID (terbesar -> terkecil)\n"
             << "0. Kembali\n";
        int p = bacaInt("Pilih: ", 0, 8);
        if (p == 0) return;

        int algo = bacaIntOpsional("Algoritma (1=Bubble 2=Selection 3=Insertion 4=Merge) [1, Enter=Bubble]: ", 1, 4, 1);
        cout << "Diurutkan dengan " << namaAlgoritma(algo) << ":\n";

        if (p <= 3) {
            vector<Anggota> v = da.keVector();
            if (p == 1)
                urutkan(v, algo, [](const Anggota &a, const Anggota &b) { return toLower(a.nama) > toLower(b.nama); });
            else if (p == 2)
                urutkan(v, algo, [](const Anggota &a, const Anggota &b) { return nimLebihBesar(a.nim, b.nim); });
            else
                urutkan(v, algo, [](const Anggota &a, const Anggota &b) { return a.id > b.id; });
            tampilAnggota(v);
        } else {
            vector<Tugas> v = dt.keVector();
            if (p == 4)
                urutkan(v, algo, [](const Tugas &a, const Tugas &b) { return a.prioritas > b.prioritas; });
            else if (p == 5)
                urutkan(v, algo, [](const Tugas &a, const Tugas &b) {
                    return kodeDariStatus(a.status) > kodeDariStatus(b.status);
                });
            else if (p == 6)
                urutkan(v, algo, [](const Tugas &a, const Tugas &b) { return a.deadline > b.deadline; });
            else if (p == 7)
                urutkan(v, algo, [](const Tugas &a, const Tugas &b) { return toLower(a.judul) > toLower(b.judul); });
            else
                urutkan(v, algo, [](const Tugas &a, const Tugas &b) { return a.id > b.id; });
            tampilTugas(v, da);
        }
    }
}