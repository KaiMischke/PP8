#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
	int opt;
	int flag_a = 0, flag_b = 0;

	while ((opt = getopt(argc, argv, "ab")) != -1) {
		if      (opt == 'a') flag_a = 1;
		else if (opt == 'b') flag_b = 1;
		else {
			fprintf(stderr, "Usage: %s [-a] [-b]\n", argv[0]);
			exit(EXIT_FAILURE);
		}
	}

	printf("flag_a=%d, flag_b=%d\n", flag_a, flag_b);
	return 0;
}


