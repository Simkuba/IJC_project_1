/**
 * @file ppm.c
 * @author Jakub Čoček, FIT
 * @brief Řešení IJC-DU1, příklad b)
 * @date 2022-03-13
 * přeloženo pomoci gcc 9.4.0
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ppm.h"
#include "error.h"

struct ppm * ppm_read(const char * filename)
{
    FILE *file;

    //otevreni souboru
    file = fopen(filename, "r");
    if(file == NULL){
        warning_message("Soubor se nepovedlo otevrit!\n");
        return NULL;
    }

    char format[3];     //pro kontrolu P6
    unsigned int xsize;
    unsigned int ysize;
    unsigned int color;

    /*cteni hlavicky souboru + kontrola spravnosti hl. dat
    (fscanf man: On success, these functions return the number of input items successfully matched...)*/
    if(fscanf(file, "%s %u %u %u", format, &xsize, &ysize, &color) != 4){
        warning_message("Problem s hlavickou souboru PPM\n");
        fclose(file);
        return NULL;
    }

    //overeni formatu P6
    if(strcmp(format, "P6") != 0){
        warning_message("Format PPM souboru musi byt P6!\n");
        fclose(file);
        return NULL;
    }

    //kontrola barvy
    if(color > 255){
        warning_message("Hodnota barvy %d je mimo rozsah 0..255!\n", color);
        fclose(file);
        return NULL;
    }

    //kontrola velikosti obrazku (souboru)
    unsigned long limit  = xsize * ysize * 3;
    if(limit > MAX_VELIKOST){
        warning_message("Soubor je prilis velky!\n");
        fclose(file);
        return NULL;
    }

    //alokace struktury
    struct ppm *final = malloc(sizeof(struct ppm) + limit);
    if(final == NULL){
        warning_message("Alokace struktury se nezdarila!\n");
        fclose(file);
        return NULL;
    }

    //nacteni dat do struktury
    final->xsize = xsize;
    final->ysize = ysize;

    if(fread(final->data, sizeof(char), limit, file) != limit){
        warning_message("Cteni ze souboru %s se nepodarilo!\n", filename);
        free(final);
        fclose(file);
        return NULL;
    }

    fclose(file);
    return final;
}

void ppm_free(struct ppm *p)
{
    free(p);
}