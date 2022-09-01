#include <cmath>
#include <cstdio>
#include <vector>
#include <map>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <regex>

#define C_ALL(X) cbegin(X), cend(X)

using namespace std;


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

map<string, map<string, string>>::iterator search(map<string, map<string, string>>::iterator begin, map<string, map<string, string>>::iterator end, string val) {
    if(begin != end && begin->first != val) {
        search(++begin, end, val);
    }
    return begin;
}

map<string, string> parse_attributes(const string& str) {
    map<string, string> attr_map;

    regex re("(\\w+)\\s*=\\s*\"(.*?)\"");
    
    const vector<smatch> matches {
        sregex_iterator{str.cbegin(), str.cend(), re},
        sregex_iterator{}
    };

    for(auto m : matches) {
        // cout << m.str(1) << " = " << m.str(2) << endl;
        attr_map[m.str(1)] = m.str(2);
    }

    return attr_map;
}

int main() {

    // parse_attributes("attr1 = \"Hello World\" attr2=\"Value2\" attr3   =  \"Value 3\"");

    // return 0;

    int Q, N;
    scanf("%d %d", &N, &Q);
    
    map<string, map<string, string>> maps;
    for(int i=0; i<N; i++) {
        char ch;
        string line, tag, attrs;
        getline(cin >> ws, line);
        if(line[0] == '<' && line[1] != '/' && line[line.size()-1] == '>') {
            line = trim(line, '<');
            line = trim(line, '>');
            stringstream(line) >> tag;
            maps[tag] = parse_attributes(line);
        }
    }
    // cout << "maps.size() = " << maps.size() << endl;
    // for(auto it = maps.begin(); it != maps.end(); it++){
    //     cout << it->first << endl;
    //     for (auto it2 = it->second.begin(); it2 != it->second.end(); it2++)
    //     {
    //         cout << it2->first << "->" << it2->second << endl;
    //     }
        
    // }
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
        for(int i = 0; i < path.size(); i++) {
            // cout << path[i] << (i < path.size() - 1 ? " -> " : string());
            if(i < path.size() - 1) {
                it = search(maps.begin(), maps.end(), path[i]);
                if(it->first.empty()){
                    cout << endl;
                    cout << "Not Found!"<< endl;
                    break;
                }
            } else {
                string val = it->second[path[i]];
                if(!val.empty()) {
                    cout << endl;
                    cout << "Found: " << val << endl;
                } else {
                    cout << endl;
                    cout << "Not Found!" << endl;                    
                }
            }
        }
        cout << endl;
    }
    
    return 0;
}
