#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <conio.h>
#include <sys/time.h>
#include <inttypes.h>

int getrand(int min, int max) {
    return (double) rand() / (RAND_MAX + 1.0) * (max - min) + min;
}

double wtime()
{
    struct timeval t;
    gettimeofday(&t, NULL);
    return (double)t.tv_sec + (double)t.tv_usec * 1E-6;
}

void counting_sort(int n, uint32_t mass[], uint32_t buffMass[])
{
    double start = wtime();
    for (int i = 0; i < n; i++)
    {
        buffMass[mass[i]]++;
    }
    int k = 0;
    for (uint32_t i = 0; i < 100000; i++)
    {
        uint32_t count = buffMass[i];
        if ( count )
        {
            for ( uint32_t j = 0; j < count; j++ )
            {
                mass[k++] = i;
            }
        }
    }
    printf("Elems: %d; time: %f\n\n", n, wtime() - start);
}

void insertion_sort(int size, uint32_t mass[])
{
    double start = wtime();
    uint32_t i, j, temp;
    for (i = 1; i < size; i++)
    {
        temp = mass[i];
        for (j = i - 1; j > 0; j--)
        {
            if (mass[j] < temp)
                break;

            mass[j + 1] = mass[j];
            mass[j] = temp;
        }
    }
    printf("Elems: %d; time: %f\n\n", size, wtime() - start);
}

void merge(uint32_t arr[], int l,
           int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;
    uint32_t L[n1], R[n2];
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void merge_sort(uint32_t arr[],
               int l, int r)
{
    if (l < r)
    {
        int m = l + (r - l) / 2;
        merge_sort(arr, l, m);
        merge_sort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}


int main()
{
    for (int N = 50000; N < 1000001; N += 50000 )
    {
        uint32_t *mass, *buffMass;
        mass = (uint32_t *)malloc(N * sizeof(uint32_t));
        buffMass = (uint32_t *)calloc(100001, sizeof(uint32_t));
        for (int i = 0; i < N; i++)
            mass[i] = getrand(0, 100000);
        //counting_sort(N, mass, buffMass);
        double start = wtime();
        //insertion_sort(N, mass);
        printf("Elems: %d;  ", N);
        merge_sort(mass, 0, N-1);
        printf("time: %f\n\n", wtime() - start);
        free(mass);
        free(buffMass);
    }
    return 0;
}
