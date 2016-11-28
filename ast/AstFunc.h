#ifndef AST_FUNC_H_
#define AST_FUNC_H_
 
#include "Expression.h"
#include "AstIdentifier.h"
#include "AstParameterList.h"
 
class AstFunc:public Expression
{
private:
  AstIdentifier* formal;
  Expression* body;
  AstFunc(AstIdentifier* formals, Expression* body);
public:
  static AstFunc* make(AstIdentifier* formal, Expression* body);
  static AstFunc* make(AstParameterList* formal, Expression* body);
  virtual string to_string(int d = 0);
  virtual string to_value();
  Expression* get_body();
  AstIdentifier* get_formal();
  virtual Expression* substitute(Expression* e1,
  	        		  Expression* e2);
  virtual bool operator==(const Expression& other);
  
  
};
 
 
#endif /* AST_FUNC_H_ */
