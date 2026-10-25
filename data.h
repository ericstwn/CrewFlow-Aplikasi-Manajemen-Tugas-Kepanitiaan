// ================================================================
//  Data.h  -  SATU-SATUNYA tempat definisi semua struct kelompok
//  Proyek : Sistem Manajemen Tugas Kepanitiaan
//
//  ATURAN:
//  1. Struct HANYA boleh didefinisikan di file ini (jangan di .h lain).
//  2. File ini TIDAK memakai "using namespace std", jadi memakai std::string.
//     Di file .cpp masing-masing boleh menulis "using namespace std;".
//  3. Jangan ubah nama struct / field tanpa kabar ke seluruh anggota.
//  4. Nama fungsi tidak boleh bentrok antar modul. Fungsi bernama sama
//     boleh ada selama tipe parameternya berbeda, contoh:
//     isEmpty(const Stack&) dan isEmpty(const Queue&).
//     Kalau parameternya sama, beri akhiran modul, contoh:
//     tampilkanTugas, tampilkanAnggota.
// ================================================================

#ifndef DATA_H
#define DATA_H
#include <iostream>
#include <string>
using namespace std;


// Status tugas
const string STATUS_DONE        = "Done";
const string STATUS_IN_PROGRESS = "In Progress";
const string STATUS_PENDING     = "Pending";

// Prioritas tugas
const int PRIORITAS_TINGGI = 1;
const int PRIORITAS_SEDANG = 2;
const int PRIORITAS_RENDAH = 3;

// ================================================================
//  DATA UTAMA : Tugas
// ================================================================
struct Tugas {
    int id;
    string nama;
    string penanggungJawab;
    string divisi;
    string deadline;      // format: DD-MM-YYYY
    int prioritas;             // 1 = Tinggi, 2 = Sedang, 3 = Rendah
    string deskripsi;
    string status;        // "Done" / "In Progress" / "Pending"
};

// ================================================================
//  ERIC : Multi Linked List (Divisi -> Anggota)
//  File : Anggota.h, Anggota.cpp
// ================================================================
struct Anggota {
    string nama;
    string nim;
    Anggota* next;
};

struct Divisi {
    string namaDivisi;
    Anggota* firstAnggota;     // child: daftar anggota divisi ini
    Divisi* next;              // parent: divisi berikutnya
};

// ================================================================
//  AQILAH : Doubly Linked List Tugas & Queue
//  File   : Tugas.h, Tugas.cpp, Queue.h, Queue.cpp
// ================================================================
struct NodeTugas {
    Tugas data;
    NodeTugas* prev;
    NodeTugas* next;
};

struct ListTugas {
    NodeTugas* head;
    NodeTugas* tail;
    int jumlah;
};

struct NodeQueue {
    Tugas data;
    NodeQueue* next;
};

struct Queue {
    NodeQueue* front;
    NodeQueue* rear;
    int jumlah;
};

// ================================================================
//  RAFI : Stack (Recycle Bin & Undo)
//  File : stack.h, stack.cpp
// ================================================================
enum JenisAksi { AKSI_TAMBAH, AKSI_EDIT, AKSI_HAPUS };
    struct Aksi {
    JenisAksi jenis;
    Tugas sebelum;
    Tugas sesudah;
};

    struct NodeStack {
    Aksi data;
    NodeStack* next;
};

struct Stack {
    NodeStack* top;
    int jumlah;
};

// ================================================================
//  SHAFIRA : Binary Search Tree (Searching)
//  File    : Searching.h, Searching.cpp, Sorting.h, Sorting.cpp
// ================================================================
struct NodeBST {
    int id;                    // kunci pencarian berdasarkan ID
    string nama;          // kunci pencarian berdasarkan nama
    NodeTugas* ptrTugas;       // menunjuk ke node tugas di DLL
    NodeBST* left;
    NodeBST* right;
};

#endif