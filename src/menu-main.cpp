#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <vector>
#include "libfat.hpp"

using namespace std;

Disk * disk;
FatTable * table;


void escreverArquivo(){
    string input, filename, aux;
    system("clear");
    cout << "___Escrever Arquivo___\n";
    cout << "Digite nome do arquivo (ex. file1): ";
    cin >> filename;
    filename += ".txt";
    while (filename.size()>96){
        cout << "Nome muito grande! Por favor digite outro(96 max): ";
        cin >> filename;
    }
    cout << "Abrindo o arquivo: " << filename;
    cout << "\n\nDigite seu texto, para finalizar CTRL+D.\n";
    cout << "------------------------------------\n";
    //captura lixo do buffer
    cin.get();
    while(getline(cin, aux)){
        input += aux + "\n";
    }
    //TODO :: Verificar funcionamento!!!
    table->addFile(filename, input.c_str(), input.size());

    cout << "\n------------------------------------escrito...\n";
    cout << "ENTER para sair.";
    cin.clear();
    cin.get();
}

void lerArquivo(){
    string infile, line;
    fstream file;
    system("clear");
    cout << "___Ler Arquivo___\n";
    cout << "Digite o nome do arquivo (ex. file1): ";
    cin >> infile;
    infile += ".txt";
    file.open(infile);
    if (file.is_open()) {
        cout << "\n----------------------------" << infile << endl;
        while (getline(file, line)) {
            cout << line << endl;
        }
        cout << "----------------------------\n";
        file.close();
        cin.get();
    }
    else cout << "Não foi possível abrir o arquivo...\n";
    cout << "\nENTER para sair.";
    cin.get();
}

void apagarArquivo(){
    string filename;
    system("clear");
    cout << "___Apagar Aquivo___\n";
    cout << "Digite o nome do arquivo a ser apagado:";
    cin >> filename;
    table->searchFile(filename);
}

void mostrarTabelaFAT(){
    //output test model
    struct filetype {
        string name;
        int size;
        int pos;
    };
    vector<filetype> fat_ex;
    system("clear");
    fat_ex.push_back(filetype());
    fat_ex.push_back(filetype());
    fat_ex.push_back(filetype());
    fat_ex[0] = {"file1", 1 ,5};
    fat_ex[1] = {"file2", 7 ,2};
    fat_ex[2] = {"file3", 3 ,9};
    cout << "___Mostra Tabela FAT___\n";
    cout << "NOME:\tTAMANHO EM DISCO:\tLOCALIZAÇÃO" << endl;
    for (auto const& file: fat_ex) {
        cout << file.name<< "\t\t" << file.size
            << "\t\t" << file.pos << endl;
    }
    cout << "ENTER para sair.";
    cin.clear();
    cin.get();
    cin.get();
}

void exibirMenu()
{
    system("clear");

    cout << "MENU\n\n";
    cout << " 1. Escrever Arquivo\n";
    cout << " 2. Ler Arquivo\n";
    cout << " 3. Apagar Arquivo\n";
    cout << " 4. Mostrar Tabela FAT\n";
    cout << " 5. Sair\n\n";
    cout << " Digite a opcao desejada: ";
}

int obtemAcao(){
    int opcao;

    exibirMenu();
    cin >> opcao;
    switch(opcao){
        case 1:
            escreverArquivo();
            break;
        case 2:
            lerArquivo();
            break;
        case 3:
            apagarArquivo();
            break;
        case 4:
            mostrarTabelaFAT();
            break;
        case 5:
            cout << "\n Fim.\n";
            return 0;
        default:
            cout << "\n Opcao invalida!\n";
            usleep(1000);
            return 1;
    }
    return opcao;
}

int main(){
    Disk myDisk;
    FatTable myTable(myDisk);

    disk = &myDisk;
    table = &myTable;

    int fim;
    do {
        fim = obtemAcao();
    }while(fim);
    return 0;
}

