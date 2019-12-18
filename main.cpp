//
//  main.cpp
//  Spell Checker
//
//  Created by Ramy ElGendi on 10/25/18.
//  Copyright © 2018 Ramy ElGendi. All rights reserved.
//
//Read from file insert small
#include <fstream>
#include <string>
#include <iostream>
#include "HashTable.cpp"
using namespace std;
void IntoDictionary(hashTable<long, string>&, string&);
void SpellChecker  (hashTable<long, string>&, string &);
void WordCustomize (string&);
void Suggest();

int main()
{
    string D_ADDRESSS = "/Users/ramyelgendi/Desktop/Computer Science/Midterm 2/Spell Checker/Spell Checker/wordlist.txt";
    int D_SIZE = 60389;
    string F_ADDRESSS = "/Users/ramyelgendi/Desktop/Computer Science/Midterm 2/Spell Checker/Spell Checker/text.txt";

    hashTable <long, string> D(D_SIZE);
    D.makeTableEmpty(-1);
    IntoDictionary(D,D_ADDRESSS);
    SpellChecker(D,F_ADDRESSS);
    return 0;
}
void WordCustomize (string& word) //Lowercase, and remove '.' & ',' & '(' & ')' at the end/beginning.
{
    string x;
    for (int i =0; i< word.length(); i++)
    {
        x += char(tolower(int(word[i])));
    }
    word = x;
    while(word.back() == ',' || word.back() == '.'|| word.back() == ')'|| word.back() == '!'|| word.back() == '?')
        word.pop_back();
    while(word.front()== '(')
        word.erase(0,1);

}
void IntoDictionary (hashTable<long,string>&D , string &D_ADDRESSS)
{
    ifstream file;
    file.open (D_ADDRESSS);
    string word;
    word.clear();
    while (file >> word)
    {
        D.insert(word);
        word.clear();
    }
    file.close();
}
void SpellChecker (hashTable<long,string>&D , string &F_ADDRESSS)
{
    ifstream file;
    file.open (F_ADDRESSS);
    string word;
    word.clear();
    cout<<" \nINCORRECT WORDS FOUND:  \n";
    while (file >> word)
    {
        WordCustomize(word);
        if(!D.search(word))
        {
            cout<<word;
            D.Suggestions(word);
        }
        word.clear();
    }
    file.close();
}
