/**
 * @file eratosthenes.c
 * @author Jakub Čoček, FIT
 * @brief Řešení IJC-DU1, příklad a)
 * @date 2022-03-12
 * přeloženo pomoci gcc 9.4.0
 */

#include "bitset.h"
#include "eratosthenes.h"
#include <math.h>

void Eratosthenes(bitset_t *arr)
{
    bitset_setbit(arr, 0, 1);    
    bitset_setbit(arr, 1, 1);    

    unsigned int i,k;

    unsigned long size = bitset_size(arr);
    for(i = 2; i < sqrt(size); i++){
        if(bitset_getbit(arr, i) == 0){
            for(k = 2*i; k < size; k+=i){
                bitset_setbit(arr, k, 1);
            }
        }
    }
}
