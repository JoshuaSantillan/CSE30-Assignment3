#include<stdio.h>
#include<stdlib.h>
#include<getopt.h>
#include "converter.h"


int main(int argc, char** argv){
	
	int opt;
	int m_flag;
	int err_opt;
	err_opt = 0;
	m_flag = 0;
	while ((opt = getopt(argc, argv, "+c")) != -1){
		switch (opt){
			case 'c':
				m_flag = 1;
				break;
			default:
				err_opt =1;
				break;
		}
	}
	if (m_flag != 1){
		usage(argv[0]);
	}
	// special case with just ./cnvrt -c
	if(argc < 3){
		exit(EXIT_SUCCESS);
	}
	
	int col = atoi(argv[2]);
	char** inputBuffer = (char**)malloc(sizeof(char*) * col);
	int* outputBuffer = (int*)malloc(sizeof(int) * atoi(argv[2]));
	char* line = NULL;
	size_t len = 0;
	ssize_t lineLength = 0;
	int i;
	for(i = 3; i < argc; i ++){
		if(atoi(argv[i]) < 1 || atoi(argv[i]) > col)
				usage(argv[0]);
	        outputBuffer[i-3] = atoi(argv[i]);
	}	       
	
	// populate inputBuffer
	int isQuote = 0;
	while((lineLength = getline(&line, &len, stdin)) != -1){
		int j = 0;
		inputBuffer[j++] = &line[0];
		for(i = 0; line[i] != '\0'; i++){
			if(line[i] == '"')
				isQuote = !isQuote;
			if(!isQuote){	
				if(line[i] == ','){
					line[i] = '\0';
					inputBuffer[j++] = &line[i+1];
				} 
				if(line[i] == '\n'){
					line[i] = '\0';
				}
			}	
	        }
		for(i = 0; i < argc-3; i++){
			printf("%s", (inputBuffer[outputBuffer[i]-1]));
			if(i == argc-4)
				printf("\n");
			else
				printf(",");
		}
	}
	free(line);
	free(inputBuffer);
	free(outputBuffer);
	return 0;
}

void usage(char *name){
	fprintf(stderr, "usage: %s [-c] [col_size] [col# ...] 1 <= col <= colsize\n", name);
	exit(EXIT_FAILURE);
}


