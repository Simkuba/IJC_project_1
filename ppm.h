/**
 * @file ppm.h
 * @author Jakub Čoček, FIT
 * @brief Řešení IJC-DU1, příklad b)
 * @date 2022-03-13
 * přeloženo pomoci gcc 9.4.0
 */

//guard
#ifndef PPM_H
#define PPM_H

#define MAX_VELIKOST 8000*8000*3

struct ppm{
    unsigned xsize; 
    unsigned ysize;
    char data[];    //RGB bajty, celkem 3 * xsize * ysize
};

/**
 * @brief načte obsah PPM souboru do touto funkcí dynamicky alokované struktury 
 */
struct ppm * ppm_read(const char * filename);

/**
 * @brief uvolní paměť dynamicky alokovanou v ppm_read
 */
void ppm_free(struct ppm *p);

#endif