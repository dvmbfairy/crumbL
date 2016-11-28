#ifndef AST_ASSIGN_H_
#define AST_ASSIGN_H_

#include "Expression.h"
#include "AstIdentifier.h"

class AstAssign:public Expression
{
  private:
    AstIdentifier* id;
    Expression* val;
    AstAssign(AstIdentifier* id, Expression* val);
  public:
    static AstAssign* make(AstIdentifier* id, Expression* val);
    virtual string to_string(int d = 0);
    virtual string to_value();
    AstIdentifier* get_id();
    Expression* get_val();
    virtual Expression* substitute(Expression* e1,
    	        		  Expression* e2);
    virtual bool operator==(const Expression& other);
    
    
};

#endif /* AST_ASSIGN_H_ */
