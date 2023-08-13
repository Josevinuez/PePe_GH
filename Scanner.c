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
* File name: Scanner.c
* Compiler: MS Visual Studio 2022
* Course: CST 8152 � Compilers, Lab Section: [011, 012]
* Assignment: A22, A32.
* Date: May 01 2022
* Purpose: This file contains all functionalities from Scanner.
* Function list: (...).
************************************************************
*/

/* TO_DO: Adjust the function header */

 /* The #define _CRT_SECURE_NO_WARNINGS should be used in MS Visual Studio projects
  * to suppress the warnings about using "unsafe" functions like fopen()
  * and standard sting library functions defined in string.h.
  * The define does not have any effect in Borland compiler projects.
  */
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>   /* standard input / output */
#include <ctype.h>   /* conversion functions */
#include <stdlib.h>  /* standard library functions and constants */
#include <string.h>  /* string functions */
#include <limits.h>  /* integer types constants */
#include <float.h>   /* floating-point types constants */

  /* #define NDEBUG to suppress assert() call */
#include <assert.h>  /* assert() prototype */

/* project header files */

#ifndef COMPILERS_H_
#include "Compilers.h"
#endif

#ifndef BUFFER_H_
#include "Reader.h"
#endif

#ifndef SCANNER_H_
#include "Scanner.h"
#endif

/*
----------------------------------------------------------------
TO_DO: Global vars definitions
----------------------------------------------------------------
*/

/* Global objects - variables */
/* This buffer is used as a repository for string literals. */
extern ReaderPointer stringLiteralTable;	/* String literal table */
i32 line;								/* Current line number of the source code */
extern i32 errorNumber;				/* Defined in platy_st.c - run-time error number */

extern i32 stateType[NUM_STATES];
extern String keywordTable[KWT_SIZE];
extern PTR_ACCFUN finalStateTable[NUM_STATES];
extern i32 transitionTable[NUM_STATES][CHAR_CLASSES];
ScannerData scData;


/* Local(file) global objects - variables */
static ReaderPointer lexemeBuffer;			/* Pointer to temporary lexeme buffer */
static ReaderPointer sourceBuffer;			/* Pointer to input source buffer */

/*
 ************************************************************
 * Intitializes scanner
 *		This function initializes the scanner using defensive programming.
 ***********************************************************
 */

i32 startScanner(ReaderPointer psc_buf) {
	/* Basic scanner initialization */
	readerRecover(psc_buf);
	readerClear(stringLiteralTable);
	line = 1;
	sourceBuffer = psc_buf;
	return EXIT_SUCCESS; /*0*/
}

/*
 ************************************************************
 * Process Token
 *		Main function of buffer, responsible to classify a char (or sequence
 *		of chars). In the first part, a specific sequence is detected (reading
 *		from buffer). In the second part, a pattern (defined by Regular Expression)
 *		is recognized and the appropriate function is called (related to final states
 *		in the Transition Diagram).
 ***********************************************************
 */

