#include <stdio.h>
#include "editor.h"
#include <stdbool.h>
#include <string.h>
/**
 * Inserts a charachter into the editing buffer
 */
int editor_insert_char(char editing_buffer[], int editing_buflen, char to_insert, int pos){
	if(pos >= editing_buflen || pos < 0)return 0;//if to insert is out of bounds return wrong
	int copy[editing_buflen]; //copy array of size given
	//fills in array copy
	for(int i = 0; i < editing_buflen; i++){
		copy[i] = editing_buffer[i];
	}
	
	//run a for loop where i = pos
	//then set index ahead to previous value at current index and i stops at editing_buflen-1 as it is moving ahead by one
	editing_buffer[pos] = to_insert;
	for(int i = pos; i < editing_buflen-1; i++){
		editing_buffer[i+1] = copy[i];
	}
	
	return 1;
}

/**
 * Deletes a charachter from the editing buffer
 */
int editor_delete_char(char editing_buffer[], int editing_buflen, char to_delete, int offset){
	//initial checks
	if(offset >= editing_buflen || offset < 0) return 0;
	bool found = false;
	
	//start at offset til length-1
	for(int i = offset; i < editing_buflen -1; i++){
		//if value at index equals to_delete, switch boolean 
		if(editing_buffer[i] == to_delete)found = true;
		// if boolean has been found and shift value an index ahead downstop at -1
		if(found){
			editing_buffer[i] = editing_buffer[i+1];
		}
	}
	if(!found)return 0; // didnt find charachter to delete
	editing_buffer[editing_buflen-1] = '\0'; //set final charachter to null 
	return 1;
}
	
	
/**
 * Replaces a String in the buffer from an offset
 */
int editor_replace_str(char editing_buffer[], int editing_buflen, const char *str, const char *replacement,int offset){
	//base cases - str is empty & invalid offset
	if(strlen(str) == 0) return -1;
	if(offset >= editing_buflen || offset < 0) return -1;
	
	
	int foundAt= -1; //found index of starting char to replace
	
	//from offset find if char in buffer equals first char in string to replace
	for(int i = offset; i < editing_buflen; i++){
		if(editing_buffer[i] == str[0]){
			foundAt =i;
			break;
		}
	}
	
	//base case - buffer does not contain string to replace
	if(foundAt < 0)return -1;
	
	int j = foundAt;//variable to move through editing buffer
	
	//get length of both string and replacement for stopping conditions
	int lengthOfstr = strlen(str);
	int lengthOfreplacement = strlen(replacement);
	
	//variable 'k' as final bound to stop at end of shorter string 
	int k = foundAt; 
	if(lengthOfstr <= lengthOfreplacement)k += lengthOfstr;
	else k += lengthOfreplacement;
	
	int arrayI = 0;//variable to run through replacement
	
	//then from that index while variable is less then appropriate lengths, remove at index and add at that index using previously defined methods
	while(j < editing_buflen && j < k){
		if(editing_buffer[j] == str[arrayI]){
			editor_delete_char(editing_buffer, editing_buflen, str[arrayI],j);
			editor_insert_char(editing_buffer, editing_buflen, replacement[arrayI], j);
			//move along in both arrays
			j++;
			arrayI++;
		}else{
			//break out if did not string is not found in its entirety
			return -1;
		}
	}
	
	int toRet = j-1;// saves last element replacement occured
	
	//if replacement still has left keep going inserting
	if(lengthOfreplacement > lengthOfstr){
		int toGo = foundAt+lengthOfreplacement;
		while (j< toGo && j< editing_buflen){
			//calling defined method does inserting as expected
			editor_insert_char(editing_buffer, editing_buflen, replacement[arrayI], j);
			//move along in both arrays
			j++;
			arrayI++;
		}
		toRet = j-1;//update toRet as more replacement occured
	}else if(lengthOfreplacement < lengthOfstr){//if String to replace still has charachters left
		int toGo = foundAt+lengthOfstr;
		while(j < toGo && j < editing_buflen){
			//calling defined method does deletion as expected
			editor_delete_char(editing_buffer, editing_buflen, str[arrayI],j);
			//move along in both arrays
			j++;
			arrayI++;
		}
	}
	return toRet;
}


/**
 * Displays the buffer in a 2D arrangment
 */
void editor_view(int rows, int cols, char viewing_buffer[rows][cols], const char editing_buffer[], int editing_buflen, int wrap){
	//populate the viewing buffer with null charachters
	for(int i = 0; i < rows; i++){
		for(int j = 0; j< cols; j++){
			viewing_buffer[i][j] = '\0';
		}
	}
	int i_edit = 0; //editing buffer index
	
	//run through 2d array the same for both cases just changes at last index of lines
	for(int i = 0; i < rows;i++){
		//catching break case - both for initial base case and if breaking out in second loop catches it again and breaks
		if(i_edit >= editing_buflen || editing_buffer[i_edit] == '\0')break;
		for(int j = 0; j < cols; j++){
			if(i_edit >= editing_buflen || editing_buffer[i_edit] == '\0' )break;
			//if at last index
			if(j == cols-1){
				//checking if view is wrapped or not
				if(!wrap){
					//if didnt fine new line char
					if(editing_buffer[i_edit] != '\n'){
						//keep moving further in the editing array
						while(editing_buffer[i_edit] != '\n'){
							i_edit++;
							if(i_edit >= editing_buflen || editing_buffer[i_edit] == '\0' )break;
						}	
						//move past new line char and move to next line in viewing buffer/loop
						i_edit++;
						break;
					}else{
						i_edit++;//just move to next line as expected char was found
					}
				}
			}else{
				//moves to next line when finding new line charachter
				if(editing_buffer[i_edit] == '\n'){
					i_edit++;//move to next char
					break;
				}else{
					//if not catching case found, populates an index as expected
					viewing_buffer[i][j] = editing_buffer[i_edit];
					i_edit++;
				}
			}
		}
	}
}
