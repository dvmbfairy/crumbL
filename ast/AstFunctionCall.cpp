#include "AstFunctionCall.h"

AstFunctionCall::AstFunctionCall(AstIdentifier* name, AstCallList* call_list)
{
	this->et = AST_FUNCTION_CALL;
	this->name = name;
	this->call_list = call_list;
	this->hash_c = 70+ name->get_hash()*5 + call_list->get_hash()*2;
}

AstFunctionCall* AstFunctionCall::make(AstIdentifier* name, AstCallList* call_list)
{
	AstFunctionCall* t = new AstFunctionCall(name, call_list);
	Expression* res = get_exp(t);
	assert(res->get_type() == AST_FUNCTION_CALL);
	return static_cast<AstFunctionCall*>(res);
}

string AstFunctionCall::to_string(int d)
{
	string res = get_depth(d) + "FUNC CALL: " + name->to_string();
	res += call_list->to_string(d+1);
	return res;
}

string AstFunctionCall::to_value()
{
	return name->to_value() + "(" + call_list->to_value() + ")";
}

AstIdentifier* AstFunctionCall::get_name()
{
	return name;
}

AstCallList* AstFunctionCall::get_call_list()
{
	return call_list;
}

Expression* AstFunctionCall::substitute(Expression* e1, Expression* e2)
{
	if(this == e1) return e2;
	Expression* this_name = this->name->substitute(e1, e2);
	assert(this_name->get_type() == AST_IDENTIFIER);
	AstIdentifier* new_name = static_cast<AstIdentifier*>(this_name);
	Expression* this_call_list = this->call_list->substitute(e1, e2);
	assert(this_call_list->get_type() == AST_CALL_LIST);
	AstCallList* new_call_list = static_cast<AstCallList*>(this_call_list);
	if(this->name == new_name && this->call_list == new_call_list) return this;
	return  AstFunctionCall::make(new_name, new_call_list);
}

bool AstFunctionCall::operator==(const Expression& other)
{
	if(other.get_type() != AST_FUNCTION_CALL) return false;
	AstFunctionCall& l = (AstFunctionCall&) other;
	return (name == l.name && call_list == l.call_list);
}