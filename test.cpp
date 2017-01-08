#include <fstream>
#include <iostream>
#include <sstream>

#include "dictionary.h"

using namespace std;

bool pred(const std::string& a, const std::string& b) { return a > b; }

int main(int argc, char* argv[])
{
    // TODO : test new functions!

    /*
    if (argc < 2)
    {
        cout << "enter name of osgt file as argument\n";
        return 1;
    }

    string file1 = argv[1];

    ifstream fs;
    fs.open(file1.c_str());

    */


    Dictionary dictionary;
    vector<string> vec;

    vec.push_back("234");
    vec.push_back("nananana");
    vec.push_back("nanana");
    vec.push_back("nanana na");
    vec.push_back("nananana");
    vec.push_back("nanana");
    vec.push_back("nanana na");
    vec.push_back("nananana");
    vec.push_back("nanana");
    vec.push_back("nanana na");
    vec.push_back("aardvark");
    vec.push_back("ZZ Top");
    vec.push_back("123");

    dictionary.add(vec);

    Dictionary dict2;
    dict2.add("strawberry fields forever");
    dict2.add("Abba");

    dictionary = combine(dictionary, dict2);

    cout << "nananana appears " << dictionary.getVal("nananana") << " times\n";

    // vector<string> sorted = dictionary.getWords([](std::string a, std::string b) { return a > b; });
    vector<string> sorted = dictionary.asVector(pred);
    for (auto i : sorted)
    {
        cout << i << endl;
    }

    cout << endl << endl << endl;

    Dictionary::const_iterator it = dictionary.begin();

    while (it != dictionary.end()) cout << it++->first << endl;


}
