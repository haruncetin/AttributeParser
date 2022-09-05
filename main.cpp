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
    Node *_found = NULL;

    Node* _search(Node *node, string tag) {
        
        if(node->getTag().compare(tag) == 0) {
            _found = node;
            return _found;
        }
        
        for(Node *child : node->getChildren()) {
            _search(child, tag);
        }
        return _found;
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

    Node* getChild(string tag) {
        for(Node *child: this->getChildren()) {
            if(child->getTag().compare(tag) == 0) {
                return child;
            }
        }
        return NULL;
    }

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
        return _attrs[attr];
    }

    Node* search(string tag) {
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

    Node root = Node("root");

    int Q, N;
    scanf("%d %d", &N, &Q);
   
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
    
    for(int i = 0; i < Q; i++) {
        string line;
        getline(cin >> ws, line);
        vector<string> path;
        for(string s : split(line, '.')) {
            for(string ss : split(s, '~')) {
                path.push_back(ss);
            }
        }
        cout << endl;
        
        Node *found;

        string attr = path[path.size()-1], tag = path[0];

        found = root.getChild(tag);
        if(!found) {
            cout << "Not Found!" << endl;
            continue;
        }
        for (int k = 1; k < path.size(); k++)
        {
            if(k < path.size() - 1) {
                if(!found) {
                    cout << "Not Found!" << endl;
                    break;
                } else {
                    string tag = path[k];
                    found = found->getChild(tag);
                    if(!found) {
                        cout << "Not Found!" << endl;
                        break;
                    }
                }
            } else {
                if(found->getAttribute(attr) != ""){
                    cout << found->getAttribute(attr) << endl;
                } else {
                    cout << "Not Found!" << endl;
                    break;
                }                
            }
        }
       
    }
    
    return 0;
}
