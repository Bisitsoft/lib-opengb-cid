# Makefile of lib-opengb-cid

# >>> Compiler >>>
#   C Compiler:
CC=gcc

#   C Compiler Flags:
flags=\
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
#   !!! v remain 2 empty line below v !!!


#   !!! ^ remain 2 empty line above ^ !!!
# <<< Compiler <<<

# >>> Target And Object Files >>>
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

lib-obj=opengbex.o ctzidn.o utility.o
# <<< Target And Object Files <<<

# >>> Makes >>>
all: $(all-target)

test-program: $(test-target)
#static-library: $(static-target)
#shared-library: $(shared-target)
#dymamic-library: $(dymamic-target)
# <<< Makes <<<

# >>> Dependencies >>>
#   Test Program:
main.exe: $(test-obj)
	$(CC) $(flags) -o $@ $^
main.o: main.c
	$(CC) $(flags) -c $< -o $@

#   Libraries Targets:
#lib-opengb-cid.a: $(static-obj)
#	ar rcsv $@ $^
##	ar crv $@ $^

#lib-opengb-cid.so: $(shared-obj)
#	$(CC) -shared $(flags) -o $@ $^

#lib-opengb-cid.dll: $(dymamic-obj)
#	$(MC) -shared $(flags) -o $@ $^

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
