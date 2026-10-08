#include "stack.h"
#include <iostream>
#include <iomanip>
using namespace std;

void createStack(Stack &S) {
    S.top = nullptr;
    S.jumlah = 0;
}

bool isEmptyStack(const Stack &S) {
    return S.top == nullptr;
}

void push(Stack &S, const Tugas &t) {
    NodeStack* baru = new NodeStack;
    baru->data = t;
    baru->next = S.top;  
    S.top = baru;        
    S.jumlah++;
}

bool pop(Stack &S, Tugas &hasil) {
    if (isEmptyStack(S)) return false;

    NodeStack* hapus = S.top;
    hasil = hapus->data;
    S.top = hapus->next;
    delete hapus;
    S.jumlah--;
    return true;
}

bool peek(const Stack &S, Tugas &hasil) {
    if (isEmptyStack(S)) return false;
    hasil = S.top->data;
    return true;
}

int jumlahStack(const Stack &S) {
    return S.jumlah;
}

void tampilkanRecycleBin(const Stack &S) {
    if (isEmptyStack(S)) {
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
    return pop(S, dummy);   
}

void kosongkanStack(Stack &S) {
    while (!isEmptyStack(S)) {
        NodeStack* hapus = S.top;
        S.top = hapus->next;
        delete hapus;
    }
    S.jumlah = 0;
}