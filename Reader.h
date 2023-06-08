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
* File name: Reader.h
* Compiler: MS Visual Studio 2022
* Course: CST 8152 – Compilers, Lab Section: [011, 012]
* Assignment: A12.
* Date: May 01 2023
* Professor: Paulo Sousa
* Purpose: This file is the main header for Reader (.h)
************************************************************
*/

/*
 *.............................................................................
 * MAIN ADVICE:
 * Please check the "TODO" labels to develop your activity.
 *.............................................................................
 */


#ifndef COMPILERS_H_
#include "Compilers.h"
#endif

#ifndef READER_H_
#define READER_H_

/* TIP: Do not change pragmas, unless necessary .......................................*/
/*#pragma warning(1:4001) *//*to enforce C89 type comments  - to make //comments an warning */
/*#pragma warning(error:4001)*//* to enforce C89 comments - to make // comments an error */

/* standard header files */
#include <stdio.h>  /* standard input/output */
#include <malloc.h> /* for dynamic memory allocation*/
#include <limits.h> /* implementation-defined data type ranges and limits */

/* CONSTANTS DEFINITION: GENERAL (NOT LANGUAGE DEPENDENT) .................................. */

/* Modes (used to create buffer reader) */
enum READER_MODE {
	MODE_FIXED = 'F', /* Fixed mode (constant size) */
	MODE_ADDIT = 'A', /* Additive mode (constant increment to be added) */
	MODE_MULTI = 'M'  /* Multiplicative mode (constant increment to be multiplied) */
};

/* Constants about controls (not need to change) */
#define READER_ERROR		(-1)						/* General error message */
#define READER_TERMINATOR	'\0'							/* General EOF */

/* CONSTANTS DEFINITION: PREFIXED BY LANGUAGE NAME (SOFIA) .................................. */

/* You should add your own constant definitions here */
#define READER_MAX_SIZE	INT_MAX-1	/* maximum capacity */ 

#define READER_DEFAULT_SIZE			250		/* default initial buffer reader capacity */
#define READER_DEFAULT_INCREMENT	10		/* default increment factor */

/* Add your bit-masks constant definitions here - Defined for BOA */
/* BITS                                (7654.3210) */
#define READER_DEFAULT_FLAG 0x00 	/* (0000.0000)_2 = (000)_10 */
/* TO_DO: BIT 3: FUL = Full */
/* TO_DO: BIT 2: EMP: Empty */
/* TO_DO: BIT 1: REL = Relocation */
/* TO_DO: BIT 0: END = EndOfBuffer */
#define READER_FUL_FLAG     0x08 	
#define READER_RSTFUL_FLAG	-READER_FUL_FLAG
#define READER_CHKFUL_FLAG	READER_FUL_FLAG

#define READER_EMP_FLAG     0x04 	
#define READER_REL_FLAG     0x02 	
#define READER_END_FLAG     0x01 

#define NCHAR				128			/* Chars from 0 to 127 */

#define CHARSEOF			(-1)		/* EOF Code for Reader */

/* STRUCTURES DEFINITION: SUFIXED BY LANGUAGE NAME (SOFIA) .................................. */

/* Offset declaration */
typedef struct offset {
	i32 mark;			/* the offset to the mark position (in chars) */
	i32 read;			/* the offset to the get a char position (in chars) */
	i32 wrte;			/* the offset to the add chars (in chars) */
} Offset;

/* Buffer structure */
typedef struct bufferReader {
	String	content;			/* pointer to the beginning of character array (character buffer) */
	i32	size;				/* current dynamic memory size (in bytes) allocated to character buffer */
	i32	increment;			/* character array increment factor */
	i32	mode;				/* operational mode indicator */
	u8	flags;				/* contains character array reallocation flag and end-of-buffer flag */
	Offset		offset;				/* Offset / position field */
	i32	histogram[NCHAR];	/* Statistics of chars */
	i32	numReaderErrors;	/* Number of errors from Reader */
} BufferReader, * ReaderPointer;

/* FUNCTIONS DECLARATION:  .................................. */
/* General Operations */
ReaderPointer	readerCreate		(i32, i32, i32);
ReaderPointer	readerAddChar		(ReaderPointer const, pp_char);
pp_boln		readerClear		    (ReaderPointer const);
pp_boln		readerFree		    (ReaderPointer const);
pp_boln		readerIsFull		(ReaderPointer const);
pp_boln		readerIsEmpty		(ReaderPointer const);
pp_boln		readerSetMark		(ReaderPointer const, i32);
i32		readerPrint		    (ReaderPointer const);
i32		readerLoad			(ReaderPointer const, FILE* const);
pp_boln		readerRecover		(ReaderPointer const);
pp_boln		readerRetract		(ReaderPointer const);
pp_boln		readerRestore		(ReaderPointer const);
/* Getters */
pp_char		readerGetChar		(ReaderPointer const);
String		readerGetContent	(ReaderPointer const, i32);
i32		readerGetPosRead	(ReaderPointer const);
i32		readerGetPosWrte	(ReaderPointer const);
i32		readerGetPosMark	(ReaderPointer const);
i32		readerGetSize		(ReaderPointer const);
i32		readerGetInc		(ReaderPointer const);
i32		readerGetMode		(ReaderPointer const);
u8		readerGetFlags		(ReaderPointer const);
pp_void		readerPrintStat		(ReaderPointer const);
i32		readerNumErrors		(ReaderPointer const);

#endif
