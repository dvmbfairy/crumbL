#include "AstAssign.h"

AstAssign* AstAssign::make(AstIdentifier* id, Expression* val, bool lazy)
{
	return new AstAssign(id, val, lazy);
}


AstAssign::AstAssign(AstIdentifier* id, Expression* val, bool lazy)
{
  this->et = AST_ASSIGN;
  this->id = id;
  this->val = val;
  this->lazy = lazy;
  this->hash_c = 1 + id->get_hash() + 6*val->get_hash() + 31*lazy;
}

string AstAssign::to_string(int d)
{
  string res =  get_depth(d) + (lazy ? "LAZY ASSIGN:" : "ASSIGN:");
  res += id->to_string(d+1);
  res +=  get_depth(d) + "VAL:\n";
  res +=  val->to_string(d+1);
  return res;
}

string AstAssign::to_value()
{
  return (lazy ? "lazy " : "") + id->to_value() + " = " + val->to_value() + ";";
}



AstIdentifier* AstAssign::get_id()
{
    return id;
}

Expression* AstAssign::get_val()
{
    return val;
}

bool AstAssign::is_lazy()
{
    return lazy;
}

Expression* AstAssign::substitute(Expression* e1, Expression* e2)
{
	//avoid capture of bound variable
	if(e1 == id) return this;
	Expression* _new_id = id->substitute(e1, e2);
	assert(_new_id->get_type() == AST_IDENTIFIER);
	AstIdentifier* new_id = static_cast<AstIdentifier*>(_new_id);
	Expression* new_val = val->substitute(e1, e2);
	return AstAssign::make(new_id, new_val, lazy);
}

bool AstAssign::operator==(const Expression& other)
{
	if(other.get_type() != AST_ASSIGN) return false;
	AstAssign& l = (AstAssign&) other;
	return id == l.id && val == l.val && lazy == l.lazy;
}
