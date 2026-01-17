#include<iostream>
#include<array>
#include<vector>
#include<fstream>

using namespace std;

struct Node {
    array<Node*, 26> next;
    bool isEnd = false;

    Node() {
        next.fill(nullptr);
    }
};

class Trie{
    private:
        Node* root = new Node();
        vector<string> suggestions;
        

        bool search(string &word, Node* node, int idx) {
            if(idx == word.length()) return node -> isEnd;

            int charIndex = word[idx] - 'a';
            if(!node->next[charIndex]) return false;

            return search(word, node->next[charIndex], idx+1);
        }

        bool isThere(string word, Node* node, int idx) {
            if(idx == word.length()) return true;

            int charIndex = word[idx] - 'a';
            if(!node -> next[charIndex]) return false;

            return isThere(word, node -> next[charIndex], idx+1);
        }

        void insert(string &word, Node* &node, int idx) {
            if(idx == word.length()) {
                node -> isEnd = true;
                return;
            }

            int charIndex = word[idx] - 'a';
            if(!node -> next[charIndex]) {
                node -> next[charIndex] = new Node();
            }

            insert(word, node -> next[charIndex], idx+1);
        }

        void remove(string &word, Node* &node, int idx) {
            if(idx == word.length()) {
                node -> isEnd = false;
                return;
            }

            int charIndex = word[idx] - 'a';
            if(!node -> next[charIndex]) return;

            remove(word, node -> next[charIndex], idx+1);
        }

        void insertAllWords() {
            ifstream file("allWords.txt");
            if(!file.is_open()) {
                cout << "Error in opening the file" << endl;
                exit(0);
            }
            string word;

            while(file >> word) {
                insert(word, root, 0);
            }

            file.close();
        }

        void nextWord(string prefix, Node* node) {
            if(suggestions.size() >= 5 || !node) return;

            if(node -> isEnd){
                suggestions.push_back(prefix);
                if(suggestions.size() >= 5) return;
            }

            for(int i =0; i<26; i++) {
                if(node -> next[i]){
                    nextWord(prefix + char('a' + i), node -> next[i]);
                }
            }
        }
    
    public:
        void start() {
            insertAllWords();
        }

        void push(string wordToInsert) {
            insert(wordToInsert, root, 0);
        }

        void pop(string wordToRemove) {
            remove(wordToRemove, root, 0);
        }

        void find(string wordToSearch) {
            if(search(wordToSearch, root, 0)) {
                cout << "Yes the word is present" << endl;
            } 
            else {
                cout << "The word isn't here" << endl;
            }
        }

        void suggest(string word) {
            suggestions.clear();

            if(!isThere(word, root, 0)) {
                cout << "There exist no such word!! \nPlease enter the correct prefix to suggest" << endl;
                return;
            }

            Node* temp = root;

            for(char ch: word) {
                temp = temp -> next[ch-'a'];
            }

            nextWord(word, temp);

            cout << "---Suggestions---" << endl;
            for(string words: suggestions)
                cout << words << " ";
            cout << endl;

        }

        ~Trie() {
            deleteNodes(root);
        }

        void deleteNodes(Node* node) {
            if(!node) return;

            for(int i =0; i<26; i++) {
                deleteNodes(node -> next[i]);
            }

            delete node;
        }

        
};

string takingInputs() {
    string myWord = "";

    cout << "Enter the prefix: ";
    cin >> myWord;

    if(myWord.empty()) {
        cout << "kindly enter the correct word" << endl;
        return takingInputs();
    }

    for(char &ch: myWord) {
        ch = tolower(ch);
    }

    return myWord;
}

int main() {
    Trie* myDictionary = new Trie();

    myDictionary -> start();

    string givenWord = takingInputs();
    
    myDictionary -> suggest(givenWord);

    delete myDictionary;

    return 0;
}