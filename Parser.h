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
* File name: parser.h
* Compiler: MS Visual Studio 2022
* Course: CST 8152 � Compilers, Lab Section: [011, 012, 013]
* Assignment: A32.
* Date: Sep 01 2022
* Professor: Paulo Sousa
* Purpose: This file is the main header for Parser (.h)
*************************************************************/

#ifndef PARSER_H_
#define PARSER_H_

/* Inclusion section */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#ifndef COMPILERS_H_
#include "Compilers.h"
#endif
#ifndef READER_H_
#include "Reader.h"
#endif
#ifndef SCANNER_H_
#include "Scanner.h"
#endif

/* Global vars */
static Token			lookahead;
extern BufferReader* stringLiteralTable;
extern i32		line;
extern Token			tokenizer();
extern String		keywordTable[KWT_SIZE];
static i32		syntaxErrorNumber = 0;

#define LANG_WRTE		"println!("
#define LANG_READ		"input&"
#define LANG_MAIN		"main("

/* TO_DO: Create ALL constants for keywords (sequence given in table.h) */

/* Constants */
enum KEYWORDS {
	NO_ATTR = -1,
	KW_let,
	KW_fn,
	KW_if,
	KW_else,
	KW_fo,
	KW_while,
	KW_match,
	KW_struct,
	KW_enum,
	KW_return,
	KW_String,
	KW_i32
};


/* TO_DO: Define the number of BNF rules */
#define NUM_BNF_RULES 12

/* Parser */
typedef struct parserData {
	i32 parsHistogram[NUM_BNF_RULES];	/* Number of BNF Statements */
} ParserData, * pParsData;

/* Number of errors */
i32 numParserErrors;

/* Scanner data */
ParserData psData;

/* Function definitions */
pp_void startParser();
pp_void matchToken(i32, i32);
pp_void syncErrorHandler(i32);
pp_void printError();
pp_void printBNFData(ParserData psData);

/* List of BNF statements */
enum BNF_RULES {
	BNF_error,										/*  0: Error token */
	BNF_codeSession,								/*  1 */
	BNF_comment,									/*  2 */
	BNF_dataSession,								/*  3 */
	BNF_optVarListDeclarations,						/*  4 */
	BNF_optionalStatements,							/*  5 */
	BNF_outputStatement,							/*  6 */
	BNF_outputVariableList,							/*  7 */
	BNF_program,									/*  8 */
	BNF_statement,									/*  9 */
	BNF_statements,									/* 10 */
	BNF_statementsPrime								/* 11 */
};


/* TO_DO: Define the list of keywords */
static String BNFStrTable[NUM_BNF_RULES] = {
	"BNF_error",
	"BNF_codeSession",
	"BNF_comment",
	"BNF_dataSession",
	"BNF_optVarListDeclarations",
	"BNF_optionalStatements",
	"BNF_outputStatement",
	"BNF_outputVariableList",
	"BNF_program",
	"BNF_statement",
	"BNF_statements",
	"BNF_statementsPrime"
};

/* TO_DO: Place ALL non-terminal function declarations */
pp_void comment();
pp_void optionalStatements();
pp_void outputStatement();
pp_void outputVariableList();
pp_void program();
pp_void statement();
pp_void statements();
pp_void statementsPrime();
pp_void expression();
pp_void term();
pp_void factor();
pp_void relationalExpression();

#endif
