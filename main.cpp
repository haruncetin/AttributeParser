#include <cmath>
#include <cstdio>
#include <vector>
#include <map>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <regex>

using namespace std;

class Node {
private:
    string _tag;
    map<string, string> _attrs;
    vector<Node *> _childs;

    Node _search(Node *node, string tag) {
        
        if(node->getTag().compare(tag) == 0) {
            return *node;
        } 
        
        for(Node *child : node->getChildren()) {
            _search(child, tag);
        }
    }

public:
    Node(string tag) : _tag(tag) {};
    
    Node() {}

    void setTag(string tag) {
        _tag = tag;
    }

    string getTag() {
        return _tag;
    }

    void addChild(Node *node) {
        _childs.push_back(node);
    }

    // Node getChild(string tag) {
    //     vector<Node *> node;
    //     copy_if(_childs.begin(), _childs.end(), back_inserter(node), [&tag](Node _node) { return _node.getTag().compare(tag) == 0; });
    //     return *node.at(0);
    // }

    vector<Node *> getChildren() {
        return _childs;
    }

    void addAllAttributes(map<string, string> attrs) {
        _attrs = attrs;
    }

    map<string, string> getAllAttributes() {
        return _attrs;
    }
    
    void setAttribute(string attr, string val) {
        _attrs[attr] = val;
    }

    string getAttribute(string attr) {
        return _attrs.at(attr);
    }

    Node search(string tag) {
        return _search(this, tag);
    }

};

inline string trim(string& str, char delim)
{
    str.erase(str.find_last_not_of(delim)+1);
    str.erase(0, str.find_first_not_of(delim));
    return str;
}

vector<string> split_r(const string &str, const regex &re = regex{"\\s+"}){
    sregex_token_iterator it(str.begin(), str.end(), re, -1);
    sregex_token_iterator end;
    return {it, end};
}

vector<string> split(string &str, char d) {
    vector<string> v;
    string s;
    stringstream ss(str);
    while(getline(ss, s, d)) {
        v.push_back(s);
    }
    return v;
}

// map<string, map<string, string>>::iterator search(map<string, map<string, string>>::iterator begin, map<string, map<string, string>>::iterator end, string val) {
//     if(begin != end && begin->first != val) {
//         search(++begin, end, val);
//     }
//     return begin;
// }

map<string, string> parse_attributes(const string& str) {
    map<string, string> attr_map;

    regex re("(\\w+)\\s*=\\s*\"(.*?)\"");
    
    const vector<smatch> matches {
        sregex_iterator{str.cbegin(), str.cend(), re},
        sregex_iterator{}
    };

    for(auto m : matches) {
        attr_map[m.str(1)] = m.str(2);
    }

    return attr_map;
}

int main() {

    // parse_attributes("attr1 = \"Hello World\" attr2=\"Value2\" attr3   =  \"Value 3\"");

    Node root = Node("root");

    // root->addChild(Node("Tag1"));

    // string tagName = root->getChild("Tag1").getTag();

    // cout << tagName << endl;

    // return 0;

    int Q, N;
    scanf("%d %d", &N, &Q);
    
    map<string, map<string, string>> maps;
    
    Node *node, *temp;
    stack<Node *> parse_stack;
    
    parse_stack.push(&root);

    for(int i=0; i<N; i++) {
        char ch;
        string line, tag, attrs;
        getline(cin >> ws, line);
        if(line[0] == '<' && line[1] != '/' && line[line.size()-1] == '>') {
            line = trim(line, '<');
            line = trim(line, '>');
            stringstream(line) >> tag;
            // root->addChild(Node(tag));
            // root->getChild(tag).addAllAttributes(parse_attributes(line));
            // maps[tag] = parse_attributes(line);
            temp = new Node(tag);
            temp->addAllAttributes(parse_attributes(line));
            parse_stack.push(temp);
        } else {
            line = trim(line, '<');
            line = trim(line, '/');
            line = trim(line, '>');            
            stringstream(line) >> tag;
            if(parse_stack.top()->getTag().compare(tag) == 0) {
                temp = parse_stack.top();
                parse_stack.pop();
                node = parse_stack.top();
                node->addChild(temp);
            }
        }
    }
    
    Node found = root.search("e");
    if(!found.getTag().empty()) {
        cout << "Found: " << found.getTag() << endl;
    } else {
        cout << "Not found!" << endl;
    }

    return 0;


    cout << "maps.size() = " << maps.size() << endl;
    for(auto it = maps.begin(); it != maps.end(); it++){
        cout << it->first << endl;
        for (auto it2 = it->second.begin(); it2 != it->second.end(); it2++)
        {
            cout << it2->first << "->" << it2->second << endl;
        }
        
    }
    for(int i = 0; i < Q; i++) {
        string line, item, tag, attr;
        getline(cin >> ws, line);
        vector<string> path;
        for(string s : split(line, '.')) {
            for(string ss : split(s, '~')) {
                // cout << ss << ", ";
                path.push_back(ss);
            }
        }
        cout << endl;
        auto it = maps.begin();
        // cout << "Path: ";
        // for(int i = 0; i < path.size(); i++) {
        //     // cout << path[i] << (i < path.size() - 1 ? " -> " : string());
        //     if(i < path.size() - 1) {
        //         it = search(maps.begin(), maps.end(), path[i]);
        //         if(it->first.empty()){
        //             cout << "Not Found!"<< endl;
        //             break;
        //         }
        //     } else {
        //         string val = it->second[path[i]];
        //         if(!val.empty()) {
        //             cout << val << endl;
        //         } else {
        //             cout << "Not Found!" << endl;                    
        //         }
        //     }
        // }
        cout << endl;
    }
    
    return 0;
}
