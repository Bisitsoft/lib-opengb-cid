# Makefile of lib-opengb-cid

# >>> Compiler >>>
#   C Compiler:
CC=gcc

#   C Compiler Flags:
flags=\
	-finput-charset=UTF-8\
	-std=c17\
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
all-target=$(static-target) $(shared-target) #$(dymamic-target)
all-obj=$(static-obj) $(shared-obj) #$(dymamic-obj)

static-target=lib-opengb-cid.a
static-obj=$(lib-obj)

shared-target=lib-opengb-cid.so
shared-obj=$(lib-obj)

#dymamic-target=lib-opengb-cid.dll
#dymamic-obj=dll.o $(lib-obj)

lib-obj=opengbex.o ctzidn.o
# <<< Target And Object Files <<<

# >>> Makes >>>
all: $(all-target)

static-library: $(static-target)
shared-library: $(shared-target)
#dymamic-library: $(dymamic-target)
# <<< Makes <<<

# >>> Dependencies >>>

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

# <<< Dependencies <<<

# >>> Clean >>>
clean:
	rm $(all-obj) $(all-target)
# <<< Clean <<<
