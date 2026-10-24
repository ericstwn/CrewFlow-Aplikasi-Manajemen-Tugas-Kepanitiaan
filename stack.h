#ifndef STACK_H
#define STACK_H

#include "data.h"


void createStack(Stack &S);                 // inisialisasi stack kosong
bool isEmptyStack(const Stack &S);          // true jika stack kosong
void push(Stack &S, const Tugas &t);        // masukkan tugas terhapus ke Recycle Bin
bool pop(Stack &S, Tugas &hasil);           // ambil tugas teratas (UNDO); false jika kosong
bool peek(const Stack &S, Tugas &hasil);    // lihat tugas teratas tanpa mengambilnya
int  jumlahStack(const Stack &S);           // banyak data di Recycle Bin
void tampilkanRecycleBin(const Stack &S);   // tampilkan isi dari yang terbaru dihapus
bool hapusPermanenTeratas(Stack &S);        // buang tugas teratas selamanya
void kosongkanStack(Stack &S);              // kosongkan Recycle Bin (dealokasi memori)

#endif