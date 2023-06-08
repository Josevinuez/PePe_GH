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
***********************************************************
* File name: Reader.c
* Compiler: MS Visual Studio 2022
* Course: CST 8152 – Compilers, Lab Section: [011, 012, 013]
* Assignment: A12.
* Date: May 01 2023
* Professor: Paulo Sousa
* Purpose: This file is the main code for Buffer/Reader (A12)
************************************************************
*/

/*
 *.............................................................................
 * MAIN ADVICE:
 * - Please check the "TODO" labels to develop your activity.
 * - Review the functions to use "Defensive Programming".
 *.............................................................................
 */

#ifndef COMPILERS_H_
#include "Compilers.h"
#endif

#ifndef READER_H_
#include "Reader.h"
#endif

/*
***********************************************************
* Function name: readerCreate
* Purpose: Creates the buffer reader according to capacity, increment
	factor and operational mode ('f', 'a', 'm')
* Author: Svillen Ranev / Paulo Sousa
* History/Versions: S22
* Called functions: calloc(), malloc()
* Parameters:
*   size = initial capacity
*   increment = increment factor
*   mode = operational mode
* Return value: bPointer (pointer to reader)
* Algorithm: Allocation of memory according to inicial (default) values.
* TODO ......................................................
*	- Adjust datatypes for your LANGUAGE.
*   - Use defensive programming
*	- Check boundary conditions
*	- Check flags.
*************************************************************
*/

ReaderPointer readerCreate(i32 size, i32 increment, i32 mode) {
	ReaderPointer readerPointer;
	/*  Defensive programming */
	/*  Adjust the values according to parameters */

	if (size <= 0) {
		size = READER_DEFAULT_SIZE;
		increment = READER_DEFAULT_INCREMENT;
	}
	if (increment <= 0) {
		mode = MODE_FIXED;
	}
	if (mode != MODE_FIXED && mode != MODE_ADDIT && mode != MODE_MULTI) {
		return NULL; // Invalid mode, do not create the reader
	}

	readerPointer = (ReaderPointer)calloc(1, sizeof(BufferReader));
	if (!readerPointer)
		return NULL;

	readerPointer->content = (String)malloc(size);
	if (!readerPointer->content) {
		free(readerPointer);
		return NULL; // Memory allocation failed
	}
	/*  Defensive programming */
		/* Initialize the histogram */
	for (int i = 0; i < 128; i++) {
		readerPointer->histogram[i] = 0;
	}
	readerPointer->size = size;
	readerPointer->increment = increment;
	readerPointer->mode = mode;

	/*  Initialize flags */
	readerPointer->flags = READER_DEFAULT_FLAG;
	readerPointer->flags |= READER_EMP_FLAG;

	/*  The created flag must be signalized as EMP */
	readerPointer->flags = READER_EMP_FLAG;

	return readerPointer;
}


