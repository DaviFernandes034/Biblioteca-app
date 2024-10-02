<h1>biblioteca app</h1>

<p>App de uma biblioteca fictica feito em linguagem C usando a interface grafica GTK</p>
<br>
<p>app feito para o projeto de extensão do curso de ciêncis da computação, 4°semestre</p>
<p>Para utiliza-lo:</p>
<li>
  git clone https://github.com/DaviFernandes034/Biblioteca-app.git. Apos isso baixar as dependencia do gtk:
      <li>
        sudo apt install libgtk-3-dev
      </li>
      <li>depois, rodar os comandos:</li>
      <li>gcc `pkg-config --cflags gtk+-3.0` -o SEU_DIRETORIO/main.c `pkg-config --libs gtk+-3.0`</li>
      <li>./main</li>
</li>

<p>obs: não testei no windows, sistema operacional usado no desenvolvimento foi Linux</p>

