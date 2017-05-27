#ifndef BITTYBUZZ_BBZKILOREG_H
#define BITTYBUZZ_BBZKILOREG_H
#include <bbzkilosymgen.h> // A header file generated at compile time containing all the symbole ID

/**
 * @brief Register a custom function.
 */
#define bbzkilo_function_register(NAME, func) bbzvm_function_register(BBZKILO_SYMID_GEN_ ## NAME);

#endif // !BITTYBUZZ_BBZKILOREG_H
