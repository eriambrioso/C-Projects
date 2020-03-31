
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct{
	char *date;
	double open;
	double high;
	double low;
	double close;
	unsigned int volume;
	double adj_close;
}STOCK;

int main(int argc, char *argv[]){
	int i = 0, j = 0, index = 0;// i tracks number of elemements in the struct there are, index is the index of the highest value
	double max;					// highest value- used as a comparison variable
	char input[100], *token;
	
	FILE *fp = fopen(argv[1], "r");
	STOCK *data = (STOCK*)malloc(sizeof(STOCK)); 		// allocate memory to the array of structs
	
	fgets(input, 100, fp);									// get the first row of column names
	
	while(fgets(input, 100, fp)){							// get the entire first row of data from the table
	
		data[i].date = (char*)malloc(sizeof(char));		// allocate memory to the date variable within the struct
		
		token = strtok(input, ",");							// tokenize the input into the proper variables...
		strcpy(data[i].date, token);
		token = strtok(NULL, ",");
		data[i].open = atof(token);
		token = strtok(NULL, ",");
		data[i].high = atof(token);
		token = strtok(NULL, ",");
		data[i].low = atof(token);
		token = strtok(NULL, ",");
		data[i].close = atof(token);
		token = strtok(NULL, ",");
		data[i].volume = atoi(token);
		token = strtok(NULL, ",");
		data[i].adj_close = atof(token);
		
		i++;
		data = (STOCK*)realloc(data, (i+1) * sizeof(STOCK));	//reallocate one more struct each time the loop runs	
	}
	fclose(fp);
	
	// find the highest 'high' value
	max = data[0].high;						// set max to first element
	while(j < i){							// j starts at 0 ad loops through the entire struct
		if(data[j].high > max){
			max = data[j].high;
			index = j;						// save the index of the highest value
		}
		
		j++;	
	}
	// print the entire struct at the index found
	
	 printf("Date: %s\nOpen: %.2lf\nHigh: %.2lf\nLow: %.2lf\nClose: %.2lf\nVolume: %u\nAdj. Close: %.2lf\n", data[index].date, data[index].open, data[index].high, data[index].low, data[index].close, data[index].volume, data[index].adj_close);
	
	
	return 0;
}













