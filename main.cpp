#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <map>
#include <algorithm>

using namespace std;


template <typename It>
void printRange(It range_begin, It range_end)
{
    for (auto it = range_begin; it != range_end; it++)
    {
        cout << *it << " ";
    }

    cout << endl;
}

using map_it = map<string, int>::iterator;

template <>
void printRange<map_it>(map_it range_begin,map_it range_end)
{
    for (auto it = range_begin; it != range_end; it++)
    {
        cout << it->first << " " << it->second << endl;
    }

    cout << endl;
}

int main()
{
    vector<string> strs = {"Cstr1", "Astr1", "Bstr1", "Cstr2", "Astr2", "Cstr3"};
    auto result = find_if(strs.begin(), strs.end(), [](const string& s)
    {
        return s[0] == 'C';
    });

    if(result == strs.end())
    {
        cout << "no elements";
    }
    else
    {
        cout << *result;
    }
    cout << endl;

    printRange(strs.begin(), strs.end());
    printRange(strs[0].begin(), strs[0].end());

    printRange(begin(strs), end(strs));
    printRange(begin(strs[0]), end(strs[0]));
    cout << endl;

    // множества

    set<string> langs= {"Python", "C", "C++", "Java", "C#", "Js"};

    auto it = langs.find("C++");
    printRange(langs.begin(), it);
    printRange(it, langs.end());

    // словари

    map<string, int> m_langs = {
            {"Python", 27},
            {"C++", 35},
            {"C", 46},
            {"Java", 23},
            {"C#", 18},
            {"Js", 23}
    };

    printRange(m_langs.begin(), m_langs.end());




}
