#include <stdio.h>
#include <stdlib.h>

struct Readings {
	int temp;
	int hum;
};

struct Readings_array {
	struct Readings readings[10];
	int max_temp;
	int min_temp;
	int max_hum;
	int min_hum;
	int log_counter;
	float avg_temp;
	float avg_hum;
};

void Readings_array_add_new_value (struct Readings_array *data_ptr, long *input_ptr)
{
	if (data_ptr->log_counter < 10) {

		data_ptr->readings[data_ptr->log_counter].temp = *input_ptr & 0x1FFF;
		data_ptr->readings[data_ptr->log_counter].hum = (*input_ptr & 0x3FFE000)>>13;
		printf("Received Temperature: %d\n", data_ptr->readings[data_ptr->log_counter].temp);
		printf("Received Humidity: %d\n", data_ptr->readings[data_ptr->log_counter].hum);
		(data_ptr->log_counter)++;
	}
	else {
		printf("Log Full\n");
	}

}

void Readings_array_average(struct Readings_array *data_ptr)
{
	int sum_temp = 0;
	int sum_hum = 0;
	for (int i = 0; i < data_ptr->log_counter; i++) {
		sum_temp += data_ptr->readings[i].temp;
		sum_hum += data_ptr->readings[i].hum;
	}
	data_ptr->avg_temp = ((float)sum_temp/data_ptr->log_counter);
	data_ptr->avg_hum = ((float)sum_hum/data_ptr->log_counter);
	if (data_ptr->log_counter == 0) {
		printf("Average Temperature: N/A\n");
		printf("Average Humidity: N/A\n");
	}
	else {
		printf("Average Temperature: %.2f\n", data_ptr->avg_temp);
		printf("Average Humidity: %.2f\n", data_ptr->avg_hum);
	}

}

void Readings_array_max(struct Readings_array *data_ptr)
{
	data_ptr->max_temp = data_ptr->readings[0].temp;
	data_ptr->max_hum = data_ptr->readings[0].hum;
	for (int i = 0; i < data_ptr->log_counter; i++) {
		if (data_ptr->max_temp < data_ptr->readings[i].temp) {
			data_ptr->max_temp = data_ptr->readings[i].temp;
		}
		if (data_ptr->max_hum < data_ptr->readings[i].hum) {
			data_ptr->max_hum = data_ptr->readings[i].hum;
		}
	}
	if (data_ptr->log_counter == 0) {
		printf("Maximum Temperature: N/A\n");
		printf("Maximum Humidity: N/A\n");
	}
	else {
		printf("Maximum Temperature: %d\n", data_ptr->max_temp);
		printf("Maximum Humidity: %d\n", data_ptr->max_hum);
	}
}

void Readings_array_min(struct Readings_array *data_ptr)
{
	data_ptr->min_temp = data_ptr->readings[0].temp;
	data_ptr->min_hum = data_ptr->readings[0].hum;
	for (int i = 0; i < data_ptr->log_counter; i++) {
		if (data_ptr->min_temp > data_ptr->readings[i].temp) {
			data_ptr->min_temp = data_ptr->readings[i].temp;
		}
		if (data_ptr->min_hum > data_ptr->readings[i].hum) {
			data_ptr->min_hum = data_ptr->readings[i].hum;
		}
	}
	if (data_ptr->log_counter == 0) {
		printf("Minimum Temperature: N/A\n");
		printf("Minimum Humidity: N/A\n");
	}
	else {
		printf("Minimum Temperature: %d\n", data_ptr->min_temp);
		printf("Minimum Humidity: %d\n", data_ptr->min_hum);
	}
}

void Readings_array_print(struct Readings_array *data_ptr)
{
	printf("Log: %d entries\n", data_ptr->log_counter);
	for (int i = 0; i < data_ptr->log_counter; i++) {
		printf("Temperature: %d\n", data_ptr->readings[i].temp);
	}
}

int main(int argc, char *argv[])
{
	struct Readings_array data;
	data.readings[0].hum = 0;
	data.readings[0].temp = 0;
	data.avg_temp = 0;
	data.avg_hum = 0;
	data.log_counter = 0;
	data.max_temp = 0;
	data.min_temp = 0;
	data.max_hum = 0;
	data.min_hum = 0;
	struct Readings_array *data_ptr = &data;

	char input[20] = { '\0' };
	long input_num = 0;
	long type = 0;

	long *input_ptr = &input_num;
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
			Readings_array_add_new_value(data_ptr, input_ptr);
			break;

		case 0x2:
			Readings_array_average(data_ptr);
			break;

		case 0x4:
			Readings_array_max(data_ptr);
			break;

		case 0x3:
			Readings_array_min(data_ptr);
			break;

		case 0x5:
			Readings_array_print(data_ptr);
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

