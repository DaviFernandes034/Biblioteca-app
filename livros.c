#include <stddef.h>
#include <string.h>
#include <stdio.h>


#define MAX_LIVRO 100

typedef struct _livros Livros;


typedef struct _livros{

    char autor[100];
    int paginas;
    char nome[100];

} Livros;


void add_livros(Livros* li, char* autor, int paginas, char* nome){

    strcpy(li->autor, autor);
    li->paginas = paginas;
    strcpy(li->nome, nome);

    FILE * arquivo = fopen("livros.txt", "a");
    if (arquivo == NULL){
        printf("erro ao abrir o arquivo. \n");
        return;
    }

    fprintf(arquivo, "livro: %s,\n autor: %s,\n paginas %d\n\n", nome, autor, paginas);

    fclose(arquivo);

    printf("livro adicionado!! \n");
   
}

 /*
 
 @author Davi fernandes
 @brief apaga o livro passado no parametro, na verdade o ato de "remover" consiste em criar um
 arquivo temporario identico ao original, caso o livro passado no parametro seja econtrado,
 adicionamos o dados do arquivo original na copia, sem o livro encontado no parametro, assim 
 apgamos o original e renomeamos a copia para virar o original

 
 */
void apagar_livro(const char* nome_livro){

    FILE * arquivo = fopen("livros.txt", "r"); //abrindo o arquivo para leitura
    FILE * temp = fopen("temp.txt", "w"); //arquivo temporario para a ecrita

    if (arquivo == NULL || temp == NULL){
       printf("erro ao abrir o arquivo");
       return; 
    }

    char linha[256];
    int encontrado = 0;

    while(fgets(linha, sizeof(linha),arquivo)){ //usando o fgets para lero texto do arquivo

        if(strstr(linha, nome_livro) ==  NULL){ //usando strstr para 
        //procurar o parametro de "nome_livro", na string linha
            fputs(linha, temp); //se não encontrar, copia a linha para o arquivo temporario
            
        }else{
            encontrado = 1;
        }
    }

    fclose(arquivo);
    fclose(temp);

    if(encontrado){
        remove("livros.txt");//remove o arquivo "livros.txt"
        rename("temp.txt","livros.txt"); //renomeia o arquivo "temp.txt" para "livros.txt"
        printf("livro: '%s' , removido com sucesso.\n", nome_livro);

    }else{
        remove("temp.txt");//caso o livro não for encotrado, remove o arquivo temporario
        printf("livro: %s, não encontrado.\n", nome_livro);
    }


}



