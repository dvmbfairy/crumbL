
#include "Evaluator.h"


/*
 * This skeleton currently only contains code to handle integer constants, print and read. 
 * It is your job to handle all of the rest of the L language.
 */





/*
 * Call this function to report any run-time errors
 * This will abort execution.
 */
void report_error(Expression* e, const string & s)
{
	cout << "Run-time error in expression " << e->to_value() << endl;
	cout << s << endl;
	exit(1);

}

/*
an expression is false if:
	integer 0
	string ""
	Nil

Otherwise, the expression is true.
*/

bool truthValue(Expression* e) {

	if(e->get_type() == AST_STRING) {
		AstString* i1 = static_cast<AstString*>(e);
		return i1->get_string() != "";

	}

	if(e->get_type() == AST_INT) {
		AstInt* i1 = static_cast<AstInt*>(e);
		return i1->get_int() != 0;
	}


	if(e->get_type() == AST_NIL) {
		return false;
	}


	return true;
}

Evaluator::Evaluator()
{
	sym_tab.push();
	func_ret_table.push();
	func_param_table.push();
	func_body_table.push();
	c = 0;

}

Expression* Evaluator::eval_binop(AstBinOp* b)
{

	Expression* e1 = b->get_first();
	Expression* e2 = b->get_second();

	e1 = eval(e1);
	e2 = eval(e2);

	if(b->get_binop_type() == CONS) {
		return e2->get_type() == AST_NIL ? e1 : AstList::make(e1, e2);
	}
	else if(b->get_binop_type() == AND) {
		bool t = truthValue(e1) && truthValue(e2);
		
		return AstInt::make(t ? 1 : 0);
	}
	else if(b->get_binop_type() == OR) {
		bool t = truthValue(e1) || truthValue(e2);
		
		return AstInt::make(t ? 1 : 0);
	}	

	if(e1->get_type() == AST_LIST || e2->get_type() == AST_LIST) {
		report_error(b, "Binops @, and, and or are the only legal binops for lists");
	}

	if(e1->get_type() != e2->get_type() && b->get_binop_type() != CONCAT) {
		report_error(b, "Binop can only be applied to expressions of same type");
	}

	binop_type t = b->get_binop_type();
	if(e1->get_type() == AST_STRING && e2->get_type() == AST_STRING && (t == PLUS || t == MINUS || t == TIMES || t == DIVIDE || t == MODULO)) {

		report_error(b, "Binop " + AstBinOp::binop_type_to_string(t) + " cannot be applied to strings");
	}

	if(e1->get_type() == AST_NIL || e2->get_type() == AST_NIL) {
		report_error(b, "Nil can only be used with binops @, and, or.");
	}

	if(b->get_binop_type() == PLUS) {
		AstInt* i1 = static_cast<AstInt*>(e1);
		AstInt* i2 = static_cast<AstInt*>(e2);
		return AstInt::make(i1->get_int() + i2->get_int());

	}
	if(b->get_binop_type() == MINUS) {
		AstInt* i1 = static_cast<AstInt*>(e1);
		AstInt* i2 = static_cast<AstInt*>(e2);
		return AstInt::make(i1->get_int() - i2->get_int());
	}
	else if(b->get_binop_type() == TIMES) {
		AstInt* i1 = static_cast<AstInt*>(e1);
		AstInt* i2 = static_cast<AstInt*>(e2);
		return AstInt::make(i1->get_int() * i2->get_int());
	}
	else if(b->get_binop_type() == DIVIDE) {
		AstInt* i1 = static_cast<AstInt*>(e1);
		AstInt* i2 = static_cast<AstInt*>(e2);
		return AstInt::make(i1->get_int() / i2->get_int());
	}
	else if(b->get_binop_type() == MODULO) {
		AstInt* i1 = static_cast<AstInt*>(e1);
		AstInt* i2 = static_cast<AstInt*>(e2);
		return AstInt::make(i1->get_int() % i2->get_int());
	}
	else if(b->get_binop_type() == CONCAT) {
		string first;
		string second;
		if(e1->get_type() == AST_INT) {
			AstInt* i1 = static_cast<AstInt*>(e1);
			long int a = i1->get_int();
			first = to_string(a);
		} else {
			AstString* i1 = static_cast<AstString*>(e1);
			first = i1->get_string();
		}
		
		if(e2->get_type() == AST_INT) {
			AstInt* i2 = static_cast<AstInt*>(e2);
			long int a = i2->get_int();
			second = to_string(a);
		} else {
			AstString* i2 = static_cast<AstString*>(e2);
			second = i2->get_string();
		}
		return AstString::make(first + second);
	}


	//handles all logical operators for ints and strings
	if(e1->get_type() == AST_STRING && e2->get_type() == AST_STRING) {

		bool t;
		string i1 = static_cast<AstString*>(e1)->get_string();
		string i2 = static_cast<AstString*>(e2)->get_string();

		switch(b->get_binop_type()) {
			case(EQ):  t = i1 == i2; break;
			case(NEQ): t = i1 != i2; break;
			case(LT):  t = i1 < i2; break;
			case(LEQ): t = i1 <= i2; break;
			case(GT):  t = i1 > i2; break;
			case(GEQ): t = i1 >= i2; break;
			default: assert(false);
		}
		return AstInt::make(t ? 1 : 0);


	}
	else if(e1->get_type() == AST_INT && e2->get_type() == AST_INT) {
		bool t;
		long int i1 = static_cast<AstInt*>(e1)->get_int();
		long int i2 = static_cast<AstInt*>(e2)->get_int();
		switch(b->get_binop_type()) {
			case(EQ):  t = i1 == i2; break;
			case(NEQ): t = i1 != i2; break;
			case(LT):  t = i1 < i2; break;
			case(LEQ): t = i1 <= i2; break;
			case(GT):  t = i1 > i2; break;
			case(GEQ): t = i1 >= i2; break;
			default: assert(false);
		}
		return AstInt::make(t ? 1 : 0);
	}

	assert(false);
}

