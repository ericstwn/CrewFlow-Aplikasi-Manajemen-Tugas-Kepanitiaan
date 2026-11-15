#include <iostream>
#include <fstream>
#include "data.h"
using namespace std;

Akun maksimalDataDaftarAkun[55];
int jumlahAkunKedaftar = 0;
bool loginBerhasil;
bool usernameSudahAda;

int main() {
    int menu;
    string username, password;

    cout << "------------------------\n";
    cout << "       CREWFLOW\n";
    cout << "------------------------\n";
    cout << "1. Login\n";
    cout << "2. Daftar\n";
    cout << "3. Exit\n";
    cout << "========================\n";
    cout << "Pilih Menu: ";
    cin >> menu;

    if (menu == 1)
    {
        cout << "-----------------------\n";
        cout << "        LOGIN\n";
        cout << "-----------------------\n";
        cout << "Username: ";
        cin >> username;
        cout << "Password: ";
        cin >> password;

        if (jumlahAkunKedaftar == 0)
        {
            cout << "Akun tidak ditemukan\n";
            cout << "Silahkan Daftar Dulu\n";
        }
        else
        {
            loginBerhasil = false;
        do
        {
        for (int i = 0; i < jumlahAkunKedaftar; i++)
        {
            if (maksimalDataDaftarAkun[i].username == username &&
                maksimalDataDaftarAkun[i].password == password)
                {
                loginBerhasil = true;
                break;
                }
            }

            if (loginBerhasil == false)
            {
                cout << "Username atau Password Salah\n";
                cout << "Silakan Coba Lagi\n";

                cout << "Username: ";
                cin >> username;
                cout << "Password: ";
                cin >> password;
            }
        } while (loginBerhasil == false);
            cout << "Login Berhasil!\n";
            cout << "Welcome to CrewFlow bos, " << username << "\n";
        }
    }

    else if (menu == 2)
    {
        cout << "======= Daftar =======\n";

            if (jumlahAkunKedaftar < 55)
            {
                cout << "Buat Username :";
                cin >> username;
                usernameSudahAda = false;

                for (int i = 0; i < jumlahAkunKedaftar; i++)
                {
                    if (maksimalDataDaftarAkun[i].username == username)
                    {
                        usernameSudahAda = true;
                        break;
                    }
                }

                if (usernameSudahAda == true)
                {
                    cout << "Username sudah digunakan\n";
                }
                else 
                {
                    cout << "Buat Password: ";
                    cin >> password;

                    maksimalDataDaftarAkun[jumlahAkunKedaftar].username = username;
                    maksimalDataDaftarAkun[jumlahAkunKedaftar].password = password;
                    jumlahAkunKedaftar++;

                    cout << "Akun berhasil dibuat, Silahkan Login\n";
                }
            }
            else
            {
                cout << "Gagal daftar, Kapasitas penuh!\n";
            }
    }

    else if (menu == 3)
    {
        cout << "Terima Kasih Udah Pakai CrewFlow ;)";
    }

    else 
    {
        cout << "Pilihan Tidak Valid!";
    }
    return 0;
}





