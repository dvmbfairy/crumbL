

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
	SymbolTable func_ret_table;
	SymbolTable func_param_table;
	SymbolTable func_body_table;

	int c;
	bool lazy_i;
public:
	Evaluator();
	Expression* eval(Expression* e);
	Expression* eval_binop(AstBinOp* b);
	Expression* eval_unop(AstUnOp* b);
	Expression* eval_func(AstFunc* fun);
};

#endif /* EVALUATOR_H_ */
