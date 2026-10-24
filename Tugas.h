// ============================================================
// Tugas.h  -  Linked List Manajemen Tugas  (AQILAH)
// ============================================================
#ifndef TUGAS_H
#define TUGAS_H

#include "Data.h"
#include "Anggota.h"

class DaftarTugas {
private:
    Tugas* head;
    int nextId;

public:
    DaftarTugas();
    ~DaftarTugas();

    int     tambah(const string& judul, int idPJ, const string& deadline, int prioritas);
    void    tampil(const DaftarAnggota& anggota) const;
    Tugas*  cariId(int id) const;
    bool    ubah(int id, const string& judul, int idPJ, const string& deadline,
                 int prioritas, int status);
    bool    hapus(int id, Tugas& salinan);        // salinan dikirim ke Stack (undo)
    void    pulihkan(const Tugas& t);             // dipakai Undo (timpa / sisip kembali)
    int     jumlah() const;
    bool    kosong() const;

    Tugas*  getHead() const { return head; }
    Tugas*& headRef()       { return head; }      // dipakai Sorting
};

// Tampilan baris tugas (juga dipakai Searching & Queue)
void tampilHeaderTugas();
void tampilBarisTugas(const Tugas* t, const DaftarAnggota& anggota);

#endif