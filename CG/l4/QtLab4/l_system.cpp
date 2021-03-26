#include "l_system.h"

void L_system::reset(const std::string &axiome)
{
    this->axiome = axiome;
    this->reset();
}

void L_system::reset()
{
    this->state = this->axiome;
    this->iters = 0;
}

void L_system::clearRules()
{
    this->rule_set.clear();
}

void L_system::addRule(char c, std::string s)
{
    rule_set[c] = s;
}

void L_system::iterate(size_t n)
{
    std::string newstate;
    for(size_t i = 0; i < n; i++){
        newstate = "";
        for(char c: this->state){
            if(this->rule_set.count(c)){
                newstate.append(rule_set.at(c));
            }else{
                newstate.push_back(c);
            }
        }
        this->iters++;
        this->state = newstate;
    }
}

std::string L_system::getState() const
{
    return state;
}

L_system::L_system()
{

}
