#ifndef ASTWHILE_H_
#define ASTWHILE_H_
#include "Expression.h"

class AstWhile:public Expression {
private:
	Expression* pred;
	Expression* do_exp;
	AstWhile(Expression* pred, Expression* do_exp);
public:
	static AstWhile* make(Expression* pred, Expression* do_exp);
	virtual string to_string(int d = 0);
	virtual string to_value();
	Expression* get_pred();
	Expression* get_do_exp();
	virtual Expression* substitute(Expression* e1,
	        		  Expression* e2);
	virtual bool operator==(const Expression& other);

};

#endif /* ASTWHILE_H_ */
