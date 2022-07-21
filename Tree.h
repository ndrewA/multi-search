#ifndef TREE_H
#define TREE_H

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <memory>

#include <iostream>

struct Node
{
    char letter;
    std::string word;
    std::unordered_map<char, std::shared_ptr<Node>> children;
    std::shared_ptr<Node> failure;
    std::shared_ptr<Node> dictionary;
    Node() { }
    Node(char c) : letter(c) { }
};

class Tree
{
    private:
        std::shared_ptr<Node> root;

    public:
        Tree(const std::unordered_set<std::string>& allWords);
        ~Tree() { }

        std::unordered_map<std::string, int> findFreq(const std::string& str);

    private:
        void makeTrie(const std::unordered_set<std::string>& allWords);
        void makeFailure(std::shared_ptr<Node> curNode, std::shared_ptr<Node> curFailure);
        void makeDictionary();

        void printTree(const std::shared_ptr<Node>& curNode);
};

#endif // TREE_H
