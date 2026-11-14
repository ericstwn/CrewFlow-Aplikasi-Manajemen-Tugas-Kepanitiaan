#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <string>
#include <cstdlib>
#include <cctype>
using namespace std;

inline string toLower(string s) {
    for (char &c : s) c = (char)tolower((unsigned char)c);
    return s;
}

inline string bacaString(const string &prompt) {
    string s;
    cout << prompt;
    if (!getline(cin, s)) {
        cout << "\nInput selesai. Program keluar.\n";
        exit(0);
    }
    return s;
}

// Membaca angka bulat dalam rentang [minV, maxV]
inline int bacaInt(const string &prompt, int minV, int maxV) {
    while (true) {
        string s = bacaString(prompt);
        try {
            size_t pos;
            int v = stoi(s, &pos);
            if (pos == s.size() && v >= minV && v <= maxV) return v;
        } catch (...) {}
        cout << "  Input tidak valid (isi angka " << minV << "-" << maxV << ").\n";
    }
}

// Sama seperti bacaInt, tapi Enter (kosong) = pakai nilai 'tetap'
inline int bacaIntOpsional(const string &prompt, int minV, int maxV, int tetap) {
    while (true) {
        string s = bacaString(prompt);
        if (s.empty()) return tetap;
        try {
            size_t pos;
            int v = stoi(s, &pos);
            if (pos == s.size() && v >= minV && v <= maxV) return v;
        } catch (...) {}
        cout << "  Input tidak valid (isi angka " << minV << "-" << maxV << ").\n";
    }
}

inline bool bacaYaTidak(const string &prompt) {
    while (true) {
        string s = toLower(bacaString(prompt + " (y/n): "));
        if (s == "y" || s == "ya") return true;
        if (s == "n" || s == "tidak") return false;
        cout << "  Jawab y atau n.\n";
    }
}

inline bool tanggalValid(const string &t) {
    if (t.size() != 10 || t[4] != '-' || t[7] != '-') return false;
    for (int i : {0, 1, 2, 3, 5, 6, 8, 9})
        if (!isdigit((unsigned char)t[i])) return false;
    int bln = stoi(t.substr(5, 2));
    int hr  = stoi(t.substr(8, 2));
    return bln >= 1 && bln <= 12 && hr >= 1 && hr <= 31;
}

inline string bacaTanggal(const string &prompt) {
    while (true) {
        string s = bacaString(prompt);
        if (tanggalValid(s)) return s;
        cout << "  Format tanggal harus YYYY-MM-DD (contoh 2026-11-20).\n";
    }
}

// Prioritas: 3 = Tinggi, 2 = Sedang, 1 = Rendah (makin besar makin penting)
inline string namaPrioritas(int p) {
    if (p == 3) return "Tinggi";
    if (p == 2) return "Sedang";
    return "Rendah";
}

// Menyeragamkan penulisan teks: spasi berlebih dibuang, huruf depan tiap kata
// dibuat besar, sisanya kecil. Contoh: "  bUdi   santoso " -> "Budi Santoso"
inline string normalisasiTeks(const string &s) {
    string hasil;
    bool awalKata = true;
    for (char ch : s) {
        unsigned char c = (unsigned char)ch;
        if (isspace(c)) {
            if (!hasil.empty() && hasil.back() != ' ') hasil += ' ';
            awalKata = true;
        } else {
            hasil += (char)(awalKata ? toupper(c) : tolower(c));
            awalKata = false;
        }
    }
    if (!hasil.empty() && hasil.back() == ' ') hasil.pop_back();
    return hasil;
}

inline bool semuaAngka(const string &s) {
    if (s.empty()) return false;
    for (char c : s)
        if (!isdigit((unsigned char)c)) return false;
    return true;
}

inline string bacaNIM(const string &prompt) {
    while (true) {
        string s = bacaString(prompt);
        if (semuaAngka(s)) return s;
        cout << "  NIM harus berupa angka saja.\n";
    }
}

inline string statusDariKode(int k) {
    if (k == 1) return "Belum";
    if (k == 2) return "Proses";
    return "Selesai";
}

inline int kodeDariStatus(const string &s) {
    if (s == "Belum") return 1;
    if (s == "Proses") return 2;
    return 3;
}

#endif