#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void SelectionSort(long int *Selec, int n){
    long int i, j, i_min, temp;

    for(i = 0; i < n-1; i++){
        i_min = i;

        for(j = i+1; j < n; j++){
            if(Selec[j] < Selec[i_min]){
                i_min = j;
            }
        }

        if(Selec[i] != Selec[i_min]){
            temp = Selec[i];
            Selec[i] = Selec[i_min];
            Selec[i_min] = temp;
        }
    }
}

void InsertionSort(long int *Insert, int n){
    long int i, j, pivo;

    pivo = 0;
    for(i = 1; i < n; i++){
        pivo = Insert[i];
        j = i-1;

        while(j >= 0 && Insert[j] > pivo){
            Insert[j+1] = Insert[j];
            j = j - 1;
            Insert[j+1] = pivo; 
        }
    }
}

void EscreveArquivo(long int *vetor, int vetor_size, int qtd){
    FILE *arquivo;
    static int index = 0;
    char filename[22];

    while(index < qtd){
        sprintf(filename, "%s_%d", "VetorOrdenado.txt", index);        
        arquivo = fopen(filename, "w");
        index++;

        for(int i = 0; i < vetor_size; i++){
            fprintf(arquivo, "%ld\n", vetor[i]);
        }

        fclose(arquivo);
    }
}

void LerArquivo(const char* filename, int i){
    FILE *arquivo;
    long int numero;
    long int* vetor;
    long int contador = 0;
    clock_t t0, t1;
    double cpu_time_used;

    vetor = (long int*)malloc(100002*sizeof(long int));

    arquivo = fopen(filename, "r");

    if(arquivo == NULL){
        printf("Erro ao abrir o arquivo!\n");
    }

    while(fscanf(arquivo, "%ld", &numero) != EOF){
        vetor[contador] = numero;
        contador++;
    }

    fclose(arquivo);

    t0 = clock();
    SelectionSort(vetor, contador);
    t1 = clock();
    cpu_time_used = ((double) (t1-t0)) / CLOCKS_PER_SEC;
    printf("Arquivo %d: \n", i);
    printf("Tempo de execução do SelectionSort: %f s\n", cpu_time_used);

    t0 = clock();
    InsertionSort(vetor, contador);
    t1 = clock();
    cpu_time_used = ((double) (t1-t0)) / CLOCKS_PER_SEC;
    printf("Tempo de execução do InsertionSort: %f s\n", cpu_time_used);
    printf("\n");
  
    EscreveArquivo(vetor, contador, i);
    free(vetor);
}

int main(int argc, char* argv[]){
    for(int i = 1; i < argc; i++){
        LerArquivo(argv[i], i);
    }
  
    return 0;
}