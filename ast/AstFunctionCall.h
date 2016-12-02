  #ifndef AST_FUNCTION_CALL_H_
  #define AST_FUNCTION_CALL_H_
  #include "Expression.h"
  #include "AstIdentifier.h"
  #include "AstCallList.h"
 
 class AstFunctionCall;

 class AstFunctionCall: public Expression
 {
   private:
      AstIdentifier* name;
      AstCallList* call_list;
      AstFunctionCall(AstIdentifier* name, AstCallList* call_list);
     
   public:
      static AstFunctionCall* make(AstIdentifier* name, AstCallList* call_list);
      virtual string to_string(int d = 0);
      virtual string to_value();
      AstIdentifier* get_name();
      AstCallList* get_call_list();
      virtual Expression* substitute(Expression* e1, Expression* e2);
      virtual bool operator==(const Expression& other);
 };
 
 
 #endif /* AST_FUNCTION_CALL_H_ */
