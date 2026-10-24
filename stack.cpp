#include "stack.h"
#include <iostream>
#include <iomanip>
using namespace std;

void createStack(Stack &S) {
    S.top = nullptr;
    S.jumlah = 0;
}

bool isEmpty(const Stack &S) {
    return S.top == nullptr;
}

void push(Stack &S, const Tugas &t) {
    NodeStack* baru = new NodeStack;
    baru->data = t;
    baru->next = S.top;   // node baru menunjuk ke top lama
    S.top = baru;         // top pindah ke node baru
    S.jumlah++;
}

bool pop(Stack &S, Tugas &hasil) {
    if (isEmpty(S)) return false;

    NodeStack* hapus = S.top;
    hasil = hapus->data;
    S.top = hapus->next;
    delete hapus;
    S.jumlah--;
    return true;
}

bool peek(const Stack &S, Tugas &hasil) {
    if (isEmpty(S)) return false;
    hasil = S.top->data;
    return true;
}

int jumlahStack(const Stack &S) {
    return S.jumlah;
}

// UNDO: ambil tugas terakhir yang dihapus dari Recycle Bin.
// Memasukkannya kembali ke daftar tugas (DLL) dilakukan di main.cpp
// memakai fungsi tambah tugas milik Aqilah.
bool undoHapus(Stack &S, Tugas &hasil) {
    if (!pop(S, hasil)) {
        cout << "Tidak ada tugas yang bisa dipulihkan.\n";
        return false;
    }
    cout << "Tugas \"" << hasil.nama << "\" berhasil dipulihkan.\n";
    return true;
}

void tampilkanRecycleBin(const Stack &S) {
    if (isEmpty(S)) {
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

    NodeStack* bantu = S.top;
    int no = 1;
    while (bantu != nullptr) {
        cout << left << setw(5)  << no++
             << setw(8)  << bantu->data.id
             << setw(22) << bantu->data.nama
             << setw(16) << bantu->data.penanggungJawab
             << setw(14) << bantu->data.divisi
             << setw(13) << bantu->data.deadline
             << bantu->data.status << "\n";
        bantu = bantu->next;
    }
    cout << string(90, '-') << "\n";
    cout << "Total di Recycle Bin: " << S.jumlah << "\n";
}

bool hapusPermanenTeratas(Stack &S) {
    Tugas dummy;
    return pop(S, dummy);   // pop lalu datanya dibuang
}

void kosongkanStack(Stack &S) {
    while (!isEmpty(S)) {
        NodeStack* hapus = S.top;
        S.top = hapus->next;
        delete hapus;
    }
    S.jumlah = 0;
}