/*
***********************************************************
* Function name: readerAddChar
* Purpose: Adds a char to buffer reader
* Parameters:
*   readerPointer = pointer to Buffer Reader
*   ch = char to be added
* Return value:
*	readerPointer (pointer to Buffer Reader)
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/

ReaderPointer readerAddChar(ReaderPointer const readerPointer, pp_char ch) {
	String tempReader = NULL;
	i32 newSize = 0;
	/* TO_DO: Defensive programming */
	if (!readerPointer || !readerPointer->content) {
		return NULL;
	}
	/* TO_DO: Reset Realocation */
	readerPointer->flags &= ~READER_RSTFUL_FLAG;

	/* TO_DO: Test the inclusion of chars */
	if (readerPointer->offset.wrte * (i32)sizeof(pp_char) < readerPointer->size) {
		/* TO_DO: This buffer is NOT full */
	} else {
		/* TO_DO: Reset Full flag */
		readerPointer->flags &= ~READER_FUL_FLAG;

		switch (readerPointer->mode) {
		case MODE_FIXED:
			return NULL;
		case MODE_ADDIT:
			/* TO_DO: Adjust new size */
			newSize = readerPointer->size + readerPointer->increment;
			/* TO_DO: Defensive programming */
			if (newSize < readerPointer->size || newSize > READER_MAX_SIZE) {
				readerPointer->flags |= READER_FUL_FLAG;
				return NULL;
			}
			break;
		case MODE_MULTI:
			/* TO_DO: Adjust new size */
			newSize = readerPointer->size * readerPointer->increment;
			/* TO_DO: Defensive programming */
			if (newSize < readerPointer->size || newSize > READER_MAX_SIZE) {
				readerPointer->flags |= READER_FUL_FLAG;
				return NULL;
			}
			break;
		default:
			return NULL;
		}
		/* TO_DO: New reader allocation */
		tempReader = (String)realloc(readerPointer->content, newSize * sizeof(pp_char));
		/* TO_DO: Defensive programming */
		if (!tempReader) {
			readerPointer->flags |= READER_FUL_FLAG;
			return NULL;
		}
		/* TO_DO: Check Relocation */
		if (tempReader != readerPointer->content) {
			readerPointer->flags |= READER_REL_FLAG;
		}
		readerPointer->content = tempReader;
		readerPointer->size = newSize;
	}
	/* TO_DO: Add the char */
	readerPointer->content[readerPointer->offset.wrte++] = ch;
	/* TO_DO: Updates histogram */
	if (ch >= 0 && ch < NCHAR) {
		readerPointer->histogram[ch]++;
	}
	return readerPointer;
}

/*
***********************************************************
* Function name: readerClear
* Purpose: Clears the buffer reader
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
pp_boln readerClear(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (!readerPointer) {
		return FALSE;
	}
	/* Reset offsets */
	readerPointer->offset.read = 0;
	readerPointer->offset.wrte = 0;

	/* TO_DO: Adjust flags original */
	readerPointer->flags = READER_DEFAULT_FLAG;
	/* Clear histogram */
	memset(readerPointer->histogram, 0, NCHAR * sizeof(i32));
	return TRUE;
}

/*
***********************************************************
* Function name: readerFree
* Purpose: Releases the buffer address
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
pp_boln readerFree(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (readerPointer == NULL)
		return FALSE;
	/* TO_DO: Free pointers */
	free(readerPointer->content);
	free(readerPointer);

	return TRUE;
}

/*
***********************************************************
* Function name: readerIsFull
* Purpose: Checks if buffer reader is full
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
pp_boln readerIsFull(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (readerPointer == NULL)
		return FALSE;
	/* TO_DO: Check flag if buffer is FUL */
	if ((readerPointer->flags & READER_CHKFUL_FLAG) == READER_FUL_FLAG)
		return TRUE;
	else
		return FALSE;
}


/*
***********************************************************
* Function name: readerIsEmpty
* Purpose: Checks if buffer reader is empty.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
pp_boln readerIsEmpty(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (readerPointer == NULL)
		return TRUE;
	/* TO_DO: Check flag if buffer is EMP */
	if ((readerPointer->flags & READER_CHKFUL_FLAG) && (readerPointer->flags & READER_EMP_FLAG))
		return TRUE;
	else
		return FALSE;
}

/*
***********************************************************
* Function name: readerSetMark
* Purpose: Adjust the position of mark in the buffer
* Parameters:
*   readerPointer = pointer to Buffer Reader
*   mark = mark position for char
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
pp_boln readerSetMark(ReaderPointer const readerPointer, i32 mark) {
	/* TO_DO: Defensive programming */
	if (readerPointer == NULL)
		return FALSE;

	/* TO_DO: Adjust mark */
	if (mark < 0 || mark > readerPointer->offset.wrte)
		return FALSE;

	readerPointer->offset.mark = mark;

	return TRUE;
}


/*
***********************************************************
* Function name: readerPrint
* Purpose: Prints the string in the buffer.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Number of chars printed.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
i32 readerPrint(ReaderPointer const readerPointer) {
	i32 cont = 0;
	pp_char c;
	/* TO_DO: Defensive programming (including invalid chars) */
	c = readerGetChar(readerPointer);
	/* TO_DO: Check flag if buffer EOB has achieved */
	while (cont < readerPointer->offset.wrte) {
		c = readerGetChar(readerPointer);
		if (readerGetFlags(readerPointer) & READER_END_FLAG)
			break;
		printf("%c", c);
		cont++;
	}
	return cont;
}

