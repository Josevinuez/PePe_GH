/*
************************************************************
* COMPILERS COURSE - Algonquin College
* Code version: Spring, 2023
* Author: Jose Vinueza
* Professors: Paulo Sousa
************************************************************
 ____  _____   ____  _____
|  _ \| ____| |  _ \| ____|
| |_) |  _|   | |_) |  _|
|  __/| |___  |  __/| |___
|_|   |_____| |_|   |_____|
							 .-----.
							/7  .  (
						   /   .-.  \
						  /   /   \  \
						 / `  )   (   )
						/ `   )   ).  \
					  .'  _.   \_/  . |
	 .--.           .' _.' )`.        |
	(    `---...._.'   `---.'_)    ..  \
	 \            `----....___    `. \  |
	  `.           _ ----- _   `._  )/  |
		`.       /"  \   /"  \`.  `._   |
		  `.    ((O)` ) ((O)` ) `.   `._\
			`-- '`---'   `---' )  `.    `-.
			   /                  ` \      `-.
			 .'                      `.       `.
			/                     `  ` `.       `-.
	 .--.   \ ===._____.======. `    `   `. .___.--`     .''''.
	' .` `-. `.                )`. `   ` ` \          .' . '  8)
   (8  .  ` `-.`.               ( .  ` `  .`\      .'  '    ' /
	\  `. `    `-.               ) ` .   ` ` \  .'   ' .  '  /
	 \ ` `.  ` . \`.    .--.     |  ` ) `   .``/   '  // .  /
	  `.  ``. .   \ \   .-- `.  (  ` /_   ` . / ' .  '/   .'
		`. ` \  `  \ \  '-.   `-'  .'  `-.  `   .  .'/  .'
		  \ `.`.  ` \ \    ) /`._.`       `.  ` .  .'  /
		   |  `.`. . \ \  (.'               `.   .'  .'
		__/  .. \ \ ` ) \                     \.' .. \__
 .-._.-'     '"  ) .-'   `.                   (  '"     `-._.--.
(_________.-====' / .' /\_)`--..__________..-- `====-. _________)
				 (.'(.'
*/

/*
************************************************************
* File name: Parser.c
* Compiler: MS Visual Studio 2022
* Course: CST 8152 – Compilers, Lab Section: [011, 012, 013]
* Assignment: A32.
* Date: Sep 01 2022
* Purpose: This file contains all functionalities from Parser.
* Function list: (...).
************************************************************
*/

#ifndef COMPILERS_H_
#include "Compilers.h"
#endif

#ifndef PARSER_H_
#include "Parser.h"
#endif

/* Parser data */
extern ParserData psData; /* BNF statistics */

/*
************************************************************
 * Process Parser
 ***********************************************************
 */
 /* TO_DO: This is the function to start the parser - check your program definition */

pp_void startParser() {
	/* TO_DO: Initialize Parser data */
	i32 i = 0;
	for (i = 0; i < NUM_BNF_RULES; i++) {
		psData.parsHistogram[i] = 0;
	}
	/* Proceed parser */
	lookahead = tokenizer();
	if (lookahead.code != SeofT) {
		program();
	}
	matchToken(SeofT, NO_ATTR);
	printf("%s%s\n", STR_LANGNAME, ": Source file parsed");
}


/*
 ************************************************************
 * Match Token
 ***********************************************************
 */
 /* TO_DO: This is the main code for match - check your definition */
pp_void matchToken(i32 tokenCode, i32 tokenAttribute) {
	i32 matchFlag = 1;
	switch (lookahead.code) {
	case KeyT:
		if (lookahead.attribute.codeType != tokenAttribute)
			matchFlag = 0;
	default:
		if (lookahead.code != tokenCode)
			matchFlag = 0;
	}
	if (matchFlag && lookahead.code == SeofT)
		return;
	if (matchFlag) {
		lookahead = tokenizer();
		if (lookahead.code == ErrT) {
			printError();
			lookahead = tokenizer();
			syntaxErrorNumber++;
		}
	}
	else
		syncErrorHandler(tokenCode);
}

/*
 ************************************************************
 * Syncronize Error Handler
 ***********************************************************
 */
