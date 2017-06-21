#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <iostream>
#include <sstream>
#include <iterator>
#include <vector>
#include "libfat.hpp"

using namespace std;

std::shared_ptr<FatTable> table;


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
    table->addFile(filename, input.c_str(), input.size());

    cout << "------------------------------------escrito...\n";
    cout << "\nENTER para sair.";
    cin.clear();
    cin.get();
}

void lerArquivo(){
    string filename, line;
    system("clear");
    cout << "___Ler Arquivo___\n";
    cout << "Digite o nome do arquivo (ex. file1): ";
    cin >> filename;
    filename += ".txt";
    std::vector<char> result = table->readFile(filename);
    if (result.size() > 0) {
        std::string output(result.begin(), result.end());
        cout << "\n----------------------------" << filename << endl;
        cout << output;
        cout << "----------------------------\n";
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
    filename += ".txt";
    if(table->eraseFromDisk(filename))
        cout << "Arquivo apagado..." << endl;
    else cout << "Arquivo inexistente..." << endl;
    cin.get();
    cout << "\nENTER para sair.";
    cin.get();
}

void mostrarTabelaFAT(){
    vector<filedescription> filesFat = table->getFatTable();
    std::stringstream result;

    system("clear");
    cout << "___Mostra Tabela FAT___\n";
    cout << "NOME:\tTAMANHO EM DISCO:\tLOCALIZAÇÃO" << endl;
    for (auto file: filesFat) {
        copy(file.sectors.begin(), file.sectors.end(),
             ostream_iterator<int>(result, " "));
        cout << file.name<< "\t\t" << file.size
            << "\t\t" << result.str() << endl;
    }
    cout << "\nENTER para sair.";
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
    auto myDisk = std::make_shared<Disk>();

    table = std::make_shared<FatTable>(myDisk);

    int fim;
    do {
        fim = obtemAcao();
    }while(fim);
    return 0;
}

