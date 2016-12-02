#ifndef ASTPARAMETERLIST_H_
#define ASTPARAMETERLIST_H_
#include "AstIdentifier.h"

class AstParameterList:public Expression {
private:
	vector<pair<AstIdentifier*, bool>> ids;
	AstParameterList(AstIdentifier* id, bool lazy);
	AstParameterList();
	AstParameterList(vector<pair<AstIdentifier*, bool>> & ids);
public:
	static AstParameterList* make(AstIdentifier* id, bool lazy);
	static AstParameterList* make();
	static AstParameterList* make(vector<pair<AstIdentifier*, bool>> & ids);

	virtual string to_string(int d = 0);
	virtual string to_value();
	const vector<pair<AstIdentifier*, bool>> & get_ids();
	AstParameterList* append_id(AstIdentifier* id, bool lazy);
	virtual Expression* substitute(Expression* e1,
	        		  Expression* e2);
	virtual bool operator==(const Expression& other);
	void compute_hash();
};

#endif /* ASTPARAMETERLIST_H_ */
