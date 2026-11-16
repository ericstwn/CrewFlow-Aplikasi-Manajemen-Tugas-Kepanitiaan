#include <iostream>
#include <fstream>
#include "data.h"
using namespace std;

Akun maksimalDataDaftarAkun[55];
int jumlahAkunKedaftar = 0;
bool loginBerhasil;
bool usernameSudahAda;
bool simpanAkun (string username, string password)
{
    ofstream file("akun.txt", ios::app);
    if (!file.is_open())
    {
        return false;
    }
    file << username << "|" << password << endl;
    file.close();

    if (file.fail())
    {
        return false;
    }
    return true;
}

void bacaDataAkun()
{
    ifstream file("akun.txt");
    string username, password;

    if (!file.is_open())
    {
        return;
    }

    while (jumlahAkunKedaftar < 55 && getline(file, username, '|') && getline(file, password))
    {
        maksimalDataDaftarAkun[jumlahAkunKedaftar].username = username;
        maksimalDataDaftarAkun[jumlahAkunKedaftar].password = password;
        jumlahAkunKedaftar++;
    }
    file.close();
}

int dashboard(string username)
    {
        int menuDashboard;
        do
        {
            cout << "====================\n";
            cout << "      CREWFLOW\n";
            cout << "====================\n";
            cout << "Selamat datang, " << username << "\n";
            cout << "1. Manajemen Anggota\n";
            cout << "2. Manajemen Tugas\n";
            cout << "3. Manajemen Jadwal\n";
            cout << "4. Antrean Tugas\n";
            cout << "5. Searching\n";
            cout << "6. Riwayat Kerja\n";
            cout << "7. Notifikasi Tugas\n";
            cout << "8. Logout\n";
            cout << "9. Exit/Keuar\n";
            cout << "====================\n";
            cout << "Pilih Menu: ";
            cin >> menuDashboard;

            if (menuDashboard == 1)
            {
                cout << "\nSubmenu Manajemen Anggota dipilih\n";
            }
            else if (menuDashboard == 2)
            {
                cout << "\nSubmenu Manajemen Tugas dipilih\n";
            }
            else if (menuDashboard == 3)
            {
                cout << "\nSubmenu Manajemen Jadwal dipilih\n";
            }
            else if (menuDashboard == 4)
            {
                cout << "\nSubmenu Antrean Tugas\n";
            }
            else if (menuDashboard == 5)
            {
                cout << "\nSubmenu Searching\n";
            }
            else if (menuDashboard == 6)
            {
                cout << "\nSubmenu Riwayat Kerja\n";
            }
            else if (menuDashboard == 7)
            {
                cout << "\nSubmenu Notifikasi Tugas\n";
            }
            else if (menuDashboard == 8)
            {
                cout << "\nBerhasil Logout!\n";
            }
            else if (menuDashboard == 9)
            {
                cout << "\nTerima Kasih Udah Pakai CrewFlow ;)\n";
                return 0;
            }
            else
            {
                cout << "\nPilihan tidak valid!\n";
            }
        } while (true);
        return 1;
    }

int main() 
{
    int menu;
    string username, password;
    bacaDataAkun();

    do
    {
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
            int hasilDashboard = dashboard(username);

            if (hasilDashboard == 0)
            {
                return 0;
            }
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
                    cout << "Username sudah digunakan!\n";
                }
                else 
                {
                    cout << "Buat Password: ";
                    cin >> password;

                    if (simpanAkun(username, password))
                    {
                    maksimalDataDaftarAkun[jumlahAkunKedaftar].username = username;
                    maksimalDataDaftarAkun[jumlahAkunKedaftar].password = password;
                    jumlahAkunKedaftar++;

                    cout << "Akun berhasil dibuat, Silahkan Login\n";
                    }
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
}while (menu !=3);
    return 0;
}






