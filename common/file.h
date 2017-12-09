/* 
 * file utilities - reading a word, line, or entire file
 * 
 * David Kotz, May 2016
 */

#ifndef __FILE_H
#define __FILE_H

#include <stdio.h>

/**************** lines_in_file ****************/
/* Returns the number of lines in the given file,
 * i.e., the number of newlines in the file.
 * (If the file does not end with a newline, it will undercount by one.)
 * On return, the file pointer is back to beginning of file.
 * This will not work for pipes or stdin when it is attached to keyboard.
 */
int lines_in_file(FILE *fp);

/**************** readuntil ****************/
/* 
 * Read characters from the file into a null-terminated string,
 * and return a pointer to it; caller must later free() the pointer.
 * Reading continues until 'stop' function returns non-zero or until EOF.
 * The character triggering 'stop' is discarded.
 * The stopfunc may be NULL, in which case it is considered always 0.
 * Returns empty string if stop occurs on the first character encountered.
 * Returns NULL if EOF reached without reading anything.
 */
char *readuntil(FILE *fp, int (*stopfunc)(int c) );

/**************** readfile ****************/
/* 
 * Read remainder of the file into a null-terminated string,
 * and return a pointer to it; caller must later free() the pointer.
 * Returns NULL if EOF reached without reading anything.
 * After the call, file pointer is at EOF.
 */
char *readfile(FILE *fp);

/**************** readline ****************/
/* 
 * Read a line from the file into a null-terminated string,
 * and return a pointer to it; caller must later free() the pointer.
 * The string returned includes NO newline, and a terminating null.
 * Returns empty string if an empty line is read.
 * Returns NULL if EOF reached without reading a line.
 */
char *readline(FILE *fp);

/**************** readword ****************/
/* 
 * Read a word from the file into a null-terminated string,
 * and return a pointer to it; caller must later free() the pointer.
 * The string returned includes NO space, and a terminating null.
 * Returns empty string if the first character encountered is space or newline.
 * Returns NULL if EOF reached without reading a word.
 */
char *readword(FILE *fp);

#endif // __FILE_H
