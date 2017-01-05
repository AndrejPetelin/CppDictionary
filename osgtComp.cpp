#include <fstream>
#include <iostream>
#include <sstream>

#include "dictionary.h"

using namespace std;



int main(int argc, char* argv[])
{
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

    cout << "nananana appears " << dictionary.find("nananana") << " times\n";

    vector<string> sorted = dictionary.getWords([](std::string a, std::string b) { return a > b; });
    for (auto i : sorted)
    {
        cout << i << endl;
    }


}
