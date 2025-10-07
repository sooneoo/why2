#include <stdio.h>
#include <stdlib.h>



#include "version.h"


int main(void) {
    Why2_Version version = why2_version();
    printf("version: %d.%d.%d\n", version.major, version.minor, version.patch);
	printf("program exit..\n");
	return EXIT_SUCCESS;
}



