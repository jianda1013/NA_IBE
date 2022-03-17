#include <pbc.h>

#include "pbcExtend.h"

typedef struct {
    element_t g;
    element_t gt;
    element_t h1;
    element_t h2;
} PK;

typedef struct {
    element_t s1;
    element_t s2;
} SK;

typedef struct {
    SK sk;
    PK pk;
} SETUP;

SETUP setup(pairing_t pairing) {
    SETUP result;
    newElementRand(result.pk.g, pairing, "G1");
    newElementRand(result.sk.s1, pairing, "Zr");
    newElementRand(result.sk.s2, pairing, "Zr");
    newElement(result.pk.gt, pairing, "GT");
    newElement(result.pk.h1, pairing, "GT");
    newElement(result.pk.h2, pairing, "GT");
    element_pairing(result.pk.gt, result.pk.g, result.pk.g);
    element_pow_zn(result.pk.h1, result.pk.gt, result.sk.s1);
    element_pow_zn(result.pk.h2, result.pk.gt, result.sk.s2);
#ifdef DEBUG
    element_printf("SETUP : \n");
    element_printf("\tPK : \n");
    element_printf("\t\tg  : %B\n", result.pk.g);
    element_printf("\t\tgt : %B\n", result.pk.gt);
    element_printf("\t\th1 : %B\n", result.pk.h1);
    element_printf("\t\th2 : %B\n", result.pk.h2);
    element_printf("\tSK : \n");
    element_printf("\t\ts1 : %B\n", result.sk.s1);
    element_printf("\t\ts2 : %B\n", result.sk.s2);
#endif
    return result;
}