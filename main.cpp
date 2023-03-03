#include <set>
#include <vector>
#include <map>
#include <list>
#include <sstream>
#include <fstream>
#include <iostream>
#include <utility>

using namespace std;

vector<string> all_words(string filename) {
    vector<string> tokens;
    string next_line;  // Each data line
    ifstream in(filename);
    // Get lines from the file and remove the punctuation.
    while (getline(in, next_line)) {
        istringstream iss(next_line);
        string token;
        while (iss >> token) {
            string nopunct = "";
            for(auto &c : token) { // Remove Punctuation
                if (isalpha(c)) {
                    nopunct +=c;
                }
            }
            tokens.push_back(nopunct);
        }
    }
    ofstream setfile(filename + "_vector.txt");
    for (vector<string>::iterator it=tokens.begin(); it!=tokens.end(); ++it) {
        //cout << " " << *it;
        setfile << " " << *it << "\n";
    }
    return tokens;
}

set<string> unique_words(string filename) {
    vector<string> tokens;
    set <string> unique;
    string next_line;  // Each data line
    ifstream in(filename);
    // Get lines from the file and remove the punctuation.
    while (getline(in, next_line)) {
        istringstream iss(next_line);
        string token;
        while (iss >> token) {
            string nopunct = "";
            for(auto &c : token) { // Remove Punctuation
                if (isalpha(c)) {
                    nopunct +=c;
                }
            }
            tokens.push_back(nopunct);
            unique.insert(nopunct);
        }
    }
    ofstream setfile(filename + "_set.txt");
    for (set<string>::iterator it=unique.begin(); it!=unique.end(); ++it) {
        //cout << " " << *it;
        setfile << " " << *it << "\n";
    }
    return unique;
}

map<string, string> word_map(string filename, vector<string> words) {
    map<string, string> wordmap;
    string last="";
    for (vector<string>::iterator it=words.begin(); it!=words.end(); it++) {
        wordmap[last]=*it;
        last = *it;
    }
    ofstream setfile(filename + "_map.txt");
    for (map<string, string>::iterator it=wordmap.begin(); it!=wordmap.end(); ++it) {
        setfile << " " << it->first << ", " << it->second << "\n";
    }
    return wordmap;
}

void print_100(map<string, string> wordmap) {
    string state = "";
    for(int i = 0; i < 100; i++){
        cout << wordmap[state] << " ";
        state = wordmap[state];
    }
    cout << endl;
}

map<string, vector<string>> word_vec_map(map<string, string> words, vector<string> tokens) {
    map<string, vector<string>> wordmap;
    string state = "";
    for(vector<string>::iterator it=tokens.begin(); it !=tokens.end(); it++) {
        wordmap[state].push_back(*it);
        state = *it;
    }
    return wordmap;
}

void print_sermon(map<string, vector<string>> wordmap) {
    srand(time(NULL)); // this line initializes the random number generatede
    string state = "";
    // Generate 100 words that sound like the author from the text file.
    for (int i = 0; i < 100; i++) {
        int ind = rand() % wordmap[state].size(); // Pick a random word that comes after state
        cout << wordmap[state][ind] << " ";
        state = wordmap[state][ind]; // Update state to be the next word
    }
    cout << endl;
}

map<vector<string>, vector<string>> bestmap(map<string, vector<string>> words, vector<string> tokens) {
    map<vector<string>, vector<string>> wordmap;
    vector<string> state;
    int M = 2;
    for (int i = 0; i < M; i++) {
        state.push_back("");
    }

    for (vector<string>::iterator it=tokens.begin(); it!=tokens.end(); it++) {
        wordmap[state].push_back(*it);
        state.push_back(*it);
        state.erase(state.begin());
    }
    return wordmap;
}


int main(int argc, char *argv[])
{
    string filename = argv[1];
    vector<string> tokens = all_words(filename);
    set<string> unique = unique_words(filename);
    cout << "Number of words "<<tokens.size()<<endl;
    cout << "Number of unique words "<<unique.size()<<endl;
    // maps
    map<string, string> wordmap = word_map(filename, tokens);
    map<string, vector<string>> bettermap = word_vec_map(wordmap, tokens);
    //print_100(wordmap);

//    // Print out the vector of strings associated with the 6th entry in the map
//    map<string, vector<string>>::iterator it = wordmap.begin();
//    for (int i = 0; i < 6 && it !=wordmap.end(); ++it, ++i) {
//        cout << "string "<<it->first<<endl;
//    }
//    cout << "6th Entry"<<endl;
//    for(auto possible:it->second) {
//        cout << possible<<" ";
//    }
//    cout << endl;

    //print_sermon(bettermap);
    //map<vector<string>, vector<string>> bestmap = bestmap(bettermap, tokens);
    map<vector<string>, vector<string>> bestmap;
    vector<string> state;
    int M = 3;
    for (int i = 0; i < M; i++) {
        state.push_back("");
    }

    for (vector<string>::iterator it=tokens.begin(); it!=tokens.end(); it++) {
        bestmap[state].push_back(*it);
        state.push_back(*it);
        state.erase(state.begin());
    }

    cout << endl;
    //print best sermon
    state.clear();
    for (int i = 0; i < M; i++) {
        state.push_back("");
    }
    for (int i = 0; i < 142; i++) {
        int ind = rand() % bestmap[state].size();
        cout << bestmap[state][ind]<<" ";
        state.push_back(bestmap[state][ind]);
        state.erase(state.begin());
    }

}