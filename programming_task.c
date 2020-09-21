#include <stdio.h>
#include <stdlib.h>

void add_new_value (int *log_counter_ptr, int *temperature_ptr, char *input_ptr)
{
	if (*log_counter_ptr < 10) {

		temperature_ptr[*log_counter_ptr] = atoi(input_ptr+1);
		printf("Received Temperature: %d\n", temperature_ptr[*log_counter_ptr]);
		(*log_counter_ptr)++;
	}
	else {
		printf("Log Full\n");
	}

}

void average_temperature(int *temperature_ptr, int *log_counter_ptr, int *sum_ptr)
{
	for (int i = 0; i < *log_counter_ptr; i++) {
		(*sum_ptr) += temperature_ptr[i];
	}
	if (*log_counter_ptr == 0) {
		printf("Average Temperature: N/A\n");
	}
	else {
		printf("Average Temperature: %.2f\n", (float)(*sum_ptr)/(*log_counter_ptr));
	}

}

void max_temperature(int *temperature_ptr, int *max_ptr, int *log_counter_ptr)
{
	*max_ptr = temperature_ptr[0];
	for (int i = 0; i < *log_counter_ptr; i++) {
		if (*max_ptr < temperature_ptr[i]) {
			*max_ptr = temperature_ptr[i];
		}
	}
	if (*log_counter_ptr == 0) {
		printf("Maximum Temperature: N/A\n");
	}
	else {
		printf("Maximum Temperature: %d\n", *max_ptr);
	}
}

void min_temperature(int *temperature_ptr, int *min_ptr, int *log_counter_ptr)
{
	*min_ptr = temperature_ptr[0];
	for (int i = 0; i < *log_counter_ptr; i++) {
		if (*min_ptr > temperature_ptr[i]) {
			*min_ptr = temperature_ptr[i];
		}
	}
	if (*log_counter_ptr == 0) {
		printf("Minimum Temperature: N/A\n");
	}
	else {
		printf("Minimum Temperature: %d\n", *min_ptr);
	}
}

void print_log_entries(int *temperature_ptr, int *log_counter_ptr)
{
	printf("Log: %d entries\n", *log_counter_ptr);
	for (int i = 0; i < *log_counter_ptr; i++) {
		printf("Temperature: %d\n", temperature_ptr[i]);
	}
}

int main(int argc, char *argv[])
{
	int temperature[10] = { 0 };
	int max = 0;
	int min = 0;
	int log_counter = 0;
	char input[5] = { '\0' };
	int sum = 0;

	int *log_counter_ptr = &log_counter;
	int *temperature_ptr = temperature;
	char *input_ptr = input;
	int *sum_ptr = &sum;
	int *max_ptr = &max;
	int *min_ptr = &min;

	
beg:;
	fgets(input, 5, stdin);
		
	
	switch(input[0]) {

		case 'T':
			add_new_value(log_counter_ptr, temperature_ptr, input_ptr);
			break;

		case 'A':
			average_temperature(temperature_ptr, log_counter_ptr, sum_ptr);
			break;

		case 'X':
			max_temperature(temperature_ptr, max_ptr, log_counter_ptr);
			break;

		case 'N':
			min_temperature(temperature_ptr, min_ptr, log_counter_ptr);
			break;

		case 'L':
			print_log_entries(temperature_ptr, log_counter_ptr);
			break;
		
		case 'Q':
			printf("Exiting...\n");
			return 0;

		default:
			printf("Input Error\n");
			break;
	}
	goto beg;

}

