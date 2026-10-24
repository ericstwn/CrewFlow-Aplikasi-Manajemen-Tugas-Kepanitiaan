// Unit test modul Stack: operasi dasar + Undo tambah/edit/hapus
// Kompilasi: g++ teststack.cpp stack.cpp -o teststack
// Syarat   : data.h, stack.h, stack.cpp berada di folder yang sama
//
// Daftar tugas ASLI milik Aqilah (DLL) belum ada, jadi di sini dipakai
// vector<Tugas> sebagai "daftar tugas tiruan". Fungsi undoDB() juga
// bisa jadi contoh cara membalikkan aksi di menu nanti.
#include <iostream>
#include <vector>
#include <cassert>
#include "stack.h"
using namespace std;

Tugas buatTugas(int id, string nama) {
    Tugas t;
    t.id = id;
    t.nama = nama;
    t.penanggungJawab = "Budi";
    t.divisi = "Acara";
    t.deadline = "01-11-2026";
    t.prioritas = PRIORITAS_SEDANG;
    t.deskripsi = "-";
    t.status = STATUS_PENDING;
    return t;
}

// ---------- daftar tugas tiruan ----------
int cariIndex(const vector<Tugas> &db, int id) {
    for (size_t i = 0; i < db.size(); i++)
        if (db[i].id == id) return (int)i;
    return -1;
}

void tambahDB(vector<Tugas> &db, Stack &S, const Tugas &t) {
    db.push_back(t);
    catatTambah(S, t);
}

void editDB(vector<Tugas> &db, Stack &S, int id, const Tugas &baru) {
    int i = cariIndex(db, id);
    assert(i >= 0);
    Tugas lama = db[i];
    db[i] = baru;
    catatEdit(S, lama, baru);
}

void hapusDB(vector<Tugas> &db, Stack &S, int id) {
    int i = cariIndex(db, id);
    assert(i >= 0);
    Tugas t = db[i];
    db.erase(db.begin() + i);
    catatHapus(S, t);
}

// Membalikkan aksi terakhir (inilah yang nanti dilakukan menu Undo)
bool undoDB(vector<Tugas> &db, Stack &S) {
    Aksi a;
    if (!undoAksi(S, a)) return false;
    switch (a.jenis) {
        case AKSI_TAMBAH: {
            int i = cariIndex(db, a.sesudah.id);
            assert(i >= 0);
            db.erase(db.begin() + i);
            break;
        }
        case AKSI_EDIT: {
            int i = cariIndex(db, a.sebelum.id);
            assert(i >= 0);
            db[i] = a.sebelum;
            break;
        }
        case AKSI_HAPUS:
            db.push_back(a.sebelum);
            break;
    }
    return true;
}

int main() {
    Stack S;
    vector<Tugas> db;
    Aksi a;

    // --- 1. Operasi dasar pada stack kosong ---
    cout << "[1] Stack kosong\n";
    createStack(S);
    assert(isEmpty(S) && jumlahStack(S) == 0);
    assert(!pop(S, a));
    assert(!peek(S, a));
    assert(!undoDB(db, S));            // Undo saat kosong aman
    tampilkanRiwayat(S);
    tampilkanRecycleBin(S);

    // --- 2. push / peek / pop (LIFO) ---
    cout << "\n[2] push, peek, pop (LIFO)\n";
    catatTambah(S, buatTugas(1, "A"));
    catatTambah(S, buatTugas(2, "B"));
    assert(!isEmpty(S) && jumlahStack(S) == 2);
    assert(peek(S, a) && a.sesudah.id == 2 && jumlahStack(S) == 2);
    assert(pop(S, a) && a.sesudah.id == 2);
    assert(pop(S, a) && a.sesudah.id == 1);
    assert(isEmpty(S));

    // --- 3. Tambah 3 tugas ---
    cout << "\n[3] Tambah 3 tugas\n";
    tambahDB(db, S, buatTugas(101, "Booking Venue"));
    tambahDB(db, S, buatTugas(102, "Cetak Poster"));
    tambahDB(db, S, buatTugas(103, "Sewa Sound"));
    assert(jumlahStack(S) == 3 && db.size() == 3);

    // --- 4. Edit status & hapus ---
    cout << "\n[4] Edit status tugas 102, hapus tugas 101\n";
    Tugas baru = db[cariIndex(db, 102)];
    baru.status = STATUS_DONE;
    editDB(db, S, 102, baru);
    hapusDB(db, S, 101);
    assert(jumlahStack(S) == 5 && db.size() == 2);
    assert(cariIndex(db, 101) == -1);
    assert(db[cariIndex(db, 102)].status == STATUS_DONE);
    tampilkanRiwayat(S);
    tampilkanRecycleBin(S);

    // --- 5. Peek aksi terakhir ---
    cout << "\n[5] Lihat aksi terakhir\n";
    assert(peek(S, a) && a.jenis == AKSI_HAPUS && a.sebelum.id == 101);
    assert(jumlahStack(S) == 5);

    // --- 6. Undo HAPUS ---
    cout << "\n[6] Undo hapus\n";
    assert(undoDB(db, S));
    int i101 = cariIndex(db, 101);
    assert(i101 >= 0);
    assert(db[i101].nama == "Booking Venue" && db[i101].penanggungJawab == "Budi");
    assert(db[i101].deadline == "01-11-2026" && db[i101].status == STATUS_PENDING);
    assert(db.size() == 3 && jumlahStack(S) == 4);

    // --- 7. Undo EDIT ---
    cout << "\n[7] Undo edit\n";
    assert(undoDB(db, S));
    assert(db[cariIndex(db, 102)].status == STATUS_PENDING);
    assert(jumlahStack(S) == 3);

    // --- 8. Undo TAMBAH x3 ---
    cout << "\n[8] Undo tambah (3 kali)\n";
    assert(undoDB(db, S));
    assert(cariIndex(db, 103) == -1);
    assert(undoDB(db, S));
    assert(undoDB(db, S));
    assert(db.empty() && isEmpty(S));
    assert(!undoDB(db, S));

    // --- 9. Kosongkan & pakai lagi ---
    cout << "\n[9] Kosongkan lalu dipakai lagi\n";
    tambahDB(db, S, buatTugas(104, "Konsumsi"));
    tambahDB(db, S, buatTugas(105, "Dokumentasi"));
    kosongkanStack(S);
    assert(isEmpty(S) && jumlahStack(S) == 0);
    tambahDB(db, S, buatTugas(106, "Pendaftaran"));
    assert(jumlahStack(S) == 1);
    tampilkanRiwayat(S);
    kosongkanStack(S);

    cout << "\nSemua tes Stack & Undo LULUS.\n";
    return 0;
}