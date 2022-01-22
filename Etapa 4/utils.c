#include<stdio.h>
#include<string.h>
#include<ctype.h>
#ifndef MAX
#define MAX 10000
#endif


	void changeName(char string[]){
    		char buffer1[MAX];
    		char buffer2[MAX];
    		strcat(strcpy(buffer1, "psinfo-report"),string);
    		strcat(strcpy(buffer2, buffer1),".info");
    		rename("psinfo-report.txt",buffer2);
	}


	int isNumeric(char string[]){						// This function will let us know if a parameter is numeric or not
		int length,i ;							// Declaring the variables
		length=strlen(string);						// The length value of the string sent as parameter
		for(i=0;i<length;i++){						// For to check each value of the string sent as parameter
			if(!isdigit(string[i])){				// If some of the char inside the array is not digit
				return 0;					// We return 0 that means is not numeric
			}
		}
		return 1;							// We return 1 that means is numeric
	}

		void writeFile(char string[]) {              			//This function will write each process into the requested file
    		char buffer[MAX];						// This is where we are going to store each line of the string
    		strcat(strcpy(buffer, string),"\n\n");  			// Apply a line break
    		FILE *fp = fopen("psinfo-report.txt", "a+");        		// Open the file
    		for(int i=0; i<strlen(buffer); i++){    			// Read each line of the string
      			fputc(buffer[i], fp);               			// Write on the file
    		}
    		fclose(fp);                             			// Close the file
	}
