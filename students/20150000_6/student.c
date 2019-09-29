#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "student.h"

//
// 학생 레코드 파일로부터  레코드 번호에 해당하는 레코드를 읽어 레코드 버퍼에 저장한다.
//
void readStudentRec(FILE *fp, char *recordbuf, int rn)
{
    fseek(fp,rn*STUDENT_RECORD_SIZE,SEEK_SET);
    fread(recordbuf,STUDENT_RECORD_SIZE,1,fp);
}

//
// Hash file로부터 rn의 레코드 번호에 해당하는 레코드를 읽어 레코드 버퍼에 저장한다.
//
void readHashRec(FILE *fp, char *recordbuf, int rn)
{
    fseek(fp,rn*HASH_RECORD_SIZE+4,SEEK_SET);
    fread(recordbuf,HASH_RECORD_SIZE,1,fp);
}
//
// Hash file에 rn의 레코드 번호에 해당하는 위치에 레코드 버퍼의 레코드를 저장한다.
//
void writeHashRec(FILE *fp, const char *recordbuf, int rn)
{
    fseek(fp,rn*HASH_RECORD_SIZE+4,SEEK_SET);
    fwrite(recordbuf,HASH_RECORD_SIZE,1,fp);
}

//
// n의 크기를 갖는 hash file에서 주어진 학번 키값을 hashing하여 주소값(레코드 번호)를 리턴한다.
//
int hashFunction(const char *sid, int n)
{
    int size = strlen(sid);
    return ((int)sid[size-1] * (int)sid[size-2])%n;
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
    FILE * sfp = fopen(RECORD_FILE_NAME,"r+b");
    FILE * hfp = fopen(HASH_FILE_NAME,"r+b");
    
    int rn = -1;
    int hash_addr;
    char a = '\0';
    if(hfp == NULL)
    {
        hfp = fopen(HASH_FILE_NAME,"w+b");
        hfp = fopen(HASH_FILE_NAME,"r+b");
    }

    fwrite(&n,4,1,hfp);
    for(int i = 0 ;i<n*HASH_RECORD_SIZE;i++)
        fwrite(&a,1,1,hfp);

    while(1)
    {
        char * hashRec = (char*)malloc(HASH_RECORD_SIZE);
    	char * studentRec = (char*)malloc(STUDENT_RECORD_SIZE);
        STUDENT * s = (STUDENT*)malloc(sizeof(STUDENT));

        fread(studentRec,STUDENT_RECORD_SIZE,1,sfp);

        rn++;
        for(int i = 0 ;i<10;i++)
            s->id[i] = studentRec[i];
        for(int i = 0;i<20;i++)
            s->name[i] = studentRec[i+10];
        for(int i = 0;i<30;i++)
            s->addr[i] = studentRec[i+30];
        s->year[0] = studentRec[60];
    	for(int i = 0;i<19;i++)
            s->dept[i] = studentRec[i+61];
	    for(int i = 0;i<15;i++)
            s->addr[i] = studentRec[i+80];
	    for(int i = 0;i<25;i++)
            s->addr[i] = studentRec[i+95];

        hash_addr = hashFunction(s->id,n);

        for(int i = 0;i<n;i++)
        {
            if(hash_addr >= n)
                hash_addr %= n;
            readHashRec(hfp,hashRec,hash_addr);
            if(hashRec[0] != '\0')
                hash_addr++;
            else
            {
                for(int j = 0;j<10;j++)
                    hashRec[j] = s->id[j];
                char a[4];
                memcpy(a,&rn,sizeof(int));
                for(int j = 0;j<4;j++)
                    hashRec[j+10] = a[j];

                writeHashRec(hfp,hashRec,hash_addr);
                break;
            }
        }
        free(hashRec);
        free(studentRec);
        free(s);
        getc(sfp);
        getc(sfp);
        if(feof(sfp))
            break;
        fseek(sfp,-2,SEEK_CUR);
    }
    fclose(hfp);
    fclose(sfp);
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
    FILE * fp = fopen(HASH_FILE_NAME,"r+b");

    int size;
    int sl = 0;
    int a;
    fread(&size,4,1,fp);
    int hash_result = hashFunction(sid,size);
    int start = hash_result;

    fseek(fp,hash_result*HASH_RECORD_SIZE+4,SEEK_SET);
    while(1)
    {
        char * buf = (char*)malloc(HASH_RECORD_SIZE);
        readHashRec(fp,buf,hash_result);
        sl++;
        if(buf[0] == '*')
        {
            free(buf);
            hash_result++;
            continue;
        }
        if(buf[0] == '\0')
        {
            fclose(fp);
            *rn = -1;
            return sl;
        }
        if(!strncmp(buf,sid,strlen(sid)))
        {
            fseek(fp,hash_result*HASH_RECORD_SIZE+SID_FIELD_SIZE+4,SEEK_SET);
            fread(&a,4,1,fp);
            *rn = hash_result;
            fclose(fp);
            return sl;
        }

        if((hash_result+1)%size == start){
            fclose(fp);
            *rn = -1;
            return sl;
        }
        hash_result++;
        free(buf);
    }
    fclose(fp);

}

//
// Hash file에서 주어진 학번 키값과 일치하는 레코드를 찾은 후 해당 레코드를 삭제 처리한다.
// 이때 학생 레코드 파일에서 레코드 삭제는 필요하지 않다.
//
void delete(const char *sid)
{
    FILE * fp = fopen(HASH_FILE_NAME,"r+b");

    int rn;
    int sl = search(sid,&rn);
    char a = '*';

    if(rn == -1)
        return;

    fseek(fp,rn*(HASH_RECORD_SIZE)+sl+3,SEEK_SET);
    fwrite(&a,1,1,fp);
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
    if(!strcmp(argv[1],"-c"))
        makeHashfile(atoi(argv[2]));
    else if(!strcmp(argv[1],"-s"))
    {
        int sl;
        int rn;
        sl = search(argv[2],&rn);
//        printf("%d %d %d",rn,&rn,*rn);
        printSearchResult(rn,sl);
    }
    else if(!strcmp(argv[1],"-d"))
        delete(argv[2]);

    return 0;
}

