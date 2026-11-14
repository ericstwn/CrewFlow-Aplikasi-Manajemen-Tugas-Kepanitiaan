// ============================================================
// Tugas.h  -  Linked List Manajemen Tugas  (AQILAH)
// ============================================================
#ifndef TUGAS_H
#define TUGAS_H

#include <string>
#include "data.h"

//inisialisasi & pengecekan
void initListTugas(ListTugas &list);
bool isEmptyTugas(const ListTugas &list);

// ----- ID otomatis (1, 2, 3, ...) -----
int  buatIdTugas();
 
// ----- CRUD -----
void       tambahTugas(ListTugas &list, const Tugas &data);          // sisip di belakang (tail)
NodeTugas* cariTugasById(const ListTugas &list, int id);             // nullptr jika tidak ada
bool       editTugas(ListTugas &list, int id, const Tugas &dataBaru);// id tidak berubah
bool       hapusTugas(ListTugas &list, int id, Tugas &dataDihapus);  // dataDihapus -> dikirim ke Stack
void       hapusSemuaTugas(ListTugas &list);
 
// ----- Tampilan -----
void tampilkanTugas(const ListTugas &list);            // head -> tail
void tampilkanTugasMundur(const ListTugas &list);      // tail -> head (memanfaatkan pointer prev)
void tampilkanDetailTugas(const Tugas &t);             // semua field termasuk deskripsi
 
// Dipakai juga oleh Queue / modul lain
void tampilkanHeaderTugas();
void tampilkanBarisTugas(const Tugas &t);
std::string teksPrioritas(int prioritas);
 
#endif
