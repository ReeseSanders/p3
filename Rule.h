#ifndef PROJECT1_RULE_H
#define PROJECT1_RULE_H
#include "Token.h"
#include "Predicate.h"
#include <vector>

class Rule {
private:
    Predicate headPredicate;
    std::vector<Predicate> followingPred;

public:
    Rule(){}

    void AddHeadPredicate(Predicate toAdd);

    void AddFollowingPred(Predicate toAdd);

    std::string ToString();


};

#endif //PROJECT1_RULE_H
