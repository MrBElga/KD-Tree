#define K 2
struct tree
{
    int coord[K];
    struct tree *esq, *dir;
};
typedef struct tree Tree;

struct fila
{
    Tree *raiz;
    struct fila *prox;
};
typedef struct fila Fila;

void initFila(Fila **fila)
{
    *fila = NULL;
}

int isEmpty(Fila *fila)
{
    return fila == NULL;
}

void enqueue(Fila **fila, Tree *raiz)
{
    Fila *novo = (Fila *)malloc(sizeof(Fila));
    novo->raiz = raiz;
    novo->prox = NULL;

    if (isEmpty(*fila))
    {
        *fila = novo;
    }
    else
    {
        Fila *temp = *fila;
        while (temp->prox != NULL)
        {
            temp = temp->prox;
        }
        temp->prox = novo;
    }
}

void dequeue(Fila **fila, Tree **info)
{
    if (!isEmpty(*fila))
    {
        Fila *aux = *fila;
        *info = (*fila)->raiz;
        *fila = (*fila)->prox;
        free(aux);
    }
    else
    {
        *info = NULL;
    }
}

void initTree(Tree **raiz)
{
    *raiz = NULL;
}

int Nula(Tree *raiz)
{
    return raiz == NULL;
}

Tree *CriaNo(int coord[K])
{
    int i;
    Tree *no = (Tree *)malloc(sizeof(Tree));
    no->dir = no->esq = NULL;
    for (i = 0; i < K; i++)

        no->coord[i] = coord[i];
    return no;
}

void exibePontos(int pontos[][K], int tamanho)
{
    int i;
    printf("[");
    for (i = 0; i <= tamanho; i++)
    {
        printf("(%d, %d)", pontos[i][0], pontos[i][1]);
        if (i < tamanho)
            printf(", ");
    }
    printf("]\n");
}

void orderByX(int ponto[][K], int init, int end)
{
    int i, j;
    int(*aux)[K] = malloc((end - init + 1) * sizeof(int[K]));

    for (i = init; i < end; i++)
    {
        for (j = init; j < end - 1; j++)
        {
            if (ponto[j][0] > ponto[j + 1][0])
            {
                aux[0][0] = ponto[j][0];
                aux[0][1] = ponto[j][1];

                ponto[j][0] = ponto[j + 1][0];
                ponto[j][1] = ponto[j + 1][1];

                ponto[j + 1][0] = aux[0][0];
                ponto[j + 1][1] = aux[0][1];
            }
        }
    }
    free(aux);
}

void orderByY(int ponto[][K], int init, int end)
{
    int i, j;
    int(*aux)[K] = malloc((end - init + 1) * sizeof(int[K]));

    for (i = init; i <= end; i++)
    {
        for (j = init; j <= end - 1; j++)
        {
            if (ponto[j][1] > ponto[j + 1][1])
            {
                aux[0][0] = ponto[j][0];
                aux[0][1] = ponto[j][1];

                ponto[j][0] = ponto[j + 1][0];
                ponto[j][1] = ponto[j + 1][1];

                ponto[j + 1][0] = aux[0][0];
                ponto[j + 1][1] = aux[0][1];
            }
        }
    }
    free(aux);
}

// ponto vetor com (x,y) o ponto que deseja inserir , n é o nivel
/*
    ordena(init,end,n);
    meio=(init+end)/2;
    insere o do meio na Tree;
    insereR(&(*raiz)->esq, init,med-1, n+1);
    insereR(&(*raiz)->dir, med+1 ,end, n+1);
*/
void Median(int *x, int init, int end)
{
    *x = (init + end) / 2;
}

void insereR(Tree **raiz, int ponto[][K], int init, int end, int n)
{
    int d, meio = 0;
    if (init <= end)
    {
        // ordena
        d = n % K;
        if (d == 0)
            orderByX(ponto, init, end);
        else
            orderByY(ponto, init, end);

        // calcula mediana
        Median(&meio, init, end);

        if (*raiz == NULL)
            *raiz = CriaNo(ponto[meio]);

        insereR(&(*raiz)->esq, ponto, init, meio - 1, n + 1);
        insereR(&(*raiz)->dir, ponto, meio + 1, end, n + 1);
    }
}

void exibe(Tree *raiz, int nivel)
{
    int i = 0;
    if (!Nula(raiz))
    {
        exibe(raiz->dir, nivel + 1);

        for (i = 0; i < nivel; i++)
        {
            printf("         ");
        }
        if (nivel > 0)
        {
            printf("<-- ");
        }
        printf("(%d, %d)\n", raiz->coord[0], raiz->coord[1]);
        exibe(raiz->esq, nivel + 1);
    }
}

/*
    distancia euclidiana raiz de (x1 - x2)^2 + (y1 - y2)^2
    calcula distancia
    if distancia <= raio: empilha
    if x-raio <= X': empilha (esquerda sempre verificar se não e nula)
    if x+raio >= X': empilha (direita sempre verificar se não e nula)
*/
double distanciaEuclidiana(int x1, int y1, int x2, int y2)
{
    return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

void buscaPontos(Tree *raiz, int pontoConsulta[K], double raio)
{
    if (raiz != NULL)
    {
        Fila *fila, *aux;
        Tree *atual;
        double distancia;
        initFila(&fila);
        initFila(&aux);
        enqueue(&fila, raiz);

        while (!isEmpty(fila))
        {

            dequeue(&fila, &atual);

            distancia = distanciaEuclidiana(pontoConsulta[0], pontoConsulta[1], atual->coord[0], atual->coord[1]);
            if (distancia <= raio && atual->coord[0] != pontoConsulta[0] && atual->coord[1] != pontoConsulta[1])
                enqueue(&aux, atual);
            if (!Nula(atual->esq) && pontoConsulta[0] - raio <= atual->coord[0])
                enqueue(&fila, atual->esq);
            if (!Nula(atual->dir) && pontoConsulta[0] + raio >= atual->coord[0])
                enqueue(&fila, atual->dir);
        }
        if (!isEmpty(aux))
        {
            printf("Pontos no raio %.2f do ponto (%d,%d):", raio, pontoConsulta[0], pontoConsulta[1]);
            while (!isEmpty(aux))
            {
                dequeue(&aux, &atual);
                printf(" (%d,%d)", atual->coord[0], atual->coord[1]);
            }
        }
        else
        {
            printf("Nao ha pontos no raio %.2f do ponto (%d,%d)", raio, pontoConsulta[0], pontoConsulta[1]);
        }
    }
}
