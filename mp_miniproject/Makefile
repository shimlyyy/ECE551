CFLAGS=-Wall -Werror -std=gnu++11 -pedantic -ggdb3
numeric:numerics.cpp
	g++ -o numerics $(CFLAGS) numerics.cpp evaluate.cpp numint.cpp mcint.cpp gradient.cpp common.cpp

clean:
	rm -f *~ numerics
