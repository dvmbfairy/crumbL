#include "AstParameterList.h"


AstParameterList* AstParameterList::make(AstIdentifier* id)
{
	AstParameterList* l = new AstParameterList(id);
	Expression* res = get_exp(l);
	assert(res->get_type() == AST_PARAMETER_LIST);
	return static_cast<AstParameterList*>(res);
}

AstParameterList* AstParameterList::make()
{
	AstParameterList* l = new AstParameterList();
	Expression* res = get_exp(l);
	assert(res->get_type() == AST_PARAMETER_LIST);
	return static_cast<AstParameterList*>(res);
}

AstParameterList* AstParameterList::make(vector<AstIdentifier*> & ids)
{
	AstParameterList* l = new AstParameterList(ids);
	Expression* res = get_exp(l);
	assert(res->get_type() == AST_PARAMETER_LIST);
	return static_cast<AstParameterList*>(res);
}


AstParameterList::AstParameterList(AstIdentifier* id)
{
	ids.push_back(id);
	this->et = AST_PARAMETER_LIST;
	compute_hash();

}

AstParameterList::AstParameterList()
{
	this->et = AST_PARAMETER_LIST;
	compute_hash();
}



AstParameterList::AstParameterList(vector<AstIdentifier*> & ids)
{
	this->ids = ids;
	this->et = AST_PARAMETER_LIST;
	compute_hash();
}

string AstParameterList::to_string(int d)
{
	  string res =  get_depth(d) + "ID LIST\n";
	  for(vector<AstIdentifier*>::iterator it = ids.begin(); it != ids.end(); it++)
	  {
	      res += (*it)->to_string(d+1);
	  }
	  return res;
}

string AstParameterList::to_value()
{
	  string res;
	  for(vector<AstIdentifier*>::iterator it = ids.begin(); it != ids.end();)
	  {
	      res += (*it)->to_value();
	      it++;
	      if(it != ids.end()) res += ", ";
	  }
	  return res;
}


const vector<AstIdentifier*> & AstParameterList::get_ids()
{
	return ids;
}


AstParameterList* AstParameterList::append_id(AstIdentifier* id)
{
	vector<AstIdentifier*> new_ids = ids;
	new_ids.push_back(id);
	return AstParameterList::make(new_ids);
}

Expression* AstParameterList::substitute(Expression* e1, Expression* e2)
{


	vector<AstIdentifier*> new_ids;
	bool changed = false;
	for(vector<AstIdentifier*>::iterator it = ids.begin(); it!= ids.end(); it++)
	{
		AstIdentifier* id = *it;
		Expression* _new_id = id->substitute(e1, e2);
		assert(_new_id->get_type() == AST_IDENTIFIER);
		AstIdentifier* new_id = static_cast<AstIdentifier*>(_new_id);
		new_ids.push_back(new_id);
		if(id != new_id) changed = true;
	}
	if(!changed) return this;
	return AstParameterList::make(new_ids);
}

bool AstParameterList::operator==(const Expression& other)
{
	if(other.get_type() != AST_PARAMETER_LIST) return false;
	AstParameterList& l = (AstParameterList&) other;
	return ids == l.ids;


}

void AstParameterList::compute_hash()
{
	this->hash_c = 0;
	for(vector<AstIdentifier*>::iterator it = ids.begin(); it!= ids.end(); it++)
	{
		AstIdentifier* id = *it;
		hash_c += id->get_hash();
	}
	this->hash_c*=3;
}

