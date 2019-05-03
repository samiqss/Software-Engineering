
all:	graph_valgrind graph_gprof generator

graph_gprof:	graph.C
	g++ -Wall -Wextra -pedantic -no-pie -pg graph.C -o graph_gprof

graph_valgrind:	graph.C
	g++ -Wall -Wextra -pedantic -no-pie -g graph.C -o graph_valgrind

generator:	gen.C
	g++ -Wall -Wextra -pedantic gen.C -o generator
