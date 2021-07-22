#include "Interpreter.h"
#include "Header.h"
#include "Tuple.h"

void Interpreter::Interpret(){
    //std::cout << "In Interpreter::Interpret()" << std::endl;
    std::vector<Predicate> schemes = myProgram.getScheme();
    std::vector<Predicate> facts = myProgram.getFacts();

    for (unsigned int i = 0; i < schemes.size(); i++) {
        std::string name = schemes.at(i).getHead();
        Header headAdd;
        headAdd.add(schemes.at(i).getString());
        Relation myRel(name, headAdd);
        myDatabase.insert(name, myRel);
    }

    for (unsigned int i = 0; i < facts.size(); i++) {
        Tuple newTup;
        newTup.add(facts.at(i).getString());
        myDatabase.add(facts.at(i).getHead(), newTup);
    }

    //std::cout << myDatabase.toString() << std::endl;

    std::vector<Predicate> query = myProgram.getQuery();
   // Relation eval = evaluatePredicate(query.at(0));
    //std::cout << eval.toString() << std::endl;
    for (unsigned int i = 0; i < query.size(); i++){
        //std::cout << query.at(i).ToString() << std::endl;
        Relation eval = evaluatePredicate(query.at(i));
        std::cout << eval.GetName() << std::endl << eval.toString();
    }
}

Relation Interpreter::evaluatePredicate(Predicate p){
    //std::cout << "Interpreter::evalutatePredicate()" << std::endl;
    Relation eval = myDatabase.getRelation(p.getHead());
    //std::cout << eval.toString() << std::endl;
    eval = eval.Evaluate(p);
    //std::cout << "Back to Interpreter::evalutatePredicate() from Relation::Evaluate()" << std::endl;
    //std::cout << eval.toString() << std::endl;
    return eval;

}