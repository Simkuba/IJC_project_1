/**
 * @file steg-decode.c
 * @author Jakub Čoček, FIT
 * @brief Řešení IJC-DU1, příklad b)
 * @date 2022-03-13
 * přeloženo pomoci gcc 9.4.0
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "ppm.h"
#include "error.h"
#include "bitset.h"
#include "eratosthenes.h"

int main(int argc, char *argv[])
{
    //kontrola poctu argumentu programu
    if(argc != 2){
        error_exit("Nespravny pocet argumentu! Program ocekava jeden.\n");
    }

    //nacteni dat do struktury, v pripade NULL chyba
    struct ppm *p_ppm = ppm_read(argv[1]);
    if(p_ppm == NULL){
        error_exit("Soubor %s se nepodarilo nacist!\n", argv[1]);
    }

    //vytvoreni bitsetu
    uint64_t size = (p_ppm->xsize * p_ppm->ysize * 3);
    bitset_alloc(bit_arr, size);

    Eratosthenes(bit_arr);

    short mess[1] = {0};
    uint64_t i;
    int index = 0;

    for(i = 29; i < size; i++){
        if((bitset_getbit(bit_arr, i)) == 0){
            bitset_setbit(mess, index, (p_ppm->data[i+1] & 1));
            index++;

            if(index == CHAR_BIT){
                
                putchar(mess[0]);

                if(mess[0] == '\0'){
                    goto konec;
                }

                index = 0;
            }
        }
    }

    free(p_ppm);
    bitset_free(bit_arr);
    error_exit("\nZprava v souboru nebyla spravne ukoncena!\n");

    konec:
    printf("\n");
    free(p_ppm);
    bitset_free(bit_arr);
}