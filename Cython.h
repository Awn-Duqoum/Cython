/**
 * @NDCython.h
 * @brief Contains prototypes for the cython functions
 *
 * <STRONG> Description: </STRONG>
 *   <P>	This file contains the declerations to functions defined in NDCython.h
 *			the intent of this file is to import helpful python fucntions into c 
 *
 *   Confidential and Proprietary.
 *   Not for distribution outside of NDI without proper authorization.
 *
 * @author Awn Duqoum      11/07/2016
 */

#ifndef NDCYTHON
#define NDCYTHON

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

#ifdef __cplusplus
extern "C" {
#endif

typedef char** List;

char* getLastElement (List src);

size_t getSize (List src);

int find (char* src, char* delimiter);

size_t countOccurrences (char* src, char* delimiter);

size_t size(char* ptr);

char *substr(char *input, size_t start, size_t len);

List split (char* src, char* delimiter);

char* join (List src, char* delimiter );

int isin (char* src, char* substring);

#ifdef __cplusplus
}
#endif

#endif
