#include <string.h>
#include <stdio.h>

typedef struct _admin Admin;

typedef struct _admin
{

    char nome[100];
    char senha[4];

} Admin;

void add_admin(Admin *ad, char *nome, char* senha)
{

    strcpy(ad->nome, nome);
    strcpy(ad->senha, senha);
}