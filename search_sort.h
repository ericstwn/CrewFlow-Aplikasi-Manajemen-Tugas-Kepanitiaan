#ifndef SEARCH_SORT_H
#define SEARCH_SORT_H

#include <vector>
#include <string>
#include <utility>
#include "common.h"
#include "anggota.h"
#include "tugas.h"
using namespace std;

// ===== Searching, Sorting & Filter - dibuat oleh Shafira =====
// Semua algoritma bekerja pada SALINAN data (vector), jadi urutan asli di linked list tidak berubah.
// Parameter 'lebihKecil(a, b)' bernilai true jika a harus berada SEBELUM b.

// ---------- SORTING ----------

template <typename T, typename Cmp>
void bubbleSort(vector<T> &a, Cmp lebihKecil) {
    int n = (int)a.size();
    for (int i = 0; i < n - 1; i++) {
        bool tukar = false;
        for (int j = 0; j < n - 1 - i; j++) {
            if (lebihKecil(a[j + 1], a[j])) {
                swap(a[j], a[j + 1]);
                tukar = true;
            }
        }
        if (!tukar) break;   // sudah urut
    }
}

template <typename T, typename Cmp>
void selectionSort(vector<T> &a, Cmp lebihKecil) {
    int n = (int)a.size();
    for (int i = 0; i < n - 1; i++) {
        int idx = i;
        for (int j = i + 1; j < n; j++)
            if (lebihKecil(a[j], a[idx])) idx = j;
        if (idx != i) swap(a[i], a[idx]);
    }
}

template <typename T, typename Cmp>
void insertionSort(vector<T> &a, Cmp lebihKecil) {
    int n = (int)a.size();
    for (int i = 1; i < n; i++) {
        T kunci = a[i];
        int j = i - 1;
        while (j >= 0 && lebihKecil(kunci, a[j])) {
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = kunci;
    }
}

template <typename T, typename Cmp>
void mergeSortRek(vector<T> &a, vector<T> &tmp, int kiri, int kanan, Cmp lebihKecil) {
    if (kiri >= kanan) return;
    int tengah = (kiri + kanan) / 2;
    mergeSortRek(a, tmp, kiri, tengah, lebihKecil);
    mergeSortRek(a, tmp, tengah + 1, kanan, lebihKecil);
    int i = kiri, j = tengah + 1, k = kiri;
    while (i <= tengah && j <= kanan) {
        if (lebihKecil(a[j], a[i])) tmp[k++] = a[j++];
        else tmp[k++] = a[i++];
    }
    while (i <= tengah) tmp[k++] = a[i++];
    while (j <= kanan) tmp[k++] = a[j++];
    for (int x = kiri; x <= kanan; x++) a[x] = tmp[x];
}

template <typename T, typename Cmp>
void mergeSort(vector<T> &a, Cmp lebihKecil) {
    if (a.size() < 2) return;
    vector<T> tmp(a.size());
    mergeSortRek(a, tmp, 0, (int)a.size() - 1, lebihKecil);
}

// algo: 1=Bubble, 2=Selection, 3=Insertion, 4=Merge
template <typename T, typename Cmp>
void urutkan(vector<T> &a, int algo, Cmp lebihKecil) {
    if (algo == 1) bubbleSort(a, lebihKecil);
    else if (algo == 2) selectionSort(a, lebihKecil);
    else if (algo == 3) insertionSort(a, lebihKecil);
    else mergeSort(a, lebihKecil);
}

string namaAlgoritma(int algo);

// ---------- SEARCHING ----------

// Linear search: mengembalikan indeks semua elemen yang cocok
template <typename T, typename Pred>
vector<int> linearSearch(const vector<T> &a, Pred cocok) {
    vector<int> hasil;
    for (int i = 0; i < (int)a.size(); i++)
        if (cocok(a[i])) hasil.push_back(i);
    return hasil;
}

// Binary search berdasarkan ID (syarat: vector sudah urut naik menurut id)
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

// ---------- FILTER ----------

template <typename T, typename Pred>
vector<T> saring(const vector<T> &a, Pred cocok) {
    vector<T> hasil;
    for (const T &x : a)
        if (cocok(x)) hasil.push_back(x);
    return hasil;
}

// Menu gabungan: Pencarian, Sorting, Filter
void menuCariSortFilter(const DaftarAnggota &da, const DaftarTugas &dt);

#endif
