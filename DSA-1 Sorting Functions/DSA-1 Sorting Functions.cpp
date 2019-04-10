// THIS IS THE PROVIDED CODE FOR PROGRAM #2, DSA 1, SPRING 2017

#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <vector>
#include <string>
#include <algorithm>
#include <ctime>
#include <cmath>
#include <cstring>
#include <cctype>
#include <cstdlib>

using namespace std;

// A simple class; each object holds one string
class Data {
public:
  string data;
  Data(const string &s) { data = s; }
};

// Load the data from a specified input file
void loadDataList(list<Data *> &l) {
  string filename;
  cout << "Enter name of input file: ";
  cin >> filename;

  ifstream input(filename.c_str());
  if (!input) {
    cerr << "Error: could not open " << filename << endl;
    exit(1);
  }

  // The first line indicates the size
  string line;
  getline(input, line);
  stringstream ss(line);
  int size;
  ss >> size;

  // Load the data
  for (int i = 0; i < size; i++) {
    string line;
    getline(input, line);
    l.push_back(new Data(line));
  }

  input.close();
}

// Output the data to a specified input file
void writeDataList(const list<Data *> &l) {
  string filename;
  cout << "Enter name of output file: ";
  cin >> filename;

  ofstream output(filename.c_str());
  if (!output) {
    cerr << "Error: could not open " << filename << endl;
    exit(1);
  }

  // Write the size first
  int size = l.size();
  output << size << endl;

  // Write the data
  for (list<Data *>::const_iterator ipD = l.begin(); ipD != l.end(); ipD++) {
    output << (*ipD)->data << endl;
  }

  output.close();
}

void sortDataList(list<Data *> &);

// The main function calls routines to get the data, sort the data,
// and output the data. The sort is timed according to CPU time.
int main() {
  list<Data *> theList;
  loadDataList(theList);

  cout << "Data loaded.  Executing sort..." << endl;

  clock_t t1 = clock();
  sortDataList(theList);
  clock_t t2 = clock();
  double timeDiff = ((double) (t2 - t1)) / CLOCKS_PER_SEC;

  cout << "Sort finished. CPU time was " << timeDiff << " seconds." << endl;

  writeDataList(theList);
}

// -------------------------------------------------
// YOU MAY NOT CHANGE OR ADD ANY CODE ABOVE HERE !!!
// -------------------------------------------------

// You may add global variables, functions, and/or
// class defintions here if you wish.
list<Data *>::iterator it, it2,tmp;
int placeholder;
int counter[1000000]={0};
Data * hold[1000000];
list<Data *> l2;
Data *holdmabuckets[200000][10];

//comparison based on decimal point location
int newcompare(string newstr, string newstr2){
	int declocation=newstr.find_last_of(".");
	int declocation2=newstr2.find_last_of(".");
	if (declocation==declocation2){
		return newstr.compare(newstr2);
	}
	else if(declocation > declocation2){
		return 1;
	}
	else{
		return -1;
	}
}

//check which set is being used
int whichset(list<Data *> &l){
    int whichlist=0;
    bool isit3=true;
    bool isit4=true;
    it=l.begin();
    string temporary=(*it)->data.substr(0,8);
    it++;
    string temporary2=(*it)->data.substr(0,8);
    if((*it)->data.length()>7){
        isit3=false;
    }
    if(temporary.compare(temporary2) != 0){
    	isit4=false;
    }
    if (l.size()<101001){
      whichlist=1;
    }
    else if(isit3){
      whichlist=3;
    }
    else if(isit4){
      whichlist=4;
    }
    else{
      whichlist=2;
    }
    return whichlist;
}

//Use for T1-T2, to nearly sort the list for 6 digits
//Note: Use insertionsort to finish sorting the nearly sorted list
void radixSort(list<Data *> &l, const list<Data *>::iterator begin, const list<Data *>::iterator end, int radix){
	if((radix < 6) && (begin != end)){
		list<Data *>::iterator bin[10];
		unsigned int counter[10] = {};
		int ind2 = radix + 1;
		for (it = begin; it != end; it++) {
			int index=((*it)->data.find_last_of("."));

			if((20 - index) > radix){
				holdmabuckets[counter[0]][0] = *it;
				(counter[0])++;
			}
			
			else{
				int pos = ((*it)->data)[radix-(20-index)] - 48;
				holdmabuckets[counter[pos]][pos] = *it;
				(counter[pos])++;
			}
		}
		it=begin;
		for(int j = 0; j < 10; j++){
			bin[j] = it;
			int start = 0;
			while(start != (counter[j])){
				*it = holdmabuckets[start][j];
				it++;
				start++;
			}
			bin[j+1] = it;
		}		
		for(int i = 0; i < 10; i++){
			radixSort(l, bin[i], bin[i+1], ind2);
		}
	}
}

//T3sort best case for small size elements
void countingsortmodified(list<Data *> &l){
	for (it=l.begin(); it!=l.end(); it++) {
		placeholder = (1000*atof(((*it)->data).c_str()));
		counter[placeholder]++;
		hold[placeholder]=(*it);
	}
	for (int i=0; i<1000000; i++) {
		while(counter[i]--) {
			l2.push_back(hold[i]);
		}
	}
	l.swap(l2);
}

//T4sort best case of nearly sorted list
void insertionSort(list<Data *> &l) {
  it = l.begin(); 
  it++;
  for (it; it!=l.end(); it++) {
    it2 = it;
    tmp = it2; 
    tmp--;
    while (it2!=l.begin() && newcompare(((*it2)->data),((*tmp)->data)) < 0) {
      iter_swap(it2,tmp);
      it2--;
      tmp--;
    }
  }
}

void sortDataList(list<Data *> &l) {
  if (whichset(l)==1){
  	cout << "Sorting T1" <<endl;
	radixSort(l, l.begin(), l.end(), 0);
	insertionSort(l);
  }
  else if(whichset(l)==2){
	cout << "Sorting T2" <<endl;
    radixSort(l, l.begin(), l.end(), 0);
    insertionSort(l);
  }
  else if(whichset(l)==3){
	cout << "Sorting T3" <<endl;
    countingsortmodified(l);
  }
  else{
  	cout << "Sorting T4" <<endl;
    insertionSort(l);
  }
}