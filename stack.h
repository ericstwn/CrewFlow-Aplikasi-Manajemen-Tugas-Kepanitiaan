#ifndef STACK_H
#define STACK_H

#include "data.h"

// Modul Stack (LIFO): Recycle Bin & Undo
// Rafi

void createStack(Stack &S);                 // inisialisasi stack kosong
bool isEmpty(const Stack &S);               // true jika stack kosong
void push(Stack &S, const Tugas &t);        // masukkan tugas terhapus ke Recycle Bin
bool pop(Stack &S, Tugas &hasil);           // ambil tugas teratas; false jika kosong
bool peek(const Stack &S, Tugas &hasil);    // lihat tugas teratas tanpa mengambilnya
int  jumlahStack(const Stack &S);           // banyak data di Recycle Bin
bool undoHapus(Stack &S, Tugas &hasil);     // pulihkan tugas yang terakhir dihapus
void tampilkanRecycleBin(const Stack &S);   // tampilkan isi dari yang terbaru dihapus
bool hapusPermanenTeratas(Stack &S);        // buang tugas teratas selamanya
void kosongkanStack(Stack &S);              // kosongkan Recycle Bin (dealokasi memori)

#endif