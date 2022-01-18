#include<stdio.h>
#include<stdlib.h>
void merge(int* array, int left, int middle, int right) {
	int i, j, k;
	int _left = middle - left + 1;
	int _right = right - middle;
	int leftarr[_left];
	int rightarr[_right];
	for (i = 0; i < _left; i++) {
		//copying left arr
		leftarr[i] = array[left + i];
	}

	for (j = 0; j < _right; j++) {
		//copying right arr
		rightarr[j] = array[middle + j + 1];
	}
	i = 0;
	j = 0;
	k = left;
	while (i < _left && j < _right) {
		if (leftarr[i] < rightarr[j]) {
			array[k] = leftarr[i];
			i++;
		}

		else {
			array[k] = rightarr[j];
			j++;
		}
		k++;
	}
	while (i < _left) {
		array[k] = leftarr[i];
		i++;
		k++;
	}
	while (j < _right) {
		array[k] = rightarr[j];
		j++;
		k++;
	}


}

void mergeSort(int* array, int  left, int right) {
	if (left < right) {

		int middle = (right + left) / 2;

		mergeSort(array, left, middle);

		mergeSort(array, middle + 1, right);

		merge(array, left, middle, right);

		return;
	}
}

int main() {
	system("clear");
	FILE* input = fopen("mergesort_input.csv", "rb");
	FILE* output = fopen("output.csv", "wb");
	if (input == NULL) {
		printf("error reading file");
		exit(1);
	}
	int size = 0;
	fseek(input, 0, SEEK_END);
	size = ftell(input);
	fseek(input, 0, SEEK_SET);
	printf(" %d\n", size);

	char* str = (char*)malloc(size + 1);
	fread(str, size, 1, input);
	str[size] = '\0';
	fclose(input);

	//count no of numbers in current line
	int numcount = 1;// 1 is for last number
	int i = 0;
	while (*(str + i) != '\n') {
		if (*(str + i) == ',') {
			numcount++;
		}
		i++;
	}
	printf("numcount %d\n", numcount);

	int* arr = (int*)malloc(sizeof(int) * numcount);

	// reading numbers
	i = 0;
	int count = 0;
	while (1) {
		int num = 0;
		while (*(str + i) >= '0' && *(str + i) <= '9') {
			num = num * 10 + (*(str + i) - '0');
			i++;
		}

		*(arr + count) = num;
		// printf("num-%d  %d\n", count, num);
		count++;
		if (*(str + i) == '\n') {
			break;
		}
		if (*(str + i) == '\0') {
			break;
		}
		i++;
	}
	mergeSort(arr, 0, numcount - 1);

	// write infile

	printf("printing array \n ");
	for (int i = 0; i < numcount; i++) {
		// printf("element-%d %d \n ", i, array[i]);
		fprintf(output, "%d", *(arr + i));
		if (i != numcount - 1)
			fprintf(output, "%c", ',');
	}



	return 0;
}