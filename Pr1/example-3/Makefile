# Усложненный make-file.  Введены переменные для параметров компиляции и исполняемых файлов

.PHONY: all debug release clean

target = Kazino-Royal.cpp

RELEASE_FLAGS = -O2 -Wall -DNDEBUG
DEBUG_FLAGS   = -g -O0 -Wall
RELEASE_EXEC  = hello
DEBUG_EXEC    = hello-dbg
#SOURCE        =

all: debug release

debug: $(DEBUG_EXEC)

hello-dbg: $(target)
	g++ $(DEBUG_FLAGS) $(target) -o $(DEBUG_EXEC) 

release: $(RELEASE_EXEC)

hello: $(target)
	g++ $(RELEASE_FLAGS) $(target) -o $(RELEASE_EXEC)

clean:
	rm -f $(RELEASE_EXEC) $(DEBUG_EXEC)
