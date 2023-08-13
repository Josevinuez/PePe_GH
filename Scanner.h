/*
************************************************************
* COMPILERS COURSE - Algonquin College
* Code version: Summer, 2023
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
* File name: Scanner.h
* Compiler: MS Visual Studio 2022
* Course: CST 8152 � Compilers, Lab Section: [011, 012]
* Assignment: A22, A32.
* Date: May 01 2022
* Purpose: This file is the main header for Scanner (.h)
* Function list: (...).
*************************************************************/

#ifndef COMPILERS_H_
#include "Compilers.h"
#endif

#ifndef READER_H_
#include "Reader.h"
#endif

#ifndef SCANNER_H_
#define SCANNER_H_

#ifndef NULL
#include <_null.h> /* NULL pointer constant is defined there */
#endif

/*#pragma warning(1:4001) */	/*to enforce C89 type comments  - to make //comments an warning */

/*#pragma warning(error:4001)*/	/* to enforce C89 comments - to make // comments an error */

/* Constants */
#define VID_LEN 20  /* variable identifier length */
#define ERR_LEN 40  /* error message length */
#define NUM_LEN 5   /* maximum number of digits for IL */

#define RTE_CODE 1  /* Value for run-time error */

#define NUM_TOKENS 19

enum TOKENS {
	ErrT,      // 0: Error token
	MthdT,     // 1: Method name  token 
	InlT,      // 2: Integer literal token
	StrT,      // 3: String literal token
	LprT,      // 4: Left parenthesis token
	RprT,      // 5: Right parenthesis token
	LbrT,      // 6: Left brace token
	RbrT,      // 7: Right brace token
	KeyT,       // 8: Keyword token
	EosT,      // 9: End of statement (semicolon)
	RteT,      // 10: Run-time error token
	SeofT,     // 11: Source end-of-file token
	CmtT,       // 12: Comment token
	AriOpT,    // 13: Arithmetic Operator token
	RelOpT,    // 14: Relational Operator token
	LogOpT,    // 15: Logical Operator token
	AssOpT,
	IncOpT,
	VarT,
};

static String tokenStrTable[NUM_TOKENS] = {
	"ErrT",
	"MtdT",
	"InlT",
	"StrT",
	"LprT",
	"RprT",
	"LbrT",
	"RbrT",
	"KwT",
	"EosT",
	"RteT",
	"SeofT",
	"CmtT",
	"AriOpT",
	"RelOpT",
	"LogOpT",
	"AssOpT",
	"IncOpT",
	"VarT"

};

typedef enum ArithmeticOperators {Add,Sub,Mul,Div} AriOperator;
typedef enum RelationalOperators {Eq,Ne,Gt,Lt} RelOperator;
typedef enum LogicalOperators {And,Or,Not} LogOperator;
typedef enum SourceEndOfFile {Seof_0,Seof_255,} EofOperator;

/* TO_DO: Data structures for declaring the token and its attributes */
typedef union TokenAttribute {
	i32 codeType;						/* integer attributes accessor */
	AriOperator arithmeticOperator;		/* arithmetic operator attribute code */
	RelOperator relationalOperator;		/* relational operator attribute code */
	LogOperator logicalOperator;		/* logical operator attribute code */
	EofOperator seofType;				/* source-end-of-file attribute code */
	i32 intValue;						/* integer literal attribute (value) */
	i32 keywordIndex;					/* keyword index in the keyword table */
	i32 contentString;					/* string literal offset from the beginning of the string literal buffer (stringLiteralTable->content) */
	f32 floatValue;						/* floating-point literal attribute (value) */
	pp_char idLexeme[VID_LEN + 1];		/* variable identifier token attribute */
	pp_char errLexeme[ERR_LEN + 1];		/* error token attribite */
} TokenAttribute;

/* TO_DO: Should be used if no symbol table is implemented */
typedef struct idAttibutes {
	u8 flags;						/* Flags information */
	union {
		i32 intValue;				/* Integer value */
		f32 floatValue;				/* Float value */
		String stringContent;		/* String value */
	} values;
} IdAttibutes;

/* Token declaration */
typedef struct Token {
	i32 code;					/* token code */
	TokenAttribute attribute;	/* token attribute */
	IdAttibutes   idAttribute;	/* not used in this scanner implementation - for further use */
} Token;

/* Scanner */
typedef struct scannerData {
	i32 scanHistogram[NUM_TOKENS];	/* Statistics of chars */
} ScannerData, * pScanData;

///////////////////////////////////////////////////////////////////////////////////////////////////////

/* EOF definitions */
#define CHARSEOF0 '\0'
#define CHARSEOF255 0xFF

/*  Special case tokens processed separately one by one in the token-driven part of the scanner:
 *  LPR_T, RPR_T, LBR_T, RBR_T, EOS_T, SEOF_T and special chars used for tokenis include _, & and ' */

 /* TO_DO: Define lexeme FIXED classes */
 /* These constants will be used on nextClass */
#define CHRCOL2 '_'
#define CHRCOL3 '('
#define CHRCOL4 '"'
#define CHRCOL5 '*'
#define CHRCOL6 '/'


/* These constants will be used on VID / MID function */
#define MNID_SUF '('
#define COMM_SYM '/'
#define MACRO '!'

/* TO_DO: Error states and illegal state */
#define ESNR	12		/* Error state with no retract */
#define ESWR	13		/* Error state with retract */
#define FS		15		/* Illegal state */

 /* TO_DO: State transition table definition */
#define NUM_STATES		14
#define CHAR_CLASSES	9