/*
***********************************************************
* Function name: readerLoad
* Purpose: Loads the string in the buffer with the content of
	an specific file.
* Parameters:
*   readerPointer = pointer to Buffer Reader
*   fileDescriptor = pointer to file descriptor
* Return value:
*	Number of chars read and put in buffer.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
i32 readerLoad(ReaderPointer const readerPointer, FILE* const fileDescriptor) {
	i32 size = 0;
	pp_char c;
	/* TO_DO: Defensive programming */
	if (readerPointer == NULL || fileDescriptor == NULL)
		return READER_ERROR;

	c = (pp_char)fgetc(fileDescriptor);
	while (!feof(fileDescriptor)) {
		if (!readerAddChar(readerPointer, c)) {
			ungetc(c, fileDescriptor);
			return READER_ERROR;
		}
		if (readerIsFull(readerPointer)) {
			ungetc(c, fileDescriptor);
			return READER_ERROR;
		}
		c = (char)fgetc(fileDescriptor);
		size++;
	}
	/* TO_DO: Defensive programming */
	return size;
}


/*
***********************************************************
* Function name: readerRecover
* Purpose: Rewinds the buffer.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
pp_boln readerRecover(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (readerPointer == NULL)
		return FALSE;

	// Check if mark offset is out of bounds
	if (readerPointer->offset.mark < 0 || readerPointer->offset.mark > readerPointer->offset.wrte)
		return FALSE;
	// Reset offsets and flags
	readerPointer->offset.read = 0;
	readerPointer->offset.wrte = 0;
	readerPointer->flags = READER_DEFAULT_FLAG;

	/* TO_DO: Recover positions */
	readerPointer->content += readerPointer->offset.mark;
	readerPointer->offset.wrte -= readerPointer->offset.mark;
	readerPointer->offset.mark = 0;

	return TRUE;
}


/*
***********************************************************
* Function name: readerRetract
* Purpose: Retracts the buffer to put back the char in buffer.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
pp_boln readerRetract(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (readerPointer == NULL) {
		return FALSE;
	}
	if (readerPointer->offset.read <= 0) {
		return FALSE;
	}
	/* TO_DO: Retract (return 1 pos read) */
	readerPointer->offset.read--;

	return TRUE;
}


/*
***********************************************************
* Function name: readerRestore
* Purpose: Resets the buffer.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
pp_boln readerRestore(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (readerPointer == NULL) {
		return FALSE;
	}/* Check if mark offset is within valid range */
	if (readerPointer->offset.mark < 0 || readerPointer->offset.mark > readerPointer->offset.wrte) {
		return FALSE;
	}
	/* TO_DO: Restore positions (read/mark) */
	readerPointer->offset.read = readerPointer->offset.mark;

	return TRUE;
}


/*
***********************************************************
* Function name: readerGetChar
* Purpose: Returns the char in the getC position.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Char in the getC position.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
pp_char readerGetChar(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (readerPointer == NULL) {
		return CHARSEOF;
	}
	/* Increment readPos offset */
	readerPointer->offset.read++;

	/* TO_DO: Check condition to read/wrte */
	if (readerPointer->offset.read == readerPointer->offset.wrte) {
		/* Set END flag */
		readerPointer->flags |= READER_END_FLAG;
		return CHARSEOF;
	}

	/* TO_DO: Reset EOB flag */
	readerPointer->flags &= ~READER_END_FLAG;

	return readerPointer->content[readerPointer->offset.read++];
}


/*
***********************************************************
* Function name: readerGetContent
* Purpose: Returns the pointer to String.
* Parameters:
*   readerPointer = pointer to Buffer Reader
*   pos = position to get the pointer
* Return value:
*	Position of string char.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
String readerGetContent(ReaderPointer const readerPointer, i32 pos) {
	/* TO_DO: Defensive programming */
	if (readerPointer == NULL || pos < 0 || pos >= readerPointer->offset.wrte) {
		return NULL;
	}
	/* TO_DO: Return content (string) */
	return readerPointer->content + pos;
}


