// ============================================================
// Queue.h  -  Antrean Tugas (FIFO) dengan Linked List  (AQILAH)
// ============================================================
#ifndef QUEUE_H
#define QUEUE_H

#include "data.h"

void initQueue(Queue &q);
bool isEmptyQueue(const Queue &q);
bool sudahAdaDiQueue(const Queue &q, int idTugas);
 
bool enqueue(Queue &q, const Tugas &data);          // false jika ID tugas sudah ada di antrean
bool dequeue(Queue &q, Tugas &hasil);               // false jika antrean kosong
bool peekQueue(const Queue &q, Tugas &hasil);       // lihat terdepan tanpa mengambil
 
bool hapusDariQueue(Queue &q, int idTugas);         // dipakai saat tugas dihapus dari daftar
bool perbaruiDiQueue(Queue &q, const Tugas &data);  // dipakai saat tugas diedit (salinan di antrean ikut diperbarui)
void kosongkanQueue(Queue &q);
void tampilkanQueue(const Queue &q);
 
#endif
