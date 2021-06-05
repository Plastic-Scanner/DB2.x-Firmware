#include "assert.h" 
#include "Arduino.h"

void assertion_failure(char* expr, char* file, char* basefile, int linenum)
{
    // These can be seen with a debugger          
    volatile const char* v_expr     = expr;
    volatile const char* v_file     = file;
    volatile int v_linenum          = linenum;
    // volatile const char* v_basefile = basefile;

    Serial.flush();
    Serial.print("Assertion failed in '");
    Serial.print(file);
    Serial.print("' on line ");
    Serial.print(linenum);
    Serial.print(": ");
    Serial.println(expr);
    Serial.flush();

    while (1);
}