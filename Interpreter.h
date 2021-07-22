#ifndef PROJECT1_INTERPRETER_H
#define PROJECT1_INTERPRETER_H
#include "DatalogProgram.h"
#include "Database.h"
#include "Relation.h"
#include "Predicate.h"
#include <iostream>
#include <string>

class Interpreter {
private:
    DatalogProgram myProgram;
    Database myDatabase;

public:
    Interpreter(DatalogProgram newProgram){myProgram = newProgram;}

    void Interpret();

    Relation evaluatePredicate(Predicate p);

};

#endif //PROJECT1_INTERPRETER_H
