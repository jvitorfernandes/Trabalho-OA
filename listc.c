#include <stdio.h>

int main(int argc, char *argv[])
{
    char ch;
    FILE * file;
    char filename[256];
    printf("Enter the name of the file:\n");
    gets(filename);
    file = fopen(filename,"r");
    while (fread(&ch, 1, 1, file) != 0)
        fwrite(&ch, 1, 1, stdout);
    fclose(file);
    return 0;
}
