#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include <limits.h>

#define MAX_VALUE_IN_ARRAY 100000

int test_array[] = {33, 45, 80, 2, 0, 9, 50};

int *build_array(int size)
{
    int *array = (int *)malloc(size * sizeof(int));

    srand(time(NULL));

    for (int i = 0; i < size; i++)
        *(array + i) = rand() % (MAX_VALUE_IN_ARRAY);

    return array;
}

int *copy_array(int *original_array, int size)
{
    int *array = (int *)malloc(size * sizeof(int));

    for (int i = 0; i < size; i++)
        *(array + i) = *(original_array + i);

    return array;
}

void swap(int *a, int *b)
{
    int aux;
    aux = *a;
    *a = *b;
    *b = aux;
}

void swap_if_a_gt_b(int *a, int *b)
{
    if ((*a > *b))
        swap(a, b);
}

void print_array(int *p_array, int first_index, int last_index)
{
    for (int i = first_index; i <= last_index; i++)
        printf("\n%d - %d", i, *(p_array + i));
}

void bubble_sort(int *p_array, int size)
{
    for (int i = 0; i < size; i++)
        for (int j = 0; j < (size - i - 1); j++)
            swap_if_a_gt_b((p_array + j), (p_array + j + 1));
}

void selection_sort(int *p_array, int size)
{
    int *greater;
    for (int i = 0; i < size; i++)
    {
        greater = p_array + size - i - 1;
        for (int j = 0; j < (size - i); j++)
            if (*(p_array + j) > *greater)
                swap((p_array + j), greater);
    }
}

void insertion_sort(int *p_array, int size)
{
    int *smaller;
    for (int i = 0; i < size; i++)
    {
        smaller = p_array + i;
        for (int j = i; j < size; j++)
            if (*(p_array + j) < *smaller)
                swap((p_array + j), smaller);
    }
}

int partition(int *p_array, int first_index, int last_index)
{
    int index_from_left;
    int index_from_right;

    int center_index = (first_index + last_index) / 2;

    //posiciona o pivot no centro do array como a mediana entre o primeiro, último e elemento central.
    swap_if_a_gt_b((p_array + first_index), (p_array + last_index));
    swap_if_a_gt_b((p_array + first_index), (p_array + center_index));
    swap_if_a_gt_b((p_array + center_index), (p_array + last_index));

    //posiciona o pivot no final do array
    swap((p_array + center_index), (p_array + last_index));

    while (1)
    {

        //posiciona o index of elemento from left no primeiro elemento maior que o pivot
        for (; *(p_array + index_from_left) < *(p_array + last_index); index_from_left++)
            ;

        //posiciona o index of elemento from right no primeiro elemento menor que o pivot
        for (; *(p_array + index_from_right) > *(p_array + last_index); index_from_right--)
            ;

        // se o indice da esquerda for maior ou igual que o da direita significa que todos os menores elementos estão a esquerda de todos os maiores elementos que o pivot
        if (index_from_left >= index_from_right)
            break;

        //inverte as posições do elemento a esquerda e a direita
        swap((p_array + index_from_left), (p_array + index_from_right));
    }

    //por último troca-se a posição do pivot com o primeiro maior elemento encontrado
    swap((p_array + index_from_right + 1), (p_array + last_index));

    return index_from_right + 1;
}

void quick_sort(int *p_array, int first_index, int last_index)
{
    //condição da chamada recursiva do quick sort
    if (last_index <= first_index)
        return;

    int pivot_index = partition(p_array, first_index, last_index);

    if ((pivot_index <= first_index) || (pivot_index >= last_index))
        return;

    quick_sort(p_array, first_index, pivot_index);
    quick_sort(p_array, pivot_index + 1, last_index);
}

int *sublist(int *p_array, int start, int end)
{
    int *new_list = (int *)malloc((end - start + 2) * sizeof(int));
    int j = 0;

    for (int i = start; i <= end; i++)
    {
        *(new_list + j) = *(p_array + i);
        j++;
    }

    *(new_list + j) = INT_MAX;
    return new_list;
}

