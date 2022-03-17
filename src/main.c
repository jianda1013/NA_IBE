#include <pbc.h>

#include "Decrypt.h"
// #include "pbcExtend.h"

int main(int argc, char const* argv[]) {
    // ************************************* //
    // set the pairing definition            //

    char param[1024];
    pairing_t pairing;
    size_t count = fread(param, 1, 1024, stdin);
    if (!count)
        return 1;
    pairing_init_set_buf(pairing, param, count);

    // ************************************* //

    element_t ID, M;
    newElementRand(ID, pairing, "Zr");
    newElementRand(M, pairing, "GT");
#ifdef DEBUG
    element_printf("INFO : \n");
    element_printf("\tID : %B\n", ID);
    element_printf("\tM  : %B\n", M);
#endif

    // ************************************* //

    SETUP Setup = setup(pairing);
    UserKey key = keygen(Setup.pk, Setup.sk, ID, pairing);
    CT ct = encrypt(ID, M, Setup.pk, pairing);
    DC dt = decrypt(ct, key, pairing);
    int result = element_cmp(dt.msg, M);
    printf("%d\n", result);
    return 0;
}
