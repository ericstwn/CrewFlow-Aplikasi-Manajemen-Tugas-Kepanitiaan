#include <iostream>
#include "data.h"
using namespace std;

int main() {
    string username;
    string password;

	cout << "\n===============\n";
    cout << "     LOGIN\n";
    cout << "===============\n";
    cout << "Username : ";
    cin >> username;
    cout << "Password : ";
    cin >> password;

    if (username == "Admin" && password == "1234") {
        cout << "Login berhasil!";
    } else {
        cout << "Login gagal\n";
        cout << "Username atau Password Salah!";
    }
    return 0;
}