void merge(int *p_array, int first_index, int center, int last_index)
{
    int *first_array = sublist(p_array, first_index, center);
    int *second_array = sublist(p_array, center + 1, last_index);

    int first_array_counter = 0;
    int second_array_counter = 0;

    for (int i = first_index; i <= last_index; i++)
    {
        if (first_array[first_array_counter] <= second_array[second_array_counter])
        {
            *(p_array + i) = first_array[first_array_counter];
            first_array_counter++;
        }
        else
        {
            *(p_array + i) = second_array[second_array_counter];
            second_array_counter++;
        }
    }
}

void merge_sort(int *p_array, int first_index, int last_index)
{
    if (last_index <= first_index)
        return;

    int center = (last_index + first_index) / 2;

    merge_sort(p_array, first_index, center);
    merge_sort(p_array, center + 1, last_index);
    merge(p_array, first_index, center, last_index);
}

double calculate_difference(clock_t start, clock_t end)
{
    return (double)(end - start) / ((CLOCKS_PER_SEC) / 1000);
}

void test(void)
{
    // int array_size = sizeof(test_array) / sizeof(test_array[0]);
    // int *p_array = test_array;

    int array_size = 500;
    int *p_array = build_array(array_size);

    printf("\nOriginal Array:");
    print_array(p_array, 0, array_size - 1);

    int *bubble_sorted = copy_array(p_array, array_size);
    int *selection_sorted = copy_array(p_array, array_size);
    int *insertion_sorted = copy_array(p_array, array_size);
    int *merge_sorted = copy_array(p_array, array_size);
    int *quick_sorted = copy_array(p_array, array_size);

    // printf("\nBubble Sort:");
    // bubble_sort(bubble_sorted, array_size);
    // print_array(bubble_sorted, 0, array_size - 1);

    // printf("\nSelection Sort:");
    // selection_sort(selection_sorted, array_size);
    // print_array(selection_sorted, 0, array_size - 1);

    // printf("\nInsertion Sort:");
    // insertion_sort(insertion_sorted, array_size);
    // print_array(insertion_sorted, 0, array_size - 1);

    // printf("\nMerge Sort:");
    // merge_sort(merge_sorted, 0, array_size - 1);
    // print_array(merge_sorted, 0, array_size - 1);

    printf("\nQuick Sort:");
    quick_sort(quick_sorted, 0, array_size - 1);
    print_array(quick_sorted, 0, array_size - 1);

    printf("\nTest finished");
}

int main()
{
    int is_test = 1;

    setlocale(LC_ALL, "");

    clock_t start, end;
    int array_size = 0;
    int *p_array;

    int *bubble_sorted;
    int *selection_sorted;
    int *insertion_sorted;
    int *merge_sorted;
    int *quick_sorted;

    double bubble_sort_time;
    double selection_sort_time;
    double insertion_sort_time;
    double merge_sort_time;
    double quick_sort_time;

    if (is_test == 1)
    {
        test();
        return 0;
    }

    for (int array_size = 50000; array_size <= 200000; array_size += 50000)
    {
        p_array = build_array(array_size);

        merge_sorted = copy_array(p_array, array_size);
        bubble_sorted = copy_array(p_array, array_size);
        selection_sorted = copy_array(p_array, array_size);
        insertion_sorted = copy_array(p_array, array_size);
        quick_sorted = copy_array(p_array, array_size);

        printf("\n\nMedindo tempos para %d valores", array_size);

        start = clock();
        bubble_sort(bubble_sorted, array_size);
        end = clock();
        bubble_sort_time = calculate_difference(start, end);
        printf("\nBubble Sort: %10.4f", bubble_sort_time);

        start = clock();
        selection_sort(selection_sorted, array_size);
        end = clock();
        selection_sort_time = calculate_difference(start, end);
        printf("\nSelection Sort: %10.4f", selection_sort_time);

        start = clock();
        insertion_sort(insertion_sorted, array_size);
        end = clock();
        insertion_sort_time = calculate_difference(start, end);
        printf("\nInsertion Sort: %10.4f", insertion_sort_time);

        start = clock();
        merge_sort(merge_sorted, 0, array_size - 1);
        end = clock();
        merge_sort_time = calculate_difference(start, end);
        printf("\nMerge Sort: %10.4f", merge_sort_time);

        start = clock();
        quick_sort(quick_sorted, 0, array_size - 1);
        end = clock();
        quick_sort_time = calculate_difference(start, end);
        printf("\nQuick Sort: %10.4f", quick_sort_time);
    }

    printf("\nOVER");
}