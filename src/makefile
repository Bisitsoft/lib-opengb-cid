# Makefile of lib-opengb-cid

CC=gcc

flags= \
	-Wfatal-errors \
	-Wextra \
	-Wshadow \
	-Wsign-compare \
	-Wundef \
	-Wwrite-strings \
	-Wredundant-decls \
	-Wdisabled-optimization \
	-Wdouble-promotion \
	-Wmissing-declarations \
	-finput-charset=UTF-8

target=main.exe

obj=main.o opengbex.o ctzidn.o

all: main.exe

main.exe: main.o opengbex.o ctzidn.o
	$(CC) $(flags) -o $@ $^

main.o: main.c
	$(CC) $(flags) -c $< -o $@
opengbex.o: opengbex.c
	$(CC) $(flags) -c $< -o $@
ctzidn.o: ctzidn.c
	$(CC) $(flags) -c $< -o $@

clean:
	rm $(target) $(obj)

#$(target):$(obj)
#	$(CC) $^ -o $@ $(flags)
#
#%.o:%.c
#	$(CC) -c $< -o $@ $(flags)