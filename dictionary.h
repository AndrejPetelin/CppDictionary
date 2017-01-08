#ifndef GUARD_DICTIONARY_H
#define GUARD_DICTIONARY_H

//=============================================================================
// dictionary.h
// (C) Andrej Petelin
// last modified: 06.01.2017 (06th of January, 2017)
//
// Dictionary is an attempt at a python-like dictionary class in C++. It's
// based around a std::map<std::string, size_t> (size_t for counting the number
// of occurrences of a word in the dictionary.
//
// use Dictionary::add to add string or vector of strings to a dictionary
// use Dictionary::remove to remove by key, iterator, iterators from to or
// vector of keys.
//
//=============================================================================

#include <algorithm>
#include <cstdlib>
#include <functional>
#include <map>
#include <string>
#include <vector>

class Dictionary
{
public:
    typedef std::map<std::string, size_t>::iterator iterator;
    typedef std::map<std::string, size_t>::const_iterator const_iterator;
    typedef std::map<std::string, size_t>::reverse_iterator reverse_iterator;
    typedef std::map<std::string, size_t>::const_reverse_iterator const_reverse_iterator;

    iterator begin() { return _data.begin(); }
    iterator end() { return _data.end(); }
    const_iterator begin() const { return _data.begin(); }
    const_iterator end() const { return _data.end(); }
    const_iterator cbegin() const { return _data.begin(); }
    const_iterator cend() const { return _data.end(); }
    reverse_iterator rbegin() { return _data.rbegin(); }
    reverse_iterator rend() { return _data.rend(); }
    const_reverse_iterator rbegin() const { return _data.rbegin(); }
    const_reverse_iterator rend() const { return _data.rend(); }
    const_reverse_iterator crbegin() const { return _data.rbegin(); }
    const_reverse_iterator crend() const { return _data.rend(); }

    // add a single word into the dictionary or increment counter if there already
    void add(const std::string& str)
    {
        if (_data.find(str) == _data.end()) _data[str] = 1;
        else _data[str] += 1;
    }

    // add a vector of words or increment respective counters if word(s) there already
    void add(const std::vector<std::string>& vec) { for (auto i : vec) add(i); }

    void add(const std::pair<std::string, size_t> p)
    {
        if (getVal(p.first) == false) _data[p.first] = p.second;
        else _data[p.first] += p.second;
    }

    // find word and remove it
    void remove(const std::string& str)
    {
        iterator it = _data.find(str);
        if (it != end()) _data.erase(it);
    }

    // find each word in vector and remove it
    void remove(const std::vector<std::string>& vec) { for (auto& i : vec) remove(i); }

    // remove word by iterator
    void remove(iterator it) { _data.erase(it); }
 
    // merges two Dictionaries, including summing the numbers of occurrences
    void join(const Dictionary& rhs)
    {
        for (auto& i : rhs._data)
        {
            if (_data.find(i.first) != _data.end()) _data[i.first] += i.second;
            else _data[i.first] = i.second;
        }
    }

    // how many occurrences of the word?
    int getVal(const std::string& str) const
    {
        const_iterator it = _data.find(str);
        return (it != _data.end()) ? it->second : 0;
    }

    std::pair<std::string, size_t> getPair(const std::string& str) const
    {
        const_iterator it = _data.find(str);
    }

    // get words as a vector of strings. Note that the order is "ASCII order"
    std::vector<std::string> asVector() const
    {
        std::vector<std::string> ret;
        for (auto& i : _data) ret.push_back(i.first);
        return ret;
    }

    // overload that returns a vector of strings from dictionary in order defined by
    // the provided predicate function (lambda, named function by pointer)
    std::vector<std::string> asVector(std::function<bool(std::string, std::string)> predicate) const
    {
        std::vector<std::string> ret = asVector();
        std::sort(ret.begin(), ret.end(), predicate);
        return ret;
    }

    Dictionary difference(const Dictionary& rhs) const
    {
        Dictionary ret;
        for (auto& i : _data)
        {
            if (!rhs.getVal(i.first)) ret.add(i);
        }
        return ret;
    }

    // returns a vector of all elements in this which are not present in rhs
    std::vector<std::string> differenceAsVector(const Dictionary& rhs) const
    {
        std::vector<std::string> ret;
        for (auto& i : _data)
        {
            if (!rhs.getVal(i.first)) ret.push_back(i.first);
        }
        return ret;
    }

    Dictionary intersection(const Dictionary& rhs) const
    {
        Dictionary ret;
        for (auto& i : _data)
        {
            size_t val = rhs.getVal(i.first);
            if (val > 0)
            {
                ret.add(std::make_pair(i.first, i.second + val));
            }
        }
        return ret;
    }

    // returns a vector of all elements, present in both this and rhs
    std::vector<std::string> intersectionAsVector(const Dictionary& rhs) const
    {
        std::vector<std::string> ret;
        for (auto& i : _data)
        {
            if (rhs.getVal(i.first)) ret.push_back(i.first);
        }
        return ret;
    }



private:
    std::map<std::string, size_t> _data;    // data member
};


//=============================================================================
// helper functions
//=============================================================================

//-----------------------------------------------------------------------------
// takes two dictionaries and creates a new one containing words from both,
// summing all the word counts where a word has been entered in both
//-----------------------------------------------------------------------------
Dictionary combine(const Dictionary& lhs, const Dictionary& rhs)
{
    Dictionary ret = lhs;
    ret.join(rhs);
    return ret;
}

//-----------------------------------------------------------------------------
// takes two dictionaries and creates a new one containing words found in both,
// summing all the word counts
//-----------------------------------------------------------------------------
Dictionary intersection(const Dictionary& lhs, const Dictionary& rhs)
{
    return lhs.intersection(rhs);
}

//-----------------------------------------------------------------------------
// takes two dictionaries and creates a new one containing words found
// in one but not the other
//-----------------------------------------------------------------------------
Dictionary exclusive(const Dictionary& lhs, const Dictionary& rhs)
{
    Dictionary ret = lhs.difference(rhs);
    ret.join(rhs.difference(lhs));
    return ret;
}


#endif // !GUARD_DICTIONARY_H
