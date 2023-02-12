/**
 * @file bitset.h
 * @author Jakub Čoček, FIT
 * @brief Řešení IJC-DU1, priklad a)
 * @date 2022-03-05
 * přeloženo pomoci gcc 9.4.0
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <limits.h>
#include "error.h"

//guard
#ifndef BITSET_H
#define BITSET_H

//typy
typedef uint64_t bitset_t;
typedef uint64_t bitset_index_t;

//pomocna makra
#define VYPOCET_VELIKOSTI(velikost) (velikost%64 == 0) ? ((velikost/64) + 1) : ((velikost/64) + 2)

//makra 
/**
 * @brief Definuje pole jmeno_pole, nuluje vsechny prvku krome prvku 0, kde je ulozena velikost v bitech
 */
#define bitset_create(jmeno_pole, velikost) static_assert(velikost>0, "Neplatná velikost pole\n"); bitset_t jmeno_pole[VYPOCET_VELIKOSTI(velikost)]={velikost, }

/**
 * @brief Definuje pole jmeno_pole, velikost je alokovana dynamicky, nuluje vsechny prvku krome prvku 0, kde je ulozena velikost v bitech
 */
#define bitset_alloc(jmeno_pole, velikost) assert(velikost<SIZE_MAX || velikost>0);bitset_t* jmeno_pole=calloc(VYPOCET_VELIKOSTI(velikost),sizeof(bitset_index_t));\
if(jmeno_pole == NULL)(fprintf(stderr, "bitset_alloc: Chyba alokace paměti\n"),exit(1));else(jmeno_pole[0]=velikost)

#ifndef USE_INLINE

/**
 * @brief Uvolnuje pamet dynamicky alokovaneho pole jmeno_pole
 */
#define bitset_free(jmeno_pole) (free(jmeno_pole))

/**
 * @brief Vraci hodnotu v poli na pozici 0 (tj. velikost pole v bitech)
 */
#define bitset_size(jmeno_pole) jmeno_pole[0]

/**
 * @brief Nastavuje bit v poli jmeno_pole na hodnotu 1 nebo 0
 */
#define bitset_setbit(jmeno_pole, index, vyraz) (vyraz != 0) ? (jmeno_pole[(index/64)+1] |= ((uint64_t)1 << (index%64))) : (jmeno_pole[(index/64)+1] &= ~((uint64_t)1 << (index%64)))

/**
 * @brief Vraci hodnotu bitu v poli jmeno_pole na indexu (1 nebo 0)
 */
#define bitset_getbit(jmeno_pole, index) (jmeno_pole[(index/64)+1] & ((uint64_t)1 << (index%64)))

#endif

//inline funkce
#ifdef USE_INLINE

/**
 * @brief Uvolnuje dynamicky alokovanou pamet pole
 * 
 * @param arr Pole, ktere je uvolnovano
 */
static inline void bitset_free(bitset_t *arr)
{
    free(arr);
}

/**
 * @brief Vraci velikost pole
 * 
 * @param arr Pole, jehoz velikost chceme ziskat
 * @return uint64_t Zikana velikost (v bitech)
 */
static inline uint64_t bitset_size(bitset_t *arr)
{
    return (arr[0]);
}

/**
 * @brief Nastavuje bit v poli na hodnotu 1 nebo 0
 * 
 * @param arr Pole, kde je bit nastavovan
 * @param index Pozice bitu v poli
 * @param vyraz Hodnota, na kterou bude bit nastaven (1 nebo 0)
 */
static inline void bitset_setbit(bitset_t *arr, uint64_t index, int vyraz)
{
    if(arr[0] < index){
        error_exit("bitset_setbit: Index %ld mimo rozsah 0..%ld\n", index, arr[0]);
    }

    if(vyraz != 0){
        arr[(index/64)+1] |= ((uint64_t)1 << (index%64));
    }
    else{
        arr[(index/64)+1] &= ~((uint64_t)1 << (index%64));
    }
}

/**
 * @brief Vraci hodnotu bitu v poli
 * 
 * @param arr Pole, kde je bit ulozen
 * @param index Pozice bitu v poli
 * @return int Hodnota bitu (1 nebo 0)
 */
static inline int bitset_getbit(bitset_t *arr, uint64_t index)
{
    if(arr[0] < index){
        error_exit("bitset_getbit: Index %ld mimo rozsah 0..%ld\n", index, arr[0]);
    }
    return (arr[(index/64)+1] & ((uint64_t)1 << (index%64)) ? 1 : 0);
}

#endif  //pro USE_INLINE

#endif //pro BITSET_H
