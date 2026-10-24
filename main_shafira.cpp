// Program uji modul Searching & Sorting (Shafira)
#include <iostream>
#include "Anggota.h"
#include "Tugas.h"
#include "Searching.h"
#include "Sorting.h"
#include "DataContoh.h"
#include "utils.h"
using namespace std;

int main() {
    DaftarAnggota anggota;
    DaftarTugas tugas;
    isiAnggotaContoh(anggota);
    isiTugasContoh(tugas);

    while (true) {
        cout << "\n=== UJI SEARCHING & SORTING ===\n"
             << "1. Pencarian & Filter\n"
             << "2. Sorting (besar ke kecil)\n"
             << "0. Keluar\n";
        int p = bacaInt("Pilih: ", 0, 2);
        if (p == 0) break;
        if (p == 1) menuPencarianFilter(anggota, tugas);
        else menuSorting(anggota, tugas);
    }
    return 0;
}