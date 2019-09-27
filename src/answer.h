#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

/** @file answer.h.
    @brief Header file for answer.c
*/

#define BUFFER_SIZE 1024  ///< Buffer size

void init_answer(void);
void compile_ans(void);
void set_create_ans(void);
void set_search_ans(void);
void set_delete_ans(void);
void set_rsearch_ans(void);
