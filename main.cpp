#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void escreverArquivo(){

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
