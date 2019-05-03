#include "takehome9.h"
#include <stdio.h>

int main()
{
    // illustrating use of variable number of parameters to function sum
    int sum4 = sum(4, 10, 20, 30, 40);
    int sum3 = sum(3, 13, -66, 200);
    printf("sum of 10+20+30+40=%d\n", sum4);
    printf("sum of 13-66+200=%d\n", sum3);
    return 0;
}
