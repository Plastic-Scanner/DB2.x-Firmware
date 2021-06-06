/*
    Modified/simplified version of the assert from:
    https://nicisdigital.wordpress.com/2011/07/05/assertions-in-microcontrollers/ 
*/
#ifndef _MYASSERT_H_
#define _MYASSERT_H_

void assertion_failure(const char* expr, const char* file, int linenum);

#define myassert(expr) \
    if (expr) ; \
    else assertion_failure(#expr, __FILE__, __LINE__)


#endif /* _MYASSERT_H_ */
