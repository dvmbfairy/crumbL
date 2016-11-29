#ifndef ASTCALLLIST_H_
#define ASTCALLLIST_H_

#include "Expression.h"

class AstCallList:public Expression {
private:
	vector<Expression*> exprs;
	AstCallList(Expression* expr);
	AstCallList();
	AstCallList(vector<Expression*> & exprs);
public:
	static AstCallList* make(Expression* expr);
	static AstCallList* make();
	static AstCallList* make(vector<Expression*> & exprs);

	virtual string to_string(int d = 0);
	virtual string to_value();
	const vector<Expression*> & get_exprs();
	AstCallList* append_expr(Expression* expr);
	virtual Expression* substitute(Expression* e1,
	        		  Expression* e2);
	virtual bool operator==(const Expression& other);
	void compute_hash();
};

#endif /* ASTCALLLIST_H_ */

