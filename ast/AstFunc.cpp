#include "AstFunc.h"


AstFunc* AstFunc::make(AstIdentifier* id, AstParameterList* params, Expression* body, Expression* ret)
{
	return new AstFunc(id, params, body, ret);
}
 

AstFunc::AstFunc(AstIdentifier* id, AstParameterList* params, Expression* body, Expression* ret)
{
  this->et = AST_FUNC;
  this->id = id;
  this->params = params;
  this->body = body;
  this->ret = ret;
  this->hash_c = 73+ params->get_hash()*9 + body->get_hash()*3;
}


string AstFunc::to_string(int d)
{ 
  string res =  get_depth(d) + "FUNC\n";
  res += get_depth(d) + "ID:\n";
  res += id->to_string(d+1);
  res +=  get_depth(d) + "PARAM LIST:\n";
  res += params->to_string(d+1);
  res += get_depth(d) +  "BODY:\n";
  res += body->program_to_string(d+1);
  res += get_depth(d) +  "RET:\n";
  res += ret->to_string(d+1);
  return res;
}

string AstFunc::to_value()
{
 return "func " + id->to_value() + "(" + params->to_value() + ") " + body->to_value() + " " + ret->to_value() + "; cnuf";
}

AstIdentifier* AstFunc::get_id()
{
	return id;
}

AstParameterList* AstFunc::get_params()
{
  return params;
}

Expression* AstFunc::get_body()
{
  return body;
}

Expression* AstFunc::get_ret()
{
	return ret;
}

Expression* AstFunc::substitute(Expression* e1, Expression* e2)
{
	//avoid \alpha capture
	if(e1 == this) return e2;
	Expression* new_id = id->substitute(e1, e2);
	assert(new_id->get_type() == AST_IDENTIFIER);
	AstIdentifier* this_id = static_cast<AstIdentifier*>(new_id);
	Expression* new_params = params->substitute(e1, e2);
	assert(new_params->get_type() == AST_PARAMETER_LIST);
	AstParameterList* this_params = static_cast<AstParameterList*>(new_params);
	Expression* new_body = body->substitute(e1, e2);
	Expression* new_ret = ret->substitute(e1, e2);
	if(id == this_id && params == this_params && body == new_body && ret == new_ret)
		return this;
	return AstFunc::make(this_id, this_params, new_body, new_ret);
}

bool AstFunc::operator==(const Expression& other)
{
	if(other.get_type() != AST_FUNC) return false;
	AstFunc& l = (AstFunc&) other;
	return (id == l.id && params == l.params && body == l.body && ret == l.ret);
}

