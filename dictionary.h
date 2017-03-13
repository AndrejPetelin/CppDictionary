#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <algorithm>
#include <functional>
#include <map>
#include <vector>

template <typename T>
class Dictionary
{
public:
    typedef typename std::map<T, size_t>::iterator iterator;
    typedef typename std::map<T, size_t>::const_iterator const_iterator;
    typedef typename std::map<T, size_t>::reverse_iterator reverse_iterator;
    typedef typename std::map<T, size_t>::const_reverse_iterator const_reverse_iterator;

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
    void add(const T& str)
    {
        if (_data.find(str) == _data.end()) _data[str] = 1;
        else _data[str] += 1;
    }

    // add a vector of words or increment respective counters if word(s) there already
    void add(const std::vector<T>& vec) { for (auto i : vec) add(i); }

    void add(const std::pair<T, size_t> p)
    {
        if (getVal(p.first) == false) _data[p.first] = p.second;
        else _data[p.first] += p.second;
    }

    // find word and remove it
    void remove(const T& str)
    {
        iterator it = _data.find(str);
        if (it != end()) _data.erase(it);
    }

    // find each word in vector and remove it
    void remove(const std::vector<T>& vec) { for (auto& i : vec) remove(i); }

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
    int getVal(const T& str) const
    {
        const_iterator it = _data.find(str);
        return (it != _data.end()) ? it->second : 0;
    }

    std::pair<T, size_t> getPair(const T& str) const
    {
        const_iterator it = _data.find(str);
        return *it;
    }

    // get words as a vector of strings. Note that the order is "ASCII order"
    std::vector<T> asVector() const
    {
        std::vector<T> ret;
        for (auto& i : _data) ret.push_back(i.first);
        return ret;
    }

    // overload that returns a vector of strings from dictionary in order defined by
    // the provided predicate function (lambda, named function by pointer)
    std::vector<T> asVector(std::function<bool(T, T)> predicate) const
    {
        std::vector<T> ret = asVector();
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
    std::vector<T> differenceAsVector(const Dictionary& rhs) const
    {
        std::vector<T> ret;
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
    std::vector<T> intersectionAsVector(const Dictionary& rhs) const
    {
        std::vector<T> ret;
        for (auto& i : _data)
        {
            if (rhs.getVal(i.first)) ret.push_back(i.first);
        }
        return ret;
    }



private:
    std::map<T, size_t> _data;    // data member
};


//=============================================================================
// helper functions
//=============================================================================

//-----------------------------------------------------------------------------
// takes two dictionaries and creates a new one containing words from both,
// summing all the word counts where a word has been entered in both
//-----------------------------------------------------------------------------
template <typename T>
Dictionary<T> combine(const Dictionary<T>& lhs, const Dictionary<T>& rhs)
{
    Dictionary<T> ret = lhs;
    ret.join(rhs);
    return ret;
}

//-----------------------------------------------------------------------------
// takes two dictionaries and creates a new one containing words found in both,
// summing all the word counts
//-----------------------------------------------------------------------------
template <typename T>
Dictionary<T> intersection(const Dictionary<T>& lhs, const Dictionary<T>& rhs)
{
    return lhs.intersection(rhs);
}

//-----------------------------------------------------------------------------
// takes two dictionaries and creates a new one containing words found
// in one but not the other
//-----------------------------------------------------------------------------
template <typename T>
Dictionary<T> exclusive(const Dictionary<T>& lhs, const Dictionary<T>& rhs)
{
    Dictionary<T> ret = lhs.difference(rhs);
    ret.join(rhs.difference(lhs));
    return ret;
}

#endif // DICTIONARY_H
