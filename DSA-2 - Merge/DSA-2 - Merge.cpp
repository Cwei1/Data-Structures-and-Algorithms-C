#include <cctype>
#include <fstream>
#include <iostream>

using namespace std;

bool mergeable[1001][1001];

int main (int argc, char ** argv) {
	int i;
	int j;
	string fIn;
	string fOut;
	string firstWord;
	string secondWord;
	string mergepos;
	ifstream inFile;
	ofstream outFile;
	cout << "Enter name of input file: ";
	cin >> fIn;
	cout << "Enter name of output file: ";
	cin >> fOut;

	inFile.open (fIn);
	outFile.open (fOut);

	if (inFile.is_open () && outFile.is_open ()) {

		while (inFile >> firstWord && inFile >> secondWord && inFile >> mergepos) {

			if ((firstWord.length () + secondWord.length()) != mergepos.length ()) {
				outFile << "*** NOT A MERGE ***" << endl;
				continue;
			}

			for (i = 0; i <= secondWord.length (); ++i) {
				for (j = 0; j <= firstWord.length (); ++j) {

					if (i == 0 && j > 0) {
						if (mergepos[j - 1] == firstWord[j - 1]) {
							if (j==1){
								mergeable[i][j]=true;
							}
							else{
								mergeable[i][j]=mergeable[i][j - 1];
							}
							continue;
						}
					} else if (j == 0 && i > 0) {
						if (mergepos[i - 1] == secondWord[i - 1]) {
							if (i==1){
								mergeable[i][j]=true;
							}
							else{
								mergeable[i][j]=mergeable[i-1][j];
							}
							continue;
						}
					}

					mergeable[i][j] = false;
				}
			}

			for (i = 1; i <= secondWord.length(); ++i) {
				for (j = 1; j <= firstWord.length(); ++j) {
					mergeable[i][j] = false;
					if (mergeable[i - 1][j] || mergeable[i][j - 1]) {
						if (secondWord[i - 1] == firstWord[j - 1] && mergepos[i + j - 1] == firstWord[j - 1]) {
							mergeable[i][j] = true;
						} 
						else if (mergeable[i - 1][j]) {
							if (mergepos[i + j - 1] == secondWord[i - 1]) {
								mergeable[i][j] = true;
							}
						} 
						else if (mergeable[i][j - 1]) {
							if (mergepos[i + j - 1] == firstWord[j - 1]) {
								mergeable[i][j] = true;
							}
						}
					}
				}
			}

			if (mergeable[secondWord.length()][firstWord.length()]) {
				i = secondWord.length ();
				j = firstWord.length ();

				while (j > 0 && i >= 0) {
					if (mergeable[i][j] && (i == 0 || !mergeable[i - 1][j])) {
						mergepos[i + j - 1] = toupper (mergepos[i + j - 1]);
						--j;
					}
					 else {
					 	--i;
					 }
				}

				outFile << mergepos << endl;

			} 
			else {
				outFile << "*** NOT A MERGE ***" << endl;
			}
		}

		inFile.close();
		outFile.close();

	} 
	else{
	 cerr << "ERROR: Unable to open file!" << endl;
	}

	return 0;
}