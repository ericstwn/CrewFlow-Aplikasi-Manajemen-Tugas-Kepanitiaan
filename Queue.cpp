// ============================================================
// Queue.cpp  -  Implementasi Queue Antrean Tugas  (AQILAH)
// ============================================================
#include "Queue.h"
#include "Tugas.h"      // untuk fungsi tampilan baris tugas
#include <iostream>
#include <iomanip>
using namespace std;

void initQueue(Queue &q) {
    q.front = nullptr;
    q.rear = nullptr;
    q.jumlah = 0;
}

bool isEmptyQueue(const Queue &q) {
    return q.front == nullptr;
}

bool sudahAdaDiQueue(const Queue &q, int idTugas) {
    for (NodeQueue *cur = q.front; cur; cur = cur->next)
        if (cur->data.id == idTugas) return true;
    return false;
}

// Masuk dari belakang (rear)
bool enqueue(Queue &q, const Tugas &data) {
    if (sudahAdaDiQueue(q, data.id)) return false;

    NodeQueue *baru = new NodeQueue;
    baru->data = data;
    baru->next = nullptr;

    if (isEmptyQueue(q)) q.front = q.rear = baru;
    else {
        q.rear->next = baru;
        q.rear = baru;
    }
    q.jumlah++;
    return true;
}

// Keluar dari depan (front)
bool dequeue(Queue &q, Tugas &hasil) {
    if (isEmptyQueue(q)) return false;

    NodeQueue *hapus = q.front;
    hasil = hapus->data;
    q.front = q.front->next;
    if (!q.front) q.rear = nullptr;
    delete hapus;
    q.jumlah--;
    return true;
}

bool peekQueue(const Queue &q, Tugas &hasil) {
    if (isEmptyQueue(q)) return false;
    hasil = q.front->data;
    return true;
}

bool hapusDariQueue(Queue &q, int idTugas) {
    NodeQueue *prev = nullptr;
    NodeQueue *cur = q.front;
    while (cur && cur->data.id != idTugas) {
        prev = cur;
        cur = cur->next;
    }
    if (!cur) return false;

    if (!prev) q.front = cur->next;
    else       prev->next = cur->next;
    if (cur == q.rear) q.rear = prev;
    delete cur;
    q.jumlah--;
    return true;
}

bool perbaruiDiQueue(Queue &q, const Tugas &data) {
    for (NodeQueue *cur = q.front; cur; cur = cur->next) {
        if (cur->data.id == data.id) {
            cur->data = data;
            return true;
        }
    }
    return false;
}

void kosongkanQueue(Queue &q) {
    Tugas dummy;
    while (dequeue(q, dummy)) {}
}

void tampilkanQueue(const Queue &q) {
    if (isEmptyQueue(q)) {
        cout << "  (Antrean kosong)\n";
        return;
    }
    cout << left << setw(8) << "Urutan";
    tampilkanHeaderTugas();
    int no = 1;
    for (NodeQueue *cur = q.front; cur; cur = cur->next, no++) {
        cout << left << setw(8) << ("#" + to_string(no));
        tampilkanBarisTugas(cur->data);
    }
    cout << "Total antrean: " << q.jumlah << " tugas\n";
}