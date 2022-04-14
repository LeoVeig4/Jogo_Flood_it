#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h> //funcao srand
#include <time.h> // sempre ser aleatorio o tabuleiro
#include <string.h>
#define NRECORD 3
typedef struct {
    int pont;
    int tam;          // tamanho do tabuleiro (um quadrado com "tam" casas de lado) (entre 3 e 20)
    int ncor;         // numero de cores usadas (valores entre 1 e "ncor") (entre 3 e 9)
    char nome[6]; // matriz com o estado atual do tabuleiro
} recorde;

typedef struct {
     int tam;          // tamanho do tabuleiro (um quadrado com "tam" casas de lado) (entre 3 e 20)
     int ncor;         // numero de cores usadas (valores entre 1 e "ncor") (entre 3 e 9)
     char mat[22][22]; // matriz com o estado atual do tabuleiro
} tabuleiro;
   
 typedef struct {
    int npos;     // número de posições ocupadas no vetor
    int ncap;     // número de posições que cabem no vetor (quanto foi alocado)
    int *vet;     // local onde colocar os valores salvos no vetor
  } vetor;
   
   void muda_cor(int rl, int gl, int bl, int rf, int gf, int bf)
{
  printf("%c[38;2;%d;%d;%d;48;2;%d;%d;%dm", 27, rl, gl, bl, rf, gf, bf);
}
  // Inicializa o tabuleiro apontado por "tab", para ter o tamanho e o número de cores fornecidas.
  // Retorna true se tudo ok e false em caso de problema (os problemas possíveis são tam ou ncor
  //   não estarem de acordo com as restrições)
  // A matriz deve ser inicializada com números aleatórios entre 1 e ncor na região do tabuleiro 
  //   e com 0 no restante.
bool tab_inic(tabuleiro *tab, int tam, int ncor)
{
    if(tam < 3 || tam > 20){
        printf("\nERRO: tamanho invalido.\n");
        return false;
    }
    if(ncor < 3 || ncor > 9){
        printf("\nERRO: numero de cor invalido.\n");
        return false;
    }
    srand(time(NULL));
    for(int i=1; i<=tam; i++){
        tab->mat[i][0]=0;
        tab->mat[i][tam+1]=0;
        for(int j=1; j<=tam; j++){
            tab->mat[i][j]=rand() % ncor+1;
        }
    }
    for(int i=0; i<=tam+1; i++){
            tab->mat[0][i]=0;
            tab->mat[tam+1][i]=0;
    }
    return true;
}
  
  // Desenha o tabuleiro apontado por "tab".
  // Deve ser desenhado somente a parte da matriz que contém o tabuleiro.
  // Cada posição do tabuleiro deve ser desenhada com 3 caracteres: 
  //   um espaço, um dígito correspondente à cor e outro espaço.
  // Os 3 caracteres devem ser desenhados com a cor de fundo correspondente à cor representada pelo dígito.
  // Para selecionar a cor, use as funções que foram disponibilizadas em alguma aula passada.
  // Você pode escolher as cores que quiser, mas deve ser possível diferenciar facilmente as 9 cores.
  // Você pode decorar o entorno do tabuleiro como quiser.
void tab_desenha(tabuleiro *tab){
    for(int i=0; i <= tab->tam+1; i++){
        for(int j=0; j <= tab->tam+1; j++){
            if( tab->mat[i][j]==0 ){
                muda_cor(100, 100, 100, 100, 100, 100);//cinza
                printf(" 0 ");
            }else if( tab->mat[i][j]==1 ){
                muda_cor(255, 255, 255, 120, 64, 32);//marrom
                printf(" 1 ");
            }else if( tab->mat[i][j]==2 ){
                muda_cor(0, 0, 0, 0, 255, 0);//verde
                printf(" 2 ");
            }else if( tab->mat[i][j]==3 ){
                muda_cor(0, 0, 0, 255, 255, 255);// branco
                printf(" 3 ");
            }else if( tab->mat[i][j]==4 ){
                muda_cor(0, 0, 0, 255, 0, 0);// vermelho
                printf(" 4 ");
            }else if( tab->mat[i][j]==5 ){
                muda_cor(0, 0, 0, 255, 255, 0);//azul fraco
                printf(" 5 ");
            }else if( tab->mat[i][j]==6 ){
                muda_cor(0, 0, 0, 139, 0, 139);//roxo
                printf(" 6 ");
            }else if( tab->mat[i][j]==7 ){
                muda_cor(255, 255, 255, 0, 0, 128);//azul escuro
                printf(" 7 ");
            }else if( tab->mat[i][j]==8 ){
                muda_cor(255, 255, 255, 0, 45, 0);//verde escuro
                printf(" 8 ");
            }else {
                muda_cor(0, 0, 0, 255, 170, 0);//laranja fraco
                printf(" 9 ");
            }
        }
        muda_cor(255, 255, 255, 0, 0, 0);// normal
        printf("\n");
    }
}
// inicializa o vetor apontado por v
    // coloca 0 em npos
