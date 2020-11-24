#include<bits/stdc++.h>
#define ALPHABET_SIZE 26
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

        bool search(string s){

            TrieNode *current = this;

            for(int i=0;i<s.length();++i){
                int index = s[i]-'a';

                if(current->children[index]==NULL){
                    return false;
                }
                current = current->children[index];
            }

            return (current !=NULL && current->isEndOfWord);
        }
};

int main(){

    TrieNode *root = new TrieNode ();

    string keys[] = {"the", "a", "there","answer", "any", "by", "bye", "their"};
    
    for (int i = 0; i < 8; i++) 
        root->insert(keys[i]);   

    
    
}