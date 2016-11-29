
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

	if(e1->get_type() != e2->get_type()) {
		report_error(b, "Binop can only be applied to expressions of same type");
	}

	binop_type t = b->get_binop_type();
	if(e1->get_type() == AST_STRING && e2->get_type() == AST_STRING && (t == PLUS || t == MINUS || t == TIMES || t == DIVIDE || t == MODULO)) {

		report_error(b, "Binop " + AstBinOp::binop_type_to_string(t) + " cannot be applied to strings");
	}

	if(e1->get_type() == AST_INT && e2->get_type() == AST_INT && t == CONCAT) {

		report_error(b, "Binop " + AstBinOp::binop_type_to_string(t) + " cannot be applied to ints");
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
		AstString* i1 = static_cast<AstString*>(e1);
		AstString* i2 = static_cast<AstString*>(e2);
		return AstString::make(i1->get_string() + i2->get_string());
	}


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
	//sym_tab.print_contents();

	//cout << e->to_string() << endl;
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
			Expression* f = sym_tab.find(id);
			if(f == NULL) {
				report_error(id, "Identifier " + id->get_id() + " is not bound in the current context");
			}

			res_exp = f;
			break;
		}

		case AST_ASSIGN:
		{
			AstAssign* assign = static_cast<AstAssign*>(e);
			AstIdentifier* id = assign->get_id();
			Expression* val = eval(assign->get_val());
			sym_tab.add(id, val);
			
			res_exp = val;
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
			while(cond_true) {
				

				if(do_exp != NULL) {
					res_exp = eval(do_exp);
				}

				cond_true = truthValue(eval(while_loop->get_pred()));

			}

			break;
		}

		default:
			assert(false);

	}
	/*switch(e->get_type())
	{
	
	case AST_UNOP:
	{
		AstUnOp* b = static_cast<AstUnOp*>(e);
		res_exp = eval_unop(b);
		break;
	}
	case AST_BINOP:
	{
		AstBinOp* b = static_cast<AstBinOp*>(e);
		res_exp = eval_binop(b);
		break;
	}
	case AST_READ:
	{
		AstRead* r = static_cast<AstRead*>(e);
		string input;
		getline(cin, input);
		if(r->read_integer()) {
			return AstInt::make(string_to_int(input));
		}
		return AstString::make(input);


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
		Expression* f = sym_tab.find(id);
		if(f == NULL) {
			report_error(id, "Identifier " + id->get_id() + " is not bound in current context");
		}
		res_exp = eval(f);
		break;
	}

	case AST_LET:
	{
		AstLet* let = static_cast<AstLet*>(e);
		Expression* v = eval(let->get_val());
		sym_tab.push();
		sym_tab.add(let->get_id(), v);
		res_exp = eval(let->get_body());
		sym_tab.pop();
		break;

	}

	case AST_BRANCH:
	{
		AstBranch* branch = static_cast<AstBranch*>(e);
		Expression* pred = eval(branch->get_pred());
		if(pred->get_type() == AST_INT) {
			AstInt* i = static_cast<AstInt*>(pred);
			if(i->get_int() != 0) {
				Expression* then = branch->get_then_exp();
				res_exp = eval(then);

			} else {
				Expression* els = branch->get_else_exp();
				res_exp = eval(els);
			}
		} else {
			report_error(e, "Predicate in conditional must be an integer");
		}

		break;
	}

	case AST_EXPRESSION_LIST:
	{

		//sym_tab.push();
		AstExpressionList* expressions = static_cast<AstExpressionList*>(e);

		const vector<Expression*>& exp = expressions->get_expressions();
		Expression* f = eval(exp[0]);

		for(unsigned int i = 1; i < exp.size(); ++i) {
			if(f->get_type() != AST_LAMBDA) {
				report_error(expressions, "Only lambda expressions can be applied to other expressions");
				return 0;
			}

			AstLambda* f_ = static_cast<AstLambda*>(f);
			Expression* e2 = f_->get_body();
			AstIdentifier* formal = f_->get_formal();
			//sym_tab.add(formal, exp[i]);
			e2 = e2->substitute(formal, exp[i]);

			//cout << e2->to_string() << endl;
			f = eval(e2);


		}


		//sym_tab.pop();




		return f;


	}

	case AST_LAMBDA:
	{
		res_exp = e;
		break;
	}

	case AST_NIL:
	{
		res_exp = e;
		break;
	}

	case AST_LIST:
	{
		res_exp = e;
		break;
	}

	//ADD CASES FOR ALL EXPRESSIONS!!
	default:
		assert(false);


	}
	*/


	Expression* next = e->get_next_exp();
	if(next != NULL) {
		eval(next);
	}
	

	return res_exp;
}
