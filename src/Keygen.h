#include "Encrypt.h"

typedef struct {
    element_t K0;
    element_t K1;
    element_t k;
} UserKey;

UserKey keygen(PK pk, SK sk, element_t ID, pairing_t pairing) {
    UserKey key;
    element_t k;
    newElementRand(k, pairing, "Zr");
    newElement(key.K0, pairing, "G1");
    newElement(key.K1, pairing, "Zr");
    element_pow_zn(key.K0, pk.g, k);
    element_mul(key.K1, sk.s2, ID);
    element_add(key.K1, key.K1, sk.s1);
    element_add(key.K1, key.K1, k);
    newElementAssign(key.k, pairing, "Zr", k);
#ifdef DEBUG
    element_printf("KEYGEN : \n");
    element_printf("\tk  : %B\n", k);
    element_printf("\tK0 : %B\n", key.K0);
    element_printf("\tK1 : %B\n", key.K1);
#endif
    return key;
}