Token tokenizer(pp_void) {
    Token currentToken = { 0 }; /* token to return after pattern recognition. Set all structure members to 0 */
    pp_char c;         /* input symbol */
    i32 state = 0;     /* initial state of the FSM */
    i32 lexStart;      /* start offset of a lexeme in the input char buffer (array) */
    i32 lexEnd;        /* end offset of a lexeme in the input char buffer (array) */
    i32 lexLength;     /* token length */
    i32 i;             /* counter */

    //pp_char newc;      // new char

    while (1) { /* endless loop broken by token returns it will generate a warning */
        c = readerGetChar(sourceBuffer);

        /* ------------------------------------------------------------------------
            Part 1: Implementation of token driven scanner.
            Every token is possessed by its own dedicated code
            -----------------------------------------------------------------------
        */

        /* TO_DO: All patterns that do not require accepting functions */
        switch (c) {
            /* Cases for spaces */
            case ' ':
            case '\t':
            case '\f':
                break;
            case '\n':
                line++;
                break;
            /* Cases for symbols */
            case ';':
                currentToken.code = EosT;
                return currentToken;
            case ')':
                currentToken.code = RprT;
                return currentToken;
            case '{':
                currentToken.code = LbrT;
                return currentToken;
            case '}':
                currentToken.code = RbrT;
                return currentToken;
            // Cases for Arithmetic Operators
            case '+':
				currentToken.code = AriOpT;
				currentToken.attribute.arithmeticOperator = Add;
				return currentToken;
            case '-':
                currentToken.code = AriOpT;
                currentToken.attribute.arithmeticOperator = Sub;
                return currentToken;
            case '*':
                currentToken.code = AriOpT;
                currentToken.attribute.arithmeticOperator = Mul;
                return currentToken;
			case '/':
				c = readerGetChar(sourceBuffer);
				if (c == '/') {
					while (c != '\n') {
						c = readerGetChar(sourceBuffer);
					}
					currentToken.code = CmtT;
					return currentToken;
				}
				else {
					currentToken.code = AriOpT;
					currentToken.attribute.arithmeticOperator = Div;
					return currentToken;
				}
			// Cases for Relational Operators
            case '=':
                currentToken.code = RelOpT;
                currentToken.attribute.relationalOperator = Eq;
                return currentToken;
                
            case '>':
                currentToken.code = RelOpT;
                currentToken.attribute.relationalOperator = Gt;
                return currentToken;
            case '<':
                currentToken.code = RelOpT;
                currentToken.attribute.relationalOperator = Lt;
                return currentToken;
            // Cases for Logical Operators
            case '&':
                currentToken.code = LogOpT;
                currentToken.attribute.logicalOperator = And;
                return currentToken;
            case '|':
                currentToken.code = LogOpT;
                currentToken.attribute.logicalOperator = Or;
                return currentToken;
			case '!':
				c = readerGetChar(sourceBuffer);
				if (c == '=') {
					currentToken.code = RelOpT;
					currentToken.attribute.relationalOperator = Ne;
				}
				else {
					readerRetract(sourceBuffer);
					currentToken.code = LogOpT;
					currentToken.attribute.logicalOperator = Not;
				}
				return currentToken;
            
            /* Cases for END OF FILE */
			case CHARSEOF0:
				currentToken.code = SeofT;
				currentToken.attribute.seofType = Seof_0;
				return currentToken;
			case CHARSEOF255:
				currentToken.code = SeofT;
				currentToken.attribute.seofType = Seof_255;
				return currentToken;

            /* ------------------------------------------------------------------------
                Part 2: Implementation of Finite State Machine (DFA) or Transition Table driven Scanner
                Note: Part 2 must follow Part 1 to catch the illegal symbols
                -----------------------------------------------------------------------
            */
            /* TO_DO: Adjust / check the logic for your language */
            default: // general case
                state = nextState(state, c);
                lexStart = readerGetPosRead(sourceBuffer) - 1;
                readerSetMark(sourceBuffer, lexStart);
                int pos = 0;
                while (stateType[state] == NOFS) {
                    c = readerGetChar(sourceBuffer);
                    state = nextState(state, c);
                    pos++;
                }
                if (stateType[state] == FSWR)
                    readerRetract(sourceBuffer);
                lexEnd = readerGetPosRead(sourceBuffer);
                lexLength = lexEnd - lexStart;
                lexemeBuffer = readerCreate((i32)lexLength + 2, 0, MODE_FIXED);
                if (!lexemeBuffer) {
                    fprintf(stderr, "Scanner error: Can not create buffer\n");
                    exit(1);
                }
                readerRestore(sourceBuffer);
                for (i = 0; i < lexLength; i++)
                readerAddChar(lexemeBuffer, readerGetChar(sourceBuffer));
                readerAddChar(lexemeBuffer, READER_TERMINATOR);
                currentToken = (*finalStateTable[state])(readerGetContent(lexemeBuffer, 0));
                readerRestore(lexemeBuffer);
                return currentToken;
        } // switch
    } //while
} // tokenizer



