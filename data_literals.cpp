#include "data_literals.h"


unsigned long long int operator ""_B(unsigned long long int n) { return n; }
unsigned long long int operator ""_KiB(unsigned long long int n) { return n * 0x400; }