/* TO_DO: Transition table - type of states defined in separate table */
static i32 transitionTable[NUM_STATES][CHAR_CLASSES] = {
	/*    [A-z],[0-9], _, (,  ", *, /, SEOF, other
		  L(0), D(1), U(2), M(3), Q(4), S(5), C(6),  E(7), O(8) */
		{     1,    4, ESNR, ESNR,    6, ESNR,   8, ESNR, ESNR},  // S0: NOAS
		{     1,    1,    1,    2,    3,    3,   3,  ESNR,    3},  // S1: NOAS
		{    FS,   FS,   FS,   FS,   FS,   FS,  FS,   FS,   FS},  // S2: ASNR (Method)
		{    FS,   FS,   FS,   FS,   FS,   FS,  FS,   FS,   FS},  // S3: ASWR (Keyword/Variable)
		{     5,    4,    5,    5,    5,    5,   5,  ESNR,    5},  // S4: NOAS
		{    FS,   FS,   FS,   FS,   FS,   FS,  FS,   FS,   FS},  // S5: ASWR (Digit) - Accepting state with retraction for numbers
		{     6,    6,    6,    6,    7,    6,   6,    7,    6},  // S6: NOAS
		{    FS,   FS,   FS,   FS,   FS,   FS,  FS,   FS,   FS},  // S7: ASNR (String)
		{   ESNR, ESNR, ESNR, ESNR, ESNR,    9, ESNR, ESNR, ESNR},  // S8: NOAS
		{    10,   10,   10,   10,   10,   10,  10,  ESNR,   10},  // S9: NOAS
		{    11,   11,   11,   11,   11,   11,  12,   FS,   11},  // S10: NOAS
		{    FS,   FS,   FS,   FS,   FS,   FS,  FS,   FS,   FS},  // S11: ASNR (Comment)
		{    FS,   FS,   FS,   FS,   FS,   FS,  FS,   FS,   FS},  // S12: ASNR (ES)
		{    FS,   FS,   FS,   FS,   FS,   FS,  FS,   FS,   FS}   // S13: ASWR (ER)
};



/* Define accepting states types */
#define NOFS	0		/* not accepting state */
#define FSNR	1		/* accepting state with no retract */
#define FSWR	2		/* accepting state with retract */

/* TO_DO: Define list of acceptable states */
static i32 stateType[NUM_STATES] = {
	NOFS, // S0: NOAS
	NOFS, // S1: NOAS
	FSNR, // S2: ASNR (Method)
	FSWR, // S3: ASWR (Keyword/Variable)
	NOFS, // S4: NOAS
	FSWR, // S5: ASWR (Digit)
	NOFS, // S6: NOAS
	FSNR, // S7: ASNR (String)
	NOFS, // S8: NOAS
	NOFS, // S9: NOAS
	FSNR, // S10: NOAS
	FSNR, // S11: ASNR (Comment)
	FSNR, // S12: ASNR (ES)
	FSWR  // S13: ASWR (ER)

};

/*
-------------------------------------------------
TO_DO: Adjust your functions'definitions
-------------------------------------------------
*/

/* Static (local) function  prototypes */
i32			startScanner(ReaderPointer psc_buf);
static i32	nextClass(pp_char c);					/* character class function */
static i32	nextState(i32, pp_char);		/* state machine function */
pp_void		printScannerData(ScannerData scData);

/*
-------------------------------------------------
Automata definitions
-------------------------------------------------
*/

/* TO_DO: Pointer to function (of one char * argument) returning Token */
typedef Token(*PTR_ACCFUN)(String lexeme);

/* Declare accepting states functions */
Token funcMTH(String lexeme);
Token funcKEY(String lexeme);
Token funcCMT(String lexeme);
Token funcIL(String lexeme);
Token funcSL(String lexeme);
Token funcErr(String lexeme);

/*
 * Accepting function (action) callback table (array) definition
 * If you do not want to use the typedef, the equvalent declaration is:
 */

 /* TO_DO: Define final state table */
static PTR_ACCFUN finalStateTable[NUM_STATES] = {
	NULL,		/* -    [00] */
	NULL,		/* -    [01] */
	funcMTH,	/* MNID	[02] */
	funcKEY,	/* KEY  [03] */
	NULL,		/* -    [04] */
	funcIL,		/*DIG   [05] */
	NULL,		/*      [06] */
	funcSL,		/*STG   [07] */
	NULL,	    /*      [08] */
	NULL,		/*      [09] */
	NULL,		/*      [10] */
	funcCMT,		/* SL   [11] */
	funcErr,	/* ERR1 [12] */
	funcErr,	/* ERR2 [13] */
};

/*
-------------------------------------------------
Language keywords
-------------------------------------------------
*/
/* TO_DO: Define the number of Keywords from the language */
#define KWT_SIZE 12

static String keywordTable[KWT_SIZE] = {
	"let",		/* KW00 */
	"fn",		/* KW01 */
	"if",		/* KW02 */
	"else",		/* KW03 */
	"for",		/* KW04 */
	"while",	/* KW05 */
	"match",	/* KW06 */
	"struct",	/* KW07 */
	"enum",		/* KW08 */
	"return",	/* KW09 */
	"String",	/* KW10 */
	"i32"		/* KW11 */
};

/* NEW SECTION: About indentation */

/*
 * Scanner attributes to be used (ex: including: intendation data
 */

#define INDENT '\t'  /* Tabulation */

 /* TO_DO: Should be used if no symbol table is implemented */
typedef struct languageAttributes {
	pp_char indentationCharType;
	i32 indentationCurrentPos;
} LanguageAttributes;

/* Number of errors */
i32 numScannerErrors;

/* Scanner data */
ScannerData scData;

#endif
