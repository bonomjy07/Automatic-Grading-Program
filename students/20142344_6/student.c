#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include "student.h"

void readStudentRec(FILE *fp, char *recordbuf, int rn)
{
}

void readHashRec(FILE *fp, char *recordbuf, int rn)
{
}

void writeHashRec(FILE *fp, const char *recordbuf, int rn)
{
}

//
// n의 크기를 갖는 hash file에서 주어진 학번 키값을 hashing하여 주소값(레코드 번호)를 리턴한다.
//
int hashFunction(const char *sid, int n)
{
	int home_addr;
	int len = strlen(sid); 

	/* Home = (A * B) % N-size  */
	home_addr = (sid[len - 1] * sid[len - 2]) % n;

	return home_addr;
}

//
// n의 크기를 갖는 hash file을 생성한다.
// Hash file은 fixed length record 방식으로 저장되며, 레코드의 크기는 14 바이트이다.
// (student.h 참조)
//
void makeHashfile(int n)
{
	// Hash file을 생성할 때 이 파일의 맨앞부분에 4바이트 헤더를 둔다. 
	// 여기에는 hash file의 크기 n을 저장한다. 이것은 search()와 (필요하면) delete()를 	// 위한 것이다.
	int hfd, dfd;
	int home_addr, actual_addr;
	int rn = 0;
	char hsh_record[HASH_RECORD_SIZE + 1] = {0};
	char dummy[HASH_RECORD_SIZE + 1] = {0};
	char sid[SID_FIELD_SIZE + 1] = {0};
	char recordbuf[STUDENT_RECORD_SIZE + 1] = {0};

	/* Create Hash File */
	if ((hfd = open(HASH_FILE_NAME, O_RDWR | O_CREAT | O_TRUNC, 0644)) < 0)
	{
		fprintf(stderr, "create error :<%s>\n", HASH_FILE_NAME);
		exit(1);
	}

	/* Open student.dat */
	if ((dfd = open(RECORD_FILE_NAME, O_RDONLY, 0644)) < 0)
	{
		fprintf(stderr, "create error :<%s>\n", RECORD_FILE_NAME);
		exit(1);
	}

	/* Write Header */
	if (write(hfd, &n, sizeof(int)) != sizeof(int))
	{
		fprintf(stderr, "write header error\n");
		exit(1);
	}

	/* Read student.dat */
	while (read(dfd, recordbuf, STUDENT_RECORD_SIZE) > 0)
	{
		memset(sid, 0, SID_FIELD_SIZE);

		/* Get studnet id */
		memcpy(sid, recordbuf, SID_FIELD_SIZE);

		/* Get Home address */
		home_addr = hashFunction(sid, n);
		actual_addr = home_addr;

		/* Find empty place */
		while (1)
		{
			memset(hsh_record, 0, HASH_RECORD_SIZE);

			// Search hash file
			lseek(hfd, 4 + (actual_addr * HASH_RECORD_SIZE), SEEK_SET);
			read(hfd, hsh_record, HASH_RECORD_SIZE);

			// Case : empty
			if (memcmp(hsh_record, dummy, HASH_RECORD_SIZE) == 0)
			{
				break;
			}

			// Wrapping actual_address by n-size
			(actual_addr + 1 >= n) ? (actual_addr = 0) : (actual_addr++);
		}

		/* Set hash_record */
		memcpy(hsh_record, sid, SID_FIELD_SIZE);
		memcpy(hsh_record + SID_FIELD_SIZE, &rn, sizeof(int));

		// Write hash record  
		lseek(hfd, 4 + (actual_addr * HASH_RECORD_SIZE), SEEK_SET);
		write(hfd, hsh_record, HASH_RECORD_SIZE);

		rn++;
	}

	close(hfd);
	close(dfd);
}

