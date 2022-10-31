# Makefile of lib-opengb-cid

# >>> Compiler >>>
#   C Compiler:
CC=gcc

#   C Compiler Flags:
flags=\
	-finput-charset=UTF-8\
	-std=c17\
	-I "../3rd-part/check-0.15.2/src" -I "." -I "./tests"\
#	-v\
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
#   !!! v remain 2 empty line below v !!!


#   !!! ^ remain 2 empty line above ^ !!!

#	Test Source Code Directory
TD=test/
# <<< Compiler <<<

# >>> Target And Object Files >>>
all-target=$(test-target) $(static-target) $(shared-target) #$(dymamic-target)
all-obj=$(test-obj) $(static-obj) $(shared-obj) #$(dymamic-obj)

test-target=test.exe
test-obj=test.o $(lib-obj) $(disabled-lib-obj) $(test-lib-obj)

demo-target=demo.exe
demo-obj=demo.o $(lib-obj)

tatic-target=lib-opengb-cid.a
static-obj=$(lib-obj)

shared-target=lib-opengb-cid.so
shared-obj=$(lib-obj)

#dymamic-target=lib-opengb-cid.dll
#dymamic-obj=dll.o $(lib-obj)

test-lib-obj=ctzidn.test.o moretype.test.o opengbex.test.o utility.test.o
lib-obj=opengbex.o ctzidn.o
disabled-lib-obj=utility.o
# <<< Target And Object Files <<<

# >>> Makes >>>
#all: $(all-target)

demo: $(demo-target)
test: $(test-target)
static-library: $(static-target)
shared-library: $(shared-target)
#dymamic-library: $(dymamic-target)
# <<< Makes <<<

# >>> Dependencies >>>
#	Demo Program:
demo.exe: $(demo-obj)
	$(CC) $(flags) -o $@ $^
demo_main.o: $(TD)demo.c
	$(CC) $(flags) -c $< -o $@

#   Test Program:
test.exe: $(test-obj)
	$(CC) $(flags) -o $@ $^
test_main.o: $(TD)test.c
	$(CC) $(flags) -c $< -o $@

ctzidn.test.o: $(TD)ctzidn.test.c
	$(CC) $(flags) -c $< -o $@
moretype.test.o: $(TD)moretype.test.c
	$(CC) $(flags) -c $< -o $@
opengbex.test.o: $(TD)opengbex.test.c
	$(CC) $(flags) -c $< -o $@
utility.test.o: $(TD)utility.test.c
	$(CC) $(flags) -c $< -o $@

#   Libraries Targets:
lib-opengb-cid.a: $(static-obj)
	ar rcsv $@ $^
##	ar crv $@ $^

lib-opengb-cid.so: $(shared-obj)
	$(CC) -shared $(flags) -o $@ $^

#lib-opengb-cid.dll: $(dymamic-obj)
#	$(MSB) -shared $(flags) -o $@ $^

#   Libraries Objects:
opengbex.o: opengbex.c
	$(CC) $(flags) -c $< -o $@
ctzidn.o: ctzidn.c
	$(CC) $(flags) -c $< -o $@
utility.o: utility.c
	$(CC) $(flags) -c $< -o $@
# <<< Dependencies <<<

# >>> Clean >>>
clean:
	rm $(all-obj) $(all-target)
# <<< Clean <<<
