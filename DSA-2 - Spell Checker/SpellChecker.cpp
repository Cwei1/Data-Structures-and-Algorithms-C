//Cardy Wei
//DSA2
//Professor Sable

#include <algorithm>
#include <chrono>
#include <fstream>
#include <iostream>
#include <string>
#include "hash.hpp"


void load (HashTable & dictionary_load, std::string fileIn) {
	std::ifstream words;
	words.open (fileIn);
	std::string line;
	while (std::getline (words, line)) {
		std::transform (line.begin (), line.end (), line.begin (), ::tolower);
		dictionary_load.insert (line);
	}
}

void SpellChecker (std::string output_file, std::string fileIn, HashTable & dictionary_load) {
	std::ifstream inputFile (fileIn);
	std::ofstream outputFile (output_file);
	std::string valid = "abcdefghijklmnopqrstuvwxyz0123456789-'";
	std::string nums = "0123456789";
	std::string x = "";

	unsigned long lineNr = 1;
	bool validjunct = false;
	bool toolong = false;
	bool isnum = false;
	char c;
	while (inputFile.get (c)) {
		c = std::tolower (c);
		if (valid.find (c) == std::string::npos) {
			validjunct = true;
		}
		else {
			validjunct = false;
		}
		if (nums.find (c) != std::string::npos) {
			isnum = true;
		}
		if (x.length () < 20) {
			if (!validjunct) {
				x += c;
			}
		 	else if (x != ""){
				if (!dictionary_load.contains (x) && !isnum){
					outputFile << "Unknown word at line " << lineNr << ": " << x << std::endl;
				}
			}
		} 
		else if (x.length () == 20 && validjunct && !toolong && !isnum) {
			if (!dictionary_load.contains (x)){
				outputFile << "Unknown word at line " << lineNr << ": " << x << std::endl;
			}
		}
		else if (!validjunct && !toolong && !isnum) {
			outputFile << "Long word at line " << lineNr << ", starts: " << x << std::endl;
			toolong = true;
			validjunct = false;
		}
		if (validjunct) {
			x = "";
			toolong = false;
			isnum = false;
		}
		if (c == '\n') ++lineNr;
	}
}


int main (int argc, char ** argv) {
	using namespace std;
	using namespace std::chrono;
	high_resolution_clock::time_point t1, t2;
	HashTable dictionary (75000);
	string dictionary_file;
	string fileIn;
	string fileOut;
	cout << "Please enter the name of the dictionary file: ";
	cin >> dictionary_file;
	t1 = high_resolution_clock::now ();
	load (dictionary, dictionary_file);
	t2 = high_resolution_clock::now ();
	duration<double> timing = duration_cast<duration<double>> (t2 - t1);
	cout << "It took " << timing.count () << " seconds to load your dictionary." << std::endl;
	cout << "Please enter your file to be Spell Checked: ";
	cin >> fileIn;
	cout << "Please enter the output file: ";
	cin >> fileOut;
	t1 = high_resolution_clock::now ();
	SpellChecker (fileOut, fileIn, dictionary);
	t2 = high_resolution_clock::now ();
	timing = duration_cast<duration<double>> (t2 - t1);
	cout << "Your document has been checked over, it took " << timing.count () << " seconds." << endl;
	return 0;
}
