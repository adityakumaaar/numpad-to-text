#include<bits/stdc++.h>
#define ALPHABET_SIZE 26
#include "dictionary.cpp"       // contains all the valid dictionary words

using namespace std;

int flag = 0;                   // for check presence of valid words

class TrieNode{
    public: 
        TrieNode *children[ALPHABET_SIZE];          // an array of pointers to hold subsequent letters of the whole word
        bool isEndOfWord;                           // bool value to signify end of word

        TrieNode(){                                 // constructor
            isEndOfWord = false;
            for(int i=0;i<ALPHABET_SIZE;++i)
                children[i]=NULL;
        }

        TrieNode* getNode(){                        // returns a node after initializing it and allocating it dynamic memory
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

        bool search(string s){                                  // used for searching

            TrieNode *current = this;

            for(int i=0;i<s.length();i++){
                int index = s[i]-'a';

                if(current->children[index]==NULL){
                    return false;
                }
                current = current->children[index];
            }

            return (current !=NULL && current->isEndOfWord);    // checks if the node exists and if it does checks if a valid word has been formed yet
        }
};



const char hashTable[10][5]                             // mapping characters to the numpad
    = { "",    "",    "abc",  "def", "ghi",
        "jkl", "mno", "pqrs", "tuv", "wxyz" };
 
void printWordHelper(int number[], int curr_digit, char output[], int n, TrieNode *root)
{
    string ans(output);                                 // since search method takes a string param
    if (curr_digit == n ) {                             // base case : reached the end of number array
        if(root->search(ans)){                          // if valid word is found
            flag = 1;                                   // even if a single word had been found it signifies that there is a match
            cout<<ans<<endl;                            // print the word 
        }
        return;                                         // return to the last caller
    }

    for (int i = 0; i < strlen(hashTable[number[curr_digit]]);i++) {     // iterating through the charcters of the current digit of the input number
        
        output[curr_digit] = hashTable[number[curr_digit]][i]; 
        
        /* 
        num 2 3 4
        idx 0 1 2 

        output[0] = {a,b,c}
        output[1] = {d,e,f}
        output[2] = {g,h,i}
        */

        printWordHelper(number, curr_digit + 1, output, n, root);        // recursively calling after incrementing the current digit
        
        if (number[curr_digit] == 0 || number[curr_digit] == 1)         // base case if 0 or 1 is found : 0 & 1 maps to no characters
            return;
    }
}

void printWordsMain(int number[], int n, TrieNode *root )
{
    char result[n + 1];                                 // initializing char array which hold intermediate answers (valid & invalid)
    result[n] = '\0';
    printWordHelper(number, 0, result, n, root);         
}

int main(){  

    TrieNode *root = new TrieNode ();                   // making the base TrieNode

    for (int i = 0; i < dictionary.size(); i++)         // adding all the words from dictionary.cpp
        root->insert(dictionary[i]);   

    string enteredNumber;                               //getting user input
    cout<<"Enter the number: ";
    cin>>enteredNumber;

    int n = enteredNumber.size();                       
    int number[n];                                      // declaring int array


    for(int i=0;i<n;++i){                               // converting user inout to int array
        number[i] = enteredNumber[i]-'0';
    }

    printWordsMain(number, n, root);                

    if(!flag){                                          // checks if even one valid word is found (global variable)
        cout<<"Match Not Found"<<endl;                  // only prints if valid word is not found
    }
}