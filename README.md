# Automatic-Grading-Program
Grade student's file automatically 

Documents made by doxygen
---------------------------------------------------------------------------------------------------------------------------------
Want to see Document ?
1. Unzip html.zip
2. Run index.html


Screenshots
---------------------------------------------------------------------------------------------------------------------------------
![pic1](https://user-images.githubusercontent.com/49272857/65776186-8e3bf880-e17c-11e9-9531-760d3d2f0b9d.png)
![pic2](https://user-images.githubusercontent.com/49272857/65776185-8e3bf880-e17c-11e9-9696-9fb3f15e9d7b.png)


What student's program does ?
---------------------------------------------------------------------------------------------------------------------------------
Main job is to create hash file("student.hsh") with progressive overflow using "studenet.dat" file that store records And
Print search number for record.

<img width="180" alt="해시데이트" src="https://user-images.githubusercontent.com/49272857/65853545-d7669500-e394-11e9-8f28-1a7aa9290215.png">  <img width="131" alt="해시함수" src="https://user-images.githubusercontent.com/49272857/65853579-ee0cec00-e394-11e9-9866-86aa6ff2f234.png">   <img width="228" alt="해시파일" src="https://user-images.githubusercontent.com/49272857/65853562-e1889380-e394-11e9-9b56-03bd4179b9c8.png">

1. Create hash file(student.hsh) by using student.dat that store some record.
2. Print "adrress of record" in hash file and "search length" needed to find record in hash file.
<img width="428" alt="스크린샷 2019-09-30 오후 4 20 26" src="https://user-images.githubusercontent.com/49272857/65857283-7b087300-e39e-11e9-89e0-4c169eeaf6d8.png">
3. Set deleted marker in hash file(student.hsh) for records to be removed.
4. After deletion, Do same thing as #2
   (Print Print "adrress of record" in hash file and "search length" needed to find record in hash file).

How it works
---------------------------------------------------------------------------------------------------------------------------------
Purpose is to explore every students's directory and Grading their score one by one.

Here is brief how grading program work.
1. Compile & run answer/* files to get answer files.
2. Change current working directory to student's directory.
3. Compile and run student's file by using Makefile.
4. Compare answer files with files student made.
5. Write result to .csv file.
6. Back to current working directory, then Go to #2 untill program explores all of students.


Usage
---------------------------------------------------------------------------------------------------------------------------------
1. Compile src/* files with Makefile.
2. Put "grading.exe, answer directory and directories in studens directory" In same directory.
3. Command ./grade
