#include "Keygen.h"

typedef struct {
    element_t msg;
} DC;

DC decrypt(CT ct, UserKey key, pairing_t pairing, SETUP setup, element_t ID) {
    DC result;
    element_t D, Cn, tmp, pow;
    newElement(D, pairing, "GT");
    newElement(tmp, pairing, "GT");
    newElement(Cn, pairing, "GT");
    newElement(pow, pairing, "Zr");
    element_pairing(D, key.K0, ct.C0);

    element_mul(pow, setup.sk.s2, ID);
    element_add(pow, pow, setup.sk.s1);
    element_add(pow, pow, key.k);
    element_mul(pow, pow, ct.r);
    element_pow_zn(tmp, setup.pk.gt, pow);

    newElement(result.msg, pairing, "GT");
    element_mul(result.msg, D, ct.C0_h);
    element_pow_zn(Cn, ct.C0_h, key.K1);
    element_div(result.msg, result.msg, Cn);

#ifdef DEBUG
    element_printf("DECRYPT : \n");
    element_printf("\tM : %B\n", result.msg);
#endif
    return result;
}