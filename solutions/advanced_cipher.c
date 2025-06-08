#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "cipher.h"
#include "asym.h"

void usage(const char *prog) {
	    fprintf(stderr, "Usage: %s -m <caesar|xor> -e key|-d key -i infile -o outfile\n", prog);
	        exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]) {
	    int opt, enc = -1, key = 0;
	        char *mode = NULL, *infile = NULL, *outfile = NULL;

		    while ((opt = getopt(argc, argv, "m:e:d:i:o:")) != -1) {
			            if      (opt == 'm') mode = optarg;
				            else if (opt == 'e') { key = atoi(optarg); enc = 1; }
					            else if (opt == 'd') { key = atoi(optarg); enc = 0; }
						            else if (opt == 'i') infile = optarg;
							            else if (opt == 'o') outfile = optarg;
								            else usage(argv[0]);
									        }

		        if (!mode || enc < 0 || !infile || !outfile) usage(argv[0]);

			    FILE *fin = fopen(infile, "r");
			        if (!fin) { perror("fopen infile"); exit(EXIT_FAILURE); }
				    FILE *fout = fopen(outfile, "w");
				        if (!fout) { perror("fopen outfile"); exit(EXIT_FAILURE); }

					    int c;
					        while ((c = fgetc(fin)) != EOF) {
							        char out;
								        if (strcmp(mode, "caesar") == 0) {
										            if (enc)
												                    out = encrypt_char(c, key);
											                else
														                out = decrypt_char(c, key);
													        } else if (strcmp(mode, "xor") == 0) {
															            if (enc)
																	                    out = encrypt_xor(c, (char)key);
																                else
																			                out = decrypt_xor(c, (char)key);
																		        } else {
																				            usage(argv[0]);
																					            }
									        fputc(out, fout);
										    }

						    fclose(fin);
						        fclose(fout);
							    return 0;
}
