#include "AstFunc.h"


AstFunc* AstFunc::make(AstParameterList* formal, Expression* body)
{
	Expression* res = body;
	assert(formal->get_ids().size() > 0);
	for(vector<AstIdentifier*>::const_reverse_iterator it =
			formal->get_ids().rbegin(); it != formal->get_ids().rend();it++)
	{
		AstIdentifier* id = *it;
		res = AstFunc::make(id, res);
	}

	assert(res->get_type() == AST_FUNC);
	return static_cast<AstFunc*>(res);

}


AstFunc* AstFunc::make(AstIdentifier* formal, Expression* body)
{
	AstFunc* l = new AstFunc(formal, body);
	Expression* res = get_exp(l);
	assert(res->get_type() == AST_FUNC);
	return static_cast<AstFunc*>(res);
}


AstFunc::AstFunc(AstIdentifier* formal, Expression* body)
{
  this->et = AST_FUNC;
  this->formal = formal;
  this->body = body;
  this->hash_c = 73+ formal->get_hash()*9 + body->get_hash()*3;
}


string AstFunc::to_string(int d)
{
  string res =  get_depth(d) + "Func\n";
  res +=  get_depth(d) + "Formal:\n";
  res += formal->to_string(d+1);
  res += get_depth(d) +  "Body:\n";
  res += body->to_string(d+1);
  return res;
}
string AstFunc::to_value()
{
 return "lambda " + formal->to_value() + ". " + body->to_value();
}


Expression* AstFunc::get_body()
{
  return body;
}



AstIdentifier* AstFunc::get_formal()
{
  return formal;
}


Expression* AstFunc::substitute(Expression* e1, Expression* e2)
{
	//avoid \alpha capture
	if(e1 == formal) return this;
	Expression* _new_f = formal->substitute(e1, e2);
	assert(_new_f->get_type() == AST_IDENTIFIER);
	AstIdentifier* new_f = static_cast<AstIdentifier*>(_new_f);
	Expression* new_body = body->substitute(e1, e2);
	return AstFunc::make(new_f, new_body);

}

bool AstFunc::operator==(const Expression& other)
{
	if(other.get_type() != AST_FUNC) return false;
	AstFunc& l = (AstFunc&) other;
	return formal == l.formal && body == l.body;
}

