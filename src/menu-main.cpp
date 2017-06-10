#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <iostream>
#include <fstream>

using namespace std;

void obtemAcao();

void escreverArquivo(){
    string input, filename;
    ofstream file;
    system("clear");
    cout << "___Escrever arquivo___\n";
    cout << "Digite nome do arquivo (ex. file1.txt): ";
    cin >> filename;
    while (filename.size()>128){
        cout << "Nome muito grande! Por favor digite outro(128 max): ";
        cin >> filename;
    }
    cout << "Opening \'" << filename <<"\' file.";

    file.open(filename);

    cout << "\n\nDigite seu texto, para finalizar CTRL+D duas vezes.\n";
    cout << "------------------------------------\n";
    while(cin){
        getline(cin, input);
	if(input.empty())
            continue;
	if(cin)
	    file << input << '\n';
    }
    //TODO :: Função para inserir na tabela fat.
    file.close();
    cout << "\n------------------------------------escrito...\n";
    cout << "ENTER para sair.";
    cin.get();
}

void lerArquivo(){
  string infile, line;
    fstream file;
    system("clear");
    cout << "___Ler arquivo___\n";
    cout << "Digite o nome do arquivo (ex. file1.txt): ";
    cin >> infile;
    file.open(infile);
    if (file.is_open()) {
        cout << "\n----------------------------" << infile << endl;
        while (getline(file, line)) {
	        cout << line << endl;
        }
        cout << "----------------------------\n";
        file.close();
    }
    else cout << "Não foi possível abrir o arquivo...\n";
    cout << "\nENTER para sair.";
    cin.get();
}

void apagarArquivo(){

}

void mostrarTabelaFAT(){

}

int exibirMenu()
{
    int opcao;
    system("clear");

    cout << "MENU\n\n";
    cout << " 1. Escrever Arquivo\n";
    cout << " 2. Ler Arquivo\n";
    cout << " 3. Apagar Arquivo\n";
    cout << " 4. Mostrar Tabela FAT\n";
    cout << " 5. Sair\n\n";
    cout << " Digite a opcao desejada: ";
    scanf("%d", &opcao);

    return opcao;
}

void obtemAcao(){
    int opcao;

    do {
        opcao = exibirMenu();

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
	            break;
	        default:
		    cout << "\n Opcao invalida!\n";
	            usleep(1000000);
        }
    } while (opcao != 5);

}

int main(){
    obtemAcao();
    return 0;
}

