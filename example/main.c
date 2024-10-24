#include "i2c.h"
#include <stdlib.h>
#include <stdio.h>

int main()
{

	stdio_init_all();
	sleep_ms(1000);
	printf("\n%d\n", i2c_simple_init(i2c0, 100000));

	return 1;

}

