# Automatic-Grading-Program
Grade student's file automatically 


Want to see Document ?
1. Unzip html.zip
2. Run index.html


Screenshots
---------------------------------------------------------------------------------------------------------------------------------


What student file do ?
---------------------------------------------------------------------------------------------------------------------------------


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
