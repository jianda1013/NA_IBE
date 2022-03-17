#include "Setup.h"

typedef struct {
    element_t C0;
    element_t C0_h;
    element_t C1;
} CT;

CT encrypt(element_t ID, element_t M, PK pk, pairing_t pairing) {
    CT cypherText;
    element_t r;
    newElementRand(r, pairing, "Zr");
    newElement(cypherText.C0, pairing, "G1");
    newElement(cypherText.C0_h, pairing, "GT");
    newElement(cypherText.C1, pairing, "GT");
    element_pow_zn(cypherText.C0, pk.g, r);
    element_pow_zn(cypherText.C0_h, pk.gt, r);
    element_pow_zn(cypherText.C1, pk.h2, ID);
    element_mul(cypherText.C1, cypherText.C1, pk.h1);
    element_pow_zn(cypherText.C1, cypherText.C1, r);
    element_mul(cypherText.C1, cypherText.C1, M);
#ifdef DEBUG
    element_printf("ENCRYPT : \n");
    element_printf("\tr    : %B\n", r);
    element_printf("\tC0   : %B\n", cypherText.C0);
    element_printf("\tC0_h : %B\n", cypherText.C0_h);
    element_printf("\tC1   : %B\n", cypherText.C1);
#endif
    return cypherText;
}