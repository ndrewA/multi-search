#include "Tree.h"

#include <queue>
#include <stack>

Tree::Tree(const std::unordered_set<std::string>& allWords)
{
    makeTrie(allWords);
    makeFailure(root, root);
    makeDictionary();
    printTree(root);
}

std::unordered_map<std::string, int> Tree::findFreq(const std::string& str)
{
    std::unordered_map<std::string, int> freq;

    std::shared_ptr<Node> curNode = root;

    for(auto curLetter : str)
    {
        while(curNode->children.find(curLetter) == curNode->children.end() && curNode != root)
            curNode = curNode->failure;

        if(curNode->children.find(curLetter) != curNode->children.end())
            curNode = curNode->children[curLetter];

        if(!curNode->word.empty())
            ++freq[curNode->word];

        std::shared_ptr<Node> dictionaryIter = curNode->dictionary;

        while(dictionaryIter)
        {
            ++freq[dictionaryIter->word];
            dictionaryIter = dictionaryIter->dictionary;
        }
    }

    return freq;
}

void Tree::makeTrie(const std::unordered_set<std::string>& allWords)
{
    root = std::make_shared<Node>();

    for(const auto& curWord : allWords)
    {
        std::shared_ptr<Node> curNode = root;

        for(const auto& curLetter : curWord)
        {
            if(curNode->children.find(curLetter) == curNode->children.end())
                curNode->children.emplace(curLetter, std::make_shared<Node>(curLetter));

            curNode = curNode->children[curLetter];
        }
        curNode->word = curWord;
    }
}

void Tree::makeFailure(std::shared_ptr<Node> curNode, std::shared_ptr<Node> curFailure)
{
    if(curNode == curFailure)
        curNode->failure = root;
    else
        curNode->failure = curFailure;

    for(const auto [curLetter, child] : curNode->children)
    {
        if(curNode == root) {

            makeFailure(child, root);

        } else {

            if(curFailure->children.find(curLetter) == curFailure->children.end()) {

                if(root->children.find(curLetter) != root->children.end())
                    makeFailure(child, root->children[curLetter]);
                else
                    makeFailure(child, root);

            } else {

                makeFailure(child, curFailure->children[curLetter]);
            }
        }
    }
}

void Tree::makeDictionary()
{
    std::queue<std::shared_ptr<Node>> openSet;

    for(const auto [curLetter, curChild] : root->children)
        openSet.push(curChild);

    while(!openSet.empty())
    {
        std::shared_ptr<Node> curNode = openSet.front();
        openSet.pop();

        if(curNode->dictionary == nullptr)
        {
            std::stack<std::shared_ptr<Node>> searchIter;
            searchIter.push(curNode);
            searchIter.push(curNode->failure);

            while(searchIter.top() != root)
            {
                if(!searchIter.top()->word.empty())
                {
                    std::shared_ptr<Node> dictionaryIter = searchIter.top();

                    while(!searchIter.empty())
                    {
                        if(searchIter.top()->word != dictionaryIter->word)
                            searchIter.top()->dictionary = dictionaryIter;

                        searchIter.pop();
                    }

                    break;

                } else {

                    searchIter.push(searchIter.top()->failure);
                }
            }
        }

        for(const auto [curLetter, curChild] : curNode->children)
            openSet.push(curChild);
    }
}

void Tree::printTree(const std::shared_ptr<Node>& curNode)
{
    if(curNode == root)
        std::cout << "ROOT\n";

    else if(curNode->failure == root)
        std::cout << curNode->letter << " | ROOT\n";

    else if(curNode->dictionary)
        std::cout << curNode->letter << " | " << curNode->failure->letter << " | " << curNode->dictionary->word << '\n';

    else
        std::cout << curNode->letter << " | " << curNode->failure->letter << '\n';

    for(const auto &[curLetter, curChild] : curNode->children)
        printTree(curChild);
}