/*
 ************************************************************
 * Get Next State
	The assert(int test) macro can be used to add run-time diagnostic to programs
	and to "defend" from producing unexpected results.
	- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
	(*) assert() is a macro that expands to an if statement;
	if test evaluates to false (zero) , assert aborts the program
	(by calling abort()) and sends the following message on stderr:
	(*) Assertion failed: test, file filename, line linenum.
	The filename and linenum listed in the message are the source file name
	and line number where the assert macro appears.
	- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
	If you place the #define NDEBUG directive ("no debugging")
	in the source code before the #include <assert.h> directive,
	the effect is to comment out the assert statement.
	- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
	The other way to include diagnostics in a program is to use
	conditional preprocessing as shown bellow. It allows the programmer
	to send more details describing the run-time problem.
	Once the program is tested thoroughly #define DEBUG is commented out
	or #undef DEBUG is used - see the top of the file.
 ***********************************************************
 */

i32 nextState(i32 state, pp_char c) {
	i32 col;
	i32 next;
	col = nextClass(c);
	next = transitionTable[state][col];
	if (DEBUG)
		printf("Input symbol: %c Row: %d Column: %d Next: %d \n", c, state, col, next);
	assert(next != FS);
	if (DEBUG)
		if (next == FS) {
			printf("Scanner Error: Illegal state:\n");
			printf("Input symbol: %c Row: %d Column: %d\n", c, state, col);
			exit(1);
		}
	return next;
}

/*
 ************************************************************
 * Get Next Token Class
	* Create a function to return the column number in the transition table:
	* Considering an input char c, you can identify the "class".
	* For instance, a letter should return the column for letters, etc.
 ***********************************************************
 */
 /* TO_DO: Use your column configuration */

 /* Adjust the logic to return next column in TT */
 /*    [A-z],[0-9],    _,    (,   "', SEOF,    /, other
		L(0), D(1), U(2), M(3), Q(4), E(5), C(6),  O(7) */

i32 nextClass(pp_char c) {
	i32 val = -1;

	switch (c) {
	case CHRCOL2:
		val = 2;
		break;
	case CHRCOL3:
		val = 3;
		break;
	case CHRCOL4:
		val = 4;
		break;
	case CHRCOL5:
		val = 5;
		break;
	case CHRCOL6:
		val = 6;
		break;
	case CHARSEOF0:
	case CHARSEOF255:
		val = 7;
		break;
	case MACRO:
		val = 0;
		break;
	default:
		if (isalpha(c))
			val = 0;
		else if (isdigit(c))
			val = 1;
		else
			val = 8;
	}
	return val;
}

/*
 ************************************************************
 * Acceptance State Function COM
 *		Function responsible to identify COM (comments).
 ***********************************************************
 */
 /* TO_DO: Adjust the function for IL */

Token funcCMT(String lexeme) {
	Token currentToken = { 0 };
	i32 i = 0, len = (i32)strlen(lexeme);
	currentToken.attribute.contentString = readerGetPosWrte(stringLiteralTable);
	for (i = 1; i < len - 1; i++) {
		if (lexeme[i] == '\n')
			line++;
	}
	currentToken.code = CmtT;
	return currentToken;
}


/*
 ************************************************************
 * Acceptance State Function IL
 *		Function responsible to identify IL (integer literals).
 * - It is necessary respect the limit (ex: 2-byte integer in C).
 * - In the case of larger lexemes, error shoul be returned.
 * - Only first ERR_LEN characters are accepted and eventually,
 *   additional three dots (...) should be put in the output.
 ***********************************************************
 */
 /* TO_DO: Adjust the function for IL */

Token funcIL(String lexeme) {
	Token currentToken = { 0 };
	i64 tlong;
	if (lexeme[0] != '\0' && strlen(lexeme) > NUM_LEN) {
		currentToken = (*finalStateTable[ESNR])(lexeme);
	}
	else {
		tlong = atol(lexeme);
		if (tlong >= 0 && tlong <= SHRT_MAX) {
			currentToken.code = InlT;
			currentToken.attribute.intValue = (i32)tlong;
		}
		else {
			currentToken = (*finalStateTable[ESNR])(lexeme);
		}
	}
	return currentToken;
}


