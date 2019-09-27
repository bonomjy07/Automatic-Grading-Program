#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <limits.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/types.h>

/** 
 * @file grading.h
 * @brief Header file for grading.c
 */

#define NUM_OF_SECTOR 5  ///< Number of sector to grade is 5.
#define ID_LENGTH     8  ///< Length of student id is 8.

void signal_handler(int);
void do_grading(int *);
int filter(const struct dirent *info);