pp_void syncErrorHandler(i32 syncTokenCode) {
	printError();
	syntaxErrorNumber++;
	while (lookahead.code != syncTokenCode) {
		if (lookahead.code == SeofT)
			exit(syntaxErrorNumber);
		lookahead = tokenizer();
	}
	if (lookahead.code != SeofT)
		lookahead = tokenizer();
}

/*
 ************************************************************
 * Print Error
 ***********************************************************
 */
pp_void printError() {
	extern numParserErrors;			/* link to number of errors (defined in Parser.h) */
	Token t = lookahead;
	printf("%s%s%3d\n", STR_LANGNAME, ": Syntax error:  Line:", line);
	printf("*****  Token code:%3d Attribute: ", t.code);
	switch (t.code) {
	case ErrT:
		printf("*ERROR*: %s\n", t.attribute.errLexeme);
		break;
	case SeofT:
		printf("SEOF_T\t\t%d\t\n", t.attribute.seofType);
		break;
	case MthdT:
		printf("MNID_T:\t\t%s\t\n", t.attribute.idLexeme);
		break;
	case StrT:
		printf("STR_T: %s\n", readerGetContent(stringLiteralTable, t.attribute.contentString));
		break;
	case KeyT:
		printf("KW_T: %s\n", keywordTable[t.attribute.codeType]);
		break;
	case LprT:
		printf("LPR_T\n");
		break;
	case RprT:
		printf("RPR_T\n");
		break;
	case LbrT:
		printf("LBR_T\n");
		break;
	case RbrT:
		printf("RBR_T\n");
		break;
	case EosT:
		printf("NA\n");
		break;
	default:
		printf("%s%s%d\n", STR_LANGNAME, ": Scanner error: invalid token code: ", t.code);
		numParserErrors++; // Updated parser error
	}
}

/*
 ************************************************************
 * Program statement
 BNF: <program> -> fn main() { <variable_declarations> <opt_statements> }
 * FIRST(<program>)= {MNID_T (fn)}.ents> }
 ***********************************************************
 */
pp_void program() {
	/* Update program statistics */
	psData.parsHistogram[BNF_program]++;
	/* Program code */
	switch (lookahead.code) {
	case CmtT:
		comment();
	case KeyT:
		matchToken(KeyT, KW_fn);
	case MthdT:
		if (strncmp(lookahead.attribute.idLexeme, LANG_MAIN, 5) == 0) {
			matchToken(MthdT, NO_ATTR); 
			matchToken(RprT, NO_ATTR);
			matchToken(LbrT, NO_ATTR);
			optionalStatements();
			statements();
			matchToken(RbrT, NO_ATTR);
			break;
		}
		else {
			printError();
		}
	case SeofT:
		; // Empty
		break;
	default:
		printError();
	}
	printf("%s%s\n", STR_LANGNAME, ": Program parsed");
}

/*
 ************************************************************
 * comment
 * BNF: comment
 * FIRST(<comment>)= {CMT_T}.
 ***********************************************************
 */
pp_void comment() {
	psData.parsHistogram[BNF_comment]++;
	matchToken(CmtT, NO_ATTR);
	printf("%s%s\n", STR_LANGNAME, ": Comment parsed");
}



 

/* TO_DO: Continue the development (all non-terminal functions) */

/*
 ************************************************************
 * Optional statement
 * BNF: <opt_statements> -> <statements> | ϵ
 * FIRST(<opt_statements>) = { ϵ , IVID_T, FVID_T, SVID_T, KW_T(KW_if),
 *				KW_T(KW_while), MNID_T(print&), MNID_T(input&) }
 ***********************************************************
 */
pp_void optionalStatements() {
	psData.parsHistogram[BNF_optionalStatements]++;
	switch (lookahead.code) {

	case CmtT:
		comment();
	case MthdT:
		if ((strncmp(lookahead.attribute.idLexeme, LANG_WRTE, 6) == 0) ||
			(strncmp(lookahead.attribute.idLexeme, LANG_READ, 6) == 0)) {
			statements();
			break;
		}
	default:
		; // Empty
	}
	printf("%s%s\n", STR_LANGNAME, ": Optional statements parsed");
}

