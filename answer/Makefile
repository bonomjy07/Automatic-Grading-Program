
# compile student.c
a.out : student.c
	gcc student.c

# create hashfile with nsize=10
create:
	./a.out -c 10

# search records that don't exist in student.dat
search:
	./a.out -s 9999999936
	./a.out -s 9999999939
	./a.out -s 9999999930
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
delete:
	./a.out -d 0000000034
	./a.out -d 0000000085

# search all records that exist in student.dat after deletion
rsearch:
	./a.out -s 0000000046
	./a.out -s 0000000033
	./a.out -s 0000000034
	./a.out -s 0000000084
	./a.out -s 0000000029
	./a.out -s 0000000037
	./a.out -s 0000000073
	./a.out -s 0000000058
	./a.out -s 0000000085

clean:
	rm a.out student.hsh
	rm search_output.txt
	rm rsearch_output.txt
