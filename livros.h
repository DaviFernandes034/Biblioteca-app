#include <livros.c>
#ifndef LIVROS_H
#define LIVROS_H

void add_livros(Livros* li, char* autor, int paginas, char* nome);
void apagar_livro(const char* nome_livro);
// Adicione outras declarações de função

#endif // LIVROS_H