/*
 ************************************************************
 * Acceptance State Function ID
 *		In this function, the pattern for IDs must be recognized.
 *		Since keywords obey the same pattern, is required to test if
 *		the current lexeme matches with KW from language.
 *	- Remember to respect the limit defined for lexemes (VID_LEN) and
 *	  set the lexeme to the corresponding attribute (vidLexeme).
 *    Remember to end each token with the \0.
 *  - Suggestion: Use "strncpy" function.
 ***********************************************************
 */
 /* TO_DO: Adjust the function for ID */

Token funcMTH(String lexeme) {
	Token currentToken = { 0 };
	size_t length = strlen(lexeme);
	pp_char lastch = lexeme[length - 1];
	i32 isID = FALSE;
	switch (lastch) {
	case MNID_SUF:
		currentToken.code = MthdT;
		isID = TRUE;
		break;
	default:
		currentToken = funcKEY(lexeme);
		break;
	}
	if (isID == TRUE) {
		strncpy(currentToken.attribute.idLexeme, lexeme, VID_LEN);
		currentToken.attribute.idLexeme[VID_LEN] = CHARSEOF0;
	}
	return currentToken;
}


/*
************************************************************
 * Acceptance State Function SL
 *		Function responsible to identify SL (string literals).
 * - The lexeme must be stored in the String Literal Table
 *   (stringLiteralTable). You need to include the literals in
 *   this structure, using offsets. Remember to include \0 to
 *   separate the lexemes. Remember also to incremente the line.
 ***********************************************************
 */

Token funcSL(String lexeme) {
	Token currentToken = { 0 };
	i32 i = 0, len = (i32)strlen(lexeme);
	currentToken.attribute.contentString = readerGetPosWrte(stringLiteralTable);
	for (i = 1; i < len - 1; i++) {
		if (lexeme[i] == '\n')
			line++;
		if (!readerAddChar(stringLiteralTable, lexeme[i])) {
			currentToken.code = RteT;
			strcpy(currentToken.attribute.errLexeme, "Run Time Error:");
			errorNumber = RTE_CODE;
			return currentToken;
		}
	}
	if (!readerAddChar(stringLiteralTable, CHARSEOF0)) {
		currentToken.code = RteT;
		strcpy(currentToken.attribute.errLexeme, "Run Time Error:");
		errorNumber = RTE_CODE;
		return currentToken;
	}
	currentToken.code = StrT;
	return currentToken;
}


/*
************************************************************
 * This function checks if one specific lexeme is a keyword.
 * - Tip: Remember to use the keywordTable to check the keywords.
 ***********************************************************
 */

Token funcKEY(String lexeme) {
	Token currentToken = { 0 };
	i32 kwindex = -1, j = 0;
	for (j = 0; j < KWT_SIZE; j++)
		if (!strcmp(lexeme, &keywordTable[j][0]))
			kwindex = j;
	if (kwindex != -1) {
		currentToken.code = KeyT;
		currentToken.attribute.codeType = kwindex;
	}
	else {
		currentToken.code = VarT;
	}
	return currentToken;
}


/*
************************************************************
 * Acceptance State Function Error
 *		Function responsible to deal with ERR token.
 * - This function uses the errLexeme, respecting the limit given
 *   by ERR_LEN. If necessary, use three dots (...) to use the
 *   limit defined. The error lexeme contains line terminators,
 *   so remember to increment line.
 ***********************************************************
 */
 /* TO_DO: Adjust the function for Errors */

Token funcErr(String lexeme) {
	Token currentToken = { 0 };
	i32 i = 0, len = (i32)strlen(lexeme);
	if (len > ERR_LEN) {
		strncpy(currentToken.attribute.errLexeme, lexeme, ERR_LEN - 3);
		currentToken.attribute.errLexeme[ERR_LEN - 3] = CHARSEOF0;
		strcat(currentToken.attribute.errLexeme, "...");
	}
	else {
		strcpy(currentToken.attribute.errLexeme, lexeme);
	}
	for (i = 0; i < len; i++)
		if (lexeme[i] == '\n')
			line++;
	currentToken.code = ErrT;
	return currentToken;
}


/*
 ************************************************************
 * The function prints the token returned by the scanner
 ***********************************************************
 */

