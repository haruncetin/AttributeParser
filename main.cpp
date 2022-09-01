#include <cmath>
#include <cstdio>
#include <vector>
#include <map>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <regex>

using namespace std;


inline string trim(string& str, char delim)
{
    str.erase(str.find_last_not_of(delim)+1);
    str.erase(0, str.find_first_not_of(delim));
    return str;
}

vector<string> split_r(string &str, const regex rx = regex{"\\s+"}){
    sregex_token_iterator it(str.begin(), str.end(), rx, -1);
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

int main() {

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
            stringstream ss(line);
            ss >> tag;
            // while(ss >> attr >> ch >> val) {
            while(ss >> attrs) {
                auto r = split_r(attrs, regex{"=\""});
                string key = r.at(0), val = r.at(1);
                maps[tag][key] = trim(val, '"');
            }
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
