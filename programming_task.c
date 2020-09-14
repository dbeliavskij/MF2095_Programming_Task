#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	int temperature[10] = { 0 };
	int max = 0;
	int min = 0;
	int log_counter = 0;
	char input[5] = { '\0' };
	int sum = 0;
	
beg:;
    	if (scanf("%s", input) != 1) {
		printf("Could not read command\n");
	}
		
	
	switch(input[0]) {

		case 'T':
			if (log_counter <= sizeof(temperature)/sizeof(int)) {

				temperature[log_counter] = atoi(&input[1]);
				printf("Received Temperature: %d\n", temperature[log_counter]);
				log_counter++;
			}
			else {
				printf("Log Full\n");
			}
			break;

		case 'A':
			for (int i = 0; i < log_counter; i++) {
				sum += temperature[i];
			}
			if (log_counter == 0) {
				printf("Average Temperature: N/A\n");
			}
			else {
				printf("Average Temperature: %.2f\n", (float)sum/log_counter);
			}
			break;

		case 'X':
			max = temperature[0];
			for (int i = 0; i < log_counter; i++) {
				if (max < temperature[i]) {
					max = temperature[i];
				}
			}
			if (log_counter == 0) {
				printf("Maximum Temperature: N/A\n");
			}
			else {
				printf("Maximum Temperature: %d\n", max);
			}
			break;

		case 'N':
			min = temperature[0];
			for (int i = 0; i < log_counter; i++) {
				if (min > temperature[i]) {
					min = temperature[i];
				}
			}
			if (log_counter == 0) {
				printf("Minimum Temperature: N/A\n");
			}
			else {
				printf("Minimum Temperature: %d\n", min);
			}
			break;

		case 'L':
			printf("Log: %d entries\n", log_counter);
			for (int i = 0; i < log_counter; i++) {
				printf("Temperature: %d\n", temperature[i]);
			}
			break;
		
		case 'Q':
			printf("Exiting...\n");
			return 0;
			break;

		default:
			printf("Input Error\n");
			break;
	}
	goto beg;

	return 0;
}

