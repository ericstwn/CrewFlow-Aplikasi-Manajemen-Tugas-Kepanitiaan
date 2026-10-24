#include <iostream>
#include "data.h"
using namespace std;

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
        cout << "\nLogin Berhasil!\n";
    }
    else if (menu == 2)
    {
        cout << "======= Daftar =======";
        
    }
    else if (menu == 3);
    {
        cout << "\nTerima Kasih Udah Pakai CrewFlow ;)\n";
    }
    else 
    {
        cout ""
    }
}



