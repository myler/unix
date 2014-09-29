#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
	int MAX = 5;
	int i = 0, j = 0;
	int *a = (int*)malloc(MAX * sizeof(int));
	int *b;
	FILE *fp1, *fp2;

	if ((fp1 = fopen("a.txt", "r")) == NULL)
		printf("open a.txt failed.\n"), exit(1);

	if ((fp2 = fopen("b.txt", "w")) == NULL)
		printf("open b.txt failed.\n"), exit(1);

	while (fscanf(fp1, "%d", &a[i]) != EOF) {
		i++;
		j++;
		if (i >= MAX) {
			MAX = 2 * MAX;
			b = (int*)realloc(a, MAX * sizeof(int));
			a = b;
		}
	}

	j--;
	while (j >= 0) {
		fprintf(fp2, "%d\n", a[j]);
		j--;
	}

	fclose(fp1);
	fclose(fp2);

	return 0;
}