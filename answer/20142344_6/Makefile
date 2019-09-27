
# compile student.c
a.out : student.c
	gcc student.c

# create hashfile with nsize=10
1:
	./a.out -c 10

# search records that don't exist in student.dat
2-1:
	./a.out -s 9999999936
	./a.out -s 9999999939
	./a.out -s 9999999930

# search all records that exist in student.dat before deletion
2-2:
	./a.out -s 0000000046
	./a.out -s 0000000033
	./a.out -s 0000000034
	./a.out -s 0000000084
	./a.out -s 0000000029
	./a.out -s 0000000037
	./a.out -s 0000000073
	./a.out -s 0000000058
	./a.out -s 0000000085

# delete 
3:
	./a.out -d 0000000034
	./a.out -d 0000000085

# search all records that exist in student.dat after deletion
4:
	./a.out -s 0000000046
	./a.out -s 0000000033
	./a.out -s 0000000034
	./a.out -s 0000000084
	./a.out -s 0000000029
	./a.out -s 0000000037
	./a.out -s 0000000073
	./a.out -s 0000000058
	./a.out -s 0000000085
