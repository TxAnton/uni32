#ifndef L_SYSTEM_H
#define L_SYSTEM_H

#include<string>
#include<map>
#include<vector>

typedef std::map<char,std::string> l_rules;

class L_system
{
private:

    std::string axiome;
    l_rules rule_set;
    std::string state;
    size_t iters;


public:
    L_system();



    void reset(const std::string &axiome);
    void reset();
    void clearRules();
    void addRule(l_rules);
    void addRule(char c, std::string s);
    void iterate(size_t n);
    std::string getState() const;
};

#endif // L_SYSTEM_H
