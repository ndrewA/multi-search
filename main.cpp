#include "Tree.h"

int main()
{
    Tree tree({{"a"}, {"b"}, {"ab"}, {"ba"}, {"bab"}, {"aba"}, {"abab"}, {"baa"}});
    std::unordered_map<std::string, int> freq = tree.findFreq("aababaabaa");

    std::cout << "=============\n";

    for(const auto& f : freq)
        std::cout << f.first << ' ' << f.second << '\n';

    return 0;
}
