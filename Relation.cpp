#include "Relation.h"
#include <sstream>
#include <map>
#include <set>

Relation::Relation(std::string toName, Header toHeader){
    name = toName;
    myHeader = toHeader;
    isQuery = false;

    //for test
    /*std::vector<std::string> vect{"hello", "Oh No", "Goodbye"};
    std::vector<std::string> vecta{"Stop", "Boo", "Left"};
    Tuple test(vect);
    Tuple testa(vecta);
    addTuple(test);
    addTuple(testa);
    toString();*/
}

void Relation::addTuple(Tuple toAdd){
    myTuples.insert(toAdd);
}

std::string Relation::toString(){
    std::string relation = "";
    if (isQuery == false) {
        for (Tuple t : myTuples) {
            relation += "  ";
            for (int i = 0; i < t.getSize(); i++) {
                relation += myHeader.at(i) + "=" + t.at(i);
                if ((i + 1) != t.getSize()) {
                    relation += ", ";
                } else {
                    relation += "\n";
                }
            }
        }
    } else {
        for (Tuple t : myTuples) {
            relation += "  ";
            for (int i = 0; i < t.getSize(); i++) {
                relation += myHeader.atQ(i) + "=" + t.at(i);
                if ((i + 1) != t.getSize()) {
                    relation += ", ";
                } else {
                    relation += "\n";
                }
            }
        }

    }

    return relation;
}

Relation Relation::Evaluate(Predicate pred) {
    //std::cout << "In Relation::Evaluate" << std::endl;
    Header head;
    std::vector<std::string> pr = pred.getString();
    std::set<std::string> varCheck;
    std::vector<std::string> toH;
    for (unsigned int i = 0; i < pr.size(); i++){
        if (pr.at(i).at(0) != '\'') {
            varCheck.insert(pr.at(i));
        }
    }
    for (auto it = varCheck.begin(); it != varCheck.end(); it++){
        toH.push_back(*it);
    }
    head.add(pr);
    Relation toReturn(pred.getHead(), head);
    for (Tuple t : myTuples) {
        std::vector<std::string> p = pr;
        std::vector<std::string> headVecAdd;
        std::map<std::string, std::string> checker;
        for (unsigned int i = 0; i < p.size(); i++) {
            if (p.at(i).at(0) != '\'') {
                if (checker.find(p.at(i)) == checker.end()) {
                    headVecAdd.push_back(p.at(i));
                    checker.insert(std::pair<std::string, std::string>(p.at(i), t.at(i)));
                    p.at(i) = t.at(i);

                } else {
                    if (t.at(i) == checker.at(p.at(i))) {
                        p.at(i) = t.at(i);
                    } else {
                        p.at(i) = "error";
                    }
                }
            }
        }
        if(checker.empty()) {
            //std::cout << "Checker is empty" << std::endl;
        }
        if (p == t.GetVector()) {
            Tuple toAdd;
            std::vector<std::string> toTupple;
            for (auto c : headVecAdd) {
                toTupple.push_back(checker.at(c));
            }
            toAdd.add(toTupple);
            toReturn.addQHead(headVecAdd);
            toReturn.addTuple(toAdd);
        }
    }
    toReturn.QueryFlag();
    return toReturn;
}

void Relation::QueryFlag(){
    isQuery = true;
    std::vector<std::string> headVec = myHeader.GetHead();
    name = name + "(";
    for (unsigned int i = 0; i < headVec.size(); i++){
        name += headVec.at(i);
        if (i < headVec.size()-1) {
            name += ",";
        }
    }
    name += ")? ";
    if (myTuples.empty()) {
        name += "No";
    } else {
        name += "Yes(";
        name += std::to_string(myTuples.size());
        name += ")";
    }
}
