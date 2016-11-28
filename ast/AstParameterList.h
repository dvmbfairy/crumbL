#ifndef ASTPARAMETERLIST_H_
#define ASTPARAMETERLIST_H_
#include "AstIdentifier.h"

class AstParameterList:public Expression {
private:
	vector<AstIdentifier*> ids;
	AstParameterList(AstIdentifier* id);
	AstParameterList();
	AstParameterList(vector<AstIdentifier*> & ids);
public:
	static AstParameterList* make(AstIdentifier* id);
	static AstParameterList* make();
	static AstParameterList* make(vector<AstIdentifier*> & ids);

	virtual string to_string(int d = 0);
	virtual string to_value();
	const vector<AstIdentifier*> & get_ids();
	AstParameterList* append_id(AstIdentifier* id);
	virtual Expression* substitute(Expression* e1,
	        		  Expression* e2);
	virtual bool operator==(const Expression& other);
	void compute_hash();
};

#endif /* ASTPARAMETERLIST_H_ */
