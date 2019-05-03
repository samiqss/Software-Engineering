#include "takehome9.h"

// given the first parameter specifies how many additional
//    parameters are supplied,
// find and return the sum of the remaining parameters
int sum(int numArgs, ...)
{
   // initialize the argument list
   va_list argList;
   va_start(argList, numArgs);

   // local variables
   int i, sum;

   // get the first value from the argument list,
   //     treating it as an int
   sum = va_arg(argList, int);

   // get the remaining values from the argument list,
   //     again treating them as ints
   for (i = 1; i < numArgs; i++) {
       sum += va_arg(argList, int);
   }

   // dispose of the argument list
   va_end(argList);

   // return the identified maximum
   return sum;
}


