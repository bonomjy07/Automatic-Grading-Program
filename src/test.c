#include "test.h"
#include "color.h"
#include "answer.h"

/**
 * @file test.c
 * @brief Collection of method to compare answer file to student file.
 * @details Methods compare answer file to student file and return score.
 * */

extern ssize_t Acreate_size;
extern ssize_t Asearch_size;
extern ssize_t Adelete_size;
extern ssize_t Asearch_size;
extern ssize_t Arsearch_size;
extern char Acreate_content[BUFFER_SIZE];
extern char Asearch_output[BUFFER_SIZE];
extern char Adelete_content[BUFFER_SIZE];
extern char Arsearch_output[BUFFER_SIZE];

extern const char *hsh_fname;
extern const char *search_fname;
extern const char *rsearch_fname;

void pp(char *buf)
{
	printf("-------------------------\n");
	for (int i = 0; i < 4; i++)
		printf("%2x ", buf[i]);
	printf("\n");
	for (int i = 4; i < 140; i++) {
		printf("%2x ", buf[i]);
		if (i % 10 - 3 == 0) 
			printf("\n");
	}
	printf("\n");
}

/** 
 * @brief Test compile sector.
 * @details Compile student's file and Grade compile sector. 
 * @param none
 * @return Retunr Integer score
 */
int test_compile(void)
{   
	const char* make_cmm = "make a.out";
	int score = 0;

	yellow("####### Compile Test Start! #######\n");

	if (system(make_cmm) == 0)
	{   
		score = 20;
		green("Compile Succeed!\n");
	}
	else
	{   
		score = 0;
		red("Compile Failed!\n");
	}

	yellow("####### Compile Test End! #######\n");
	return score;
}

/** 
 * @brief Test create sector.
 * @details 
 * 1. Read "student.hsh" file student created
 * 2. Compare answer file to student file
 * 3. Return score result 
 * @param none
 * @return Retunr Integer score
 * */

int test_create(void)
{
	int fd;
	ssize_t create_size;
	int score = 0;
	char create_content[BUFFER_SIZE] = {0};

	yellow("#########Create Test Start!#########\n");

	// Get create result : "student.hsh" file
	if ((fd = open(hsh_fname, O_RDONLY)) < 0)
	{
		fprintf(stderr, "open %s error\n", hsh_fname); 
		return 0;
	}

	create_size = read(fd, create_content, BUFFER_SIZE);

	// Compare file size
	if (create_size == Acreate_size)
	{
		score += 10;
		green("<File size is correct!>\n");
	}
	else if (create_size < Acreate_size)
	{
		printf("Answer  size : %zd\n", Acreate_size);
		printf("Student size : %zd\n", create_size);
		red("<File size is less than expected size...>\n");
		return 0;
	}

	// Compare file contents
	if (memcmp(create_content, Acreate_content, Acreate_size) == 0)
	{
		score += 10;
		green("<File content is correct!>\n");
	}
	else
	{
		pp(create_content);
		pp(Acreate_content);
		red("<File content is wrong..>\n");
	}

	yellow("#########Create Test Finished!#########\n\n");

	close(fd);
	return score;
}

/** 
 * @brief Test search sector.
 * @details 
 * 1. Read "output.txt" file student made
 * 2. Compare answer file to student file
 * 3. Return score result 
 * @param none
 * @return Retunr Integer score
 * */

int test_search(void) 
{
	int fd;
	char search_output[BUFFER_SIZE] = {0};
	ssize_t search_size;
	int score = 0;

	yellow("#########Search Test Start!#########\n");

	// Get test result file
	if ((fd = open(search_fname, O_RDONLY)) < 0)
	{
		fprintf(stderr, "open %s error\n", search_fname);
		return 0;
		//exit(1);
	}

	// Read test result file
	search_size = read(fd, search_output, sizeof(search_output));

	// Test 2-1 : search records that don't exist in student.dat
	if (search_size != Asearch_size)
	{
		red("<Search failed : output.txt size is diff\n");
		return 0;
	}

	//...
	if (memcmp(search_output, Asearch_output, Asearch_size) == 0)
	{
		score = 20;

		green("<Search suceed!>\n");
	}
	else
	{
		printf("Search ans :\n%s\n", Asearch_output);
		printf("Search stu :\n%s\n", search_output);
		red("<Search failed : print_result is wrong..>\n");
	}

	yellow("#########Search Test Finished!#########\n\n");

	close(fd);
	return score;
}

/** 
 * @brief Test delete sector.
 * @details 
 * 1. Read "student.hsh" file student made after deleted some record in .hsh file.
 * 2. Compare answer file to student file.
 * 3. Return score result.
 * @param none
 * @return Retunr Integer score
 * */

int test_delete(void)
{
	int fd;
	int delete_size;
	char delete_content[BUFFER_SIZE] = {0};
	int score = 0;

	yellow("#########Delete Test Start!#########\n");

	// Get test result file
	if ((fd = open("student.hsh", O_RDONLY)) < 0)
	{
		fprintf(stderr, "can't file student.hsh\n");
		return 0;
	}

	// Read test result file
	delete_size = read(fd, delete_content, BUFFER_SIZE);

	/* Compare Answer to search result */
	if (delete_size != Adelete_size) 
	{
		red("<Delete failed : file size is wrong..\n");
		return 0;
	}

	// Compare
	if (memcmp(delete_content, Adelete_content, Adelete_size) == 0)
	{
		score = 20;
		green("<Delete suceed!>\n");
	}
	else
	{
		pp(delete_content); pp(Adelete_content);
		red("<Delete failed : file contents is wrong....>\n");
	}

	yellow("#########Delete Test Finished!#########\n\n");

	close(fd);
	return score;
}

/** 
 * @brief Test re-search sector.
 * @details 
 * This sector is for searching after deleted some record in "student.hsh" file.
 * 1. Read "output.txt" file student made
 * 2. Compare answer file to student file
 * 3. Return score result 
 * @param none
 * @return Retunr Integer score
 * */

int test_rsearch(void)
{
	int fd;
	ssize_t rsearch_size;
	char rsearch_output[BUFFER_SIZE] = {0};
	int score = 0;

	yellow("#########Re_Search Test Start!#########\n");

	if ((fd = open(rsearch_fname, O_RDONLY)) < 0)
	{
		fprintf(stderr, "open %s error\n", rsearch_fname);
		return 0;
		//exit(1);
	}

	rsearch_size = read(fd, rsearch_output, BUFFER_SIZE);

	// Compare output.txt size
	if (rsearch_size != Arsearch_size)
	{
		red("<Rsearch failed : file size is wrong>\n");
		printf("%zd %zd\n", rsearch_size, Arsearch_size);
		return 0;
	}

	// Compare output.txt
	if (memcmp(rsearch_output, Arsearch_output, Arsearch_size) == 0)
	{
		score = 20;
		green("<Rsearch suceed!>\n");
	}
	else
	{
		red("<Rsearch failed : output is wrong>\n");
		printf("Rsearch ans :\n%s\n", Arsearch_output);
		printf("Rsearch stu :\n%s\n", rsearch_output);
	}

	yellow("#########Re_Search Test End!#########\n");

	close(fd);
	return score;
}
