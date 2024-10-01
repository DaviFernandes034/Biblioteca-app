#include <gtk/gtk.h>
#include "livros.c"
#include "admin.c"
#include <stdbool.h>
#include <stdlib.h>



GtkBuilder *builder;
GtkWidget *window;
GtkStack *stack;
GtkListStore *modelo_Armazenamento;


void on_main_window_destroy(GtkWidget *widget, gpointer data){

    gtk_main_quit();
}

void on_lembrar_clicked(GtkWidget *widget, gpointer data){

  
}

//funcao para chamar a caixa de dialogo

void mensagem(char text[100], char segundo_text[100], char icon_name[100]){

    GtkMessageDialog *mensagem =gtk_builder_get_object(builder, "mensagem");

    //funcoes para carregar os objets de textos e o icone
    g_object_set(mensagem, "text", text, NULL);
    g_object_set(mensagem, "secondary_text", segundo_text, NULL);
    g_object_set(mensagem, "icon_name", icon_name, NULL);

    gtk_widget_show_all(mensagem); //mostra na tela
    gtk_dialog_run(mensagem); //aguarda o usuaria clicar na tela
    gtk_widget_hide(mensagem); //esconde a caixa de dialogo

}
//funcao pra testar o login e chamar a segunda parte da aplicação
void loggin(char *nome, char* senha, bool *lembrar){

    Admin *ad;

    add_admin(ad, "rada", "1234");

    if ((strcmp(ad->nome, nome) == 0) && (strcmp(ad->senha, senha) == 0)){

         g_print("usuario logado");
         mensagem("Bem vindo", "Usuario logado", "emblem-default");
         gtk_stack_set_visible_child_name(stack, "view_inicial");

    }else{

        g_print("loggin errado");
        mensagem("mal vindo", "Usuario não logado", "emblem-default");
    }

}

//funcao do botao login
void on_logn_btn_clicked(GtkWidget *widget, gpointer data){

   char *nome = gtk_entry_get_text(gtk_builder_get_object(builder, "nome"));
  char *senha = gtk_entry_get_text(gtk_builder_get_object(builder, "senha"));
  bool *lembrar = gtk_toggle_button_get_active(gtk_builder_get_object(builder, "lembrar"));

  loggin(nome, senha, lembrar); 
  
}

void on_btn_cadastrar_inicial_clicked(GtkWidget *widget, gpointer data){

     gtk_stack_set_visible_child_name(stack, "view_cadastro");
}

void on_btn_listar_clicked(GtkWidget *widget, gpointer data){

     gtk_stack_set_visible_child_name(stack, "view_listar");
}

void on_btn_sair_clicked(GtkWidget *widget, gpointer data){
 
    gtk_stack_set_visible_child_name(stack, "view_inicial");

}

void on_btn_voltar_cad_clicked(GtkWidget *widget, gpointer data){

        gtk_stack_set_visible_child_name(stack, "view_inicial");

}

void on_btn_cadastrar_clicked(GtkWidget *widget, gpointer data){

    char *autor = gtk_entry_get_text(gtk_builder_get_object(builder, "cad_autor"));
    char *cad_nome = gtk_entry_get_text(gtk_builder_get_object(builder, "cad_nome"));
    char *paginas_text = gtk_entry_get_text(gtk_builder_get_object(builder, "cad_pagina"));

    //convertendo a string paginas para inteiro
    int paginas = atoi(paginas_text);

    

    if (strcmp(autor, "") == 0 || strcmp(cad_nome, "") == 0 || paginas == 0){

        mensagem("AVISO","Todos os campos são obrigatorios", "dialog-error");
    }else{

        Livros *li = (Livros*) malloc(sizeof(Livros));

        if (li == NULL) {
              mensagem("ERRO", "Falha na alocação de memória", "dialog-error");
                return; // Verifique se a alocação foi bem-sucedida
        }

        add_livros(li,autor,paginas, cad_nome);
        mensagem("AVISO","livro cadastrado com sucesso", "emblem-default");
        
    }
}

void on_btn_listar_voltar_clicked(GtkWidget *widget, gpointer data){

    gtk_stack_set_visible_child_name(stack, "view_inicial");
}

void on_btn_listar_listar_clicked(GtkWidget *widget, gpointer data){

    char linha[256];
    char livro[100], autor[100]; 
    int paginas;
    FILE *arquivo;
    GtkTreeIter iter;
    // Limpar o modelo de armazenamento anterior
    gtk_list_store_clear(modelo_Armazenamento);


    // Abrir o arquivo .txt
    arquivo = fopen("livros.txt", "r");
    if (arquivo == NULL) {
        mensagem("AVISO", "Erro ao abrir arquivo", "dialog-error");
        return;
    }


    

    // Ler o conteúdo do arquivo linha por linha
    while (fgets(linha, sizeof(linha), arquivo)) {

            // Procurar e extrair o nome do livro
        if (sscanf(linha, "livro: %[^,]", livro) == 1) {
            // Ler a linha seguinte para obter o autor
            fgets(linha, sizeof(linha), arquivo);
            sscanf(linha, "autor: %[^,]", autor);

            // Ler a próxima linha para obter o número de páginas
            fgets(linha, sizeof(linha), arquivo);
            sscanf(linha, "paginas: %d", &paginas);

            // Adicionar uma nova linha ao modelo de armazenamento
            gtk_list_store_append(modelo_Armazenamento, &iter);
            gtk_list_store_set(modelo_Armazenamento,&iter,

                                        0,autor,
                                        1,livro,
                                        2,paginas,
                                        -1 );

     
        }
 
    }

    // Fechar o arquivo após leitura
         fclose(arquivo);
}


int main(int argc, char *argv[]){

    gtk_init(&argc, &argv);

    builder = gtk_builder_new_from_file("appBiblioteca.glade");

    gtk_builder_add_callback_symbols(
    builder,
    "on_main_window_destroy", G_CALLBACK(on_main_window_destroy),
    "on_lembrar_clicked", G_CALLBACK(on_lembrar_clicked),
    "on_logn_btn_clicked", G_CALLBACK(on_logn_btn_clicked),
    "on_btn_cadastrar_inicial_clicked", G_CALLBACK(on_btn_cadastrar_inicial_clicked),
    "on_btn_listar_clicked", G_CALLBACK(on_btn_listar_clicked),
    "on_btn_sair_clicked", G_CALLBACK(on_btn_sair_clicked),
    "on_btn_voltar_cad_clicked", G_CALLBACK(on_btn_voltar_cad_clicked),
    "on_btn_cadastrar_clicked", G_CALLBACK(on_btn_cadastrar_clicked),
    "on_btn_listar_voltar_clicked", G_CALLBACK(on_btn_listar_voltar_clicked),
    "on_btn_listar_listar_clicked", G_CALLBACK(on_btn_listar_listar_clicked),
    NULL);
gtk_builder_connect_signals(builder,NULL);

stack = GTK_STACK(gtk_builder_get_object(builder, "stack"));
window = GTK_WIDGET(gtk_builder_get_object(builder, "main_window"));
modelo_Armazenamento = GTK_LIST_STORE(gtk_builder_get_object(builder, "liststore1"));
gtk_widget_show_all(window);
gtk_main();
return 0;

}
