
#include <iostream>
#include <string>
#include <stack>
#include <queue>
#include <climits>
#include <cfloat>
using namespace std;

/**********************************************************/
/******** GLOBAL TYPES, CONSTANTS, AND VARIABLES **********/
/**********************************************************/

// define the maximum number of nodes in the graph,
//    node id's are assumed to be 0..Vertices-1
const int VERTICES = 4096;

// store the number of nodes currently in the graph
// (initially 0, and cannot exceed VERTICES)
int numnodes = 0;

// store the number of edges currently in the graph
// (initially 0, and cannot exceed (VERTICES-1)^2)
int numedges = 0;

// define the contents of an individual node in the graph
struct node {
   int nodeid;      // the node's position in Graph[] 
   string nodename; // text data for the application
   float nodedata;  // numeric data for the application
   bool visited, processed; // flags used for graph traversals
   bool inmst;      // flag used for spanning tree creation
   float distance;  // distance from source node
};

// store pointers to the graph nodes in an array,
//    Graph[i] contains a pointer to the node whose id is i
node *Graph[VERTICES];
 
// create the adjacency matrix for the graph,
//    Edges[i][j] is a positive weight if there
//       is an edge going from node i to node j
//    and is 0 otherwise
float Edges[VERTICES][VERTICES];

/**********************************************************/
/************** EDGELIST HEAP CLASS ***********************/
/**********************************************************/

// define the contents of an edge,
//    used for building edgelists
//    (for use in spanning tree algorithms)
struct edgenode {
   int src;
   int dest;
   float weight;
};

typedef edgenode* edgenodeptr;

// define a heap, used to store edges with
//    the minimum weight edge on top
class heap {
   public:
      heap(int sz = 0);
      ~heap();
      bool insert(edgenode *e);
      edgenode *remove();
   private:
      int maxsize;
      int cursize;
      edgenode* *edges;
};

edgenode *heap::remove()
{
   if ((cursize >= maxsize) || (!edges)) return NULL;
   edgenode *victim = edges[0];
   edges[0] = edges[--cursize];
   edgenode *e = edges[0];
   if (!e) return NULL;
   edges[cursize] = NULL;
   int pos = 0;
   do {

      // see if e needs to swap with either of its children
      int left = 2 * pos + 1;
      int right = left + 1;

      // quit if there are no children
      if ((left >= cursize) || (edges[left] == NULL)) break;

      // check against a lone left child
      else if (left == (cursize-1)) {
          edgenode *tmp = edges[left];
          if (tmp->weight < e->weight) {
             edges[left] = e;
             edges[pos] = tmp;
             pos = left;
          } else break;
      } 

      // check against the larger of two children
      else {
         edgenode *l = edges[left];
         edgenode *r = edges[right];
         if (!l || !r) break;
         if ((l->weight > r->weight) && (l->weight > e->weight)) {
            edges[left] = e;
            edges[pos] = l;
            pos = left;
         } 
         else if (r->weight > e->weight) {
            edges[right] = e;
            edges[pos] = r;
            pos = right;
         } 
         else break;
      }

   } while (pos < cursize);
   return victim;
}

bool heap::insert(edgenode *e)
{
   // make sure we have an edge to insert
   if (!e) return false;

   // insert the new edge
   edges[cursize++] = e;

   // percolate the edge up the heap
   int pos = cursize - 1;
   while (pos > 0) {
      // figure out the position of the parent 
      int parent = (pos - 1) / 2;
      // if the parent is null there's an error
      //    (there should be no nulls between 
      //     the heap root and the insert point)
      if (!edges[parent]) return false;
      // if the parent weight is no bigger than e's
      //    then e is as far up the heap as it needs to go
      if (edges[parent]->weight <= e->weight) return true;
      // otherwise swap e and its parent
      edges[pos] = edges[parent];
      edges[parent] = e;
      pos = parent;
   }
   return true;
}

heap::heap(int sz)
{
   if (sz < 0) sz = 0;
   if (sz == 0) edges = NULL;
   else edges = new edgenodeptr[sz];
   if (!edges) maxsize = 0;
   else maxsize = sz;
   cursize = 0;
   for (int i = 0; i < maxsize; i++) edges[i] = NULL;
}

heap::~heap()
{
   delete edges;
}

/**********************************************************/
/************** GRAPH FUNCTIONS ***************************/
/**********************************************************/

