#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <iostream>
#include <istream>
#include <fstream>


using namespace std;

int obtemAcao();

void escreverArquivo(){
    string input, filename, aux;
    ofstream file;
    system("clear");
    cout << "___Escrever arquivo___\n";
    cout << "Digite nome do arquivo (ex. file1): ";
    cin >> filename;
    filename += ".txt";
    while (filename.size()>96){
        cout << "Nome muito grande! Por favor digite outro(96 max): ";
        cin >> filename;
    }
    cout << "Abrindo o arquivo: " << filename;

    file.open(filename);

    cout << "\n\nDigite seu texto, para finalizar CTRL+D.\n";
    cout << "------------------------------------\n";
    while(cin >> input){
        aux += input;
        aux += ' ';
    }
    file << aux;
    file << endl;
    //TODO :: Função para inserir no disco.
    file.close();
    cout << "\n------------------------------------escrito...\n";
    cout << "ENTER para sair.";
    cin.clear();
    cin.get();
}

void lerArquivo(){
  string infile, line;
    fstream file;
    system("clear");
    cout << "___Ler arquivo___\n";
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

}

void mostrarTabelaFAT(){

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
            usleep(1000000);
            return 1;
    }
    return opcao;
}

int main(){
    int fim;
    do {
        fim = obtemAcao();
    }while(fim);
    return 0;
}

