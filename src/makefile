# Makefile of lib-opengb-cid

# >>> Compiler >>>
#   C Compiler:
CC=gcc

#	Test Source Code Directory
TEST_SRC=./tests/
#	libcheck Source Code Directory
LIBCHECK_SRC=../3rd-part/check-0.15.2/src/

#   C Compiler Flags:
flags=\
	-finput-charset=UTF-8\
	-std=c17\
	-I "$(LIBCHECK_SRC)" -B "$(LIBCHECK_SRC)../" -I "." -I "$(TEST_SRC)"\
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
# <<< Compiler <<<

# >>> Target And Object Files >>>
all-target=$(test-target) $(demo-target) $(static-target) $(shared-target) #$(dymamic-target)
all-obj=$(test-obj) $(demo-obj) $(static-obj) $(shared-obj) #$(dymamic-obj)

test-target=test.exe
test-obj=test.o $(lib-obj) $(disabled-lib-obj) $(libcheck-obj) $(test-lib-obj)

demo-target=demo.exe
demo-obj=demo.o $(lib-obj)

tatic-target=lib-opengb-cid.a
static-obj=$(lib-obj)

shared-target=lib-opengb-cid.so
shared-obj=$(lib-obj)

libcheck-obj=check.h check_error.o check_list.o check_log.o check_msg.o check_pack.o check_print.o check_run.o check_str.o check.o

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
#	Demo Targets:
demo.exe: $(demo-obj)
	$(CC) $(flags) -o $@ $^
demo.o: $(TEST_SRC)demo.c
	$(CC) $(flags) -c $< -o $@

#   Test Targets:
test.exe: $(test-obj)
	$(CC) $(flags) -o $@ $^
test.o: $(TEST_SRC)test.c
	$(CC) $(flags) -c $< -o $@

#   Libraries Targets:
lib-opengb-cid.a: $(static-obj)
	ar rcsv $@ $^
##	ar crv $@ $^

lib-opengb-cid.so: $(shared-obj)
	$(CC) -shared $(flags) -o $@ $^

#lib-opengb-cid.dll: $(dymamic-obj)
#	$(MSB) -shared $(flags) -o $@ $^

#	Test Objects
ctzidn.test.o: $(TEST_SRC)ctzidn.test.c
	$(CC) $(flags) -c $< -o $@
moretype.test.o: $(TEST_SRC)moretype.test.c
	$(CC) $(flags) -c $< -o $@
opengbex.test.o: $(TEST_SRC)opengbex.test.c
	$(CC) $(flags) -c $< -o $@
utility.test.o: $(TEST_SRC)utility.test.c
	$(CC) $(flags) -c $< -o $@

#   Libraries Objects:
opengbex.o: opengbex.c
	$(CC) $(flags) -c $< -o $@
ctzidn.o: ctzidn.c
	$(CC) $(flags) -c $< -o $@
utility.o: utility.c
	$(CC) $(flags) -c $< -o $@

#	libcheck Objects:
check.h:
	cd "$(LIBCHECK_SRC)../"
	make distclean
	./configure
check_error.o: $(LIBCHECK_SRC)check_error.c
	$(CC) $(flag) -c $< -o $@
check_list.o: $(LIBCHECK_SRC)check_list.c
	$(CC) $(flag) -c $< -o $@
check_log.o: $(LIBCHECK_SRC)check_log.c
	$(CC) $(flag) -c $< -o $@
check_msg.o: $(LIBCHECK_SRC)check_msg.c
	$(CC) $(flag) -c $< -o $@
check_pack.o: $(LIBCHECK_SRC)check_pack.c
	$(CC) $(flag) -c $< -o $@
check_print.o: $(LIBCHECK_SRC)check_print.c
	$(CC) $(flag) -c $< -o $@
check_run.o: $(LIBCHECK_SRC)check_run.c
	$(CC) $(flag) -c $< -o $@
check_str.o: $(LIBCHECK_SRC)check_str.c
	$(CC) $(flag) -c $< -o $@
check.o: $(LIBCHECK_SRC)check.c
	$(CC) $(flag) -c $< -o $@
# <<< Dependencies <<<

# >>> Clean >>>
clean:
	rm $(all-obj) $(all-target)
# <<< Clean <<<
