/**
 * @file NDCython.c
 *
 * This file contains the definitions to functions declared in NDCython.h
 * the intent of this file is to import helpful python fucntions into c 
 *
 * @see NDCython.h
 *
 * @author Awn Duqoum (aduqoum)
 *
 */

#include "NDCython.h"
/*****************************************************************
Name:           getLastElement

Input Values:
	List src       : Input string from which the substring is to come from

Output Values:
	None

Returned Value:
    char* ret         : The last string in the list

Description:
	Returns the last string in the list

*****************************************************************/
char* getLastElement (List src)
{
	size_t i = 0;
	if(src == NULL)
		return NULL;
	while( src[i] != NULL)
		i++;
	
	return src[i-1];
}
/*****************************************************************
Name:           substr

Input Values:
	char *prt       :  Pointer to the first element of the character array

Output Values:
	None

Returned Value:
    size_t ret         : The size of the array 

Description:
	Returns the size of a character array using a pointer to the first element of the character array
*****************************************************************/
size_t size(char *ptr)
{
    //variable used to access the subsequent array elements.
    int offset = 0;
    //variable that counts the number of elements in your array
    int count = 0;

    //While loop that tests whether the end of the array has been reached
    while (*(ptr + offset) != '\0')
    {
        //increment the count variable
        ++count;
        //advance to the next element of the array
        ++offset;
    }
    //return the size of the array
    return count;
}
/*****************************************************************
Name:           substr

Input Values:
	char *input       : Input string from which the substring is to come from
	size_t start      : The start index of the substring
	size_t len        : Length of the substring

Output Values:
	None

Returned Value:
    char* ret         : The substring requested 

Description:
	Returns a substring from a string using a start index and a length, 
	if the input is NULL or the not long enough or not enough memory was found, NULL is returned

*****************************************************************/
 char *substr(char *input, size_t start, size_t len) { 
	char *ret = NULL;
	if(input == NULL || size(&input[0]) < start + len)
		return NULL;

	ret = (char*) malloc(len+1);
	if(ret == NULL)  //Check if malloc fails
		return NULL; // no need to free as no memory was allocated
    memcpy(ret, input+start, len);
    ret[len]  = '\0';
    return ret;
}
/*****************************************************************
Name:           countOccurrences

Input Values:
	char* src         : Input string from which the substring is to come from
	char* delimiter   : The substring we are counting

Output Values:
	None

Returned Value:
    size_t count      : The amount of times 'delimiter' is found in 'src'

Description:
	This function counts the number of times a substring is found in an input string,
	returns zero if not found or invaild vaules are given

*****************************************************************/
 size_t countOccurrences (char* src, char* delimiter)
{
	int i_length, count = 0,i = 0, secondCount = 0, i_Dlength;
	if( src == NULL || delimiter == NULL) 
		return 0;
	
	i_length = size(&src[0]);
	i_Dlength = size(&delimiter[0]);

	for( i; i < i_length; i ++){
		if(src[i] == delimiter[0] && (i+i_Dlength) < i_length) {
			while(secondCount < i_Dlength){
				if( src[i + secondCount] != delimiter[secondCount])
					break;
				secondCount ++;
			}
			if(secondCount == i_Dlength) //if we did not break early
				count ++;
		}
	}
	return count;
}
/*****************************************************************
Name:           find

Input Values:
	char* src         : Input string from which the substring is to come from
	char* delimiter   : The substring we are looking for

Output Values:
	None

Returned Value:
    int               : The first location of the delimiter if found, -1 otherwise

Description:
	This function finds the first occurance of the delimiter in the input string, if the 
	delimiter is more than one char long its starting location will be returned.

*****************************************************************/
int find (char* src, char* delimiter)
{
	int i_length,i = 0, count = 0, i_Dlength;
	if( src == NULL || delimiter == NULL) 
		return 0;
	
	i_length = size(&src[0]);
	i_Dlength = size(&delimiter[0]);

	for( i; i < i_length; i ++){
		if(src[i] == delimiter[0] && (i+i_Dlength) < i_length) {
			while(count < i_Dlength){
				if( src[i + count] != delimiter[count])
					break;
				count ++;
			}
			return i;
		}
	}
	return -1;
}
/*****************************************************************
Name:           split

Input Values:
	char* src         : Input string from which the substring is to come from
	char* delimiter   : The substring we are splitting with

Output Values:
	None

Returned Value:
    List des        : An array of char arrays containing the substrings 
						or NULL if the inputs are invaild or not enough memory was found 

Description:
	This function finds the first occurance of the delimiter in the input string, if the 
	delimiter is more than one char long its starting location will be returned. The last element of
	the returned array is NULL

*****************************************************************/
 List split (char* src, char* delimiter )
{
	size_t i_occurrences = 0, i_length = 0, i_occurrenceCount = 0, i_Dlength = 0, i_location = 0, i_Templocation;
	List des = NULL;
	if( src == NULL)
		return NULL;
	
	i_occurrenceCount = 0; // Initialize the counter to zero 
	i_length = size(&src[0]); // Length of the input string
	i_Dlength = size(&delimiter[0]); // Length of the delimiter

	i_occurrences = countOccurrences(src,delimiter); // find the amount of times the delimiter occurs in the input string

	des = (List) malloc (sizeof(char*) * i_occurrences + 2); // Allocate enough memory to store the substrings
	if(des == NULL) //Check if malloc fails
	{
		free (des);
		return NULL;
	}
	while( i_occurrenceCount < i_occurrences )
	{
		i_Templocation = find(src,delimiter); //No checking needed here as we know the delimiter will be found 
		des[i_occurrenceCount] = (char*) malloc (sizeof(char) * i_Templocation + 1); // Allocate enough memory for the substring
		if(des[i_occurrenceCount] == NULL)  //Check if malloc fails
		{
			free (des);
			return NULL;
		}
		strcpy(des[i_occurrenceCount], substr(src, 0, i_Templocation )); // Copy substring over
		src = src + i_Templocation + i_Dlength; //Move the pointer over the already used section
		i_location += i_Templocation + i_Dlength;
		i_occurrenceCount ++;
	}
	
	des[i_occurrenceCount] = (char*) malloc (sizeof(char) *  i_length - i_location); // Allocate enough memory for the rest of the string
	if(des[i_occurrenceCount] == NULL)  //Check if malloc fails
	{
		free (des);
		return NULL;
	}
	strcpy(des[i_occurrenceCount], substr(src, 0, i_length - i_location));
	
	des[i_occurrenceCount +1] = NULL;
	
	return des;
}
/*****************************************************************
Name:           join

Input Values:
	List src         : Source of the substrings we are adding together
	char* delimiter    : What to add between substrings

Output Values:
	None

Returned Value:
    char* des         : Array of all substrings

Description:
	This function concatinates all substirngs found in the src input, or returns NULL if 
	the inputs are invaild or not enough memory was found 

*****************************************************************/
 char* join (List src, char* delimiter )
{
	size_t count = 0, totalSize = 0,i_dlength = 0; 
	char * des = NULL;

	if( src == NULL || delimiter==NULL ) 
		return NULL;
	
	i_dlength = size(&delimiter[0]);

	//We do not know how much memory we need to allocate yet, count the size of all substrings and add size of delimiter
	while( src[count] != NULL)
	{
		totalSize += (size(src[count]) + i_dlength) * sizeof(char);
		count ++;
	}

	des = (char*) malloc (totalSize); // +1 for \0
	memset(des,'\0', totalSize +1);
	if(des == NULL) //check if malloc failed
		return NULL;

	count = 0;
	while( src[count] != NULL)
	{
		strcat(des, src[count]);
		strcat(des, delimiter);
		count ++;
	}

	return des;
}
 /*****************************************************************
Name:           getSize

Input Values:
	List src         : The list which the user wants the size of

Output Values:
	None

Returned Value:
    size_t count      : The size of the list

Description:
	This function counts the number elements in a list and returns the number

*****************************************************************/
 size_t getSize (List src)
 {
	 size_t i = 0;
	 if(src == NULL)
		 return 0;
	 while(src[i] != NULL)
		 i++;
	 return i;
 }
 /*****************************************************************
Name:           isin

Input Values:
	char* src         : The string to be search 
	char* substring   : The substring that is to be found

Output Values:
	None

Returned Value:
    int ret      : 0 if substring is not found
				   1 if substring is found

Description:
	This funciton searchs a string for a specified substring

*****************************************************************/
 int isin (char* src, char* substring)
 {
	 if(src == NULL || substring == NULL)
		return FALSE;

	 if(countOccurrences(src,substring) > 0)
		return TRUE;
	return FALSE;
 }