#include <stdio.h>

/** 
 * @file color.h
 * @brief Header file for color.c
 */

#define ANSI_COLOR_RED     "\x1b[31m" ///< Color Red
#define ANSI_COLOR_GREEN   "\x1b[32m" ///< Color Green
#define ANSI_COLOR_YELLOW  "\x1b[33m" ///< Color Yellow
#define ANSI_COLOR_BLUE    "\x1b[34m" ///< Color Blue
#define ANSI_COLOR_MAGENTA "\x1b[35m" ///< Color Magneta
#define ANSI_COLOR_CYAN    "\x1b[36m" ///< Color Cyan
#define ANSI_COLOR_RESET   "\x1b[0m"  ///< Reset Color

void red(char*);
void yellow(char*);
void green(char*);
/*
void reset(char*);
void magneta(char*);
void cyan(char*);
void blue(char*);
*/