/*
***********************************************************
* Function name: readerGetPosRead
* Purpose: Returns the value of getCPosition.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	The read position offset.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
i32 readerGetPosRead(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (readerPointer == NULL || readerPointer->offset.read < 0 || readerPointer->offset.read >= readerPointer->offset.wrte) {
		return READER_ERROR;  // Invalid read position
	}
	/* TO_DO: Return read */
	return readerPointer->offset.read;
}


/*
***********************************************************
* Function name: readerGetPosWrte
* Purpose: Returns the position of char to be added
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Write position
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
i32 readerGetPosWrte(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (readerPointer == NULL) {
		return READER_ERROR;  // Invalid reader pointer
	}
	/* TO_DO: Return wrte */
	return readerPointer->offset.wrte;
}


/*
***********************************************************
* Function name: readerGetPosMark
* Purpose: Returns the position of mark in the buffer
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Mark position.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
i32 readerGetPosMark(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (readerPointer == NULL) {
		return READER_ERROR;  // Invalid reader pointer
	}
	/* TO_DO: Return mark */
	return readerPointer->offset.mark;
}


/*
***********************************************************
* Function name: readerGetSize
* Purpose: Returns the current buffer capacity
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Size of buffer.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
i32 readerGetSize(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (readerPointer == NULL) {
		return READER_ERROR;  // Invalid reader pointer
	}
	/* TO_DO: Return size */
	return readerPointer->size;
}

/*
***********************************************************
* Function name: readerGetInc
* Purpose: Returns the buffer increment.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	The Buffer increment.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
i32 readerGetInc(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (readerPointer == NULL) {
		return READER_ERROR;  // Invalid reader pointer
	}

	/* Check boundary conditions */
	if (readerPointer->increment < 0) {
		return READER_ERROR;  // Invalid increment value
	}

	/* TO_DO: Return increment */
	return readerPointer->increment;
}

/*
***********************************************************
* Function name: readerGetMode
* Purpose: Returns the operational mode
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Operational mode.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
i32 readerGetMode(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (readerPointer == NULL) {
		return READER_ERROR;  // Invalid reader pointer
	}

	/* Check boundary condition */
	if (readerPointer->mode < MODE_FIXED || readerPointer->mode > MODE_MULTI) {
		return READER_ERROR;  // Invalid mode value
	}
	/* TO_DO: Return mode */
	return readerPointer->mode;
}


/*
***********************************************************
* Function name: readerGetFlags
* Purpose: Returns the entire flags of Buffer.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Flags from Buffer.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
u8 readerGetFlags(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (readerPointer == NULL) {
		return 0;  // Invalid reader pointer
	}
	/* TO_DO: Return flags */
	return readerPointer->flags;
}



/*
***********************************************************
* Function name: readerPrintStat
* Purpose: Shows the char statistic.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value: (Void)
* TO_DO:
*   - Use defensive programming
*	- Adjust for your LANGUAGE.
*************************************************************
*/
pp_void readerPrintStat(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (readerPointer == NULL) {
		printf("Invalid reader pointer.\n");
		return;
	}
	/* TO_DO: Print the histogram */
	printf("Reader Statistics:\n");
	printf("Size: %d\n", readerGetSize(readerPointer));
	printf("Increment: %d\n", readerGetInc(readerPointer));
	printf("Mode: %d\n", readerGetMode(readerPointer));
	printf("Flags: %u\n", readerGetFlags(readerPointer));

	printf("Histogram:\n");
	for (int i = 0; i < NCHAR; i++) {
		printf("Char '%c': Count %d\n", i, readerPointer->histogram[i]);
	}

}

/*
***********************************************************
* Function name: readerNumErrors
* Purpose: Returns the number of errors found.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Number of errors.
* TO_DO:
*   - Use defensive programming
*	- Adjust for your LANGUAGE.
*************************************************************
*/
i32 readerNumErrors(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (readerPointer == NULL) {
		return 0;
	}
	/* TO_DO: Returns the number of errors */
	return readerPointer->numReaderErrors;
}
