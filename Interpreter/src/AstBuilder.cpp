/*
 * fuzuli : A general purpose interpreter
 * Copyright (C) 2012 Mehmet Hakan Satman <mhsatman@yahoo.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <cstdlib>
#include <cstring>
#include "../include/FuzuliTypes.h"

namespace fuzuli {

using namespace std;

AstBuilder::AstBuilder(SourceCode *code) {
	this->code = code;
}

AstBuilder::~AstBuilder() {
	// TODO Auto-generated destructor stub
}

Expression* AstBuilder::getNextExpression() {
	Token *tok, *cmd;
	vector<Expression*> *exprlist = new vector<Expression*>();
	tok = this->code->getNextToken();
	//cout << "AstBuilder:getNextExpression:Token: "<<tok->getContent()<<endl;
	if (tok->getType() == EOP) {
		return (NULL);
	}
	if (tok->getType() == HTML) {
		//WebExpression *ie = new WebExpression(tok->getContent());
		//return (ie);
	}
	if (tok->getType() != LPARENTH) {
		cout << "LPARANT required at line " << this->code->getCurrentLine()
				<< " but found " << tok->getContent() << "(" << tok->getType()
				<< ")" << endl;
	}
	cmd = this->code->getNextToken();
	while (1) {
		tok = this->code->getNextToken();
		if (tok->getType() == EOP) {
			cout << "Missed closing right paranthesis at line "
					<< this->code->getCurrentLine() << endl;
			exit(-1);
		}
		if (tok->getType() == LPARENTH) {
			this->code->pushBackToken();
			exprlist->push_back(getNextExpression());
		} else if (tok->getType() == RPARENTH) {
			break;
		} else {
			if (tok->getType() == INTEGER) {
				IntegerConstantExpression *ie = new IntegerConstantExpression(tok);
				exprlist->push_back(ie);
			} else if (tok->getType() == FLOAT) {
				FloatConstantExpression *ie = new FloatConstantExpression(tok);
				exprlist->push_back(ie);
			} else if (tok->getType() == STRING) {
				StringExpression *ie = new StringExpression(tok);
				exprlist->push_back(ie);
			} else if (tok->getType() == IDENTIFIER) {
				IdentifierExpression *ie = new IdentifierExpression(tok);
				exprlist->push_back(ie);
			} else if (tok->getType() == HTML) {
				//WebExpression *webexp = new WebExpression(tok->getContent());
				//exprlist->push_back(webexp);
			}
		}
	}
	Expression *callResult = this->fuzuliCall(cmd, exprlist);
	return (callResult);
}

Expression *AstBuilder::fuzuliCall(Token *tok, vector<Expression*> *expr) {
	if (tok->getType() == PLUS) {
		PlusExpression *pe = new PlusExpression(expr);
		return (pe);
	} else if (tok->getType() == ASTERIX) {
		AsterixExpression *pe = new AsterixExpression(expr);
		return (pe);
	} else if (tok->getType() == MINUS) {
		SubtractionExpression *pe = new SubtractionExpression(expr);
		return (pe);
	} else if (tok->getType() == DIVIDE) {
		DivisionExpression *pe = new DivisionExpression(expr);
		return (pe);
	} else if (tok->getType() == EQUALS) {
		EqualsExpression *pe = new EqualsExpression(expr);
		return (pe);
	} else if (tok->getType() == NOTEQUALS) {
		NotEqualsExpression *pe = new NotEqualsExpression(expr);
		return (pe);
	} else if (tok->getType() == LESSTHAN) {
		LessExpression *pe = new LessExpression(expr);
		return (pe);
	} else if (tok->getType() == LESSOREQUALTHAN) {
		LessOrEqualExpression *pe = new LessOrEqualExpression(expr);
		return (pe);
	} else if (tok->getType() == BIGGERTHAN) {
		BiggerExpression *pe = new BiggerExpression(expr);
		return (pe);
	} else if (tok->getType() == BIGGEROREQUALTHAN) {
		BigOrEqualExpression *pe = new BigOrEqualExpression(expr);
		return (pe);
	} else if (tok->getType() == PERCENT) {
		ModulaExpression *pe = new ModulaExpression(expr);
		return (pe);
	} else if (tok->getType() == COLON) {
		ColonExpression *pe = new ColonExpression(expr);
		return (pe);
	} else if (tok->getType() == MINUSMINUS) {
		DecExpression *pe = new DecExpression(expr);
		return (pe);
	} else if (tok->getType() == PLUSPLUS) {
		IncExpression *pe = new IncExpression(expr);
		return (pe);
	} else if (tok->getType() == AMPERSAND) {
		BitAndExpression *pe = new BitAndExpression(expr);
		return (pe);
	} else if (tok->getType() == PIPE) {
		BitOrExpression *pe = new BitOrExpression(expr);
		return (pe);
	} else if (tok->getType() == BITSHIFTLEFT) {
		BitShiftLeftExpression *pe = new BitShiftLeftExpression(expr);
		return (pe);
	} else if (tok->getType() == BITSHIFTRIGHT) {
		BitShiftRightExpression *pe = new BitShiftRightExpression(expr);
		return (pe);
	} else if (tok->getType() == TILDE) {
		BitNotExpression *pe = new BitNotExpression(expr);
		return (pe);
	} else if (tok->getType() == HAT) {
		BitXORExpression *pe = new BitXORExpression(expr);
		return (pe);
	} else if (tok->getType() == IDENTIFIER) {
		if (strcmp(tok->getContent(), "inc") == 0) {
			IncExpression *pe = new IncExpression(expr);
			return (pe);
		} else if (strcmp(tok->getContent(), "and") == 0) {
			AndExpression *pe = new AndExpression(expr);
			return (pe);
		} else if (strcmp(tok->getContent(), "or") == 0) {
			OrExpression *pe = new OrExpression(expr);
			return (pe);
		} else if (strcmp(tok->getContent(), "not") == 0) {
			NotExpression *pe = new NotExpression(expr);
			return (pe);
		} else if (strcmp(tok->getContent(), "if") == 0) {
			IfExpression *pe = new IfExpression(expr);
			return (pe);
		} else if (strcmp(tok->getContent(), "for") == 0) {
			ForExpression *pe = new ForExpression(expr);
			return (pe);
		} else if (strcmp(tok->getContent(), "foreach") == 0) {
			ForEachExpression *pe = new ForEachExpression(expr);
			return (pe);
		} else if (strcmp(tok->getContent(), "dotimes") == 0) {
			DoTimesExpression *pe = new DoTimesExpression(expr);
			return (pe);
		} else if (strcmp(tok->getContent(), "break") == 0) {
			BreakExpression *pe = new BreakExpression(expr);
			return (pe);
		} else if (strcmp(tok->getContent(), "switch") == 0) {
			SwitchExpression *pe = new SwitchExpression(expr);
			return (pe);
		} else if (strcmp(tok->getContent(), "case") == 0) {
			CaseExpression *pe = new CaseExpression(expr);
			return (pe);
		} else if (strcmp(tok->getContent(), "block") == 0) {
			BlockExpression *pe = new BlockExpression(expr);
			return (pe);
		} else if (strcmp(tok->getContent(), "group") == 0) {
			//GroupExpression *pe = new GroupExpression(expr);
			//return (pe);
		} else if (strcmp(tok->getContent(), "print") == 0) {
			PrintExpression *pe = new PrintExpression(expr);
			return (pe);
		} else if (strcmp(tok->getContent(), "println") == 0) {
			PrintlnExpression *pe = new PrintlnExpression(expr);
			return (pe);
		} else if (strcmp(tok->getContent(), "let") == 0) {
			LetExpression *pe = new LetExpression(expr);
			return (pe);
		} else if (strcmp(tok->getContent(), "def") == 0) {
			DefExpression *pe = new DefExpression(expr);
			return (pe);
		} else if (strcmp(tok->getContent(), "clone") == 0) {
			CloneExpression *pe = new CloneExpression(expr);
			return (pe);
		} else if (strcmp(tok->getContent(), "while") == 0) {
			WhileExpression *pe = new WhileExpression(expr);
			return (pe);
		} else if (strcmp(tok->getContent(), "list") == 0) {
			ListExpression *pe = new ListExpression(expr);
			return (pe);
		} else if (strcmp(tok->getContent(), "length") == 0) {
			LengthExpression *pe = new LengthExpression(expr);
			return (pe);
		} else if (strcmp(tok->getContent(), "nth") == 0) {
			NthExpression *pe = new NthExpression(expr);
			return (pe);
		} else if (strcmp(tok->getContent(), "set") == 0) {
			SetExpression *pe = new SetExpression(expr);
			return (pe);
		} else if (strcmp(tok->getContent(), "append") == 0) {
			AppendExpression *pe = new AppendExpression(expr);
			return (pe);
		} else if (strcmp(tok->getContent(), "prepend") == 0) {
			PrependExpression *pe = new PrependExpression(expr);
			return (pe);
		} else if (strcmp(tok->getContent(), "remove") == 0) {
			RemoveExpression *pe = new RemoveExpression(expr);
			return (pe);
		} else if (strcmp(tok->getContent(), "find") == 0) {
			FindExpression *pe = new FindExpression(expr);
			return (pe);
		} else if (strcmp(tok->getContent(), "fill") == 0) {
			FillExpression *pe = new FillExpression(expr);
			return (pe);
		} else if (strcmp(tok->getContent(), "first") == 0) {
			FirstExpression *pe = new FirstExpression(expr);
			return (pe);
		} else if (strcmp(tok->getContent(), "last") == 0) {
			LastExpression *pe = new LastExpression(expr);
			return (pe);
		} else if (strcmp(tok->getContent(), "params") == 0) {
			ParamsExpression *pe = new ParamsExpression(expr);
			return (pe);
		} else if (strcmp(tok->getContent(), "function") == 0) {
			FunctionExpression *pe = new FunctionExpression(expr);
			return (pe);
		} else if (strcmp(tok->getContent(), "return") == 0) {
			ReturnExpression *pe = new ReturnExpression(expr);
			return (pe);
		} else if (strcmp(tok->getContent(), "dynload") == 0) {
			DynLoadExpression *pe = new DynLoadExpression(expr);
			return (pe);
		} else if (strcmp(tok->getContent(), "C") == 0) {
			CExpression *pe = new CExpression(expr);
			return (pe);
		} else if (strcmp(tok->getContent(), "typeof") == 0) {
			TypeofExpression *pe = new TypeofExpression(expr);
			return (pe);
		} else if (strcmp(tok->getContent(), "type") == 0) {
			TypeExpression *pe = new TypeExpression(expr);
			return (pe);
		} else if (strcmp(tok->getContent(), "require") == 0) {
			RequireExpression *pe = new RequireExpression(expr);
			return (pe);
		} else if (strcmp(tok->getContent(), "eval") == 0) {
			EvalExpression *pe = new EvalExpression(expr);
			return (pe);
		} else if (strcmp(tok->getContent(), "expression") == 0) {
			ExpressionExpression *pe = new ExpressionExpression(expr);
			return (pe);
		} else if (strcmp(tok->getContent(), "explode") == 0) {
			ExplodeExpression *pe = new ExplodeExpression(expr);
			return (pe);
		} else if (strcmp(tok->getContent(), "REQUEST") == 0) {
			//RequestExpression *pe = new RequestExpression(expr);
			//return (pe);
		} else if (strcmp(tok->getContent(), "isset") == 0) {
			//IssetExpression *pe = new IssetExpression(expr);
			//return (pe);
		} else if (strcmp(tok->getContent(), "setcookie") == 0) {
			//SetCookieExpression *pe = new SetCookieExpression(expr);
			//return (pe);
		} else if (strcmp(tok->getContent(), "getcookie") == 0) {
			//GetCookieExpression *pe = new GetCookieExpression(expr);
			//return (pe);
		} else if (strcmp(tok->getContent(), "include") == 0) {
			//IncludeExpression *pe = new IncludeExpression(expr);
			//return (pe);
		} else if (strcmp(tok->getContent(), "dump") == 0) {
			DumpExpression *pe = new DumpExpression(expr);
			return (pe);
		} else if (strcmp(tok->getContent(), "gc") == 0) {
			//GCExpression *pe = new GCExpression(expr);
			//return (pe);
		} else if (strcmp(tok->getContent(), "setprecision") == 0) {
			SetPrecisionExpression *pe = new SetPrecisionExpression(expr);
			return (pe);
		} else if (strcmp(tok->getContent(), "setepsilon") == 0) {
			SetEpsilonExpression *pe = new SetEpsilonExpression(expr);
			return (pe);
		} else if (strcmp(tok->getContent(), "class") == 0) {
			ClassExpression *pe = new ClassExpression(expr);
			return (pe);
		} else if (strcmp(tok->getContent(), "new") == 0) {
			NewExpression *pe = new NewExpression(expr);
			return (pe);
		} else if (strcmp(tok->getContent(), "delete") == 0) {
			//DeleteExpression *pe = new DeleteExpression(expr);
			//return (pe);
		} else if (strcmp(tok->getContent(), "timing") == 0) {
			TimingExpression *pe = new TimingExpression(expr);
			return (pe);
		}else {
			/* It may be a FuzuliFunction */
			expr->insert(expr->begin(), new IdentifierExpression(tok));
			FunctionCallExpression *pe = new FunctionCallExpression(expr);
			return (pe);
		}
	}
	return (NULL);
}

} /* namespace fuzuli */

