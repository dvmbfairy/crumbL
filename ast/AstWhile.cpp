#include "AstWhile.h"

AstWhile* AstWhile::make(Expression* pred, Expression* do_exp)
{
	return new AstWhile(pred, do_exp);
}


AstWhile::AstWhile(Expression* pred, Expression* do_exp)
{
	this->et = AST_WHILE;
	this->pred = pred;
	this->do_exp = do_exp;

	this->hash_c = 5* pred->get_hash() +2*(do_exp == NULL ? 147 : do_exp->get_hash());


}




string AstWhile::to_string(int d)
{
  string res =  get_depth(d) + "WHILE""\n";
  res +=  get_depth(d) + "Predicate:\n";
  res += pred->to_string(d+1);
  res += get_depth(d) +  "Do:\n";
  res += do_exp == NULL ? "" : do_exp->program_to_string(d+1);
  return res;
}

string AstWhile::to_value()
{
  return "(while " + pred->to_value() + " do " + do_exp->to_value()+ ")";
}


Expression* AstWhile::AstWhile::get_pred()
{
	return pred;
}

Expression* AstWhile::AstWhile::get_do_exp()
{
	return do_exp;
}


Expression* AstWhile::substitute(Expression* e1,
        		  Expression* e2)
{
	if(e1 == this) return e2;
	Expression* new_pred = pred->substitute(e1, e2);
	Expression* new_do = do_exp->substitute(e1, e2);
	if(pred == new_pred && do_exp == new_do)
		return this;
	return AstWhile::make(new_pred, new_do);
}


bool AstWhile::operator==(const Expression& other)
{
	if(other.get_type() != AST_WHILE) return false;
	AstWhile& b = (AstWhile&) other;
	return pred == b.pred && do_exp == b.do_exp;
}


