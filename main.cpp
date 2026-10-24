#include <iostream>
#include "common.h"
#include "utils.h"
#include "anggota.h"
#include "tugas.h"
#include "riwayat.h"
#include "search_sort.h"
using namespace std;

// Data contoh supaya program langsung bisa dicoba
static void isiDataContoh(DaftarAnggota &da, DaftarTugas &dt) {
    da.tambah("Budi Santoso", "Ketua Panitia", "081111111111", true);
    da.tambah("Citra Lestari", "Sekretaris", "082222222222", true);
    da.tambah("Dimas Pratama", "Divisi Acara", "083333333333", false);
    da.tambah("Eka Putri", "Divisi Humas", "084444444444", true);
    dt.tambah("Booking aula", 1, "2026-11-10", 1, "Proses");
    dt.tambah("Buat proposal sponsor", 2, "2026-11-05", 1, "Belum");
    dt.tambah("Desain poster", 4, "2026-11-15", 2, "Belum");
    dt.tambah("Pesan konsumsi", 3, "2026-11-20", 3, "Belum");
}

static void dashboard(const DaftarAnggota &da, const DaftarTugas &dt, const Queue<int> &antrean, const Riwayat &rw) {
    int belum = 0, proses = 0, selesai = 0;
    for (const Tugas &t : dt.keVector()) {
        if (t.status == "Belum") belum++;
        else if (t.status == "Proses") proses++;
        else selesai++;
    }
    cout << "\n==============================================\n"
         << "   SISTEM MANAJEMEN TUGAS KEPANITIAAN\n"
         << "==============================================\n"
         << " Anggota: " << da.ukuran() << " | Tugas: " << dt.ukuran()
         << " (Belum " << belum << ", Proses " << proses << ", Selesai " << selesai << ")\n"
         << " Antrean: " << antrean.ukuran() << " | Riwayat: " << rw.jumlah() << " aksi\n";
}

int main() {
    DaftarAnggota anggota;
    DaftarTugas tugas;
    Queue<int> antrean;      // menyimpan ID tugas
    Riwayat riwayat;

    isiDataContoh(anggota, tugas);

    while (true) {
        dashboard(anggota, tugas, antrean, riwayat);
        cout << "1. Manajemen Anggota\n"
             << "2. Manajemen Tugas\n"
             << "3. Antrean Tugas\n"
             << "4. Pencarian, Sorting & Filter\n"
             << "5. Riwayat & Undo\n"
             << "0. Keluar\n";
        int p = bacaInt("Pilih menu: ", 0, 5);
        if (p == 0) break;
        if (p == 1) menuAnggota(anggota);
        else if (p == 2) menuTugas(tugas, anggota, riwayat, antrean);
        else if (p == 3) menuAntrean(antrean, tugas, anggota, riwayat);
        else if (p == 4) menuCariSortFilter(anggota, tugas);
        else if (p == 5) menuRiwayat(riwayat, tugas, anggota, antrean);
    }
    cout << "Terima kasih. Program selesai.\n";
    return 0;
}
