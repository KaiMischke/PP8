#include "cipher.h"

char encrypt_char(char c, int shift) {
	    if (c >= 'A' && c <= 'Z') return 'A' + (c - 'A' + shift) % 26;
	        if (c >= 'a' && c <= 'z') return 'a' + (c - 'a' + shift) % 26;
		    return c;
}

char decrypt_char(char c, int shift) {
	    return encrypt_char(c, 26 - (shift % 26));
}
