#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
	int opt;
	int number = 0;
	char *str = NULL;
	char *infile = NULL, *outfile = NULL;

	while ((opt = getopt(argc, argv, "n:s:i:o:")) != -1) {
		if      (opt == 'n') number  = atoi(optarg);
		else if (opt == 's') str     = optarg;
		else if (opt == 'i') infile  = optarg;
		else if (opt == 'o') outfile = optarg;
		else {
			fprintf(stderr, "Usage: %s -n num -s str -i infile -o outfile\n", argv[0]);
			exit(EXIT_FAILURE);
		}
	}

	printf("number=%d, string=%s, infile=%s, outfile=%s\n",
			number,
			str     ? str     : "(null)",
			infile  ? infile  : "(none)",
			outfile ? outfile : "(none)");
	return 0;
}
