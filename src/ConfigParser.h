#pragma once

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <map>
#include <utility>
#include <algorithm> 

using namespace std;

// trim from start
static inline string &ltrim(string &s) {
    s.erase(s.begin(), find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace))));
    return s;
}

// trim from end
static inline string &rtrim(string &s) {
    s.erase(find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(), s.end());
    return s;
}

// trim from both ends
static inline string &trim(string &s) {
    return ltrim(rtrim(s));
}

typedef map<string, string> t_dict;


class Config {
    private:
        t_dict dict;
    public:
        Config(void);
        void setDefaults(void);
        void set(string key, string value);
        string get(string key);
        void print(ostream& stream = cout);
        void parseConfigFile(string path);
};
