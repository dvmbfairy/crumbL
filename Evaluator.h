

#ifndef EVALUATOR_H_
#define EVALUATOR_H_

class Expression;
class AstBinOp;
class AstUnOp;
class AstFunc;
#include "SymbolTable.h"
#include "ast/expression.h"
class Evaluator {
private:
	SymbolTable sym_tab;
	SymbolTable func_tab;

	int c;
public:
	Evaluator();
	Expression* eval(Expression* e);
	Expression* eval_binop(AstBinOp* b);
	Expression* eval_unop(AstUnOp* b);
	Expression* eval_func(AstFunc* fun);
};

#endif /* EVALUATOR_H_ */
