#include<bits/stdc++.h>
#define ALPHABET_SIZE 26
#include "dictionary.cpp"

using namespace std;


class TrieNode{
    public: 
        TrieNode *children[ALPHABET_SIZE];
        bool isEndOfWord; 

        TrieNode(){
            isEndOfWord = false;
            for(int i=0;i<ALPHABET_SIZE;++i)
                children[i]=NULL;
        }

        TrieNode* getNode(){
            TrieNode *p = new TrieNode;

            p->isEndOfWord = false;

            for(int i=0;i<ALPHABET_SIZE;++i)
                p->children[i]=NULL;

            return p;
        }

        void insert(string s){
            TrieNode *current = this;

            for(int i=0;i<s.length();++i){
                int index = s[i]-'a';                           //get the index of that character

                if(current->children[index]==NULL){             //if the character doesn't exist 
                    current->children[index] = getNode();       //initialize that character (at the correct index)
                }

                current = current->children[index];             //move the current to the next character
            }
            current->isEndOfWord=true;                          //after adding all the characters in the for loop mark the last charcter as end of word
        }


};

bool search(TrieNode *root , string s){

    TrieNode *current = root;

    for(int i=0;i<s.length();i++){
        int index = s[i]-'a';

        if(current->children[index]==NULL){
            return false;
        }
        current = current->children[index];
    }

    return (current !=NULL && current->isEndOfWord);
}

const char hashTable[10][5]
    = { "",    "",    "abc",  "def", "ghi",
        "jkl", "mno", "pqrs", "tuv", "wxyz" };
 
void printWordsUtil(int number[], int curr_digit,
                    char output[], int n, TrieNode *root)
{
    // Base case, if current output word is prepared
    int i;

    // cout<<output<<endl;
    string ans(output);
    // cout<<ans;
    // cout<<root;
    // cout<<ans;
    if (curr_digit == n ) {
        if(search(root, ans))
            cout<<ans<<endl;
        return;
    }
 
    // Try all 3 possible characters for current digir in
    // number[] and recur for remaining digits
    for (i = 0; i < strlen(hashTable[number[curr_digit]]);
         i++) {
        output[curr_digit]
            = hashTable[number[curr_digit]][i];
        printWordsUtil(number, curr_digit + 1, output, n, root);
        if (number[curr_digit] == 0
            || number[curr_digit] == 1)
            return;
    }
}




void printWords(int number[], int n, TrieNode *root )
{
    char result[n + 1];
    result[n] = '\0';
    printWordsUtil(number, 0, result, n, root);
}

int main(){  

    TrieNode *root = new TrieNode ();

    // string dictionary[] = {"bfh", "adg", "adh", "adiya"};
    
    for (int i = 0; i < dictionary.size(); i++) 
        root->insert(dictionary[i]);   

    int number[] = { 9, 3 };
    int n = sizeof(number) / sizeof(number[0]);
    printWords(number, n, root);
}