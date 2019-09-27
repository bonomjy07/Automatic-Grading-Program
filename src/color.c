#include "color.h"

/** 
 * @file color.c
 * @brief Collection of Method to print with color
 */

/** 
 * @brief Print string parameter in red.
 * @details Used it When answer is wrong.
 * @param character array.
 * @return void
 */

void red(char *s) 
{
	printf(ANSI_COLOR_RED "%s" ANSI_COLOR_RESET, s);
}

/** 
 * @brief Print string parameter in yellow.
 * @details Used it to display grading sectors.
 * @param character array.
 * @return void
 */

void yellow(char *s) 
{
	printf(ANSI_COLOR_YELLOW "%s" ANSI_COLOR_RESET, s);
}

/** 
 * @brief Print string parameter in green color.
 * @details Used it When answer is collect.
 * @param character array.
 * @return void
 */

void green(char *s) 
{
	printf(ANSI_COLOR_GREEN "%s" ANSI_COLOR_RESET, s);
}


/***************************************************** 
void magneta(char *s) 
{
	printf(ANSI_COLOR_MAGENTA "%s" ANSI_COLOR_RESET, s);
}

void cyan(char *s) 
{
	printf(ANSI_COLOR_CYAN "%s" ANSI_COLOR_RESET, s);
}

void blue(char *s) 
{
	printf(ANSI_COLOR_BLUE "%s" ANSI_COLOR_RESET, s);
}
*/
