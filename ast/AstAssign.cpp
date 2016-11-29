#include "AstAssign.h"

AstAssign* AstAssign::make(AstIdentifier* id, Expression* val)
{
	AstAssign* l = new AstAssign(id, val);
	Expression* res = get_exp(l);
	assert(res->get_type() == AST_ASSIGN);
	return static_cast<AstAssign*>(res);
}


AstAssign::AstAssign(AstIdentifier* id, Expression* val)
{
  this->et = AST_ASSIGN;
  this->id = id;
  this->val = val;
  this->hash_c = 1 + id->get_hash() + 6*val->get_hash();
}

string AstAssign::to_string(int d)
{
  string res =  get_depth(d) + "ASSIGN:";
  res += id->to_string(d+1);
  res +=  get_depth(d) + "VAL:\n";
  res +=  val->to_string(d+1);
  return res;
}

string AstAssign::to_value()
{
  return id->to_value() + " = " + val->to_value() + ";";
}



AstIdentifier* AstAssign::get_id()
{
    return id;
}

Expression* AstAssign::get_val()
{
    return val;
}

Expression* AstAssign::substitute(Expression* e1, Expression* e2)
{
	//avoid capture of bound variable
	if(e1 == id) return this;
	Expression* _new_id = id->substitute(e1, e2);
	assert(_new_id->get_type() == AST_IDENTIFIER);
	AstIdentifier* new_id = static_cast<AstIdentifier*>(_new_id);
	Expression* new_val = val->substitute(e1, e2);
	return AstAssign::make(new_id, new_val);
}

bool AstAssign::operator==(const Expression& other)
{
	if(other.get_type() != AST_ASSIGN) return false;
	AstAssign& l = (AstAssign&) other;
	return id == l.id && val == l.val;
}
