#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

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

void obtemAcao();

void escreverArquivo(){
    char *cg;
    char ch, filename[256];
    FILE * file;
    system("clear");
    printf("___Escrever arquivo___\n");
    printf("Digite nome do arquivo: ");
    scanf("\n");
    fgets(filename, sizeof(filename), stdin);
    filename[strcspn(filename, "\n")] = 0;
    printf("Opening \'%s\' file.", filename);

    file = fopen(filename, "w");

    printf("\n\nDigite seu texto, para finalizar CTRL+C.\n");
    while (fread(&ch, 1, 1, stdin) != 0)
        fwrite(&ch, 1, 1, file);//implementar forma de sair da escrita
    //TODO nao funcionando ainda funcao de escrita em arquivo
    fclose(file);
    printf("\n------------------------------------\n");
    printf(" 1. Escrever novo arquivo\n 2. Voltar ao menu");
    printf(" Digite a opção desejada: ");
    int opcao;
    scanf("%d", &opcao);
    switch (opcao){
        case 1:
            escreverArquivo();
            break;
        case 2:
            obtemAcao();
            break;
    }
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
	            printf("\n Fim.\n");
	            break;
	        default:
	            printf("\n Opcao invalida!");
	            usleep(1000000);
        }
    } while (opcao != 5);

}

int main(){
    obtemAcao();
    return 0;
}
