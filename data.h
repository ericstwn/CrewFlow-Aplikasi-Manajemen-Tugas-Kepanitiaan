#ifndef DATA_H
#define DATA_H

// ================================================================
//  Data.h  -  SATU-SATUNYA tempat definisi semua struct kelompok
//  Proyek : Sistem Manajemen Tugas Kepanitiaan
//
//  ATURAN:
//  1. Struct HANYA boleh didefinisikan di file ini (jangan di .h lain).
//  2. File ini TIDAK memakai "using namespace std", jadi memakai std::string.
//     Di file .cpp masing-masing boleh menulis "using namespace std;".
//  3. Jangan ubah nama struct / field tanpa kabar ke seluruh anggota.
//  4. Nama fungsi diberi akhiran modul agar tidak bentrok, contoh:
//     isEmptyStack, isEmptyQueue, tampilkanTugas, tampilkanAnggota.
// ================================================================

#include <string>

// ---------------- Konstanta bersama ----------------
// Status tugas
const std::string STATUS_DONE        = "Done";
const std::string STATUS_IN_PROGRESS = "In Progress";
const std::string STATUS_PENDING     = "Pending";

// Prioritas tugas
const int PRIORITAS_TINGGI = 1;
const int PRIORITAS_SEDANG = 2;
const int PRIORITAS_RENDAH = 3;

// ================================================================
//  DATA UTAMA : Tugas
// ================================================================
struct Tugas {
    int id;
    std::string nama;
    std::string penanggungJawab;
    std::string divisi;
    std::string deadline;      // format: DD-MM-YYYY
    int prioritas;             // 1 = Tinggi, 2 = Sedang, 3 = Rendah
    std::string deskripsi;
    std::string status;        // "Done" / "In Progress" / "Pending"
};

// ================================================================
//  ERIC : Multi Linked List (Divisi -> Anggota)
//  File : Anggota.h, Anggota.cpp
// ================================================================
struct Anggota {
    std::string nama;
    std::string nim;
    Anggota* next;
};

struct Divisi {
    std::string namaDivisi;
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
//  File : Stack.h, Stack.cpp
// ================================================================
struct NodeStack {
    Tugas data;
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
    std::string nama;          // kunci pencarian berdasarkan nama
    NodeTugas* ptrTugas;       // menunjuk ke node tugas di DLL
    NodeBST* left;
    NodeBST* right;
};

#endif