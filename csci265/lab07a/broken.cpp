#include <cstdio>
#include <cmath>
#include <cstdlib>

// possible tower id values, for the source,
//    destination, and auxilliary towers
enum ID { SRC, DEST, AUX };

// default size of the tower (number of disks)
const int DefaultSize = 3;

// value used to specify an empty tower
const int EMPTY = -1;

// each tower has a maximum size, current size,
//    and an array of disks
struct Tower {
   int currSize;
   int maxSize;
   int *disks;
   ID id;
};

// given the number of disks and the tower id,
//    allocate and initialize a tower,
// return true if successful, false otherwise
bool initialize(Tower &t, int disks, enum ID id)
{
   t.currSize = 0;
   t.maxSize = disks;
   t.id = id;
   t.disks = new int[disks];
   if (!t.disks) return false;
   return true;
}

// push a numbered disk onto the tower
void push(Tower &t, int diskNum)
{
   t.disks[t.currSize++] = diskNum;
}

// pop a numbered disk off the tower, returning its number
// returns -1 if tower is empty
int pop(Tower &t)
{
   if (t.currSize == 0) return EMPTY;
   return t.disks[--t.currSize];
}

// release any memory allocated for the tower
void release(Tower &t) {
   if (t.disks) delete[] t.disks;
}

// display the required move to the user
void printMove(Tower &src, Tower &dest, int diskNum)
{
   printf("Move the top disk (%d) from tower %d to tower %d\n", diskNum, src.id, dest.id);
}

// draw the current tower contents, left to right
void printTower(Tower &t)
{
   printf("   Tower[%d]: ", t.id);
   for (int i = 0; i < t.currSize; i++) printf("%d,", t.disks[i]);
   printf("\n");
}

// determine the legal move needed to get a disk from the
//    specified current source to the current destination
void makeMove(Tower &currSrc, Tower &currDest)
{
   // get the top disk from both towers
   int srcNum = pop(currSrc);
   int destNum = pop(currDest);

   // see if either tower was empty, if so move TO that tower
   if (srcNum == EMPTY) {
      push(currSrc, destNum);
      printMove(currDest, currSrc, destNum);
   } else if (destNum == EMPTY) {
      push(currDest, srcNum);
      printMove(currSrc, currDest, srcNum);
   }

   // otherwise move the smaller of the two disks,
   //    putting the larger back first
   else if (srcNum > destNum) {
      push(currSrc, srcNum);
      push(currSrc, destNum);
      printMove(currDest, currSrc, destNum);
   } else {
      push(currDest, destNum);
      push(currDest, srcNum);
      printMove(currSrc, currDest, srcNum);
   }
}

// transfer the specified number of disks from the top of the
//    source tower to the top of the destination tower,
//    using the auxilliary tower as needed
void transfer(int disks, Tower &src, Tower &dest, Tower &aux)
{
   // the total number of moves needed is 2^disks-1
   int moves = pow(2, disks);

   // if the number of disks is even we need to swap our
   //    aux and dest towers
   Tower realAux, realDest;
   if ((disks % 2) == 0) {
      realAux = dest;
      realDest = aux;
   } else {
      realAux = aux;
      realDest = dest;
   }

   // process all the moves in order,
   //    the direction of the move is based on both the move
   //        number and the value of the top disks on both towers
   //    (i.e. the direction may get reversed inside makeMove)
 
   for (int mv = 1; mv <= moves-1; mv++){
       if ((mv % 3) == 0) makeMove(realAux, realDest);
       else if ((mv % 3) == 1) makeMove(src, realDest);
       else makeMove(src, realAux);
       // draw the three towers
       printTower(src);
       printTower(realDest);
       printTower(realAux);
   }
}

int main(int argc, char *argv[])
{
   // number of disks to be processed,
   // user can override the default with a command line argument
   int numDisks = DefaultSize;
   if ((argc == 2) && (atoi(argv[1]) > 0)) numDisks = atoi(argv[1]);

   // set up the three towers
   Tower src, dest, aux;
   bool success = initialize(src, numDisks, SRC);
   success = success && initialize(dest, numDisks, DEST);
   success = success && initialize(aux, numDisks, AUX);
   if (success) {
      // let the user know what's  happening
      printf("\nTransferring %d disks from tower %d to tower %d\n",
         numDisks, src.id, dest.id);

      // push the original disks onto src,
      //    from largest to smallest
      for (int p = numDisks; p > 0; p--) push(src, p);

      // show them the original tower contents
      printTower(src);
      printTower(dest);
      printTower(aux);
      printf("\n");

      // move all the disks from the source tower to the destination tower,
      //    using the intermediate tower
      transfer(numDisks, src, dest, aux);
      printf("\nDone!!!\n\n");
   } else printf("\nTower allocation failed, ending program\n\n");

   // free any allocated memory and end the program
   release(src);
   release(dest);
   release(aux);
   return 0;
}