// List of graph functions
void empty_graph();
bool remove_node(int id);
int insert_node(string name, float data);
bool lookup_node(int id, string &name, float &data);
bool add_edge(int src_id, int dest_id, float wt);
float remove_edge(int src_id, int dest_id);
float check_edge(int src_id, int dest_id);
bool print_node(int id);
void print_graph();
int  get_graphsize();
int  get_maxsize();
void depth_first();
void breadth_first();
bool mst();
int get_numedges();

// return the number of edges currently in the graph
int get_numedges()
{
   return numedges;
}

// call print_node on each node in the graph,
//    using a depth-first ordering
void depth_first()
{
   // set all nodes' visited and processed flags to false
   for (int i = 0; i < VERTICES; i++) {
       if (Graph[i] != NULL) {
          Graph[i]->visited = false;
          Graph[i]->processed = false;
       }
   }

   // maintain a stack of nodes to be processed
   stack<node*> s;

   // id will track the starting node for seperate
   //    graph components, in case the graph isn't
   //    fully connected
   int id = 0;
   int component = 1;

   do { // find and process the next graph component, if any

      // find the next vertex that hasn't been processed
      while ((id < VERTICES) && (Graph[id] == NULL)) id++;
      if (id >= VERTICES) return;
      if (Graph[id]->processed == true) { id++; continue; }

      // otherwise push our new starting point for exploration
      //    (after setting its visited field to true)
      cout << endl << "Processing graph component " << (component++) << endl;
      Graph[id]->visited = true;
      s.push(Graph[id]);
   
      // while the stack isn't empty
      //    take the next node off the stack
      //       and print it
      //    for each adjacent node
      //       if it hasn't been visited yet
      //          set its visited flag to true
      //          and push it on the stack
      while (s.size() > 0) {
         node *n = s.top();
         s.pop();
         if (!n) continue;
         int nid = n->nodeid;
         print_node(nid);
         n->processed = true;
         for (int j = 0; j < VERTICES; j++) {
             if ((Edges[nid][j] != 0) && (Graph[j] != NULL)) {
                if (Graph[j]->visited == false) {
                    Graph[j]->visited = true;
                    s.push(Graph[j]);
                }
             }
         }
      }
      
   } while (id < VERTICES);
}

// call print_node on each node in the graph,
//    using a breadth-first ordering
void breadth_first()
{
   // set all nodes' visited and processed flags to false
   for (int i = 0; i < VERTICES; i++) {
       if (Graph[i] != NULL) {
          Graph[i]->visited = false;
          Graph[i]->processed = false;
       }
   }

   // maintain a queue of nodes to be processed
   deque<node*> q;

   // id will track the starting node for seperate
   //    graph components, in case the graph isn't
   //    fully connected
   int id = 0;
   int component = 1;

   do { // find and process the next graph component, if any

      // find the next vertex that hasn't been visited
      while ((id < VERTICES) && (Graph[id] == NULL)) id++;
      if (id >= VERTICES) return;
      if (Graph[id]->processed == true) { id++; continue; }

      // otherwise push our new starting point for exploration
      //    (after setting its visited field to true)
      cout << endl << "Processing graph component " << (component++) << endl;
      Graph[id]->visited = true;
      q.push_back(Graph[id]);
   
      // while the queue isn't empty
      //    take the next node out of the queue
      //       and print it
      //    for each adjacent node
      //       if it hasn't been visited yet
      //          set its visited flag to true
      //          and put it into the queue
      while (q.size() > 0) {
         node *n = q.front();
         q.pop_front();
         if (!n) continue;
         int nid = n->nodeid;
         print_node(nid);
         Graph[nid]->processed = true;
         for (int j = 0; j < VERTICES; j++) {
             if ((Edges[nid][j] != 0) && (Graph[j] != NULL)) {
                if (Graph[j]->visited == false) {
                    Graph[j]->visited = true;
                    q.push_back(Graph[j]);
                }
             }
         }
      }
   } while (id < VERTICES);
}

// call print_node on each node in the graph,
//   ordered by the node ids
void print_graph()
{
   for (int i = 0; i < VERTICES; i++)
       if (Graph[i]) print_node(i);
}

// return the number of nodes currently in the graph
int  get_graphsize()
{
   return numnodes;
}

// return the number of nodes the graph is capable of holding
//   (i.e. vertices)
int  get_maxsize()
{
   return VERTICES;
}

// initialize an empty graph,
//    wiping out the old graph (if any)
void empty_graph()
{
   for (int i = 0; i < VERTICES; i++) {
       delete Graph[i];
       Graph[i] = NULL;
       for (int j = 0; j < VERTICES; j++) 
           Edges[i][j] = 0;
   }
   numnodes = 0;
}

