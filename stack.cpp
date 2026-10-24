#include "stack.h"
#include <iostream>
#include <iomanip>
using namespace std;

const char* namaJenisAksi(JenisAksi j) {
    switch (j) {
        case AKSI_TAMBAH: return "TAMBAH";
        case AKSI_EDIT:   return "EDIT";
        case AKSI_HAPUS:  return "HAPUS";
    }
    return "?";
}

// ---------------- Operasi dasar Stack ----------------

void createStack(Stack &S) {
    S.top = nullptr;
    S.jumlah = 0;
}

bool isEmpty(const Stack &S) {
    return S.top == nullptr;
}

void push(Stack &S, const Aksi &a) {
    NodeStack* baru = new NodeStack;
    baru->data = a;
    baru->next = S.top;   // node baru menunjuk ke top lama
    S.top = baru;         // top pindah ke node baru
    S.jumlah++;
}

bool pop(Stack &S, Aksi &hasil) {
    if (isEmpty(S)) return false;

    NodeStack* hapus = S.top;
    hasil = hapus->data;
    S.top = hapus->next;
    delete hapus;
    S.jumlah--;
    return true;
}

bool peek(const Stack &S, Aksi &hasil) {
    if (isEmpty(S)) return false;
    hasil = S.top->data;
    return true;
}

int jumlahStack(const Stack &S) {
    return S.jumlah;
}

// ---------------- Mencatat aksi ----------------

void catatTambah(Stack &S, const Tugas &baru) {
    Aksi a;
    a.jenis = AKSI_TAMBAH;
    a.sebelum = Tugas();     // tidak dipakai
    a.sesudah = baru;
    push(S, a);
}

void catatEdit(Stack &S, const Tugas &lama, const Tugas &baru) {
    Aksi a;
    a.jenis = AKSI_EDIT;
    a.sebelum = lama;
    a.sesudah = baru;
    push(S, a);
}

void catatHapus(Stack &S, const Tugas &dihapus) {
    Aksi a;
    a.jenis = AKSI_HAPUS;
    a.sebelum = dihapus;
    a.sesudah = Tugas();     // tidak dipakai
    push(S, a);
}

// ---------------- Undo ----------------
// Mengambil aksi terakhir dari stack. Membalikkannya ke daftar tugas
// dilakukan di main.cpp / menu, memakai fungsi tambah, edit, hapus
// milik Aqilah.
bool undoAksi(Stack &S, Aksi &hasil) {
    if (!pop(S, hasil)) {
        cout << "Tidak ada aksi yang bisa di-undo.\n";
        return false;
    }

    if (hasil.jenis == AKSI_TAMBAH) {
        cout << "Undo TAMBAH: tugas \"" << hasil.sesudah.nama
             << "\" (ID " << hasil.sesudah.id << ") dibatalkan.\n";
    } else if (hasil.jenis == AKSI_EDIT) {
        cout << "Undo EDIT: perubahan tugas \"" << hasil.sebelum.nama
             << "\" (ID " << hasil.sebelum.id << ") dibatalkan.\n";
    } else {
        cout << "Undo HAPUS: tugas \"" << hasil.sebelum.nama
             << "\" (ID " << hasil.sebelum.id << ") dipulihkan.\n";
    }
    return true;
}

// ---------------- Tampilan ----------------

void tampilkanRiwayat(const Stack &S) {
    if (isEmpty(S)) {
        cout << "\nRiwayat kosong.\n";
        return;
    }

    cout << "\n=== RIWAYAT AKSI (terbaru di atas) ===\n";
    cout << left << setw(5)  << "No"
         << setw(9)  << "Aksi"
         << setw(8)  << "ID"
         << setw(24) << "Nama Tugas"
         << "Keterangan\n";
    cout << string(80, '-') << "\n";

    NodeStack* bantu = S.top;
    int no = 1;
    while (bantu != nullptr) {
        const Aksi &a = bantu->data;
        // TAMBAH memakai data "sesudah", EDIT & HAPUS memakai "sebelum"
        const Tugas &t = (a.jenis == AKSI_TAMBAH) ? a.sesudah : a.sebelum;

        string ket;
        if (a.jenis == AKSI_TAMBAH)     ket = "Tugas ditambahkan";
        else if (a.jenis == AKSI_HAPUS) ket = "Tugas dihapus";
        else if (a.sebelum.status != a.sesudah.status)
            ket = "Status: " + a.sebelum.status + " -> " + a.sesudah.status;
        else
            ket = "Data tugas diubah";

        cout << left << setw(5)  << no++
             << setw(9)  << namaJenisAksi(a.jenis)
             << setw(8)  << t.id
             << setw(24) << t.nama
             << ket << "\n";
        bantu = bantu->next;
    }
    cout << string(80, '-') << "\n";
    cout << "Total riwayat: " << S.jumlah << " aksi\n";
}

// Recycle Bin = tampilan khusus aksi HAPUS saja (tidak mengubah stack)
void tampilkanRecycleBin(const Stack &S) {
    int total = 0;
    for (NodeStack* b = S.top; b != nullptr; b = b->next)
        if (b->data.jenis == AKSI_HAPUS) total++;

    if (total == 0) {
        cout << "\nRecycle Bin kosong.\n";
        return;
    }

    cout << "\n=== RECYCLE BIN (terbaru dihapus di atas) ===\n";
    cout << left << setw(5)  << "No"
         << setw(8)  << "ID"
         << setw(22) << "Nama Tugas"
         << setw(16) << "PJ"
         << setw(14) << "Divisi"
         << setw(13) << "Deadline"
         << "Status\n";
    cout << string(90, '-') << "\n";

    int no = 1;
    for (NodeStack* b = S.top; b != nullptr; b = b->next) {
        if (b->data.jenis != AKSI_HAPUS) continue;
        const Tugas &t = b->data.sebelum;
        cout << left << setw(5)  << no++
             << setw(8)  << t.id
             << setw(22) << t.nama
             << setw(16) << t.penanggungJawab
             << setw(14) << t.divisi
             << setw(13) << t.deadline
             << t.status << "\n";
    }
    cout << string(90, '-') << "\n";
    cout << "Total di Recycle Bin: " << total << "\n";
}

// ---------------- Pembersihan ----------------

void kosongkanStack(Stack &S) {
    while (!isEmpty(S)) {
        NodeStack* hapus = S.top;
        S.top = hapus->next;
        delete hapus;
    }
    S.jumlah = 0;
}