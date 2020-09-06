/*

Author: Ananya

*/
#include<bits/stdc++.h>

using namespace std;


// CSV Reader
class CSVReader {
    string fileName;
    char delimeter;

	vector<string> split(string line) {
		string s = "";
		vector<string> splits;
		for (auto c: line) {
			if (c == delimeter) {
				splits.push_back(s);
				s = "";
			} else {
				s += c;
			}
		} 
		splits.push_back(s);
		return splits;
	} 

public:
    CSVReader(string filename, char delim = ',') : fileName(filename), delimeter(delim) {}

    vector<vector<string>> getData() {
	    
	    ifstream file(fileName);
	    
	    vector<vector<string>> dataList;
	    string line = "";

	    while (getline(file, line)) {
	        vector<string> vec = split(line);
	        dataList.push_back(vec);
	    }

	    file.close();
	    return dataList;
    }
};

// Trie node
struct node {
	map<char, node*> children;
	int frequency;
	bool end;
	node() {
		frequency = 0, end = false;
	}
};

void insert(node* root, string word, int frequency) {
	
	node* current = root;
	for (auto ch: word) {
		node* next = current->children[ch];
		if (!next) {
			next = new node();
			current->children[ch] = next;
		}
		current = next;
	}
	current->end = true;
	current->frequency = frequency;
}

bool search(node* root, string word, int &frequency) {
	node* current = root;

	for (auto ch: word) {
		node* next = current->children[ch];
		if (!next) {
			return false;
		}
		current = next;
	}
	frequency = current->frequency;
	return current->end;
}

int main(int argc, char* argv[]) {

	if (argc < 2) {
		cerr << "Usage: " << argv[0] << " CSV_File_Path" << endl;
		return 1;
	}

	CSVReader reader(argv[1]);
	vector<vector<string>> wordList = reader.getData();

	node* root = new node();


	for (auto line: wordList) {
		string word = line[0];
		int frequency = stoi(line[1]);
		// insert word into the trie
		insert(root, word, frequency);
	}

	string input = "";
	while(1) {
		cout << "Enter word to search (0 to exit): ";
		cin >> input;
		if (input == "0") {
			break;
		}

		// since dictionary has all lower case characters
		for (auto &ch: input) {
			ch = tolower(ch);
		}

		int frequency = 0;
		if (search(root, input, frequency)) {
			cout << "YES, " << frequency << endl; 
		} else {
			cout << "NO" << endl;
		}
	}

	cout << "\nBye! :)\n";

	return 0;
}
