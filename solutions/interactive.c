#include <stdio.h>
#define BUF_SIZE 100

int main(void) {
	char name[BUF_SIZE];
	int age;

	printf("Enter your name: ");
	scanf("%99s", name);
	printf("Hello, %s!\n", name);

	printf("Enter your age: ");
	scanf("%d", &age);
	printf("You are %d years old.\n", age);

	// File scanning
	FILE *fp = fopen("data.txt", "r");
	if (!fp) { perror("fopen"); return 1; }
	char fname[BUF_SIZE];
	int fage;
	if (fscanf(fp, "%99s %d", fname, &fage) == 2) {
		printf("File data: %s is %d years old.\n", fname, fage);
	}
	fclose(fp);
	return 0;
}
