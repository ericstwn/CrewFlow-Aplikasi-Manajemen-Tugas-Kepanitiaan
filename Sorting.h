#ifndef SORTING_H
#define SORTING_H

#include <vector>
#include <string>
#include <utility>
#include "Data.h"
#include "Anggota.h"
#include "Tugas.h"
using namespace std;

// ===== Sorting (Bubble Sort utama) - dibuat oleh Shafira =====
// Semua algoritma bekerja pada SALINAN data (vector), jadi urutan asli di linked list tidak berubah.
// Parameter 'dahulu(a, b)' bernilai true jika a harus berada SEBELUM b.
// Untuk urutan besar ke kecil, dahulu(a, b) dibuat dengan a > b.

template <typename T, typename Cmp>
void bubbleSort(vector<T> &a, Cmp dahulu) {
    int n = (int)a.size();
    for (int i = 0; i < n - 1; i++) {
        bool tukar = false;
        for (int j = 0; j < n - 1 - i; j++) {
            if (dahulu(a[j + 1], a[j])) {
                swap(a[j], a[j + 1]);
                tukar = true;
            }
        }
        if (!tukar) break;   // sudah urut, berhenti lebih awal
    }
}

template <typename T, typename Cmp>
void selectionSort(vector<T> &a, Cmp dahulu) {
    int n = (int)a.size();
    for (int i = 0; i < n - 1; i++) {
        int idx = i;
        for (int j = i + 1; j < n; j++)
            if (dahulu(a[j], a[idx])) idx = j;
        if (idx != i) swap(a[i], a[idx]);
    }
}

template <typename T, typename Cmp>
void insertionSort(vector<T> &a, Cmp dahulu) {
    int n = (int)a.size();
    for (int i = 1; i < n; i++) {
        T kunci = a[i];
        int j = i - 1;
        while (j >= 0 && dahulu(kunci, a[j])) {
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = kunci;
    }
}

template <typename T, typename Cmp>
void mergeSortRek(vector<T> &a, vector<T> &tmp, int kiri, int kanan, Cmp dahulu) {
    if (kiri >= kanan) return;
    int tengah = (kiri + kanan) / 2;
    mergeSortRek(a, tmp, kiri, tengah, dahulu);
    mergeSortRek(a, tmp, tengah + 1, kanan, dahulu);
    int i = kiri, j = tengah + 1, k = kiri;
    while (i <= tengah && j <= kanan) {
        if (dahulu(a[j], a[i])) tmp[k++] = a[j++];
        else tmp[k++] = a[i++];
    }
    while (i <= tengah) tmp[k++] = a[i++];
    while (j <= kanan) tmp[k++] = a[j++];
    for (int x = kiri; x <= kanan; x++) a[x] = tmp[x];
}

template <typename T, typename Cmp>
void mergeSort(vector<T> &a, Cmp dahulu) {
    if (a.size() < 2) return;
    vector<T> tmp(a.size());
    mergeSortRek(a, tmp, 0, (int)a.size() - 1, dahulu);
}

// algo: 1 = Bubble, 2 = Selection, 3 = Insertion, 4 = Merge
template <typename T, typename Cmp>
void urutkan(vector<T> &a, int algo, Cmp dahulu) {
    if (algo == 1) bubbleSort(a, dahulu);
    else if (algo == 2) selectionSort(a, dahulu);
    else if (algo == 3) insertionSort(a, dahulu);
    else mergeSort(a, dahulu);
}

string namaAlgoritma(int algo);

// Menu sorting anggota dan tugas (semua urutan besar -> kecil)
void menuSorting(const DaftarAnggota &da, const DaftarTugas &dt);

#endif