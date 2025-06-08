#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "cipher.h"

void usage(const char *prog) {
	    fprintf(stderr, "Usage: %s -e shift|-d shift -i infile -o outfile\n", prog);
	        exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]) {
	    int opt, shift = 0, enc = -1;
	        char *infile = NULL, *outfile = NULL;

		    while ((opt = getopt(argc, argv, "e:d:i:o:")) != -1) {
			            if      (opt == 'e') { shift = atoi(optarg); enc = 1; }
				            else if (opt == 'd') { shift = atoi(optarg); enc = 0; }
					            else if (opt == 'i') infile = optarg;
						            else if (opt == 'o') outfile = optarg;
							            else usage(argv[0]);
								        }

		        if (enc < 0 || !infile || !outfile) usage(argv[0]);

			    FILE *fin = fopen(infile, "r");
			        if (!fin) { perror("fopen infile"); exit(EXIT_FAILURE); }
				    FILE *fout = fopen(outfile, "w");
				        if (!fout) { perror("fopen outfile"); exit(EXIT_FAILURE); }

					    int c;
					        while ((c = fgetc(fin)) != EOF) {
							        char out;
								        if (enc)
										            out = encrypt_char(c, shift);
									        else
											            out = decrypt_char(c, shift);
										        fputc(out, fout);
											    }

						    fclose(fin);
						        fclose(fout);
							    return 0;
}
