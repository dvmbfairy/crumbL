#include "AstCallList.h"


AstCallList* AstCallList::make(Expression* expr)
{
	AstCallList* l = new AstCallList(expr);
	Expression* res = get_exp(l);
	assert(res->get_type() == AST_CALL_LIST);
	return static_cast<AstCallList*>(res);
}

AstCallList* AstCallList::make()
{
	AstCallList* l = new AstCallList();
	Expression* res = get_exp(l);
	assert(res->get_type() == AST_CALL_LIST);
	return static_cast<AstCallList*>(res);
}

AstCallList* AstCallList::make(vector<Expression*> & exprs)
{
	AstCallList* l = new AstCallList(exprs);
	Expression* res = get_exp(l);
	assert(res->get_type() == AST_CALL_LIST);
	return static_cast<AstCallList*>(res);
}


AstCallList::AstCallList(Expression* expr)
{
	exprs.push_back(expr);
	this->et = AST_CALL_LIST;
	compute_hash();

}

AstCallList::AstCallList()
{
	this->et = AST_CALL_LIST;
	compute_hash();
}



AstCallList::AstCallList(vector<Expression*> & exprs)
{
	this->exprs = exprs;
	this->et = AST_CALL_LIST;
	compute_hash();
}

string AstCallList::to_string(int d)
{
	  string res =  get_depth(d) + "CALL LIST:\n";
	  for(vector<Expression*>::iterator it = exprs.begin(); it != exprs.end(); it++)
	  {
	      res += (*it)->to_string(d+1);
	  }
	  return res;
}

string AstCallList::to_value()
{
	  string res;
	  for(vector<Expression*>::iterator it = exprs.begin(); it != exprs.end();)
	  {
	      res += (*it)->to_value();
	      it++;
	      if(it != exprs.end()) res += ", ";
	  }
	  return res;
}


const vector<Expression*> & AstCallList::get_exprs()
{
	return exprs;
}


AstCallList* AstCallList::append_expr(Expression* expr)
{
	vector<Expression*> new_exprs = exprs;
	new_exprs.push_back(expr);
	return AstCallList::make(new_exprs);
}

Expression* AstCallList::substitute(Expression* e1, Expression* e2)
{


	vector<Expression*> new_exprs;
	bool changed = false;
	for(vector<Expression*>::iterator it = exprs.begin(); it!= exprs.end(); it++)
	{
		Expression* expr = *it;
		Expression* _new_expr = expr->substitute(e1, e2);
		assert(_new_expr->get_type() == AST_IDENTIFIER);
		Expression* new_expr = static_cast<Expression*>(_new_expr);
		new_exprs.push_back(new_expr);
		if(expr != new_expr) changed = true;
	}
	if(!changed) return this;
	return AstCallList::make(new_exprs);
}

bool AstCallList::operator==(const Expression& other)
{
	if(other.get_type() != AST_CALL_LIST) return false;
	AstCallList& l = (AstCallList&) other;
	return exprs == l.exprs;


}

void AstCallList::compute_hash()
{
	this->hash_c = 0;
	for(vector<Expression*>::iterator it = exprs.begin(); it!= exprs.end(); it++)
	{
		Expression* expr = *it;
		hash_c += expr->get_hash();
	}
	this->hash_c*=3;
}