// if a node with the specified id exists,
//    it is removed from the graph
//    along with all edges to and from it
// returns true iff a node is removed
bool remove_node(int id)
{
   if ((id < 0) || (id >= VERTICES) || (Graph[id] == NULL)) return false;
   delete Graph[id];
   Graph[id] = NULL;
   for (int i = 0; i < VERTICES; i++) {
       if (Edges[i][id]) numedges--;
       else Edges[i][id] = 0;
       if (Edges[id][i]) numedges--;
       else Edges[id][i] = 0;
   }
   numnodes--;
   return true;
}

// create a node and insert it's pointer in the first
//    free graph position, returning it's id value
// returns -1 if unsuccessful
int insert_node(string name, float data)
{
   int id = 0;
   while (id < VERTICES) {
      if (Graph[id] == NULL) {
         Graph[id] = new node;
         if (!Graph[id]) return -1;
         Graph[id]->nodeid = id;
         Graph[id]->nodename = name;
         Graph[id]->nodedata = data;
         numnodes++;
         return id;
      }
      id++;
   }
   return -1;
}

// copy the name and data from the node in position id
//    return true iff successful
bool lookup_node(int id, string &name, float &data)
{
   if ((id < 0) || (id >= VERTICES) || (Graph[id] == NULL)) return false;
   name = Graph[id]->nodename;
   data = Graph[id]->nodedata;
   return true;
}

// create an edge from the node in position src_id
//    to the node in position dest_id
// return true iff a new edge is successfully added
bool add_edge(int src_id, int dest_id, float wt)
{
   if ((src_id < 0) || (src_id >= VERTICES) || (Graph[src_id] == NULL)) return false;
   if ((dest_id < 0) || (dest_id >= VERTICES) || (Graph[dest_id] == NULL)) return false;
   if (Edges[src_id][dest_id]) return false;
   Edges[src_id][dest_id] = wt;
   numedges++;
   return true;
}

// remove the edge from the node in position src_id
//    to the node in position dest_id
// return the edge weight iff an edge is successfully removed
//    and 0 otherwise
float remove_edge(int src_id, int dest_id)
{
   if ((src_id < 0) || (src_id >= VERTICES) || (Graph[src_id] == NULL)) return false;
   if ((dest_id < 0) || (dest_id >= VERTICES) || (Graph[dest_id] == NULL)) return false;
   if (!Edges[src_id][dest_id]) return false;
   float weight = Edges[src_id][dest_id];
   Edges[src_id][dest_id] = 0;
   numedges--;
   return weight;
}

// return the edge weight if there is an edge from the node in
//    position src_id to the node in position dest_id
// or 0 otherwise
float check_edge(int src_id, int dest_id)
{
   if ((src_id < 0) || (src_id >= VERTICES) || (Graph[src_id] == NULL)) return 0;
   if ((dest_id < 0) || (dest_id >= VERTICES) || (Graph[dest_id] == NULL)) return 0;
   return Edges[src_id][dest_id];
}

// display the name, data and data for the node in
//    position id, then list the node ids for every 
//    node which can be reached via one edge from
//    this node
bool print_node(int id)
{
   if ((id < 0) || (id >= VERTICES) || (Graph[id] == NULL)) {
      cout << "Invalid node: " << id << endl;
      return false;
   }
   cout << "Vertex " << id << ": (";
   cout << Graph[id]->nodename << ", " << Graph[id]->nodedata << ") with outgoing edges to =>" << endl;
   for (int i = 0; i < VERTICES; i++) {
       if (Edges[id][i] > 0) cout << "   node " << i << ", weight " << Edges[id][i] << endl;
   }
   return true;
}

