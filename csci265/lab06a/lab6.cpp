// lab6.cpp
// Sami Al-Qusus
// csci265 lab06a
// Oct 27,2017
//
// 

#include<iostream>
#include<stdlib.h>
#include<wchar.h>
#include<algorithm>
#include<regex>
using namespace std;

//compare function required for qsort
int compare (const void * a, const void * b)
{
	  return ( *(int*)a - *(int*)b );
}

int main()
{
	cout<< "//// trying out swap /////"<< endl;
	
	int val_1=1;
	int val_2=2;
	cout<< "val_1 is: "<<val_1<<endl;
	cout<< "val_2 is: "<<val_2<<endl;
	swap( val_1 , val_2);


	cout<< "val_1 is now: "<<val_1 <<endl;
	cout<< "val_2 is now: "<<val_2 <<endl;
	

	cout<< "///// trying out qsort ////"<<endl;
	
	//an array for int numbers we will sort
	int values[] = {5, 2, 4, 0, 3};
	cout<< "current unsorted numbers: "<< endl;
	for (int i=0; i<6; i++)
		cout<<values[i]<<" ";

	cout<<endl;
	qsort (values, 6, sizeof(int), compare);
	cout<< "result of qsort: "<<endl;
	for (int i=0; i<6; i++)
		cout<<values[i]<< " ";
	cout<<endl;
	
	cout<< "////// trying out the constat RAND_MAX thats in <stdlib.h> ////"<<endl;

	cout<< "the largest random number we can generate through rand() function call is:" <<RAND_MAX<<endl;
	
	cout<< "/////// trying out the <regex> library ///////"<<endl;
	
	string name= "samialqusus";
	regex part("(sami)(.*)");
	if (regex_match(name,part))
		cout << "string object matched"<< endl;
	else 
		cout << "string object did not match!!"<< endl;









	return 0;
}
