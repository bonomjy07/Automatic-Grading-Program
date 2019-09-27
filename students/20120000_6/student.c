#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "student.h"

//
// 학생 레코드 파일로부터  레코드 번호에 해당하는 레코드를 읽어 레코드 버퍼에
// 저장한다.
//
void readStudentRec(FILE *fp, char *recordbuf, int rn)
{
  fseek(fp, STUDENT_RECORD_SIZE * rn, SEEK_SET);
  fread(recordbuf, STUDENT_RECORD_SIZE, 1, fp);
}

//
// Hash file로부터 rn의 레코드 번호에 해당하는 레코드를 읽어 레코드 버퍼에
// 저장한다.
//
void readHashRec(FILE *fp, char *recordbuf, int rn)
{
  fseek(fp, HASH_RECORD_SIZE * rn + 4, SEEK_SET);
  fread(recordbuf, HASH_RECORD_SIZE, 1, fp);
}

//
// Hash file에 rn의 레코드 번호에 해당하는 위치에 레코드 버퍼의 레코드를
// 저장한다.
//
void writeHashRec(FILE *fp, const char *recordbuf, int rn)
{
  fseek(fp, HASH_RECORD_SIZE * rn + 4, SEEK_SET);
  fwrite(recordbuf, HASH_RECORD_SIZE, 1, fp);
}

//
// n의 크기를 갖는 hash file에서 주어진 학번 키값을 hashing하여 주소값(레코드
// 번호)를 리턴한다.
//
int hashFunction(const char *sid, int n)
{
  int len = strlen(sid);
  return sid[len - 2] * sid[len - 1] % n;
}

//
// n의 크기를 갖는 hash file을 생성한다.
// Hash file은 fixed length record 방식으로 저장되며, 레코드의 크기는 14
// 바이트이다. (student.h 참조)
//
void makeHashfile(int n)
{
  FILE *fp_hash = fopen(HASH_FILE_NAME, "wb+");
  int32_t table_size = n;
  fwrite(&table_size, sizeof(int32_t), 1, fp_hash);
  for (int i = 0; i < n * HASH_RECORD_SIZE; ++i) {
    fwrite("\0", 1, 1, fp_hash);
  }

  FILE *fp = fopen(RECORD_FILE_NAME, "rb");
  char id[SID_FIELD_SIZE + 1];
  memset(id, 0, SID_FIELD_SIZE + 1);
  STUDENT record;
  int32_t index = 0;
  while (fread(&record, STUDENT_RECORD_SIZE, 1, fp) > 0) {
    memcpy(id, record.id, SID_FIELD_SIZE);
    int hash = hashFunction(id, n);
    for (int i = 0; i < n; ++i) {
      char buf[HASH_RECORD_SIZE];
      readHashRec(fp_hash, buf, (hash + i) % n);
      if (buf[0] == '\0') {
        memcpy(buf, id, SID_FIELD_SIZE);
        memcpy(buf + SID_FIELD_SIZE, &index, sizeof(int32_t));
        writeHashRec(fp_hash, buf, (hash + i) % n);
        break;
      }
    }
    ++index;
  }

  fclose(fp_hash);
}

//
// 주어진 학번 키값을 hash file에서 검색한다.
// 그 결과는 주어진 학번 키값이 존재하는 hash file에서의 주소(레코드 번호)와
// search length이다. 검색한 hash file에서의 주소는 rn에 저장하며, 이때 hash
// file에 주어진 학번 키값이 존재하지 않으면 rn에 -1을 저장한다. (search()는
// delete()에서도 활용할 수 있음) search length는 함수의 리턴값이며, 검색 결과에
// 상관없이 search length는 항상 계산되어야 한다.
//
int search(const char *sid, int *rn)
{
  FILE *fp_hash = fopen(HASH_FILE_NAME, "rb");
  int32_t n;
  fread(&n, sizeof(int32_t), 1, fp_hash);
  int32_t i;
  for (i = 0; i < n; ++i) {
    char buf[HASH_RECORD_SIZE];
    *rn = hashFunction(sid, n);
    readHashRec(fp_hash, buf, (*rn + i) % n);
    if (buf[0] == '\0')
      break;
    if (strncmp(buf, sid, SID_FIELD_SIZE) == 0) {
      *rn = (*rn + i) % n;
      fclose(fp_hash);
      return i + 1;
    }
  }
  *rn = -1;
  fclose(fp_hash);
  return (i + 1 < n) ? i + 1 : n;
}

//
// Hash file에서 주어진 학번 키값과 일치하는 레코드를 찾은 후 해당 레코드를 삭제
// 처리한다. 이때 학생 레코드 파일에서 레코드 삭제는 필요하지 않다.
//
void delete (const char *sid)
{
  int32_t rn;
  search(sid, &rn);
  if (rn == -1)
    return;
  FILE *fp_hash = fopen(HASH_FILE_NAME, "rb+");
  fseek(fp_hash, rn * HASH_RECORD_SIZE + 4, SEEK_SET);
  fwrite("*", 1, 1, fp_hash);
  fclose(fp_hash);
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
  while (1);
  // 학생레코드파일은 student.h에 정의되어 있는 STUDENT_FILE_NAME을,
  // hash file은 HASH_FILE_NAME을 사용한다.

  // 검색 기능을 수행할 때 출력은 반드시 주어진 printSearchResult() 함수를
  // 사용한다.

  if (argc == 3 && strcmp(argv[1], "-c") == 0) {
    makeHashfile(atoi(argv[2]));
  }
  else if (argc == 3 && strcmp(argv[1], "-s") == 0) {
    int32_t rn, sl;
    sl = search(argv[2], &rn);
    printSearchResult(rn, sl);
  }
  else if (argc == 3 && strcmp(argv[1], "-d") == 0) {
    delete (argv[2]);
  }
  else {
    fprintf(stderr, "ERROR: input error\n");
  }
  return 0;
}
