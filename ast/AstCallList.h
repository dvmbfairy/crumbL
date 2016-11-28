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



// call_list: %empty {
//   $$ = AstCallList::make();
// }
// |
// expression
// {
//   $$ = AstCallList::make($1);
// }
// |
// call_list TOKEN_COMMA expression
// {
//   Expression* e = $1;
//   assert(e->get_type() == AST_CALL_LIST);
//   AstCallList* list = static_cast<AstCallList*>(e);
//   $$ = list->append_id($3);
// }

// |
// TOKEN_WHILE TOKEN_LPAREN conditional TOKEN_RPAREN TOKEN_DO program TOKEN_OB
// {
//   $$ = AstWhile::make($3, $6);
// }
// |
// TOKEN_FUNC TOKEN_IDENTIFIER TOKEN_LPAREN parameter_list TOKEN_RPAREN program TOKEN_RET expression TOKEN_SEMICOLON TOKEN_CNUF
// {
//   $$ = AstAssign::make(getIdentifier($2), getFunc($4, $6));
// }

// parameter_list: %empty {
//   $$ = AstParameterList::make();
// }
// |
// TOKEN_IDENTIFIER
// {
//   $$ = AstParameterList::make(getIdentifier($1));
// }
// |
// parameter_list TOKEN_COMMA TOKEN_IDENTIFIER
// {
//   Expression* e = $1;
//   assert(e->get_type() == AST_PARAMETER_LIST);
//   AstParameterList* list = static_cast<AstParameterList*>(e);
//   $$ = list->append_id(getIdentifier($3));
// }

