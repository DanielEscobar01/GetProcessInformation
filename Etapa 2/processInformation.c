#include<stdio.h>
#include<string.h>
#ifndef MAX
#define MAX 10000
#endif

  void writeFile(char string[]);	// Send the string we want to write and the method will create the file and write onto it


  void getProcessInformation(char process[], int print){			// This function get the details from certain process and write the information in a file.
		char lastPart[] = "/status";					// The last part of the code
		char destination[256] = "/proc/";				// The first part of the code
		strcat(destination,process);					// Concatenate the first part with the previous concatenated part
		strcat(destination,lastPart);					// Concatenate the Id with the last part
		char *filename = destination;					// Setting file name as the file of the process
	    	FILE *fp = fopen(filename, "r"); 				// Open the requested file in lecture mode
	    	if (fp == NULL) {						// Check if the file exists
			printf("\nThe process you are trying to access does not exist -> %s\n", process);	// If it doesnt exist, then we throw a message
			char statusdata[]= "The requested process does not exist";				// This is where we are going to save the information
			if(print==1){						// If the parameter is 1, that mean we have to write the information on the file
		    		writeFile(statusdata);				// Call writeFile method
		    	}
	    	}else{
			char statusdata[MAX]= "";				// This is were we are going to save the information
			char temp[264]="";					// Define temporary variable
			char temp2[264]="";					// Define temporary variable
			char temp3[264]="";					// Define temporary variable
			char temp4[264]="";					// Define temporary variable for the name
    			char delimitador[] = ":";				// Define temporary variable
		    	const unsigned MAX_LENGTH = 10000; 			// The maximum length of the text
		    	char buffer[MAX_LENGTH]; 				// This is where we are going to store each line of the document
			fgets(buffer, MAX_LENGTH, fp); 				// Reads the first line of the file
			char *token = strtok(buffer, delimitador); 		// We use this to divide the string using the delimiter ":"
			token = strtok(NULL, delimitador);			// We take the value after the first appearance of ":"
			strcat(temp4, token);   				// Stores the name state in temp4
			token = strtok(NULL, delimitador);			// We take the value after the first appearance of ":"

			while( token != NULL ) {
				strcat(temp4, ":");   				// Stores the name state in temp4
				strcat(temp4, token);   				// Stores the name state in temp4
				token = strtok(NULL, delimitador);			// We take the value after the first appearance of ":"

			}

			strcat(statusdata, "\n\nNombre del proceso: ");		// Stores the process name in statusData
			strcat(statusdata, temp4);				// Stores the process name in statusData
			fgets(buffer, MAX_LENGTH, fp);				// Reads the second line of the file
			fgets(buffer, MAX_LENGTH, fp);				// Reads the third line of the file
			token = strtok(buffer, delimitador);     // We use this to divide the string using the delimiter ":"
			token = strtok(NULL, delimitador);			// We take the value after the first appearance of ":"
			strcat(statusdata, "Estado: ");				// Stores the process Estado in statusData
			strcat(statusdata, token);   				// Stores the process state in statusData
			int VmExe = 0;								//Si la variable VmExe existe en el proceso (Bandera)
		   	for (int i = 0; i < 51; i++ ){ 				// Read the i-next lines of the file
				fgets(buffer, MAX_LENGTH, fp);	 		// Get the i-line of the file

				token = strtok(buffer, delimitador); //toma el valor de lo que está antes de los dos puntos del buffer

				if(strcmp( token, "VmExe" ) == 0){
					VmExe = VmExe + 1;				//Cambio la bandera

					if(strcmp( temp3, "" ) == 0){
						strcat(statusdata, "Tamaño total de la imagen de memoria:\n");			// Stores the process Estado in statusData
					}else{
						strcat(statusdata, "Tamaño total de la imagen de memoria: ");			// Stores the process Estado in statusData
						strcat(statusdata, temp3);
					}

					token = strtok(NULL, delimitador);
					strcat(statusdata, "\tTamaño de la sección de memoria TEXT: ");				// Stores the process Estado in statusData
					strcat(statusdata, token);
					if(strcmp( temp, "" ) == 0){
						strcat(statusdata, "\tEste proceso no tiene la variable VmData\n");		// Stores the process Estado in statusData
					}else{
						strcat(statusdata, "\tTamaño de la sección de memoria DATA: ");			// Stores the process Estado in statusData
						strcat(statusdata, temp);
					}

					if(strcmp( temp2, "" ) == 0){
						strcat(statusdata, "\tEste proceso no tiene la variable VmStk\n");		// Stores the process Estado in statusData
					}else{
						strcat(statusdata, "\tTamaño de la sección de memoria STACK: ");		// Stores the process Estado in statusData
						strcat(statusdata, temp2);
					}
				}

				if(strcmp( token, "voluntary_ctxt_switches" ) == 0){
					if(VmExe == 0){
						if(strcmp( temp3, "" ) == 0){
							strcat(statusdata, "Tamaño total de la imagen de memoria:\n");				// Stores the process Estado in statusData
						}else{
							strcat(statusdata, "Tamaño total de la imagen de memoria: ");				// Stores the process Estado in statusData
							strcat(statusdata, temp3);
						}
						strcat(statusdata, "\tEste proceso no tiene la variable VmExe\n");				// Stores the process Estado in statusData
						if(strcmp( temp, "" ) == 0){
						strcat(statusdata, "\tEste proceso no tiene la variable VmData\n");				// Stores the process Estado in statusData
						}else{
							strcat(statusdata, "\tTamaño de la sección de memoria DATA: ");				// Stores the process Estado in statusData
							strcat(statusdata, temp);
						}

						if(strcmp( temp2, "" ) == 0){
						strcat(statusdata, "\tEste proceso no tiene la variable VmStk\n");				// Stores the process Estado in statusData
						}else{
							strcat(statusdata, "\tTamaño de la sección de memoria STACK: ");				// Stores the process Estado in statusData
							strcat(statusdata, temp2);
						}
					}
					token = strtok(NULL, delimitador);
					token[strcspn(token, "\n")] = 0;  //Elimina el salto de linea
					strcat(statusdata, "Número de cambios de contexto realizados (Voluntarios - no voluntarios): ");	// Stores the process Estado in statusData
					strcat(statusdata, token);
				}

				if(strcmp( token, "nonvoluntary_ctxt_switches" ) == 0){
					token = strtok(NULL, delimitador);
					if(token != NULL){
						strcat(statusdata, " - ");				// Stores the process Estado in statusData
						strcat(statusdata, token);
					}else{
						break;
					}
				}

				if(strcmp( token, "VmData" ) == 0){
					token = strtok(NULL, delimitador);
					strcat(temp, token); 		// Stores the memory image size in temp
				}

				if(strcmp( token, "VmStk" ) == 0){
					token = strtok(NULL, delimitador);
					strcat(temp2, token); 		// Stores the memory image size in temp
				}

				if(strcmp( token, "VmPeak" ) == 0){
					token = strtok(NULL, delimitador);
					strcat(temp3, token); 		// Stores the memory image size in temp
				}

			}

			printf("%s", statusdata);		// Print the All data in statusdata
		    	fclose(fp);
		    	if(print==1){
		    		writeFile(statusdata);
		    	}							// Close the file
	    	}

	}
