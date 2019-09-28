# Automatic-Grading-Program
Grade student's file automatically 

Documents by doxygen
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
1. Create hash file(student.hsh) by referecing student.dat that store some record.
2. Print search length for certain records.
3. Set deleted marker in hash file(student.hsh) for records to be removed.
4. After deletion, Print search length for certain records.

How it works
---------------------------------------------------------------------------------------------------------------------------------
Purpose is to explore every students's directory and then Grading their score one by one.

Here is brief how grading program work.
1. Compile & run answer/* files to get answer files.
2. Change current working directory to student's directory.
3. Compile and run student's file with Makefile.
4. Compare answer files with files student made.
5. Write result to .csv file.
6. Back to current working directory, then Go to #2 untill program explores all of students.


Usage
---------------------------------------------------------------------------------------------------------------------------------
1. Compile src/* files with Makefile.
2. Put "grading.exe, answer directory and directories in studens directory" In same directory.
3. Command ./grade