pp_void printToken(Token t) {
	extern String keywordTable[]; /* link to keyword table in */
	switch (t.code) {
	case RteT:
		printf("RTE_T\t\t%s", t.attribute.errLexeme);
		/* Call here run-time error handling component */
		if (errorNumber) {
			printf("%d", errorNumber);
			exit(errorNumber);
		}
		printf("\n");
		break;
	case ErrT:
		printf("ERRT\t\t%s\n", t.attribute.errLexeme);
		scData.scanHistogram[ErrT]++;
		break;
	case SeofT:
		printf("SEOFT\t\t%d\t\n", t.attribute.seofType);
		scData.scanHistogram[SeofT]++;
		break;
	case MthdT:
		printf("MthdT\t\t%s\n", t.attribute.idLexeme);
		scData.scanHistogram[MthdT]++;
		break;
	case InlT:
		printf("InlT\t\t%d\n", t.attribute.intValue);
		scData.scanHistogram[InlT]++;
		break;
	case StrT:
		printf("StrT\t\t%d\t ", (i32)t.attribute.codeType);
		printf("%s\n", readerGetContent(stringLiteralTable, (i32)t.attribute.codeType));
		scData.scanHistogram[StrT]++;
		break;
	case LprT:
		printf("LprT\n");
		scData.scanHistogram[LprT]++;
		break;
	case RprT:
		printf("RprT\n");
		scData.scanHistogram[RprT]++;
		break;
	case LbrT:
		printf("LbrT\n");
		scData.scanHistogram[LbrT]++;
		break;
	case RbrT:
		printf("RbrT\n");
		scData.scanHistogram[RbrT]++;
		break;
	case KeyT:
		printf("KeyT\t\t%s\n", keywordTable[t.attribute.codeType]);
		scData.scanHistogram[KeyT]++;
		break;
	case VarT:
		printf("VarT\n");
		scData.scanHistogram[VarT]++;
		break;
	case CmtT:
		printf("CmtT\n");
		scData.scanHistogram[CmtT]++;
		break;
	case AriOpT:
		if (t.attribute.arithmeticOperator==Add) {
			printf("AddT\n");
		}
		if (t.attribute.arithmeticOperator == Sub) {
			printf("SubT\n");
		}
		if (t.attribute.arithmeticOperator == Mul) {
			printf("MulT\n");
		}
		if (t.attribute.arithmeticOperator == Div){
			printf("DivT\n");
		}
		scData.scanHistogram[AriOpT]++;
		break;
	case RelOpT:
		if (t.attribute.relationalOperator == Eq) {
			printf("Eq\n");

		}
		if (t.attribute.relationalOperator == Ne) {
			printf("Ne\n");
		}
		if (t.attribute.relationalOperator == Gt) {
			printf("Ge\n");
		}
		if (t.attribute.relationalOperator == Lt) {
			printf("Lt\n");
		}
		scData.scanHistogram[RelOpT]++;

		break;
	case LogOpT:
		if (t.attribute.relationalOperator == And) {
			printf("AndT\n");
		}
		if (t.attribute.relationalOperator == Or) {
			printf("OrT\n");
		}
		if (t.attribute.relationalOperator == Not) {
			printf("NotT\n");
		}
		scData.scanHistogram[LogOpT]++;

		break;
	case EosT:
		printf("EOS_T\n");
		scData.scanHistogram[EosT]++;
		break;

	default:
		printf("Scanner error: invalid token code: %d\n", t.code);
	}
}

/*
 ************************************************************
 * The function prints statistics of tokens
 * Param:
 *	- Scanner data
 * Return:
 *	- Void (procedure)
 ***********************************************************
 */
void printScannerData(ScannerData scData) {
	const char* tokenNames[NUM_TOKENS] = {
		"ErrT", "MthdT", "InlT", "StrT", "LprT", "RprT", "LbrT", "RbrT",
		"KeyT", "EosT", "RteT", "SeofT", "CmtT", "AriOpT", "RelOpT",
		"LogOpT", "AssOpT", "IncOpT", "VarT"
	};
	for (int i = 0; i < NUM_TOKENS; i++) {
		printf("Token[%s]=%d\n", tokenNames[i], scData.scanHistogram[i]);
	}
	printf("----------------------------------\n");
}
