#ifndef PROJECT1_RELATION_H
#define PROJECT1_RELATION_H
#include <iostream>
#include <set>
#include <string>
#include "Tuple.h"
#include "Header.h"
#include "Predicate.h"

class Relation {
private:
    std::set<Tuple> myTuples;
    std::string name;
    Header myHeader;
    bool isQuery;

public:
    Relation(std::string toName, Header toHeader);
    void addTuple(Tuple toAdd);
    std::string toString();
    Relation Evaluate(Predicate pred);
    std::string GetName(){return name;}
    void QueryFlag();
    void addQHead(std::vector<std::string> toAdd){myHeader.addQ(toAdd);}
};

#endif //PROJECT1_RELATION_H