/*
 ************************************************************
 * Statements
 * BNF: <statements> -> <statement><statementsPrime>
 * FIRST(<statements>) = { IVID_T, FVID_T, SVID_T, KW_T(KW_if),
 *		KW_T(KW_while), MNID_T(input&), MNID_T(print&) }
 ***********************************************************
 */
pp_void statements() {
	psData.parsHistogram[BNF_statements]++;
	statement();
	statementsPrime();
	printf("%s%s\n", STR_LANGNAME, ": Statements parsed");
}

/*
 ************************************************************
 * Statements Prime
 * BNF: <statementsPrime> -> <statement><statementsPrime> | ϵ
 * FIRST(<statementsPrime>) = { ϵ , IVID_T, FVID_T, SVID_T,
 *		KW_T(KW_if), KW_T(KW_while), MNID_T(input&), MNID_T(print&) }
 ***********************************************************
 */
pp_void statementsPrime() {
	psData.parsHistogram[BNF_statementsPrime]++;
	if (lookahead.code != RbrT) {  // Until we reach the closing brace of a block
		statement();
		statementsPrime();
	}

	switch (lookahead.code) {
	case MthdT:
		if (strncmp(lookahead.attribute.idLexeme, LANG_WRTE, 6) == 0) {
			statements();
			break;
		}
	default:
		; //empty string
	}
}

/*
 ************************************************************
 * Arithmetic Expression
 * BNF: <expression> -> <term> { (+|-) <term> }
 * FIRST(<expression>) = { InlT, VarT, LprT }
 ***********************************************************
 */
pp_void expression() {
	term();  // Start with a term
	while (lookahead.code == AriOpT && (lookahead.attribute.arithmeticOperator == Add || lookahead.attribute.arithmeticOperator == Sub)) {
		if (lookahead.attribute.arithmeticOperator == Add) {
			matchToken(AriOpT, Add);  
			term();
		}
		else if (lookahead.attribute.arithmeticOperator == Sub) {
			matchToken(AriOpT, Sub); 
			term();
		}
	}
}
/*
 ************************************************************
 * Arithmetic Term
 * BNF: <term> -> <factor> { (*|/) <factor> }
 * FIRST(<term>) = { InlT, VarT, LprT }
 ***********************************************************
 */
pp_void term() {
	factor();
	while (lookahead.code == AriOpT && (lookahead.attribute.arithmeticOperator == Mul || lookahead.attribute.arithmeticOperator == Div)) {
		if (lookahead.attribute.arithmeticOperator == Mul) {
			matchToken(AriOpT, Mul);
			factor();
		}
		else if (lookahead.attribute.arithmeticOperator == Div) {
			matchToken(AriOpT, Div);
			factor();
		}
	}
}
/*
 ************************************************************
 * Arithmetic Factor
 * BNF: <factor> -> InlT | VarT | ( <expression> )
 * FIRST(<factor>) = { InlT, VarT, LprT }
 ***********************************************************
 */
pp_void factor() {
	if (lookahead.code == InlT) {
		matchToken(InlT, NO_ATTR);
	}
	else if (lookahead.code == VarT) {
		matchToken(VarT, NO_ATTR);
	}
	else if (lookahead.code == LprT) {
		matchToken(LprT, NO_ATTR);
		expression();
		matchToken(RprT, NO_ATTR);
	}
	else {
		printError();
	}
}
/*
 ************************************************************
 * Relational Expression
 * BNF: <relationalExpression> -> <expression> <relationalOperator> <expression>
 * FIRST(<relationalExpression>) = { InlT, VarT, LprT }
 ***********************************************************
 */
pp_void relationalExpression() {
	expression();
	if (lookahead.code == RelOpT) {  // Assuming RelOpT is a token for relational operators
		switch (lookahead.attribute.relationalOperator) {
		case Eq:
			matchToken(RelOpT, Eq);
			break;
		case Ne:
			matchToken(RelOpT, Ne);
			break;
		case Gt:
			matchToken(RelOpT, Gt);
			break;
		case Lt:
			matchToken(RelOpT, Lt);
			break;
		default:
			printError();
			break;
		}
		expression();
	}
	else {
		printError();
	}
}
/*
 ************************************************************
 * Conditional Statement
 * BNF: <conditional> -> if <relationalExpression> { <statements> } [else { <statements> }]
 * FIRST(<conditional>) = { KeyT(KW_if) }
 ***********************************************************
 */
