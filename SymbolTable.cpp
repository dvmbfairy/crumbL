#include "SymbolTable.h"
#include "ast/expression.h"

SymbolTable::SymbolTable()
{


}


void SymbolTable::push()
{
	map<AstIdentifier*, Expression*> cur_map;
	map<AstIdentifier*, Expression*> lazy_cur_map;
	values.push_back(cur_map);
	lazy_values.push_back(lazy_cur_map);

}

pair<Expression*, bool> SymbolTable::find(AstIdentifier* id)
{

	for(int i = values.size()-1; i >= 0; i--) {
		map<AstIdentifier*, Expression*>& normal = values[i];
		map<AstIdentifier*, Expression*>& lazy = lazy_values[i];

		if(lazy.count(id) > 0) {
			pair<Expression*, bool> r;
			r.first = lazy[id];
			r.second = true;
			return r;
		}

		if(normal.count(id) > 0) {
			pair<Expression*, bool> r;
			r.first = normal[id];
			r.second = false;
			return r;
		}

		

	}

	pair<Expression*, bool> r;
	r.first = NULL;
	r.second = false;
	return r;

}


void SymbolTable::pop()
{
	if(values.size() == 0)
	{
		cout << "You can only pop from a symbol table that you have pushed on first"
				<< endl;
		assert(false);
	}
	values.pop_back();
	lazy_values.pop_back();
}

void SymbolTable::add(AstIdentifier* id, Expression* e)
{
	if(values.size() == 0)
	{
		cout << "You can only add to a symbol table that you have pushed on first"
				<< endl;
		assert(false);
	}
	values[values.size()-1][id] = e;
}

void SymbolTable::add_lazy(AstIdentifier* id, Expression* e)
{
	if(lazy_values.size() == 0)
	{
		cout << "You can only add to a symbol table that you have pushed on first"
				<< endl;
		assert(false);
	}
	lazy_values[lazy_values.size()-1][id] = e;
}

void SymbolTable::remove(AstIdentifier* id)
{
	if(values.size() == 0)
	{
		cout << "You can only remove from a symbol table that you have pushed on first"
				<< endl;
		assert(false);
	}
	values[values.size()-1].erase(id);
}

void SymbolTable::remove_lazy(AstIdentifier* id)
{
	if(lazy_values.size() == 0)
	{
		cout << "You can only remove from a symbol table that you have pushed on first"
				<< endl;
		assert(false);
	}
	lazy_values[lazy_values.size()-1].erase(id);
}

void SymbolTable::print_contents()
{
	cout << "******** Symbol Table ******** " << endl;
	int i = 0;
	for(vector<map<AstIdentifier*, Expression*> >::iterator it = values.begin();
				it != values.end(); it++, i++)
	{
		cout << "Bindings at level " << i <<  ":" << endl;
		map<AstIdentifier*, Expression*> & cur = *it;
		for(map<AstIdentifier*, Expression*>::iterator it2 = cur.begin();
				it2 != cur.end(); it2++) {
			cout << "\t" << it2->first->to_string(1) << "   -> " <<
					it2->second->to_string(1) << endl;
		}

	}
	cout << "******** ********* ******** " << endl;
}
