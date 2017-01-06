#ifndef GUARD_DICTIONARY_H
#define GUARD_DICTIONARY_H

#include <algorithm>
#include <cstdlib>
#include <functional>
#include <map>
#include <vector>
#include <string>

class Dictionary
{
public:
    Dictionary() = default;

    void add(const std::string& str)
    {
        if (_data.find(str) == _data.end()) _data[str] = 1;
        else _data[str] += 1;
    }

    void add(const std::vector<std::string>& vec) { for (auto i : vec) add(i); }
    
    void join(const Dictionary& rhs)
    {
        for (auto& i : rhs._data)
        {
            if (_data.find(i.first) != _data.end()) _data[i.first] += i.second;
            else _data[i.first] = i.second;
        }
    }

    int find(const std::string& str) const
    {
        std::map<std::string, size_t>::const_iterator it = _data.find(str);
        return (it != _data.end()) ? it->second : 0;
    }

    std::vector<std::string> getWords() const
    {
        std::vector<std::string> ret;
        for (auto& i : _data) ret.push_back(i.first);
        return ret;
    }

    std::vector<std::string> getWords(std::function<bool(const std::string&, const std::string&)> predicate)
    {
        std::vector<std::string> ret = getWords();
        std::sort(ret.begin(), ret.end(), predicate);
        return ret;
    }

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

private:
    std::map<std::string, size_t> _data;
};

Dictionary combine(const Dictionary& lhs, const Dictionary& rhs)
{
    Dictionary ret = lhs;
    ret.join(rhs);
    return ret;
}


#endif // !GUARD_DICTIONARY_H
