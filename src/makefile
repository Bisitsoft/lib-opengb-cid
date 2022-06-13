# Makefile of lib-opengb-cid

CC=gcc

flags= \
	-finput-charset=UTF-8\
#	-Wfatal-errors \
#	-Wextra \
#	-Wshadow \
#	-Wsign-compare \
#	-Wundef \
#	-Wwrite-strings \
#	-Wredundant-decls \
#	-Wdisabled-optimization \
#	-Wdouble-promotion \
#	-Wmissing-declarations \
##	-Wall
# !!! v remain 2 empty line below v !!!


# !!! ^ remain 2 empty line above ^ !!!

all-target=$(test-target) #$(static-target) $(shared-target)
all-obj=$(test-obj) #$(static-obj) $(shared-obj)

test-target=main.exe
test-obj=main.o $(lib-obj)

#tatic-target=lib-opengb-cid.a
#static-obj=$(lib-obj)

#shared-target=lib-opengb-cid.so
#shared-obj=$(lib-obj)

#dymamic-target=lib-opengb-cid.dll
#dymamic-obj=dll.o $(lib-obj)

lib-obj=opengbex.o ctzidn.o

all: $(all-target)

test-program: $(test-target)
#static-library: $(static-target)
#shared-library: $(shared-target)
#dymamic-library: $(dymamic-target)

main.exe: $(test-obj)
	$(CC) $(flags) -o $@ $^
main.o: main.c
	$(CC) $(flags) -c $< -o $@

#lib-opengb-cid.a: $(static-obj)
#	ar rcsv $@ $^
##	ar crv $@ $^

#lib-opengb-cid.so: $(shared-obj)
#	$(CC) -shared $(flags) -o $@ $^

#lib-opengb-cid.dll: $(dymamic-obj)
#	$(MC) -shared $(flags) -o $@ $^

opengbex.o: opengbex.c
	$(CC) $(flags) -c $< -o $@
ctzidn.o: ctzidn.c
	$(CC) $(flags) -c $< -o $@

clean:
	rm $(all-obj) $(all-target)

#$(target):$(obj)
#	$(CC) $^ -o $@ $(flags)
#
#%.o:%.c
#	$(CC) -c $< -o $@ $(flags)