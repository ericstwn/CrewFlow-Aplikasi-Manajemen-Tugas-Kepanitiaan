// ============================================================
// Tugas.cpp  -  Implementasi Double Linked List Tugas  (AQILAH)
// ============================================================
#include "Tugas.h"
#include <iostream>
#include <iomanip>
using namespace std;

static int idTerakhir = 0;  // penghitung ID otomatis

// inisialisasi
void initListTugas(ListTugas &list) {
    list.head = nullptr;
    list.tail = nullptr;
    list.jumlah = 0;
}

bool isEmptyTugas(const ListTugas &list) {
    return list.head == nullptr;
}

int buatIdTugas() {
    return ++idTerakhir;
}

//------------CREATE----------
void tambahTugas(ListTugas &list, const Tugas &data) {
    NodeTugas *baru = new NodeTugas;
    baru->data = data;
    baru->prev = list.tail;
    baru->next = nullptr;
 
    if (list.tail) list.tail->next = baru;
    else           list.head = baru;
    list.tail = baru;
    list.jumlah++;
 
    // jaga agar ID otomatis tidak bentrok (misal saat tugas dipulihkan dari Stack)
    if (data.id > idTerakhir) idTerakhir = data.id;

}

//----------READ------------

NodeTugas* cariTugasById(const ListTugas &list, int id) {
    for (NodeTugas *cur = list.head; cur; cur = cur->next)
        if (cur->data.id == id) return cur;
    return nullptr;
}
 
string teksPrioritas(int prioritas) {
    if (prioritas == PRIORITAS_TINGGI) return "Tinggi";
    if (prioritas == PRIORITAS_SEDANG) return "Sedang";
    return "Rendah";
}
 
void tampilkanHeaderTugas() {
    cout << left << setw(5)  << "ID"
         << setw(24) << "Nama Tugas"
         << setw(14) << "PJ"
         << setw(12) << "Divisi"
         << setw(12) << "Deadline"
         << setw(10) << "Prioritas"
         << "Status" << "\n";
    cout << string(87, '-') << "\n";
}
 
void tampilkanBarisTugas(const Tugas &t) {
    cout << left << setw(5)  << t.id
         << setw(24) << t.nama
         << setw(14) << t.penanggungJawab
         << setw(12) << t.divisi
         << setw(12) << t.deadline
         << setw(10) << teksPrioritas(t.prioritas)
         << t.status << "\n";
}
 
void tampilkanTugas(const ListTugas &list) {
    if (isEmptyTugas(list)) {
        cout << "  (Belum ada data tugas)\n";
        return;
    }
    tampilkanHeaderTugas();
    for (NodeTugas *cur = list.head; cur; cur = cur->next)
        tampilkanBarisTugas(cur->data);
    cout << "Total: " << list.jumlah << " tugas\n";
}
 
void tampilkanTugasMundur(const ListTugas &list) {
    if (isEmptyTugas(list)) {
        cout << "  (Belum ada data tugas)\n";
        return;
    }
    tampilkanHeaderTugas();
    for (NodeTugas *cur = list.tail; cur; cur = cur->prev)
        tampilkanBarisTugas(cur->data);
}
 
void tampilkanDetailTugas(const Tugas &t) {
    cout << "ID              : " << t.id << "\n"
         << "Nama            : " << t.nama << "\n"
         << "Penanggung jawab: " << t.penanggungJawab << "\n"
         << "Divisi          : " << t.divisi << "\n"
         << "Deadline        : " << t.deadline << "\n"
         << "Prioritas       : " << teksPrioritas(t.prioritas) << "\n"
         << "Deskripsi       : " << t.deskripsi << "\n"
         << "Status          : " << t.status << "\n";
}
 
// ---------------- UPDATE ----------------
bool editTugas(ListTugas &list, int id, const Tugas &dataBaru) {
    NodeTugas *node = cariTugasById(list, id);
    if (!node) return false;
    node->data = dataBaru;
    node->data.id = id;      // ID tidak boleh berubah
    return true;
}
 
// ---------------- DELETE ----------------
bool hapusTugas(ListTugas &list, int id, Tugas &dataDihapus) {
    NodeTugas *node = cariTugasById(list, id);
    if (!node) return false;
 
    dataDihapus = node->data;
 
    if (node->prev) node->prev->next = node->next;
    else            list.head = node->next;
 
    if (node->next) node->next->prev = node->prev;
    else            list.tail = node->prev;
 
    delete node;
    list.jumlah--;
    return true;
}
 
void hapusSemuaTugas(ListTugas &list) {
    while (list.head) {
        NodeTugas *t = list.head;
        list.head = list.head->next;
        delete t;
    }
    list.tail = nullptr;
    list.jumlah = 0;
}