pp_void conditional() {
	matchToken(KeyT, KW_if);
	relationalExpression();
	matchToken(LbrT, NO_ATTR);
	statements();
	matchToken(RbrT, NO_ATTR);

	if (lookahead.code == KeyT && lookahead.attribute.codeType == KW_else) {
		matchToken(KeyT, KW_else);
		matchToken(LbrT, NO_ATTR);
		statements();
		matchToken(RbrT, NO_ATTR);
	}
}

/*
 ************************************************************
 * Variable Declaration
 * BNF: <declaration> -> let <relationalExpression> [= <expression>] ;
 * FIRST(<declaration>) = { KeyT(KW_let) }
 ***********************************************************
 */
pp_void declaration() {
	matchToken(KeyT, KW_let);
	relationalExpression();

	if (lookahead.code == Eq) {
		matchToken(Eq, NO_ATTR); // Match '=' token
		expression(); // Parse the expression to the right of the assignment
	}
	matchToken(EosT, NO_ATTR); // Expect a ';' at the end
}


/*
 ************************************************************
 * Single statement
 * BNF: <statement> -> <assignment statement> | <selection statement> |
 *	<iteration statement> | <input statement> | <output statement>
 * FIRST(<statement>) = { IVID_T, FVID_T, SVID_T, KW_T(KW_if), KW_T(KW_while),
 *			MNID_T(input&), MNID_T(print&) }
 ***********************************************************
 */
pp_void statement() {
	psData.parsHistogram[BNF_statement]++;
	switch (lookahead.code) {
	case KeyT:
		switch (lookahead.attribute.codeType) {
		case KW_let:
			declaration();
			break;
		case KW_if:
			conditional();
			break;
		default:
			printError();
			break;
		}
		break;
	case MthdT:
		if (strncmp(lookahead.attribute.idLexeme, LANG_WRTE, 6) == 0) {
			outputStatement();
		}
		break;
	default:
		printError();
	}
	printf("%s%s\n", STR_LANGNAME, ": Statement parsed");
}

/*
 ************************************************************
 * Output Statement
 * BNF: <output statement> -> print& (<output statementPrime>);
 * FIRST(<output statement>) = { MNID_T(print&) }
 ***********************************************************
 */
pp_void outputStatement() {
	psData.parsHistogram[BNF_outputStatement]++;
	matchToken(MthdT, NO_ATTR);
	outputVariableList();
	matchToken(RprT, NO_ATTR);
	matchToken(EosT, NO_ATTR);
	printf("%s%s\n", STR_LANGNAME, ": Output statement parsed");
}

/*
 ************************************************************
 * Output Variable List
 * BNF: <opt_variable list> -> <variable list> | ϵ
 * FIRST(<opt_variable_list>) = { IVID_T, FVID_T, SVID_T, ϵ }
 ***********************************************************
 */
pp_void outputVariableList() {
	psData.parsHistogram[BNF_outputVariableList]++;
	switch (lookahead.code) {
	case StrT:
		matchToken(StrT, NO_ATTR);
		break;
	default:
		;
	}
	printf("%s%s\n", STR_LANGNAME, ": Output variable list parsed");
}

/*
 ************************************************************
 * The function prints statistics of BNF rules
 * Param:
 *	- Parser data
 * Return:
 *	- Void (procedure)
 ***********************************************************
 */
 /*
 pp_void printBNFData(ParserData psData) {
 }
 */
pp_void printBNFData(ParserData psData) {
	/* Print Parser statistics */
	printf("Statistics:\n");
	printf("----------------------------------\n");
	int cont = 0;
	for (cont = 0; cont < NUM_BNF_RULES; cont++) {
		if (psData.parsHistogram[cont] > 0)
			printf("%s%s%s%d%s", "Token[", BNFStrTable[cont], "]=", psData.parsHistogram[cont], "\n");
	}
	printf("----------------------------------\n");
}