// if the graph has a minimal spanning tree,
//    display the list of edges in the tree
//       and return true
// otherwise return false
bool mst()
{
   // initialize every node's spanning tree flag to false
   for (int i = 0; i < VERTICES; i++) {
       if (Graph[i] != NULL) {
          Graph[i]->inmst = false;
       }
   }

   // create a heap of edgelists, large enough to
   //    store all the edges currently in the graph
   heap edgelist(get_numedges());

   // find a starting node and mark it as in the mst
   int pos = 0;
   int cursize = get_graphsize();
   while ((Graph[pos] == NULL) && (pos < cursize)) pos++;
   // if there were no nodes then the graph is empty
   if (pos >= cursize) return true;

   // use a queue of edgenodes to keep track of our mst
   deque<edgenode*> mst;

   // keep track of the number of nodes in our mst
   int mstsize = 1;

   // keep a pointer to the current node
   node *curr = Graph[pos];
   do {
      // mark the current node as part of the mst
      if (!curr) break;
      else curr->inmst = true;

      // put the current node's edges in the heap
      for (int i = 0; i < VERTICES; i++) {
          if (Edges[pos][i] > 0) {
             edgenode *new_e = new edgenode;
             if (new_e) {
                new_e->src = pos;
                new_e->dest = i;
                new_e->weight = Edges[pos][i]; 
                edgelist.insert(new_e);
             }
          }
      }

      // find the top heaped edge that connects an mst node
      //    to a non-mst node (quit if there is none)
      edgenode *nexte;
      node *n1, *n2;
      while ((nexte = edgelist.remove()) != NULL) {
         n1 = Graph[nexte->src];
         n2 = Graph[nexte->dest];
         if ((!n1) || (!n2))  {
            delete nexte;
            continue;
         }
         if (n1->inmst != n2->inmst) break;
      }
      if (!nexte) break;

      // add the selected edge to the mst
      mst.push_front(nexte);
      mstsize++;

      // make the new current node the one the new edge
      //   adds to the tree
      if (n1->inmst) {
         n2->inmst = true;  
         pos = n2->nodeid;
         curr = n2;
      } else  {
         n1->inmst = true;  
         pos = n1->nodeid;
         curr = n1;
      }
   } while(mstsize < get_graphsize());

   // if we couldn't build the entire spanning tree
   //    then the final result is false
   // otherwise the mst is now complete, so display it
   //    and set the final result to true
   bool result = false;
   if (mstsize >= (get_graphsize() - 1)) {
        result = true;
        cout << "The complete spanning tree is" << endl;
   } else cout << "The partial spanning tree is" << endl;
   while (!mst.empty()) {
      edgenode *e = mst.front();
      mst.pop_front();
      if (e) {
         cout << e->src << "->" << e->dest << " (" << e->weight << ")" << endl;
         delete e;
      }
   }
   return result;
}

// compute and display the distance of each node
//    from a designated source node
// return true if successful, false otherwise
bool distances(int src)
{
   // make sure the node exists
   if (!Graph[src]) return false;

   // initialize every node's distance to infinity
   for (int i = 0; i < VERTICES; i++) {
       if (Graph[i] != NULL) {
          Graph[i]->distance = FLT_MAX;
       }
   }

   // initialize the distance to the start node
   Graph[src]->distance = 0;

   // create a heap big enough to hold all the edges
   heap edgelist(get_numedges());

   // add all the source node's edges to the heap
   for (int d = 0; d < VERTICES; d++) {
       if (Edges[src][d] > 0) {
          edgenode *e = new edgenode;
          if (e) {
             e->src = src;
             e->dest = d;
             e->weight = Edges[src][d];
             edgelist.insert(e);
          }
       }
   }

   // while the heap isn't empty
   //    remove the next (smallest) edge from the heap
   //    if the edge gives us a new shorter path
   //       to the destination vertex then:
   //          update the distance to that vertex
   //          and insert all it's vertices into the graph
   //    (if the graph is bidirectional we could do similarly
   //     in the other direction)
   edgenode *e;
   node *s, *d;
   while ((e = edgelist.remove()) != NULL) {
      s = Graph[e->src];
      d = Graph[e->dest];
      float w = e->weight;
      if (d->distance > (s->distance + w)) {
         for (int j = 0; j < VERTICES; j++) {
             if (Edges[e->dest][j] > 0) {
                edgenode *new_e = new edgenode;
                if (new_e) {
                   new_e->src = e->src;
                   new_e->dest = j;
                   new_e->weight = Edges[e->src][j];
                   edgelist.insert(new_e);
                }
             }
         }
      }
      delete e;
   }

   // go through the graph, displaying the distance to each node
   for (int i = 0; i < VERTICES; i++) {
       if (Graph[i] && (i != src)) {
          cout << src << "->" << i << " distance: ";
          if (Graph[i]->distance == FLT_MAX) cout << "infinite" << endl;
          else cout << Graph[i]->distance << endl;
       }
   }
   return true;
}

/**********************************************************/
/******** APPLICATION FUNCTIONS ***************************/
/**********************************************************/

// List of application functions
char getcommand();
void printmenu();
bool processcommand(char cmd);
int getint();
float getfloat();

int main()
{

   printmenu();
   char cmd = getcommand();
   while (processcommand(cmd)) { 
      cout << endl;
      cmd = getcommand();
   }

   return 0;
}

