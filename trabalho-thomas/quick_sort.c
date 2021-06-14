#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include <limits.h>

#define MAX_VALUE_IN_ARRAY 100000

int *build_array(int size)
{
    // função que cria um vetor de size posições

    int *array = (int *)malloc(size * sizeof(int));

    srand(time(NULL));

    for (int i = 0; i < size; i++)
        *(array + i) = rand() % (MAX_VALUE_IN_ARRAY);

    return array;
}

void swap(int *a, int *b)
{
    //Função para inverter o valor de duas variáves. Como são usados ponteiros, o valor efetivamente é mudado na posição de memória.
    int aux;
    aux = *a;
    *a = *b;
    *b = aux;
}

void swap_if_a_gt_b(int *a, int *b)
{
    //essa função encapsula a lógica comum a vários algoritmos de ordenação de trocar dois valores se um for maior que outro
    if ((*a > *b))
        swap(a, b);
}

void print_array(int *p_array, int first_index, int last_index)
{
    // função auxiliar para imprimir todos os elementos do vetor
    for (int i = first_index; i <= last_index; i++)
        printf("\n%d - %d", i, *(p_array + i));
}

double calculate_difference(clock_t start, clock_t end)
{
    return (double)(end - start) / ((CLOCKS_PER_SEC) / 1000);
}

void position_pivot_in_the_end(int *p_array, int first_index, int last_index)
{
    // para escolher o pivot, a técnica utilizada é a mediana entre o primeiro, último e elemento central.

    int center_index = (first_index + last_index) / 2;

    //posiciona o pivot no centro do array através da mediana
    swap_if_a_gt_b((p_array + first_index), (p_array + last_index));
    swap_if_a_gt_b((p_array + first_index), (p_array + center_index));
    swap_if_a_gt_b((p_array + center_index), (p_array + last_index));

    //posiciona o pivot no final do array
    swap((p_array + center_index), (p_array + last_index));
}

int partition(int *p_array, int first_index, int last_index)
{
    //função responsável por posicionar o pivot no lugar correto com todos os elementos menores que ele a esquerda e maiores a direita

    // posiciona o pivot no final do array
    position_pivot_in_the_end(p_array, first_index, last_index);

    //essa lógica é responsável por manter o elementos maiores que o pivot à direita dos elementos menores
    int index_from_left = first_index;
    for (int index_from_right = first_index; index_from_right < last_index; index_from_right++)
    {
        //verifica-se a cada valor do vetor se esse é menor do que o pivot.
        if (*(p_array + index_from_right) < *(p_array + last_index))
        {
            //se o valor for menor que o pivot, é necessário colocar ele na menor posição após os outros valores que sabemos ser menores também
            swap((p_array + index_from_left), (p_array + index_from_right));
            //após isso, incrementa-se o índice
            index_from_left++;
        }
    }

    index_from_left++;

    //por último troca-se a posição do pivot com o primeiro maior elemento encontrado
    swap((p_array + index_from_left), (p_array + last_index));

    return index_from_left;
}

void quick_sort(int *p_array, int first_index, int last_index)
{
    //condição da chamada recursiva do quick sort
    if (last_index <= first_index)
        return;

    //chama a função partition que retorna a posição correta do novo pivot
    int pivot_index = partition(p_array, first_index, last_index);

    //o quick sort é um algoritmo recursivo, chamado para sub-vetores tantas vezes quando necessário para ordenar completamente o vetor original
    quick_sort(p_array, first_index, pivot_index - 1);
    quick_sort(p_array, pivot_index + 1, last_index);
}

int main()
{
    setlocale(LC_ALL, "");

    clock_t start, end;
    int *quick_sorted;
    double quick_sort_time;

    for (int array_size = 50000; array_size <= 200000; array_size += 50000)
    {
        //é feito um loop passando por 50k, 100k, 150k e 200k entradas para verificar a performance do algoritmo
        printf("\n\nMedindo tempos para %d valores", array_size);

        quick_sorted = build_array(array_size);

        start = clock();
        quick_sort(quick_sorted, 0, array_size - 1);
        end = clock();

        quick_sort_time = calculate_difference(start, end);
        printf("\nQuick Sort: %10.4f", quick_sort_time);
    }
}