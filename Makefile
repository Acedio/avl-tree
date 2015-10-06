CPPFLAGS := -g

all: avl

avl: main.o avl.o
	g++ $(CPPFLAGS) $^ -o $@

main.o: main.cpp AVLTree.h
	g++ $(CPPFLAGS) -c $< -o $@

avl.o: AVLTree.cpp AVLTree.h
	g++ $(CPPFLAGS) -c $< -o $@

.PHONY : clean graphs
clean:
	rm avl *.o *.gv *.png

graphs: avl
	./avl | csplit -z -f 'graph' -b '%02d.gv' - "/}/+1" "{*}"
	make graphs.stamp

graphs.stamp: $(patsubst %.gv,%.png,$(wildcard *.gv))
	touch graphs.stamp

graph%.png: graph%.gv
	dot -Tpng -o $@ $<
