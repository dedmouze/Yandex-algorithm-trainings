﻿#include <unordered_set>
#include <iostream>
#include <vector>
#include <string>
#include <map>

class node
{
public:
    std::string key;
    std::vector<node*> children;
};

void connect_nodes(std::map<std::string, std::pair<node, int>>& map, const std::string children, const std::string parent)
{
    map[parent].first.children.push_back(&map[children].first);
}

int count_children(std::map<std::string, std::pair<node, int>>& map, const std::string root)
{
    if (map[root].first.children.size() == 0) return 0;

    int ancestor_count = map[root].first.children.size();
    for (int i = 0; i < map[root].first.children.size(); ++i)
        ancestor_count += count_children(map, map[root].first.children[i]->key);

    map[root].second = ancestor_count;

    return ancestor_count;
}

int main()
{
    int N;
    std::cin >> N;

    std::string children, parent;
    std::vector<std::string> names;
    std::unordered_set<std::string> children_set;
    std::map<std::string, std::pair<node, int>> map;
    for (int i = 0; i < N - 1; ++i)
    {
        std::cin >> children >> parent;
        children_set.insert(children);
        if (!map.count(children))
        {
            map[children] = {{ children, std::vector<node*>() }, 0 };
            names.push_back(children);
        }
        if (!map.count(parent))
        {
            map[parent] = { { parent, std::vector<node*>() }, 0 };
            names.push_back(parent);
        }

        connect_nodes(map, children, parent);
    }

    std::string root = "";
    for (int i = 0; i < names.size(); ++i)
    {
        if (!children_set.count(names[i]))
        {
            root = names[i];
            break;
        }
    }

    count_children(map, root);

    for (auto& [name, count] : map) std::cout << name << " " << count.second << std::endl;
}
