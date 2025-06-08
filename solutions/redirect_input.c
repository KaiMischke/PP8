#include <stdio.h>
#define BUF_SIZE 256

int main(void) {
	char buf[BUF_SIZE];
	if (fgets(buf, BUF_SIZE, stdin))
		printf("You entered: %s", buf);
	return 0;
}
