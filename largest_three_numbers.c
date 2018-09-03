#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

#define NUM_TO_FIND 3
#define MAX_LEN 100
#define RAND_ABS_MAX 5000

/*
 * insert_max_into_array
 *
 * Find the largest numbers in the array
 *
 * Inputs:
 * max_array - Array that holds the max numbers
 * num_to_find - How many largest numbers to find
 *
 */
void insert_max_into_array (int *max_array, int new_max)
{
	int temp;
	max_array[0] = new_max;

	for (int i = 1; i < NUM_TO_FIND; i++) {
		if (max_array[i] < max_array[i-1]) {
			temp = max_array[i];
			max_array[i] = max_array[i-1];
			max_array[i-1] = temp;
		} else {
			break;
		}
	}
}

/*
 * search_array
 *
 * Find the largest numbers in the array
 *
 * Inputs:
 * array - Array to search
 * len - Length of array
 * max_array - Array that holds the max numbers
 * num_to_find - How many largest numbers to find
 *
 */
void search_array(int *array, int len, int *max_array, int num_to_find)
{
	for (int i = 0; i < num_to_find; i++) {
		max_array[i] = INT_MIN;
	}

	for (int i = 0; i < len; i++) {
		if (array[i] > max_array[0]) {
			insert_max_into_array(max_array, array[i]);
		}
	}
}

/*
 * create_array
 *
 * Create an array of random integers between -5,000 to 5,000
 *
 * Inputs:
 * len - Length of array
 *
 * Returns: New array populated with random numbers
 *
 */
int *create_array (int len)
{
	int *array;

	array = malloc(len * sizeof(int));

	srand(time(0));
	for (int i = 0; i < len; i++) {
		array[i] = (rand() % (RAND_ABS_MAX*2 + 1)) - RAND_ABS_MAX;
	}

	return array;
}

int main (int argc, char *argv[])
{
	int *test_array, array_len;
	int max_array[NUM_TO_FIND];

	/* Parse user arguments */
	if (argc < 2) {
		array_len = MAX_LEN;
	} else if (argc == 2) {
		array_len = atoi(argv[1]);
		if (array_len < NUM_TO_FIND || array_len > MAX_LEN) {
			printf("Please specify array length between %d and %d\n",
				NUM_TO_FIND, MAX_LEN);
			return 1;
		}
	} else {
		printf("Too many arguments supplied\n");
		return 1;
	}

	test_array = create_array(array_len);
	search_array(test_array, array_len, max_array, NUM_TO_FIND);

	printf("Array:\n");
	for (int i = 0; i < array_len; i++) {
       		printf("%d ", test_array[i]);
	}
	printf("\n\n3 largest numbers:\n");
	for (int i = 0; i < NUM_TO_FIND; i++) {
        	printf("%d ", max_array[i]);
	}
	printf("\n");

	free(test_array);
	return 0;
}
