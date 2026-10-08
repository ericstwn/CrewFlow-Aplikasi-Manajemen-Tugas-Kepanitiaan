// ============================================================
// Queue.cpp  -  Implementasi Queue Antrean Tugas  (AQILAH)
// ============================================================
#include "Queue.h"

AntreanTugas::AntreanTugas() : front(nullptr), rear(nullptr), ukuran(0) {}

AntreanTugas::~AntreanTugas() {
    int dummy;
    while (dequeue(dummy)) {}
}

bool AntreanTugas::isEmpty() const { return front == nullptr; }

int AntreanTugas::jumlah() const { return ukuran; }

bool AntreanTugas::sudahAda(int idTugas) const {
    for (QueueNode* cur = front; cur; cur = cur->next)
        if (cur->idTugas == idTugas) return true;
    return false;
}

// Masuk dari belakang (rear)
bool AntreanTugas::enqueue(int idTugas) {
    if (sudahAda(idTugas)) return false;

    QueueNode* baru = new QueueNode;
    baru->idTugas = idTugas;
    baru->next = nullptr;

    if (isEmpty()) front = rear = baru;
    else {
        rear->next = baru;
        rear = baru;
    }
    ukuran++;
    return true;
}

// Keluar dari depan (front)
bool AntreanTugas::dequeue(int& idTugas) {
    if (isEmpty()) return false;
    QueueNode* hapus = front;
    idTugas = hapus->idTugas;
    front = front->next;
    if (!front) rear = nullptr;
    delete hapus;
    ukuran--;
    return true;
}

bool AntreanTugas::peek(int& idTugas) const {
    if (isEmpty()) return false;
    idTugas = front->idTugas;
    return true;
}

// Hapus id tertentu dari tengah antrean (tugas sudah dihapus dari daftar)
void AntreanTugas::hapusId(int idTugas) {
    QueueNode* prev = nullptr;
    QueueNode* cur = front;
    while (cur && cur->idTugas != idTugas) {
        prev = cur;
        cur = cur->next;
    }
    if (!cur) return;

    if (!prev) front = cur->next;
    else       prev->next = cur->next;
    if (cur == rear) rear = prev;
    delete cur;
    ukuran--;
}

void AntreanTugas::tampil(const DaftarTugas& tugas, const DaftarAnggota& anggota) const {
    if (isEmpty()) {
        cout << "  (Antrean kosong)\n";
        return;
    }
    cout << "Urutan  ";
    tampilHeaderTugas();
    int no = 1;
    for (QueueNode* cur = front; cur; cur = cur->next, no++) {
        Tugas* t = tugas.cariId(cur->idTugas);
        cout << left << "#" << no << (no < 10 ? "      " : "     ");
        if (t) tampilBarisTugas(t, anggota);
        else   cout << "(tugas ID " << cur->idTugas << " tidak ditemukan)\n";
    }
}