void vet_inic(vetor *v){
    v->ncap=0;
    v->npos=0;
    v->vet= NULL;
}
  
    // retorna true se o vetor não contiver nenhuma posição, false caso contenha alguma
bool vet_vazio(vetor *v){
    if(v->npos==0){
        return true;
    }
    return false;
}
  
    // insere os valores a, b no vetor apontado por v
  // caso não tenha sido alocada memória ainda, aloca o suficiente para 2 posições (4 inteiros)
  // caso a capacidade atual do vetor seja insuficiente, realoque o vetor com o dobro da capacidade atual
  // imprime uma mensagem de erro e aborta a execução caso não consiga alocar memória
void vet_insere(vetor *v, int a, int b){
    v->npos++;
    if(v->npos*2 > v->ncap){
        if(v->ncap==0){
            v->ncap=2;
            v->vet = malloc(v->ncap * sizeof(int));
            if(v->vet== NULL){
            printf("Erro: memoria insuficiente");
            exit(1);
            }
        }else{
            v->ncap= v->ncap*2;
            v->vet = realloc(v->vet, v->ncap*sizeof(int));
            if(v->vet== NULL){
            printf("Erro: memoria insuficiente");
            exit(1);
            }
        }
    }
    v->vet[v->npos*2] = a;
    v->vet[v->npos*2+1] = b;
    
}
  
    // remove uma posição (dois inteiros) do vetor apontado por v; coloca esses valores nos locais apontados por pa e pb
  // imprime uma mensagem de erro e aborta a execução do programa caso o vetor esteja vazio
  // caso o número de posições ocupadas seja inferior a 1/3 da capacidade, realoque o vetor com metade da capacidade
void vet_remove(vetor *v, int *px, int *py){
    if(v->npos <= 0){
         printf("ERRO: tentou retirar de vetor vazio");
        exit(1);
    }
    *px= v->vet[v->npos*2];
    *py= v->vet[v->npos*2+1];
    v->npos--;
    if( v->npos*2 < v->ncap/3){
        v->ncap= v->ncap/2;
        v->vet = realloc(v->vet, v->ncap*sizeof(int));
    }
}
//linha, coluna
// preenche no tabuleiro apontado por "tab", a região de mesma cor que inicia na posição "lin,col", com a cor "cor"
void flood_fill(tabuleiro *tab, int lin, int col, int cor){
    int corvelha, px, py;
    vetor v;
    corvelha=tab->mat[lin][col];
    vet_inic(&v);
    vet_insere(&v, lin, col);
    if(corvelha != cor){
        while(!vet_vazio(&v)){
            vet_remove(&v, &px, &py);
            tab->mat[py][px]= cor;
            if(tab->mat[py+1][px] == corvelha){//cima
                vet_insere(&v, px, py+1);
            }
            if(tab->mat[py-1][px] == corvelha){//baixo
                vet_insere(&v, px, py-1);
            }
            if(tab->mat[py][px+1] == corvelha){//direita
                vet_insere(&v, px+1, py);
            }
            if(tab->mat[py][px-1] == corvelha){//esquerda
                vet_insere(&v, px-1, py);
            }
        }
    }
    free (v.vet);
}
bool ganhou(tabuleiro *tab){
    int cor= tab->mat[1][1], aux=0;
    
    for(int i=1; i<=tab->tam; i++){
        for(int j=1; j<=tab->tam; j++){
            if(tab->mat[i][j] == cor){
                aux++;
            }
        }
    }
    if(aux == tab->tam * tab->tam){
        return true;
    } else{
        return false;
    }
    
}
void le_record(int ncor, int ntam, recorde r[], int *achado){
    FILE *entrada;
    entrada = fopen("recorde", "r");
    if(entrada == NULL){
        printf("\nArquivo de recordes nao foi encontrado.");
        exit(1);
    }
    char linha[100], nome[6];
    int cor, tam, pont;
    for(;;){
        fgets(linha, 100, entrada);
        if(feof(entrada)){
            break;
        }
        sscanf(linha, "%d %d %d %s", &tam, &cor, &pont, nome);
        if( ncor == cor && ntam == tam ){
            if (*achado == 3){
                break;
            }
            r[*achado].ncor= cor;
            r[*achado].tam= tam;
            r[*achado].pont= pont;
            strcpy(r[*achado].nome, nome);
            
            *achado = *achado + 1;
        }
    }
    fclose(entrada);
    
}
void continuar(){
    int p;
    for(;;){
        printf("\n\nQuer jogar novamente? Tente uma melhor pontuação\n1 Para jogar novamente ou 2 para parar ");
        setbuf(stdin,NULL);
        scanf(" %d", &p);
        if(p == 2){
            exit (0);
        }else if(p == 1){
            printf("\n\n");
            break;
        } else{
            printf("Opção inalida, tente de novo\n");
        }
    }
}
void grava_recorde(int ncor, int ntam, recorde r[], int achado){
    //abre os arquivos copia e add
    FILE *novo;
    novo= fopen("novo", "w");
    FILE *antigo;
    antigo= fopen("recorde", "r");
    if(antigo == NULL || novo == NULL){
        printf("Erro de abertura de arquivos");
    }
    char linha[100], nome[6];
    int cor, tam, pont, i=0;
    for(;;){
        fscanf(antigo,"%d %d %d %s", &tam, &cor, &pont, nome);
        if(feof(antigo)){
            break;
        }
        if(ncor != cor || ntam != tam){
            fprintf(novo, "%d %d %d %s\n", tam, cor, pont, nome);
        }
    }
    if(achado== NRECORD){
        for(int j=0; j < achado; j++){
            fprintf(novo, "%d %d %d %s\n", ntam, ncor, r[j].pont, r[j].nome);
        }
    }else {
        for(int j=0; j<achado+1; j++){
           fprintf(novo, "%d %d %d %s\n", ntam, ncor, r[j].pont, r[j].nome);
        }
    }
    fclose(antigo);
    //rename("novo", "recorde");
    if(rename("novo", "recorde") != 0){
        printf("Erro ao gravar o nome da pasta de recordes");
        exit(1);
    }
    fclose(novo);
}
void orderna_recorde(recorde r[], int tam){
    int pontaux;
    char nomeaux[5]; //da pra mudar e fazer com tamanhos variáveis
    if(tam != 3){//para funcionar com tam que n seja 3
        tam++;
    }
    for(int i=0; i<tam; i++){
        for(int j=i+1; j<tam; j++){
            if(r[i].pont > r[j].pont){
                pontaux = r[i].pont;
                strcpy(nomeaux, r[i].nome);
                r[i].pont = r[j].pont;
                strcpy(r[i].nome, r[j].nome);
                r[j].pont= pontaux;
                strcpy(r[j].nome, nomeaux);
            }
        }
    }
}
void nome_recorde(char nome[]){
    char nomeaux[30];
    int aux=0;
    do {
        printf("\nDigite o nome para ficar para os Recordes: ");
        setbuf(stdin,NULL);
        fgets(nomeaux, 29, stdin);
        for(int i=0; aux<5; i++){
            if(nomeaux[i] == '\n' || i>30  ){
                break;
            }
            if(nomeaux[i] >='a' && nomeaux[i] <= 'z' || nomeaux[i] >= 'A' && nomeaux[i] <='Z'){
                nome[aux]= nomeaux[i];
                aux++;
            }
        }
        if(aux==0){
            printf("Escreva um nome valido");
        }
    } while(aux==0);
    if( aux < 5 ){
        for(; aux<5; aux++){
            nome[aux]= ' ';
        }
    }
}

