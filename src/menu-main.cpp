#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

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

