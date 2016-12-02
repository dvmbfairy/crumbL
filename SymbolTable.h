
#ifndef SYMBOLTABLE_H_
#define SYMBOLTABLE_H_

class Expression;
class AstIdentifier;
#include <vector>
#include <map>

using namespace std;



class SymbolTable {
private:
	vector<map<AstIdentifier*, Expression*> > values;
	vector<map<AstIdentifier*, Expression*> > lazy_values;
public:
	SymbolTable();
	void push();
	void pop();
	void add(AstIdentifier* id, Expression* e);
	void add_lazy(AstIdentifier* id, Expression* e);
	void remove(AstIdentifier* id);
	void remove_lazy(AstIdentifier* id);
	pair<Expression*, bool> find(AstIdentifier* id);
	void print_contents();

};

#endif /* SYMBOLTABLE_H_ */
