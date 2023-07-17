/*
************************************************************
* COMPILERS COURSE - Algonquin College
* Code version: Summer, 2023
* Author: Jose Vinueza
* Professors: Paulo Sousa
************************************************************
###################################################
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
* File name: compilers.c
* Compiler: MS Visual Studio 2022
* Course: CST 8152 – Compilers, Lab Section: [011, 012]
* Assignment: A12, A22, A32.
* Date: May 01 2023
* Professor: Paulo Sousa
* Purpose: This file is the main program of Compilers Project
* Function list: main().
************************************************************
*/


#include <stdio.h>
#include <stdlib.h>

#ifndef COMPILERS_H_
#include "Compilers.h"
#endif

/*
 * ............................................................................
 * ADVICE 1:
 * Please check the "TODO" labels to develop your activity.
 *
 * ADVICE 2: This file must be updated according to each assignment
 * (see the progression: reader > scanner > parser).
 * ............................................................................
 */

/*
***********************************************************
* Function name: main
* Purpose: Main function
* Author: Paulo Sousa
* History/Versions: Ver F22
* Called functions: mainReader(), mainScanner(), mainParser()
* Parameters: Command line arguments - argc, argv
* Return value: Status
* Algorithm: -
*************************************************************
*/

i32 main(int argc, char** argv) {
	i32 i;
	pp_char option;
	printLogo();
	if (DEBUG) {
		for (i = 0; i < argc; ++i)
			printf("argv[%d] = %s\n", i, argv[i]);
	}
	if (argc < 2) {
		printf("%s%c%s%c%s%c%s", "OPTIONS:\n* [",
			PGM_READER, "] - Reader\n* [",
			PGM_SCANNER, "] - Scanner\n* [",
			PGM_PARSER, "] - Parser\n");
		return EXIT_FAILURE;
	}
	option = argv[1][0];
	switch (option) {
	case PGM_READER:
		printf("%s%c%s", "\n[Option '", PGM_READER, "': Starting READER .....]\n\n");
		mainReader(argc, argv);
		break;
	case PGM_SCANNER:
		printf("%s%c%s", "\n[Option '", PGM_SCANNER, "': Starting SCANNER ....]\n\n");
		mainScanner(argc, argv);
		break;
	/*case PGM_PARSER:
		printf("%s%c%s", "\n[Option '", PGM_PARSER, "': Starting PARSER .....]\n\n");
		mainParser(argc, argv);
		break;*/
	default:
		printf("%s%c%s%c%s%c%s", "* OPTIONS:\n- [",
			PGM_READER, "] - Reader\n- [",
			PGM_SCANNER, "] - Scanner\n- [",
			PGM_PARSER, "] - Parser\n");
		break;
	}
	return EXIT_SUCCESS;
}

/*
***********************************************************
* Function name: printLogo
* Purpose: Print Logo
* Author: Paulo Sousa
* History/Versions: Ver S23
* Called functions: -
* Parameters: -
* Return value: (Null)
* Algorithm: -
*************************************************************
*/
pp_void printLogo() {
	printf(
		"                             .-----.\n"
		"                            /7  .  (\n"
		"                           /   .-.  \\\n"
		"                          /   /   \\  \\\n"
		"                         / `  )   (   )\n"
		"                        / `   )   ).  \\\n"
		"                      .'  _.   \\_/  . |\n"
		"     .--.           .' _.' )`.        |\n"
		"    (    `---...._.'   `---.'_)    ..  \\\n"
		"     \\            `----....___    `. \\  |\n"
		"      `.           _ ----- _   `._  )/  |\n"
		"        `.       /\"  \\   /\"  \\`.  `._   |\n"
		"          `.    ((O)` ) ((O)` ) `.   `._\\\n"
		"            `-- '`---'   `---' )  `.    `-.\n"
		"               /                  ` \\      `-.\n"
		"             .'                      `.       `.\n"
		"            /                     `  ` `.       `-.\n"
		"     .--.   \\ ===._____.======. `    `   `. .___.--`     .''''.\n"
		"    ' .` `-. `.                )`. `   ` ` \\          .' . '  8)\n"
		"   (8  .  ` `-.`.               ( .  ` `  .`\\      .'  '    ' /\n"
		"    \\  `. `    `-.               ) ` .   ` ` \\  .'   ' .  '  /\n"
		"     \\ ` `.  ` . \\`.    .--.     |  ` ) `   .``/   '  // .  /\n"
		"      `.  ``. .   \\ \\   .-- `.  (  ` /_   ` . / ' .  '/   .'\n"
		"        `. ` \\  `  \\ \\  '-.   `-'  .'  `-.  `   .  .'/  .'\n"
		"          \\ `.`.  ` \\ \\    ) /`._.`       `.  ` .  .'  /\n"
		"           |  `.`. . \\ \\  (.'               `.   .'  .'\n"
		"        __/  .. \\ \\ ` ) \\                     \\.' .. \\__\n"
		" .-._.-'     '\"  ) .-'   `.                   (  '\"     `-._.--.\n"
		"(_________.-====' / .' /\\_)`--..__________..-- `====-. _________)\n"
		"             (.'(.'\n");
}
