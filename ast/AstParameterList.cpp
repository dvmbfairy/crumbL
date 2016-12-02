#include "AstParameterList.h"


AstParameterList* AstParameterList::make(AstIdentifier* id, bool lazy)
{
	AstParameterList* l = new AstParameterList(id, lazy);
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

AstParameterList* AstParameterList::make(vector<pair<AstIdentifier*, bool>> & ids)
{
	AstParameterList* l = new AstParameterList(ids);
	Expression* res = get_exp(l);
	assert(res->get_type() == AST_PARAMETER_LIST);
	return static_cast<AstParameterList*>(res);
}


AstParameterList::AstParameterList(AstIdentifier* id, bool lazy)
{
	ids.push_back(make_pair(id, lazy));
	this->et = AST_PARAMETER_LIST;
	compute_hash();

}

AstParameterList::AstParameterList()
{
	this->et = AST_PARAMETER_LIST;
	compute_hash();
}



AstParameterList::AstParameterList(vector<pair<AstIdentifier*, bool>> & ids)
{
	this->ids = ids;
	this->et = AST_PARAMETER_LIST;
	compute_hash();
}

string AstParameterList::to_string(int d)
{
	  string res =  get_depth(d) + "ID LIST\n";
	  for(vector<pair<AstIdentifier*, bool>>::iterator it = ids.begin(); it != ids.end(); it++)
	  {
              AstIdentifier* id = (*it).first;
              bool lazy = (*it).second;
	      res += get_depth(d+1) + (lazy ? "lazy " : "") + id->to_value() + "\n";
	  }
	  return res;
}

string AstParameterList::to_value()
{
	  string res;
	  for(vector<pair<AstIdentifier*, bool>>::iterator it = ids.begin(); it != ids.end();)
	  {
              AstIdentifier* id = (*it).first;
              bool lazy = (*it).second;
	      res += (lazy ? "lazy " : "") + id->to_value();
	      it++;
	      if(it != ids.end()) res += ", ";
	  }
	  return res;
}


const vector<pair<AstIdentifier*, bool>> & AstParameterList::get_ids()
{
	return ids;
}


AstParameterList* AstParameterList::append_id(AstIdentifier* id, bool lazy)
{
	vector<pair<AstIdentifier*, bool>> new_ids = ids;
	new_ids.push_back(make_pair(id, lazy));
	return AstParameterList::make(new_ids);
}

Expression* AstParameterList::substitute(Expression* e1, Expression* e2)
{


	vector<pair<AstIdentifier*, bool>> new_ids;
	bool changed = false;
	for(vector<pair<AstIdentifier*, bool>>::iterator it = ids.begin(); it!= ids.end(); it++)
	{
		AstIdentifier* id = (*it).first;
		Expression* _new_id = id->substitute(e1, e2);
		assert(_new_id->get_type() == AST_IDENTIFIER);
		AstIdentifier* new_id = static_cast<AstIdentifier*>(_new_id);
		new_ids.push_back(make_pair(new_id, (*it).second));
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
	for(vector<pair<AstIdentifier*, bool>>::iterator it = ids.begin(); it!= ids.end(); it++)
	{
		AstIdentifier* id = (*it).first;
                bool lazy = (*it).second;
		hash_c += (lazy ? 31 : 1) * id->get_hash();
	}
	this->hash_c*=3;
}

