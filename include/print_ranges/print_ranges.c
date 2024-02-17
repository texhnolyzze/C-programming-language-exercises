

#include <stdio.h>
#include "print_ranges.h"
#include "limits.h"
#include "float.h"

void print_ranges(void) {
    printf("char %d %d\n", CHAR_MIN, CHAR_MAX);
    printf("unsigned char %u %u\n", 0, UCHAR_MAX);
    printf("short %d %d\n", SHRT_MIN, SHRT_MAX);
    printf("unsigned short %u %u\n", 0, USHRT_MAX);
    printf("int %d %d\n", INT_MIN, INT_MAX);
    printf("unsigned int %u %u\n", 0, UINT_MAX);
    printf("long %ld %ld\n", LONG_MIN, LONG_MAX);
    printf("unsigned long %d %lu\n", 0, ULONG_MAX);
    printf("long long %lld %lld\n", LONG_LONG_MIN, LONG_LONG_MAX);
    printf("unsigned long long %d %llu\n", 0, ULONG_LONG_MAX);
    printf("float %f %f\n", FLT_MIN, FLT_MAX);
    printf("double %f %f\n", DBL_MIN, DBL_MAX);
    printf("long double %Lf %Lf\n", LDBL_MIN, LDBL_MAX);
    long long d;
}
