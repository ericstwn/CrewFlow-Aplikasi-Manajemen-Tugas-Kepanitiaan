// ============================================================
// Queue.h  -  Antrean Tugas (FIFO) dengan Linked List  (AQILAH)
// ============================================================
#ifndef QUEUE_H
#define QUEUE_H

#include "Data.h"
#include "Tugas.h"

class AntreanTugas {
private:
    QueueNode* front;
    QueueNode* rear;
    int ukuran;

public:
    AntreanTugas();
    ~AntreanTugas();

    bool enqueue(int idTugas);          // false jika sudah ada di antrean
    bool dequeue(int& idTugas);         // false jika antrean kosong
    bool peek(int& idTugas) const;
    bool isEmpty() const;
    bool sudahAda(int idTugas) const;
    void hapusId(int idTugas);          // dipakai saat tugas dihapus
    int  jumlah() const;
    void tampil(const DaftarTugas& tugas, const DaftarAnggota& anggota) const;
};

#endif