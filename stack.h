#ifndef STACK_H
#define STACK_H

#include "data.h"

// ================================================================
//  Modul Stack (LIFO): Riwayat Aksi, Recycle Bin & Undo
//  Penanggung jawab: Rafi
//
//  Setiap aksi pada tugas dicatat ke stack. Undo mengambil aksi
//  TERAKHIR, lalu pemanggil (menu) membalikkannya ke daftar tugas:
//
//    AKSI_TAMBAH -> undo: HAPUS tugas  aksi.sesudah.id dari daftar
//    AKSI_EDIT   -> undo: KEMBALIKAN tugas ke data aksi.sebelum
//    AKSI_HAPUS  -> undo: TAMBAH KEMBALI tugas aksi.sebelum
//
//  Modul ini tidak menyentuh daftar tugas (DLL milik Aqilah),
//  sehingga bisa diuji sendiri.
// ================================================================

// ---- Operasi dasar Stack ----
void createStack(Stack &S);                  // inisialisasi stack kosong
bool isEmpty(const Stack &S);                // true jika stack kosong
void push(Stack &S, const Aksi &a);          // masukkan aksi ke stack
bool pop(Stack &S, Aksi &hasil);             // ambil aksi teratas; false jika kosong
bool peek(const Stack &S, Aksi &hasil);      // lihat aksi teratas tanpa mengambil
int  jumlahStack(const Stack &S);            // banyak aksi di riwayat

// ---- Mencatat aksi (panggil SETELAH aksinya berhasil dilakukan) ----
void catatTambah(Stack &S, const Tugas &baru);
void catatEdit(Stack &S, const Tugas &lama, const Tugas &baru);
void catatHapus(Stack &S, const Tugas &dihapus);

// ---- Undo ----
bool undoAksi(Stack &S, Aksi &hasil);        // ambil aksi terakhir untuk dibalikkan

// ---- Tampilan ----
void tampilkanRiwayat(const Stack &S);       // semua aksi, terbaru di atas
void tampilkanRecycleBin(const Stack &S);    // hanya tugas yang DIHAPUS

// ---- Pembersihan ----
void kosongkanStack(Stack &S);               // kosongkan riwayat (dealokasi memori)

const char* namaJenisAksi(JenisAksi j);      // "TAMBAH" / "EDIT" / "HAPUS"

#endif