#include "limits.h"

unsigned long max_value(unsigned nchars){
    if(nchars == 0){
        return 0;
    }
    if(nchars > 8){
        return 0;
    }
    unsigned long result = (1UL<<((CHAR_BIT * nchars)-1UL))-1;
    return result;
}