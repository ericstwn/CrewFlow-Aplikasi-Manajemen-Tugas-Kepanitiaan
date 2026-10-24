// Unit test modul Stack & Undo (dijalankan terpisah dari main.cpp)
// Kompilasi: g++ test_stack.cpp stack.cpp -o test_stack
// Syarat   : data.h, stack.h, stack.cpp berada di folder yang sama
#include <iostream>
#include <cassert>
#include "stack.h"
using namespace std;

Tugas buatTugas(int id, string nama) {
    Tugas t;
    t.id = id;
    t.nama = nama;
    t.penanggungJawab = "Budi";
    t.divisi = "Acara";
    t.deadline = "01-11-2026";
    t.prioritas = PRIORITAS_SEDANG;
    t.deskripsi = "-";
    t.status = STATUS_PENDING;
    return t;
}

int main() {
    Stack S;
    Tugas t;

    // --- 1. Stack kosong ---
    cout << "[1] Stack kosong\n";
    createStack(S);
    assert(isEmpty(S));
    assert(!pop(S, t));
    assert(!peek(S, t));
    assert(!undoHapus(S, t));          // Undo saat kosong aman

    // --- 2. Simulasi menghapus 3 tugas ---
    cout << "\n[2] Hapus 3 tugas -> masuk Recycle Bin\n";
    push(S, buatTugas(101, "Booking Venue"));
    push(S, buatTugas(102, "Cetak Poster"));
    push(S, buatTugas(103, "Sewa Sound"));
    assert(!isEmpty(S));
    assert(jumlahStack(S) == 3);
    tampilkanRecycleBin(S);

    // --- 3. Peek tidak mengubah isi ---
    cout << "\n[3] Peek\n";
    assert(peek(S, t) && t.id == 103);
    assert(jumlahStack(S) == 3);

    // --- 4. Undo berurutan (LIFO) ---
    cout << "\n[4] Undo berurutan\n";
    assert(undoHapus(S, t) && t.id == 103 && t.nama == "Sewa Sound");
    assert(undoHapus(S, t) && t.id == 102 && t.nama == "Cetak Poster");
    assert(jumlahStack(S) == 1);

    // --- 5. Data hasil Undo utuh ---
    cout << "\n[5] Data hasil Undo utuh\n";
    assert(undoHapus(S, t));
    assert(t.id == 101 && t.nama == "Booking Venue");
    assert(t.penanggungJawab == "Budi" && t.divisi == "Acara");
    assert(t.deadline == "01-11-2026" && t.status == STATUS_PENDING);
    assert(isEmpty(S));

    // --- 6. Hapus permanen & kosongkan ---
    cout << "\n[6] Hapus permanen & kosongkan\n";
    push(S, buatTugas(104, "Konsumsi"));
    push(S, buatTugas(105, "Dokumentasi"));
    assert(hapusPermanenTeratas(S));   // 105 dibuang selamanya
    assert(peek(S, t) && t.id == 104);
    kosongkanStack(S);
    assert(isEmpty(S) && jumlahStack(S) == 0);
    tampilkanRecycleBin(S);

    // --- 7. Stack bisa dipakai lagi ---
    cout << "\n[7] Dipakai lagi setelah dikosongkan\n";
    push(S, buatTugas(106, "Pendaftaran"));
    assert(undoHapus(S, t) && t.id == 106);
    kosongkanStack(S);

    cout << "\nSemua tes Stack & Undo LULUS.\n";
    return 0;
}