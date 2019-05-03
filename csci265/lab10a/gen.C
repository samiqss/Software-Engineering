// generate a random graph
#include <cstdio>
#include <cstdlib>
#include <ctime>

// default number of nodes and edges to generate
const int DefNodes = 16;
const int DefEdges = 64;

int main(int argc, char *argv[])
{
   // determine the number of nodes and edges in the graph
   int numNodes, numEdges;
   if (argc > 1) numNodes = atoi(argv[1]);
   if (numNodes < 1) numNodes = DefNodes;
   if (argc > 2) numEdges = atoi(argv[2]);
   if (numEdges < 1) numEdges = DefEdges;

   // seed the random number generator
   srand(time(NULL));

   // generate the commands to create the random nodes
   for (int n = 0; n < numNodes; n++) {
       printf("I %d %ld\n", n, random());
   }

   // generate the commands to create the random edges
   for (int e = 0; e < numEdges; e++) {
       long src = random() % numNodes;
       long dest = random() % numNodes;
       long val = random() % numNodes;
       printf("A %ld %ld %ld\n", src, dest, val);
   }

   // print the graph, request a bread-first search, depth-first search,
   //    and minimum spanning tree, then quit
   printf("G\nB\nD\nT\nQ\n");
   return 0;
}