//
// 주어진 학번 키값을 hash file에서 검색한다.
// 그 결과는 주어진 학번 키값이 존재하는 hash file에서의 주소(레코드 번호)와 search length이다.
// 검색한 hash file에서의 주소는 rn에 저장하며, 이때 hash file에 주어진 학번 키값이
// 존재하지 않으면 rn에 -1을 저장한다. (search()는 delete()에서도 활용할 수 있음)
// search length는 함수의 리턴값이며, 검색 결과에 상관없이 search length는 항상 계산되어야 한다.
//
int search(const char *sid, int *rn)
{
	int fd;
	int sl = 0;
	int home_addr, actual_addr; 
	int hsize;
	char hash_record[HASH_RECORD_SIZE + 1] = {0};
	char buf[sizeof(int) + 1] = {0};
	char dummy[HASH_RECORD_SIZE + 1] = {0};

	/* Open student.hsh */
	if ((fd = open(HASH_FILE_NAME, O_RDONLY)) < 0) 
	{
		fprintf(stderr, "open error :%s\n", HASH_FILE_NAME);
		exit(1);
	}

	/* Get hash table size */
	read(fd, buf, sizeof(int));
	memcpy(&hsize, buf, sizeof(int));

	/* Get Home addres */
	home_addr = hashFunction(sid, hsize);
	actual_addr = home_addr;

	/* Get hash record */
	while (1)
	{
		memset(hash_record, 0, HASH_RECORD_SIZE);
		sl++;

		/* Get Hash record */
		lseek(fd, 4 + (actual_addr * HASH_RECORD_SIZE), SEEK_SET);
		read(fd, hash_record, HASH_RECORD_SIZE); 

		/* Same sid */
		if (memcmp(sid, hash_record, SID_FIELD_SIZE) == 0)
		{
			*rn = actual_addr;
			break;
		}

		/* NULL */
		if (memcmp(dummy, hash_record, HASH_RECORD_SIZE) == 0)
		{
			*rn = -1;
			break;
		}

		/* Can't find */
		if (sl >= hsize)
		{
			*rn = -1;
			break;
		}

		/* Ready to ready next hash record */
		(actual_addr + 1 >= hsize) ? (actual_addr = 0) : (actual_addr++);
	}

	close(fd);
	return sl;
}

//
// Hash file에서 주어진 학번 키값과 일치하는 레코드를 찾은 후 해당 레코드를 삭제 처리한다.
// 이때 학생 레코드 파일에서 레코드 삭제는 필요하지 않다.
//
void delete(const char *sid)
{
	int fd;
	int hsize;
	int rn;
	int home_addr, actual_addr;
	int sl; 
	char hash_buf[HASH_RECORD_SIZE + 1] = {0};
	char buf[sizeof(int) + 1] = {0};

	sl = search(sid, &rn);

	/* Can't find */
	if (rn == -1)
		return;

	// Open student.hsh
	if ((fd = open(HASH_FILE_NAME, O_RDWR)) < 0)
	{
		fprintf(stderr, "open error :%s\n", HASH_FILE_NAME);
		exit(1);
	}

	// Get header
	read(fd, buf, sizeof(int));
	memcpy(&hsize, buf, sizeof(int));

	// Get home_addr address 
	home_addr = hashFunction(sid, hsize);
	actual_addr = (home_addr + sl - 1) % hsize;

	// Write hash record 
	lseek(fd, 4 + (actual_addr * HASH_RECORD_SIZE), SEEK_SET);
	write(fd, "*", 1);
}

//
// rn은 hash file에서의 레코드 번호를, sl은 search length를 의미한다.
//
void printSearchResult(int rn, int sl)
{
	printf("%d %d\n", rn, sl);
}

int main(int argc, char *argv[])
{
	// 학생레코드파일은 student.h에 정의되어 있는 STUDENT_FILE_NAME을, 
	// hash file은 HASH_FILE_NAME을 사용한다.

	// 검색 기능을 수행할 때 출력은 반드시 주어진 printSearchResult() 함수를 사용한다.

	int flag_c = 0, flag_s = 0, flag_d = 0, c;
	int hash_size;
	char sid[SID_FIELD_SIZE + 1] = {0};
	int rn, sl;

	/* Check argument */
	if (argc != 3)
	{
		fprintf(stderr, "usage : ./a.out -c     \"size\"\n");
		fprintf(stderr, "usage : ./a.out -[s|d] \"sid\"\n");
		exit(1);
	}

	/* Get option */
	while ((c = getopt(argc, argv, "csd")) != -1) 
	{
		switch (c) 
		{
			case 'c':
				flag_c = 1;
				hash_size = atoi(argv[2]);
				break;
			case 's':
				flag_s = 1;
				memcpy(sid, argv[2], strlen(argv[2]));
				break;
			case 'd':
				flag_d = 1;
				memcpy(sid, argv[2], strlen(argv[2]));
				break;
			case '?':
				printf("Unknown flag :\n");
				break;
		}
	}

	/* Execute proper option */
	if (flag_c)
	{
		makeHashfile(hash_size);
	}
	else if (flag_s)
	{
		sl = search(sid, &rn);
		printSearchResult(rn, sl);
	}
	else if (flag_d)
	{
		delete(sid);
	}

	exit(0);
}
