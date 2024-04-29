#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "dbms.h"
#include <stdbool.h>

/**
 * Diplays the row in specified format
 */
int db_show_row(const struct db_table *db, unsigned int row){
	//saves album locally as no modification being made
	struct album  alb = (db->table)[row];
	if(row >= db->rows_used)return 0; //failure base case
	
	//display array 
	char disp[100];
	
	//getting id in allotted slot
	int id =alb.id;
	
	int index =5;
	//filling values for id backwards to account for id of any size
	while(id>0 && index >=0){
		disp[index] = '0' +id%10;
		index--;
		id /=10;
	}
	//filling rest of the space with chars so that initialised null chars do not terminate string early
	while(index > -1){
			disp[index] = ' ';
			index--;
	}
	index=6;
	disp[index]=':';
	
	//Getting the album title
	char * given_album = alb.title;
	int alb_len = strlen(alb.title);
	
	//Determining starting index to fill title in from
	if(alb_len>=20){
		index = 7;
	}else{
		index = 27 - alb_len;
		//if shorter than space allocated, fills in blank charachters 
		for(int i = index-1; i > 6; i--){
			disp[i] = ' ';
		}
	}
	//populating array
	for(int i = 0;index < 27; i++){
		disp[index] = given_album[i];
		index++;
	}
	index=27;
	disp[index]=':';
	
	//Getting artist title
	char * artist = alb.artist;
	int art_len = strlen(artist);
	//Determining starting index to fill title in from
	//
	if(art_len>=20){
		index = 28;
	}else{
		index = 48 - art_len;
		//if shorter than space allocated, fills in blank charachters 
		for(int i = index-1; i > 27; i--){
			disp[i] = ' ';
		}
	}

	//populating array
	for(int i = 0;index < 48; i++){
		disp[index] = artist[i];
		index++;
	}
	index=48;
	disp[index]=':';
	
	//as the year is always going to be 4 digits, index to populate from is determined
	index= 52;
	int year = alb.year;
	//filling in year, digit by digit - mod function getting the last digit accordingly 
	for(int i = 0; i < 4; i++){
		disp[index] = '0' +year % 10;
		year /=10;
		index--;
	}
	//finishing array withnew line and terminating null charachter
	index = 53;
	disp[index] = '\n';
	disp[++index]= '\0';
	
	//display the string
	printf("%s",disp);
	return 1;
}

/**
 * Adds a album to the table using dynamic memory allocation
 */
int db_add_row(struct db_table *db, struct album *a){
	//check rows of the table 
	if(db->rows_used >= db->rows_total){
		//allocates memory for table if not allocated
		if(db->table == NULL){
			 (db->table) = (struct album *)calloc(5, sizeof( struct album));
		}else{
		//reallocates more space for entries
			 (db->table) = (struct album *)realloc(db->table, (db->rows_total + 5) * sizeof(struct album)); 
		}
		//if memory allocation did not succeed, failure
		if(db->table == NULL)return 0;
		db->rows_total +=5;//updating number of rows
	}
	//adding album to row by dereferencing pointer to the album
	db->table[db->rows_used]=*a;
	db->rows_used++;
	return 1;
}

/**
 * Removes an album and adjusts the memory allocated for the table
 */
int db_remove_row(struct db_table *db, unsigned long id){
	//checking base case for failure
	if(db->rows_used == 0 || db->table ==NULL) return 0;
	
	// Find the index of the album with the specified id
	int found = -1;
    for (int i = 0; i < db->rows_used; i++) {
        if (db->table[i].id == id) {
            found = i;
            break;
        }
    }
	if(found < 0)return 0;//no id match found
	
	//shifting album down to remove and fill table
	for(int i = found; i < (db->rows_used) -1; i ++){
		db->table[i] = db->table[i+1];
	}
	db->rows_used--;
	
	//if large space alloted and not filled
	if((db->rows_total - db->rows_used) >= 5){
		int new_max = (db->rows_used / 5) * 5;
		db->table = realloc(db->table,  new_max* sizeof(struct album));//use of integer division to have appropriate size re-allocated 
		db->rows_total = new_max;
	}else if (db->rows_used == 0){
		//if empty frees memory and sets members appropriately
		free(db->table);
		db->rows_total = 0;
		db->rows_used = 0;
	}
	return 1;
}
