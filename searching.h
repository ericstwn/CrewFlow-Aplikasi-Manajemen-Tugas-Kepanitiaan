#ifndef SEARCHING_H
#define SEARCHING_H

#include <vector>
#include <string>
#include "Data.h"
#include "Anggota.h"
#include "Tugas.h"
using namespace std;

// ===== Searching (Linear Search utama) & Filter - dibuat oleh Shafira =====
// Pencarian bekerja pada SALINAN data (vector) dan tidak peka huruf besar/kecil.

// Linear search: mengembalikan indeks semua elemen yang cocok
template <typename T, typename Pred>
vector<int> linearSearch(const vector<T> &a, Pred cocok) {
    vector<int> hasil;
    for (int i = 0; i < (int)a.size(); i++)
        if (cocok(a[i])) hasil.push_back(i);
    return hasil;
}

// Binary search berdasarkan ID (syarat: vector sudah urut NAIK menurut id)
template <typename T>
int binarySearchId(const vector<T> &a, int id) {
    int kiri = 0, kanan = (int)a.size() - 1;
    while (kiri <= kanan) {
        int tengah = (kiri + kanan) / 2;
        if (a[tengah].id == id) return tengah;
        if (a[tengah].id < id) kiri = tengah + 1;
        else kanan = tengah - 1;
    }
    return -1;
}

// Filter: ambil semua elemen yang memenuhi syarat
template <typename T, typename Pred>
vector<T> saring(const vector<T> &a, Pred cocok) {
    vector<T> hasil;
    for (const T &x : a)
        if (cocok(x)) hasil.push_back(x);
    return hasil;
}

// Menu: 1. Pencarian  2. Filter
void menuPencarianFilter(const DaftarAnggota &da, const DaftarTugas &dt);

#endif