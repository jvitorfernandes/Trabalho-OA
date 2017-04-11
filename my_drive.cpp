#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>

using namespace std;

//CARACTERISTICAS DO DISCO
#define TRILHAS_PC 5
#define SETORES_PT 60
#define TRILHAS_PF 10
#define T_SETOR 512
#define T_CLUSTER 4
#define t_SEEK_med 4
#define t_SEEK_min 1
#define t_LATENCIA_med 6
#define t_TRANSF 12

typedef struct block { unsigned char bytes_s[T_SETOR]; } block;
typedef struct sector_array { block sector[SETORES_PT]; } sector_array;
typedef struct track_array { sector_array track[TRILHAS_PC]; } track_array;

typedef struct fatlist_s {
    char file_name[100];
    unsigned int first_sector;
} fatlist;

typedef struct fatent_s {
    unsigned int used;
    unsigned int eof;
    unsigned int next;
} fatent;

void escreverArquivo(){
    string filename;
    cout << "___Escrever arquivo___" << endl;
    cout << "Digite nome do arquivo: ";
    cin >> filename;
}

void lerArquivo(){

}

void apagarArquivo(){

}

void mostrarTabelaFAT(){

}

int exibirMenu()
{
    int opcao;

    system("clear");

    printf("MENU\n\n");
    printf(" 1. Escrever Arquivo\n");
    printf(" 2. Ler Arquivo\n");
    printf(" 3. Apagar Arquivo\n");
    printf(" 4. Mostrar Tabela FAT\n");
    printf(" 5. Sair\n\n");
    printf(" Digite a opcao desejada: ");
    scanf("%d", &opcao);

    return opcao;
}

int main(){
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
	            printf("\n Fim.\n");
	            break;
	        default:
	            printf("\n Opcao invalida!");
	            usleep(1000000);
        }
    } while (opcao != 5);

    return 0;
}
