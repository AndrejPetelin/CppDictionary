#ifndef GUARD_DICTIONARY_H
#define GUARD_DICTIONARY_H

#include <algorithm>
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
        if (_dict.find(str) == _dict.end()) _dict[str] = 1;
        else _dict[str] += 1;
    }

    void add(const std::vector<std::string>& vec) { for (auto i : vec) add(i); }

    int find(const std::string& str) const
    {
        std::map<std::string, int>::const_iterator it = _dict.find(str);
        return (it != _dict.end()) ? it->second : 0;
    }

    std::vector<std::string> getWords() const
    {
        std::vector<std::string> ret;
        for (auto& i : _dict) ret.push_back(i.first);
        return ret;
    }

    std::vector<std::string> getWords(std::function<bool(const std::string&, const std::string&)> pred)
    {
        std::vector<std::string> ret = getWords();
        std::sort(ret.begin(), ret.end(), pred);
        return ret;
    }

private:
    std::map<std::string, int> _dict;
};


#endif // !GUARD_DICTIONARY_H