Expression* Evaluator::eval_unop(AstUnOp* b)
{

	Expression* e = b->get_expression();
	Expression* eval_e = eval(e);

	if(b->get_unop_type() == PRINT) {
		if(eval_e->get_type() == AST_STRING) {
			AstString* s = static_cast<AstString*>(eval_e);
			cout << s->get_string() << endl;
		}
		else cout << eval_e->to_value() << endl;

		return AstInt::make(0);

	}
	else if(b->get_unop_type() == ISNIL) {
		int i = eval_e->get_type() == AST_NIL ? 1 : 0;
		return AstInt::make(i);
	}
	else if(b->get_unop_type() == HD) {
		if(eval_e->get_type() == AST_LIST) {
			AstList* list = static_cast<AstList*>(eval_e);
			return list->get_hd();
		} else {
			return eval_e;
		}
	}
	else if(b->get_unop_type() == TL) {
		if(eval_e->get_type() == AST_LIST) {
			AstList* list = static_cast<AstList*>(eval_e);
			return list->get_tl();
		} else {
			return AstNil::make();
		}
	}
	else if(b->get_unop_type() == NOT) {
		bool t = truthValue(eval_e);
		return AstInt::make(t ? 0 : 1);

	}


	assert(false);


}

Expression* Evaluator::eval(Expression* e)
{

	Expression* res_exp = NULL;
	
	switch(e->get_type()) {
		case AST_UNOP:
		{
			AstUnOp* u = static_cast<AstUnOp*>(e);
			res_exp = eval_unop(u);
			break;
		}

		case AST_BINOP:
		{
			AstBinOp* b = static_cast<AstBinOp*>(e);
			res_exp = eval_binop(b);
			break;
		}

		case AST_INT:
		{
			res_exp = e;
			break;
		}

		case AST_STRING:
		{
			res_exp = e;
			break;
		}

		case AST_IDENTIFIER:
		{
			
			AstIdentifier* id = static_cast<AstIdentifier*>(e);
			pair<Expression*, bool> find = sym_tab.find(id);

			//if true, the value found has not yet been evaluated.
			if(find.second) {
				sym_tab.remove_lazy(id);
				Expression* evaluated = eval(find.first);
				sym_tab.add(id, evaluated);
				res_exp = evaluated;
				break;
			}

			if(find.first == NULL) {
				report_error(id, "Identifier " + id->get_id() + " is not bound in the current context");
			}

			res_exp = find.first;
			break;

		}

		case AST_ASSIGN:
		{
			AstAssign* assign = static_cast<AstAssign*>(e);

			AstIdentifier* id = assign->get_id();

			if(assign->is_lazy()) {
				res_exp = assign->get_val();
				sym_tab.add_lazy(id, res_exp);
			} else {
				res_exp = eval(assign->get_val());
				sym_tab.remove_lazy(id);
				sym_tab.add(id, res_exp);
			}

			break;
		}


		case AST_BRANCH: {
			AstBranch* branch = static_cast<AstBranch*>(e);
			bool cond_true = truthValue(eval(branch->get_pred()));
			
			if(cond_true) {
				Expression* then = branch->get_then_exp();
				if(then != NULL) {
					res_exp = eval(then);
				}
			}
			else {
				Expression* els = branch->get_else_exp();
				if(els != NULL) {
					res_exp = eval(els);
				}
			}

			break;
		}

		case AST_NIL: {
			res_exp = e;
			break;
		}

		case AST_LIST: {
			res_exp = e;
			break;
		}

		case AST_WHILE: {
			AstWhile* while_loop = static_cast<AstWhile*>(e);
			bool cond_true = truthValue(eval(while_loop->get_pred()));

			Expression* do_exp = while_loop->get_do_exp();
			//does the cookie crumble?
			while(cond_true) {
				

				if(do_exp != NULL) {
					res_exp = eval(do_exp);
				}

				cond_true = truthValue(eval(while_loop->get_pred()));

			}

			break;
		}

		case AST_FUNC: {
			AstFunc* func = static_cast<AstFunc*>(e);
			AstIdentifier* func_name = func->get_id();
			AstParameterList* param_list = func->get_params();
			Expression* body = func->get_body();
			Expression* func_ret = func->get_ret();
			if(func_body_table.find(func_name).first != NULL) {
				report_error(func, "Function " + func_name->get_id() + " has already been defined.");
			}

			func_body_table.add(func_name, body);
			func_param_table.add(func_name, param_list);
			func_ret_table.add(func_name, func_ret);

			break;
		}

		case AST_FUNCTION_CALL: {
			AstFunctionCall* func_call = static_cast<AstFunctionCall*>(e);
			AstIdentifier* func_name = func_call->get_name();

			AstCallList* call_list = func_call->get_call_list();

			if(func_body_table.find(func_name).first == NULL) {
				report_error(func_call, "Function " + func_name->get_id() + " has not been defined.");
			}

			Expression* body = func_body_table.find(func_name).first;
			Expression* func_ret = func_ret_table.find(func_name).first;
			AstParameterList* func_param_list = static_cast<AstParameterList*>(func_param_table.find(func_name).first);
			

			vector<Expression*> list = call_list->get_exprs();

			vector<pair<AstIdentifier*, bool> > ids =  func_param_list->get_ids();
			size_t ls = list.size();
			size_t is = ids.size();
			if(ls != is) {
				report_error(func_call, "Incorrect number of arguments to function " + func_name->get_id() + "." +
					" Expected " + to_string(is) + ", got " + to_string(ls) + ".");
			}


			vector<Expression*> evaluated_arguments;

			//first, evaluate all arguments in the current environment.
			for(uint i = 0; i < ids.size(); ++i) {
				Expression* expr = ids[i].second ? list[i] : eval(list[i]);

				evaluated_arguments.push_back(expr);
			}

			//now, bind all arguments to their respective ideas in a fresh environment.
			sym_tab.push();
			func_ret_table.push();
			func_param_table.push();
			func_body_table.push();

			for(uint i = 0; i < evaluated_arguments.size(); ++i) {
				if(ids[i].second) { //lazy
					sym_tab.add_lazy(ids[i].first, evaluated_arguments[i]);
				} else {
					sym_tab.add(ids[i].first, evaluated_arguments[i]);
				}
				
			}
			eval(body);
			Expression* ret_expression = eval(func_ret);
			res_exp = ret_expression;
			sym_tab.pop();
			func_ret_table.pop();
			func_param_table.pop();
			func_body_table.pop();

			break;
		}	

		default:
			assert(false);

	}

	//if there's another statement in the program, evaluate it.
	Expression* next = e->get_next_exp();
	if(next != NULL) {
		eval(next);
	}
	
	return res_exp;
}
