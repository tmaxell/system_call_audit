#include <iostream>
#include <fstream>
#include <unistd.h>
#include <string>

using namespace std;

void createFile() {
    // Открываем файл для записи
    ofstream outfile("test.txt");
    if (!outfile) {
        cerr << "Failed to open test.txt for writing." << endl;
        return;
    }

    // Записываем данные в файл
    outfile << "Hello, world!" << endl;
    outfile.close();

    cout << "File 'test.txt' has been created." << endl;
}

int main() {
    string command;

    while (true) {
        cout << "Enter a command ('create' to create a file, 'quit' to exit): ";
        cin >> command;

        if (command == "create") {
            createFile();
        } else if (command == "quit") {
            break;
        } else {
            cout << "Invalid command. Please try again." << endl;
        }
    }

    return 0;
}