char getcommand()
{
   cout << "Enter your command choice (T, B, D, G, V, E, I, A, R, C, H, Q, S, M, N)" << endl;
   char cmd;
   cin >> cmd;
   cmd = toupper(cmd);
   switch (cmd) {
      case 'G':
      case 'V':
      case 'E':
      case 'B':
      case 'D':
      case 'I':
      case 'A':
      case 'R':
      case 'C':
      case 'S':
      case 'T':
      case 'M':
      case 'N':
      case 'H':
      case 'Q': return cmd;
      default:  cout << "You have entered an invalid command" << endl;
                return getcommand();
   }
}

void printmenu()
{
   cout << "Enter A to add an edge," << endl;
   cout << "   or B to perform a breadth-first traversal of the graph," << endl;
   cout << "   or C to eliminate an edge," << endl;
   cout << "   or D to perform a depth-first traversal of the graph," << endl;
   cout << "   or E to display a single edge," << endl;
   cout << "   or G to print the entire graph," << endl;
   cout << "   or H for help," << endl;
   cout << "   or I to insert a new vertex," << endl;
   cout << "   or M to lookup the number of elements the graph can hold," << endl;
   cout << "   or N to start a new (empty) graph," << endl;
   cout << "   or Q to quit." << endl;
   cout << "   or R to remove a vertex," << endl;
   cout << "   or S to lookup the number of elements currently in the graph," << endl;
   cout << "   or T to compute the minimal spanning tree." << endl;
   cout << "   or V to display a single vertex," << endl;
}

bool processcommand(char cmd)
{
   string key;
   float data, wt;
   int id, src, dest;
   bool result1, result2;
   switch (cmd) {
      case 'T': cout << "Computing minimal spanning tree:" << endl;
                if (!mst()) cout << "There is no spanning tree" << endl;
                break;
      case 'D': cout << "Performing depth-first search" << endl;
                depth_first();
                break;
      case 'B': cout << "Performing breath-first search" << endl;
                breadth_first();
                break;
      case 'H': printmenu(); 
                break;
      case 'I': cout << "Inserting new vertex" << endl;
                cout << "Enter the text data for the new vertex" << endl;
                cin >> key;
                data = getfloat();
                cout << "(" << key << "," << data << ") ";
                id = insert_node(key, data);
                if (id >= 0)
                   cout << "was inserted with id " << id << endl;
                else cout << "was not inserted correctly" << endl;
                break;
      case 'S': cout << "There are " << get_graphsize() << " vertices in the graph" << endl;
                break;
      case 'M': cout << "The graph can hold " << get_maxsize() << " vertices" << endl;
                break;
      case 'N': empty_graph();
                cout << "The graph has been emptied" << endl;
                break;
      case 'R': id = getint();
                result1 = lookup_node(id, key, data);
                result2 = remove_node(id);
                if (result1 && result2) {
                   cout << "Removed vertex " << id << " (";
                   cout << key << "," << data << ")" << endl;
                } else {
                   cout << "Unable to remove vertex " << id << endl;
                }
                break;
      case 'G': cout << "The graph contents are: " << endl;
                print_graph();
                break; 
      case 'V': id = getint();
                print_node(id); 
                break;
      case 'E': cout << "For the source, ";
                src = getint();
                cout << "For the destination, ";
                dest = getint();
                wt = check_edge(src, dest);
                if (wt != 0) {
                   cout << "There is an edge from " << src << " to " << dest;
                   cout << " with weight " << wt << endl;
                } else {
                   cout << "There is no edge from " << src << " to " << dest << endl;
                }
                break;
      case 'A': cout << "Adding new edge:" << endl;
                cout << "For the source, ";
                src = getint();
                cout << "For the destination, ";
                dest = getint();
                cout << "For the edge weight, ";
                wt = getfloat();
                if (add_edge(src, dest, wt) && add_edge(dest, src, wt)) {
                   cout << "Added edge from " << src << " to " << dest;
                   cout << ", weight " << wt << endl;
                } else
                   cout << "Unable to add an edge from " << src << " to " << dest << endl;
                break;
      case 'C': cout << "For the source, ";
                src = getint();
                cout << "For the destination, ";
                dest = getint();
                wt = remove_edge(src, dest);
                if (wt != 0) {
                   cout << "Removed an edge from " << src << " to " << dest;
                   cout << ", with weight " << wt << endl;
                } else {
                   cout << "Unable to remove an edge from " << src << " to " << dest << endl;
                }
                break;
      case 'Q': return false;
      default:  return true;
   }
   return true;
}

int getint()
{
   string tmp;
   cout << "Enter a vertex id" << endl;
   cin >> tmp;
   return atoi(tmp.c_str());
}

float getfloat()
{
   string tmp;
   cout << "Enter a numeric value" << endl;
   cin >> tmp;
   return atof(tmp.c_str());
}
