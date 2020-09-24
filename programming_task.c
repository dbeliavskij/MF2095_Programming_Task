#include <stdio.h>
#include <stdlib.h>

void add_new_value (int *temperature_ptr, int *log_counter_ptr, long *input_ptr)
{
	if (*log_counter_ptr < 10) {

		temperature_ptr[*log_counter_ptr] = *input_ptr & 0x3FFFFFF;
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
	char input[20] = { '\0' };
	int sum = 0;
	long input_num = 0;
	long type = 0;

	int *log_counter_ptr = &log_counter;
	int *temperature_ptr = temperature;
	long *input_ptr = &input_num;
	int *sum_ptr = &sum;
	int *max_ptr = &max;
	int *min_ptr = &min;
	char *end_char;
	
beg:;
	input[0] = '\0';
	if (fgets(input, 20, stdin) == NULL) {
		printf("Input Error\n");
	}
	input_num = strtol(input, &end_char, 16);
	type = input_num & 0x1C000000;
	type = type >> 26;		
	
	switch(type) {

		case 0:
			add_new_value(temperature_ptr, log_counter_ptr, input_ptr);
			break;

		case 0x2:
			average_temperature(temperature_ptr, log_counter_ptr, sum_ptr);
			break;

		case 0x4:
			max_temperature(temperature_ptr, max_ptr, log_counter_ptr);
			break;

		case 0x3:
			min_temperature(temperature_ptr, min_ptr, log_counter_ptr);
			break;

		case 0x5:
			print_log_entries(temperature_ptr, log_counter_ptr);
			break;
		
		case 0x6:
			printf("Exiting...\n");
			return 0;

		default:
			printf("Input Error\n");
			break;
	}
	goto beg;

}

