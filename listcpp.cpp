#include <fstream>
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    char ch;
    fstream file;
    char filename[256];
    cout << "Enter the name of the file: " << flush;
    cin >> filename;
    file.open(filename, ios::in);
    file.unsetf(ios::skipws);
    while (1) {
        file >> ch;
        if (file.fail()) break;
        cout << ch;
    }
    file.close();
    return 0;
}
