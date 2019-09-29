#include "answer.h"

/** 
 * @file answer.c
 * @details  Compile files in answer directory, Run exetable files, then \n
 * Read files(student.hsh, search_output, rsearch_output), 
 * Initiate answer variables.
 * \n cf) rsearch means re-search or, search hash file(student.hsh) again after deleted some records
*/

ssize_t Acreate_size;  ///< Size variable for creater-file size answer
ssize_t Asearch_size;  ///< Size variable for search-output size answer
ssize_t Adelete_size;  ///< Size variable for delete-file size answer
ssize_t Arsearch_size; ///< Size variable for re-search-output size answer

char Acreate_content[BUFFER_SIZE]; ///< Buffer for create-file answer
char Asearch_output[BUFFER_SIZE];  ///< Buffer for search-output answer
char Adelete_content[BUFFER_SIZE]; ///< Buffer for delete-file answer
char Arsearch_output[BUFFER_SIZE]; ///< Buffer for re-search-output answer

const char *hsh_fname = "student.hsh";             ///< file name for file to create
const char *search_fname = "search_output.txt";    ///< file name for output result of search
const char *rsearch_fname = "rsearch_output.txt";  ///< file name for output result of re-search

/** 
 * @brief Call method that initiate answer variables.
 * @details 
 * 1. Change directory to "./answer". 
 * 2. Call methods to initiate answer variables,
 * 3. Go back to current working directory
 * @param none
 * @return void
 */

void init_answer(void)
{
	printf("-------Initiate answer start!-------\n");
	chdir("./answer");

	compile_ans();
	set_create_ans();
	set_search_ans();
	set_delete_ans();
	set_rsearch_ans();

	chdir("../");
	printf("-------Initiate answer finished!-------\n");
}

/** 
 * @brief Compile answer files 
 * @details
 * 1. Remove files that don't need.
 * 2. Compile answer files.
 * @param none
 * @return void
 * */

void compile_ans(void)
{
	system("cp src/* ./");
	system("make clean");
	system("make a.out");
}

/** 
 * @brief Initiate answer for create-section 
 * @details Command Makefile to make answer for create-section, then
 * Store answer variables.
 * @param none
 * @return void
 */

void set_create_ans(void)
{
	int fd;

	system("make create");

	if ((fd = open(hsh_fname, O_RDONLY)) < 0) 
	{
		fprintf(stderr, "open %s error during set_create_ans()\n", hsh_fname);
		exit(1);
	}

	if ((Acreate_size = read(fd, Acreate_content, BUFFER_SIZE)) < 0)
	{
		fprintf(stderr, "read %s error during set_create_ans()\n", hsh_fname);
		exit(1);
	}

	close(fd);
}

/** 
 * @brief Initiate answer for search-section 
 * @details Command Makefile to make answer for search-section, then
 * Store answer variables.
 * @param none
 * @return void
 */

void set_search_ans(void)
{
	int fd;
	char cmm[BUFFER_SIZE] = {0};

	sprintf(cmm, "%s > %s", "make search", search_fname);
	system(cmm);

	if ((fd = open(search_fname, O_RDONLY)) < 0) 
	{
		fprintf(stderr, "open %s error during set_search_ans()\n", search_fname);
		exit(1);
	}

	if ((Asearch_size = read(fd, Asearch_output, sizeof(Asearch_output))) < 0)
	{
		fprintf(stderr, "read %s error during set_search_ans()\n", search_fname);
		exit(1);
	}

	close(fd);
}

/** 
 * @brief Initiate answer for delete-section 
 * @details Command Makefile to make answer for delete-section, then
 * Store answer variables.
 * @param none
 * @return void
 */

void set_delete_ans(void)
{
	int fd;

	system("make delete");

	if ((fd = open(hsh_fname, O_RDONLY)) < 0) 
	{
		fprintf(stderr, "open %s error during set_delete_ans()\n", hsh_fname);
		exit(1);
	}

	if ((Adelete_size = read(fd, Adelete_content, sizeof(Adelete_content))) < 0)
	{
		fprintf(stderr, "read %s error during set_delete_ans()\n", hsh_fname);
		exit(1);
	}

	close(fd);
}

/** 
 * @brief Initiate answer for rsearch-section 
 * @details Command Makefile to make answer for rsearch-section, then
 * Store answer variables.
 * @param none
 * @return void
 */

void set_rsearch_ans(void)
{
	int fd;
	char cmm[BUFFER_SIZE] = {0};

	sprintf(cmm, "%s > %s", "make rsearch", rsearch_fname);
	system(cmm);

	if ((fd = open(rsearch_fname, O_RDONLY)) < 0) 
	{
		fprintf(stderr, "open %s error during set_rsearch_ans()\n", rsearch_fname);
		exit(1);
	}

	if ((Arsearch_size = read(fd, Arsearch_output, BUFFER_SIZE)) < 0)
	{
		fprintf(stderr, "read %s error during set_rearch_ans()\n", rsearch_fname);
		exit(1);
	}

	close(fd);
}
