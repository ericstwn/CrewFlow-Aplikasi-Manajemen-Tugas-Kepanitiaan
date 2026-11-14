// ============================================================
// test_Aqilah.cpp  -  Test fitur Tugas (Doubly Linked List) & Queue
// Compile (dari folder yang berisi Data.h, Tugas.*, Queue.*):
//   g++ -std=c++11 test_Aqilah.cpp Tugas.cpp Queue.cpp -o test_aqilah
//   .\test_aqilah        (PowerShell)   atau   ./test_aqilah  (Linux/Mac)
// TIDAK membutuhkan file Anggota / Stack / Searching.
// ============================================================
#include <iostream>
#include "Tugas.h"
#include "Queue.h"

using namespace std;

// Pembuat data tugas biar test ringkas
Tugas buatTugas(const string &nama, const string &pj, const string &divisi,
                const string &deadline, int prioritas, const string &deskripsi) {
    Tugas t;
    t.id = buatIdTugas();
    t.nama = nama;
    t.penanggungJawab = pj;
    t.divisi = divisi;
    t.deadline = deadline;
    t.prioritas = prioritas;
    t.deskripsi = deskripsi;
    t.status = STATUS_PENDING;
    return t;
}

int lulus = 0, gagal = 0;
void cek(bool kondisi, const string &deskripsi) {
    cout << (kondisi ? "  [LULUS] " : "  [GAGAL] ") << deskripsi << "\n";
    if (kondisi) lulus++; else gagal++;
}

int main() {
    cout << "=== TEST FITUR TUGAS ===\n";

    ListTugas daftar;
    Queue antrean;
    initListTugas(daftar);
    initQueue(antrean);

    // ---------- 1. Tambah tugas ----------
    cout << "\n[1] Tambah 3 tugas\n";
    Tugas a = buatTugas("Menyusun proposal", "Eric",    "Acara",      "15-10-2026", PRIORITAS_TINGGI, "Proposal sponsor");
    Tugas b = buatTugas("Membuat notulen",   "Aqilah",  "Sekretaris", "12-10-2026", PRIORITAS_SEDANG, "Notulen rapat mingguan");
    Tugas c = buatTugas("Menghitung anggaran","Rafi",   "Bendahara",  "20-10-2026", PRIORITAS_TINGGI, "RAB kegiatan");
    tambahTugas(daftar, a);
    tambahTugas(daftar, b);
    tambahTugas(daftar, c);
    cek(daftar.jumlah == 3, "Jumlah tugas = 3");
    cek(a.id == 1 && b.id == 2 && c.id == 3, "ID otomatis 1, 2, 3");

    // ---------- 2. Tampilkan tugas ----------
    cout << "\n[2] Tampilkan semua tugas (head -> tail)\n";
    tampilkanTugas(daftar);
    cout << "\nTampilkan mundur (tail -> head, lewat pointer prev)\n";
    tampilkanTugasMundur(daftar);
    cout << "\nDetail tugas ID 2:\n";
    NodeTugas *n = cariTugasById(daftar, 2);
    if (n) tampilkanDetailTugas(n->data);
    cek(n != nullptr && n->data.nama == "Membuat notulen", "cariTugasById(2) benar");
    cek(cariTugasById(daftar, 99) == nullptr, "cariTugasById(99) -> nullptr");

    // ---------- 3. Edit tugas ----------
    cout << "\n[3] Edit tugas ID 1\n";
    Tugas baru = a;
    baru.nama = "Proposal FINAL";
    baru.deadline = "18-10-2026";
    baru.status = STATUS_IN_PROGRESS;
    cek(editTugas(daftar, 1, baru), "editTugas(1) berhasil");
    cek(!editTugas(daftar, 99, baru), "editTugas(99) ditolak");
    cek(cariTugasById(daftar, 1)->data.nama == "Proposal FINAL", "Nama berubah");
    cek(cariTugasById(daftar, 1)->data.status == STATUS_IN_PROGRESS, "Status berubah");
    tampilkanTugas(daftar);

    // ---------- 4. Hapus tugas ----------
    cout << "\n[4] Hapus tugas ID 2 (tengah)\n";
    Tugas dihapus;   // salinan ini nanti dikirim Rafi ke Stack (Recycle Bin)
    cek(hapusTugas(daftar, 2, dihapus), "hapusTugas(2) berhasil");
    cek(dihapus.nama == "Membuat notulen", "Data yang dihapus tersimpan untuk Stack");
    cek(daftar.jumlah == 2 && cariTugasById(daftar, 2) == nullptr, "Tugas ID 2 hilang dari daftar");
    cek(daftar.head->next == daftar.tail && daftar.tail->prev == daftar.head, "Pointer prev/next tetap tersambung");
    cek(!hapusTugas(daftar, 99, dihapus), "hapusTugas(99) ditolak");
    tampilkanTugas(daftar);

    // ---------- 5. Queue: masukkan tugas ke antrean ----------
    cout << "\n[5] Enqueue tugas ke antrean (ID 3 lalu ID 1)\n";
    cek(enqueue(antrean, cariTugasById(daftar, 3)->data), "enqueue ID 3");
    cek(enqueue(antrean, cariTugasById(daftar, 1)->data), "enqueue ID 1");
    cek(!enqueue(antrean, cariTugasById(daftar, 1)->data), "enqueue ID 1 lagi ditolak (duplikat)");
    tampilkanQueue(antrean);

    // ---------- 6. Queue: ambil tugas dari antrean (FIFO) ----------
    cout << "\n[6] Dequeue (ambil tugas terdepan)\n";
    Tugas t;
    cek(peekQueue(antrean, t) && t.id == 3, "peek -> terdepan = ID 3");
    cek(dequeue(antrean, t) && t.id == 3, "dequeue ke-1 -> ID 3 (masuk pertama, keluar pertama)");
    cek(dequeue(antrean, t) && t.id == 1, "dequeue ke-2 -> ID 1");
    cek(isEmptyQueue(antrean), "Antrean kosong");
    cek(!dequeue(antrean, t), "dequeue saat kosong -> false");

    // ---------- 7. Pulihkan tugas yang dihapus (simulasi Undo) ----------
    cout << "\n[7] Simulasi Undo: tambahkan lagi tugas yang tadi dihapus\n";
    tambahTugas(daftar, dihapus);
    cek(daftar.jumlah == 3 && cariTugasById(daftar, 2) != nullptr, "Tugas ID 2 kembali");
    Tugas tugasBaru = buatTugas("Tugas baru", "Shafira", "Humas", "30-10-2026", PRIORITAS_RENDAH, "-");
    cek(tugasBaru.id > 3, "ID baru tidak bentrok dengan ID yang dipulihkan");

    hapusSemuaTugas(daftar);
    kosongkanQueue(antrean);

    cout << "\nHASIL: " << lulus << " lulus, " << gagal << " gagal\n";
    cout << "\nPengujian selesai.\n";

    return gagal == 0 ? 0 : 1;
}