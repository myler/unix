void initArray();
void printArray();

int main(int argc, char const *argv[])
{
	initArray();
	//printf("error\n");
	printArray();
	return 0;
}

void initArray() {
	int array[100];
	int i;
	for (i = 0; i < 100; i++) {
		array[i] = i;
	}
}

void printArray() {
	int array[100];
	int i;
	for (i = 0; i < 100; i++) {
		printf("%d ", array[i] + 1);
	}
	printf("\n");
}