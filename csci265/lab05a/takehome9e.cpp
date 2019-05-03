# 1 "takehome9.cpp"
# 1 "<built-in>"
# 1 "<command-line>"
# 1 "/usr/include/stdc-predef.h" 1 3 4
# 1 "<command-line>" 2
# 1 "takehome9.cpp"
# 1 "takehome9.h" 1



# 1 "/usr/lib/gcc/x86_64-linux-gnu/6/include/stdarg.h" 1 3 4
# 40 "/usr/lib/gcc/x86_64-linux-gnu/6/include/stdarg.h" 3 4

# 40 "/usr/lib/gcc/x86_64-linux-gnu/6/include/stdarg.h" 3 4
typedef __builtin_va_list __gnuc_va_list;
# 99 "/usr/lib/gcc/x86_64-linux-gnu/6/include/stdarg.h" 3 4
typedef __gnuc_va_list va_list;
# 5 "takehome9.h" 2





# 9 "takehome9.h"
int sum(int numArgs, ...);
# 2 "takehome9.cpp" 2




int sum(int numArgs, ...)
{

   va_list argList;
   
# 10 "takehome9.cpp" 3 4
  __builtin_va_start(
# 10 "takehome9.cpp"
  argList
# 10 "takehome9.cpp" 3 4
  ,
# 10 "takehome9.cpp"
  numArgs
# 10 "takehome9.cpp" 3 4
  )
# 10 "takehome9.cpp"
                            ;


   int i, sum;



   sum = 
# 17 "takehome9.cpp" 3 4
        __builtin_va_arg(
# 17 "takehome9.cpp"
        argList
# 17 "takehome9.cpp" 3 4
        ,
# 17 "takehome9.cpp"
        int
# 17 "takehome9.cpp" 3 4
        )
# 17 "takehome9.cpp"
                            ;



   for (i = 1; i < numArgs; i++) {
       sum += 
# 22 "takehome9.cpp" 3 4
             __builtin_va_arg(
# 22 "takehome9.cpp"
             argList
# 22 "takehome9.cpp" 3 4
             ,
# 22 "takehome9.cpp"
             int
# 22 "takehome9.cpp" 3 4
             )
# 22 "takehome9.cpp"
                                 ;
   }


   
# 26 "takehome9.cpp" 3 4
  __builtin_va_end(
# 26 "takehome9.cpp"
  argList
# 26 "takehome9.cpp" 3 4
  )
# 26 "takehome9.cpp"
                 ;


   return sum;
}
