#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <windows.h>
#include "tad.h"

#define K 2

// ordena o vetor por x
// {{5,25}, {10,12}, {30,40}, {35,45}, {50,30} ,{70,70}};
// calcula a mediana e insere quem ficou para tras
//    x          {30,40}
// ordenar o vetor por y
// {{10,12},{5,25},  {30,40} ,{50,30}, {35,45}, {70,70}}
//    x            {30,40}
//    y    {10,12}       {35,45}
// ordena o veto por X
//{{5,25},{10,12},  {30,40} ,{35,45},{50,30},{70,70}}
//   x                       {30,40}
//   y       {10,12}                         {35,45}
//   x               {5,25}       {50,30}            {70,70}

int main()
{
    system("MODE con cols=200 lines=50");
    system("title KD-Tree");
    system("cls");

    int n = 6, i;
    int coord[n][K];
    double raio = 10.0;
    int pontoConsulta[K];
    Tree *raiz;
    
    srand(time(NULL));
    for (i = 0; i < n; i++)
    {
        coord[i][0] = rand() % 100;
        coord[i][1] = rand() % 100;
    }

    printf("pontos gerados a partir de n = %d: ",n);
    exibePontos(coord, n - 1);
    printf("\n");

    initTree(&raiz);
    n = sizeof(coord) / sizeof(coord[0]);
    insereR(&raiz, coord, 0, n - 1, 0);
    printf("======================================ARVORE======================================\n");
    exibe(raiz, 0);
    printf("==================================================================================\n");

    printf("\n\n\n=================================BUSCA PELO PONTO=================================\n");
    pontoConsulta[0] = coord[(n - 1) / rand() % 10][0];
    pontoConsulta[1] = coord[(n - 1) / rand() % 10][1];
    buscaPontos(raiz, pontoConsulta, raio);
    printf("\n==================================================================================\n");
    return 0;
}
