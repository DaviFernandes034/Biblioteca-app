#include "livros.c"


int main(){

    Livros li;

    add_livros(&li,"rick riordan", 234, "Os herois do olimpo");
    add_livros(&li,"rick riordan", 123, "Percy Jackson");
    add_livros(&li,"rick riordan", 354, "As cronicas dos kanes");

   // apagar_livro("Os herois do olimpo");

    return 0; 


}