int main()
{
    for(;;){
        tabuleiro tab;
        tab.tam= 0;
        tab.ncor=0;
        printf("Para iniciar o jogo, digite um tamanho para o tabuleiro entre 3 e 20: ");
        scanf(" %d", &tab.tam);
        printf("Agora, escolha entre 3 e 9 cores para fazer parte do tabuleiro: ");
        scanf(" %d", &tab.ncor);
    
        if(!tab_inic(&tab, tab.tam, tab.ncor )){
            return 0;
        }
        tab_desenha(&tab);
        int jogadas=0, cor;
        while(!ganhou(&tab)){
            printf("Escolha uma cor, digitando o algarismo que ela representa: ");
            scanf(" %d", &cor);
            if(cor < 1 || cor > tab.ncor){
                printf("COR INVALIDA, tente novamente:\n");
                continue;
            }
            flood_fill(&tab, 1, 1, cor);
            tab_desenha(&tab);
            jogadas++;
        }
        printf("Parabens, voce ganhou em %d jogadas!!", jogadas);
        //mostrar os registros de mesma configuração
        recorde r[NRECORD];
        int achado=0 ;
        le_record( tab.ncor, tab.tam, r, &achado );
        printf("\n\nRecordes da mesma configuracao\n\n");
        
        if(achado==0){
            printf("Ainda nao ha recordes nessa modalidade\n");
        }else{
            for(int i=0 ; i< achado ;i++){
                printf("%d %d %d %s", r[i].ncor, r[i].tam, r[i].pont, r[i].nome);
                printf("\n");
            }
        }
        //se já tem 3 registros e a pontuação atual é igual ou pior desses 3 registros o programa pergunta se ele quer jogar outra partida
        if(achado == 3 && r[NRECORD-1].pont <= jogadas){
            continuar();
        } else{ //senão antes de fazer isso o programa pergunta as iniciais ao jogador e atualiza o arquivo de recordes
            char nomenovo[5];
            if(achado==3){
                r[NRECORD-1].pont= jogadas;
                //insere o nome do novo player
                nome_recorde(nomenovo);
                strcpy(r[NRECORD-1].nome, nomenovo);
                //fazer um ordenador para as pont
                orderna_recorde(r, NRECORD);
            } else{
                r[achado].pont= jogadas;
                //insere o nome do novo player
                nome_recorde(nomenovo);
                strcpy(r[achado].nome, nomenovo);
                //fazer um ordenador para as pont
                orderna_recorde(r, achado);
            }
            grava_recorde(tab.ncor, tab.tam, r, achado);
            continuar();
        }
    }
    
    return 0;
}


