// ============================================================
// Tugas.cpp  -  Implementasi Linked List Tugas  (AQILAH)
// ============================================================
#include "Tugas.h"
#include <iomanip>

DaftarTugas::DaftarTugas() : head(nullptr), nextId(1) {}

DaftarTugas::~DaftarTugas() {
    while (head) {
        Tugas* t = head;
        head = head->next;
        delete t;
    }
}

int DaftarTugas::tambah(const string& judul, int idPJ, const string& deadline, int prioritas) {
    Tugas* baru = new Tugas;
    baru->id = nextId++;
    baru->judul = judul;
    baru->idPJ = idPJ;
    baru->deadline = deadline;
    baru->prioritas = prioritas;
    baru->status = BELUM;
    baru->next = nullptr;

    if (!head) {
        head = baru;
    } else {
        Tugas* cur = head;
        while (cur->next) cur = cur->next;
        cur->next = baru;
    }
    return baru->id;
}

void tampilHeaderTugas() {
    cout << left << setw(5) << "ID" << setw(26) << "Judul Tugas" << setw(16) << "PJ"
         << setw(13) << "Deadline" << setw(11) << "Prioritas" << setw(8) << "Status" << "\n";
    cout << string(79, '-') << "\n";
}

void tampilBarisTugas(const Tugas* t, const DaftarAnggota& anggota) {
    Anggota* pj = anggota.cariId(t->idPJ);
    cout << left << setw(5) << t->id << setw(26) << t->judul
         << setw(16) << (pj ? pj->nama : string("-"))
         << setw(13) << t->deadline << setw(11) << namaPrioritas(t->prioritas)
         << setw(8) << namaStatus(t->status) << "\n";
}

void DaftarTugas::tampil(const DaftarAnggota& anggota) const {
    if (!head) {
        cout << "  (Belum ada data tugas)\n";
        return;
    }
    tampilHeaderTugas();
    for (Tugas* cur = head; cur; cur = cur->next) tampilBarisTugas(cur, anggota);
}

Tugas* DaftarTugas::cariId(int id) const {
    for (Tugas* cur = head; cur; cur = cur->next)
        if (cur->id == id) return cur;
    return nullptr;
}

bool DaftarTugas::ubah(int id, const string& judul, int idPJ, const string& deadline,
                       int prioritas, int status) {
    Tugas* t = cariId(id);
    if (!t) return false;
    t->judul = judul;
    t->idPJ = idPJ;
    t->deadline = deadline;
    t->prioritas = prioritas;
    t->status = status;
    return true;
}

bool DaftarTugas::hapus(int id, Tugas& salinan) {
    Tugas* prev = nullptr;
    Tugas* cur = head;
    while (cur && cur->id != id) {
        prev = cur;
        cur = cur->next;
    }
    if (!cur) return false;

    salinan = *cur;
    salinan.next = nullptr;

    if (!prev) head = cur->next;
    else       prev->next = cur->next;
    delete cur;
    return true;
}

// Jika id masih ada -> timpa isinya. Jika sudah tidak ada -> sisip lagi (urut berdasarkan id).
void DaftarTugas::pulihkan(const Tugas& t) {
    Tugas* ada = cariId(t.id);
    if (ada) {
        ada->judul = t.judul;
        ada->idPJ = t.idPJ;
        ada->deadline = t.deadline;
        ada->prioritas = t.prioritas;
        ada->status = t.status;
        return;
    }

    Tugas* baru = new Tugas(t);
    baru->next = nullptr;

    if (!head || baru->id < head->id) {
        baru->next = head;
        head = baru;
    } else {
        Tugas* cur = head;
        while (cur->next && cur->next->id < baru->id) cur = cur->next;
        baru->next = cur->next;
        cur->next = baru;
    }
    if (baru->id >= nextId) nextId = baru->id + 1;
}

int DaftarTugas::jumlah() const {
    int n = 0;
    for (Tugas* cur = head; cur; cur = cur->next) n++;
    return n;
}

bool DaftarTugas::kosong() const { return head == nullptr; }