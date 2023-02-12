/**
 * @file primes.c
 * @author Jakub Čoček, FIT
 * @brief Řešení IJC-DU1, příklad a)
 * @date 2022-03-12
 * přeloženo pomoci gcc 9.4.0
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "bitset.h"
#include "eratosthenes.h"

#define N 300000000

int main()
{
    clock_t start;
    start = clock();

    bitset_alloc(bit_arr, N);

    Eratosthenes(bit_arr);
    
    uint64_t primes[10];
    int count = 0;

    for(uint64_t i = N-1; i > 0; i--){
        if((bitset_getbit(bit_arr, i)) == 0){
            primes[count] = i;
            count++;

            if(count == 10){
                break;
            }
        }
    }

    for(int i = count - 1; i >= 0 ; i--){
        printf("%ld\n", primes[i]);
    }

    bitset_free(bit_arr);
    fprintf(stderr, "Time=%.3g\n", (double)(clock()-start)/CLOCKS_PER_SEC);
}