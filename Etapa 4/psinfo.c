#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<sys/utsname.h>
#include<string.h>
#include <sys/stat.h>
#ifndef MAX
#define MAX 10000
#endif

	void changeName(char string[]);	// Change the name of the file with the process id
	void getProcessInformation(char process[], int print);	// Sent the process id and if you want to print, and then see the magic
	int isNumeric(char string[]); 	// Send string to check if its a number or not


	int main(int argc, char *argv[]){
		if(argc<2) {								// If the argc value is less 2, that means theres nothing sent as parameter
			printf("You must send a value as parameter\n");			// We let the user know that he is stu***
			return EXIT_FAILURE;						// We return because there is not enough information
		}
		char *operationType = argv[1];						// Getting the first parameter
		if(argc ==2){								// If the argc value equals 2, that means there is only one parameter to evaluate
			if(isNumeric(operationType)!=1){				// If the isNumeric method return something different than 1, that means is not numeric
				printf("You must send a numeric value instead of: %s\n", operationType); 	//Let the user know about the error
				return EXIT_FAILURE;					// We return because we need numeric values for ID
			} else {
				getProcessInformation(operationType,0);			// Get the process information without writing on a file (Thats why we sent 0 as parameter)
			}
		} else {
		if(strcmp(operationType, "-r")==0){					// If operationType is -r we must write the values on the file
			char states[MAX] = "";						// This variable is used to store the process id values
			for(int i=2;i<argc;i++){					// For for the next items sent as parameters
				char *processId = argv[i];				// Getting the process id sent as parameter
				if(isNumeric(processId)==0){				// If isNumeric equals 0, that means the input is not numeric
					printf("Please write numbers instead of this shit \n");	// Let the user know the error
				}else{
					strcat(states, "-");				// Concatenate the - to show different processes
					strcat(states, processId);			// Concatenate the previous process with the next one
					getProcessInformation(processId,1);		// The second parameter is 1 because we want to write on the file
				}


			}
			changeName(states);					// Change the name of the file with the process id
		} else if (strcmp(operationType, "-l")==0){			// If operationType is -l we must print the results
			for(int i=2;i<argc;i++){				// For for the next items sent as parameters
				char *processId = argv[i];			// Getting the process id sent as parameter
				if(isNumeric(processId)==0){			// If isNumeric equals 0, that means the input is not numeric
					printf("Please write numbers instead of this shit \n"); // Let the user know the error
				}else{
					getProcessInformation(processId,0);	// The second parameter is because we dont want to write on the file

				}

			}
			} else {
				printf("If you want to check two or more processes you must put the -l first\n"); // Message to let the user know the error
				return EXIT_FAILURE;				// We return because for two or more ids, we need the -l or -f first.
			}
		}


	return 0; 								// Return
	}
