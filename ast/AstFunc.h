#ifndef AST_FUNC_H_
#define AST_FUNC_H_
 
#include "Expression.h"
#include "AstIdentifier.h"
#include "AstParameterList.h"
 
class AstFunc:public Expression
{
private:
  AstIdentifier* id;
  AstParameterList* params;
  Expression* body;
  Expression* ret;
  AstFunc(AstIdentifier* id, AstParameterList* params, Expression* body, Expression* ret);
public:
  static AstFunc* make(AstIdentifier* id, AstParameterList* params, Expression* body, Expression* ret);
  virtual string to_string(int d = 0);
  virtual string to_value();
  AstIdentifier* get_id();
  AstParameterList* get_params();
  Expression* get_body();
  Expression* get_ret();
  virtual Expression* substitute(Expression* e1,
  	        		  Expression* e2); 
  virtual bool operator==(const Expression& other);
  
  
};
 
 
#endif /* AST_FUNC_H_ */
