#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <stdlib.h>
#include <time.h>
#include "forca.h"

//var globais
char palavraSecreta[TAMANHO_PALAVRA];
char chutes[26];
int chutesDados = 0;

 
void abertura() {
    printf("**********************\n");
    printf("*    Jogo da Forca   *\n");
    printf("**********************\n\n");
}

void chuta() {
        char chute;
        printf("Qual letra? ");
        scanf(" %c", &chute);
        chutes[chutesDados] = chute;
        chutesDados++;
}

void desenhaforca(){

    int erros = chutesErrados();
    printf("  _______       \n");
    printf(" |/      |      \n");
    printf(" |      %c%c%c  \n", (erros >= 1 ? '(' : ' '), (erros >= 1 ? '_' : ' '), (erros >= 1 ? ')' : ' '));
    printf(" |      %c%c%c  \n", (erros >= 3 ? '\\' : ' '), (erros >= 2 ? '|' : ' '), (erros >= 3 ? '/' : ' '));
    printf(" |       %c     \n", (erros >= 2 ? '|' : ' '));
    printf(" |      %c %c   \n", (erros >= 4 ? '/' : ' '), (erros >=4 ? '\\' : ' '));
    printf(" |              \n");
    printf("_|___           \n");
    printf("\n\n");

    for(int i = 0; i < strlen(palavraSecreta); i++){
        int achou = jachutou(palavraSecreta[i]);

        if(achou){
            printf("%c ", palavraSecreta[i]);
        } else {
            printf("_ ");
        }
    }
    printf("\n");

}

void adicionaPalavra(){
    char quero;
    printf("Você deseja adicionar uma nova palavra no jogo? (S/N): ");
    scanf(" %c", &quero);
    if(quero == 'S'){
        char novaPalavra[TAMANHO_PALAVRA];
        printf("Qual a nova palavra? ");
        scanf("%s", novaPalavra);

        FILE* f;
        f = fopen("palavras.txt", "r+");
        if(f == 0){
            printf("Desculpe, banco de dados não disponivel!\n\n");
            exit(1);
        }

        int qtd;
        fscanf(f, "%d", &qtd);
        qtd++;

        fseek(f, 0, SEEK_SET);
        fprintf(f, "%d", qtd);

        fseek(f, 0, SEEK_END);
        fprintf(f, "\n%s", novaPalavra);

        fclose(f);
    }
}

void escolhepalavra(){
    FILE* f;
    f = fopen("palavras.txt", "r");
    if(f == 0){
        printf("Desculpe, banco de dados não disponivel!\n\n");
        exit(1);
    } 

    int qntdepalavras;
    fscanf(f, "%d", &qntdepalavras);

    srand(time(0));
    int randomico = rand() % qntdepalavras;

    for(int i = 0; i <= randomico; i++){
        fscanf(f,"%s", palavraSecreta);
    }

    fclose(f);
}

int acertou(){
    for(int i = 0; i < strlen(palavraSecreta); i ++){
        if(!jachutou(palavraSecreta[i])){
            return 0;
        }
    }
    return 1;
}

int chutesErrados(){
    int erros = 0;
    for(int i = 0; i < chutesDados; i++){
        int existe = 0;
        for(int j = 0; j < strlen(palavraSecreta); j++){
            if(chutes[i] == palavraSecreta[j]){
                existe = 1;
                break;
            }
        }
        if(!existe) erros++; 
    }
    return erros;
}

int enforcou(){
    return chutesErrados() >= 5;
}

int jachutou(char letra){
    int achou = 0;

    for(int j = 0; j < chutesDados; j++){           
        if(chutes[j] == letra){
            achou = 1;
            break;
        }
    }
    return achou;
}

void mensagemAcertou(){
    printf("Parabéns, você ganhou!\n");
    printf("          {}        \n");
    printf("         /__\\       \n"); 
    printf("       /|    |\\     \n");  
    printf("      (_|    |_)    \n"); 
    printf("         \\  /       \n");
    printf("          )(        \n"); 
    printf("        _|__|_      \n"); 
    printf("      _|______|_    \n");
    printf("     |__________|   \n\n");
}

void mensagemPerdeu(){
    printf("Puxa, você foi enforcado, tente novamente!\n");
    printf("       ______          \n");
    printf("    .-"      "-.       \n");
    printf("   /           \\      \n");
    printf("  |              |     \n");
    printf("  |,  .-.  .-.  ,|     \n");
    printf("  | )(__/ \\__)( |     \n"); 
    printf("  |/     /\\   \\|     \n");
    printf("  (_     ^^     _)     \n");
    printf("  \\__|IIIIII|__/      \n");
    printf("    |\\IIIIII/ |       \n");  
    printf("   \\          /       \n");
    printf("     `--------`        \n\n"); 
}


int main() {
    setlocale(LC_ALL, "Portuguese_Brazil");

    escolhepalavra(palavraSecreta);
    abertura();

    do{
        desenhaforca();
        //captura um novo chute
        chuta();
    } while(!acertou() && !enforcou());
    if(acertou()){
        mensagemAcertou();
    } else {
        mensagemPerdeu();
    }
}
