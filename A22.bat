:: -----------------------------------------------------------------------
:: COMPILERS COURSE - SCRIPT                                             -
:: SCRIPT A22 - CST8152 - Summer 2023                                    -
:: -----------------------------------------------------------------------

CLS
SET COMPILER=PePE.exe

SET FILE1=INPUT0_Empty
SET FILE2=INPUT1_Hello
SET FILE3=INPUT2_Volume
SET FILE4=INPUT3_Factorial
SET FILE5=INPUT4_Datatypes
SET FILE6=INPUT5_General

SET ASSIGNMENT=A22
SET EXTENSION=pp
SET OUTPUT=out
SET ERROR=err

SET PARAM=S

:: -----------------------------------------------------------------------
:: Begin of Tests (A22 - S22)                                            -
:: -----------------------------------------------------------------------

@echo off

echo "************************************************************"
echo " ____  _____   ____  _____"
echo "|  _ \| ____| |  _ \| ____|"
echo "| |_) |  _|   | |_) |  _|"
echo "|  __/| |___  |  __/| |___"
echo "|_|   |_____| |_|   |_____|"
echo "							 .-----."
echo "							/7  .  ("
echo "						   /   .-.  \"
echo "						  /   /   \  \"
echo "						 / `  )   (   )"
echo "						/ `   )   ).  \"
echo "					  .'  _.   \_/  . |"
echo "	 .--.           .' _.' )`.        |"
echo "	(    `---...._.'   `---.'_)    ..  \"
echo "	 \            `----....___    `. \  |"
echo "	  `.           _ ----- _   `._  )/  |"
echo "		`.       /\  \   /\  \`.  `._   |"
echo "		  `.    ((O)` ) ((O)` ) `.   `._\"
echo "			`-- '`---'   `---' )  `.    `-."
echo "			   /                  ` \      `-."
echo "			 .'                      `.       `."
echo "			/                     `  ` `.       `-."
echo "	 .--.   \ ===._____.======. `    `   `. .___.--`     .''''."
echo "	' .` `-. `.                )`. `   ` ` \          .' . '  8)"
echo "   (8  .  ` `-.`.               ( .  ` `  .`\      .'  '    ' /"
echo "	\  `. `    `-.               ) ` .   ` ` \  .'   ' .  '  /"
echo "	 \ ` `.  ` . \`.    .--.     |  ` ) `   .``/   '  // .  /"
echo "	  `.  ``. .   \ \   .-- `.  (  ` /_   ` . / ' .  '/   .'"
echo "		`. ` \  `  \ \  '-.   `-'  .'  `-.  `   .  .'/  .'"
echo "		  \ `.`.  ` \ \    ) /`._.`       `.  ` .  .'  /"
echo "		   |  `.`. . \ \  (.'               `.   .'  .'"
echo "		__/  .. \ \ ` ) \                     \.' .. \__"
echo " .-._.-'     '\  ) .-'   `.                   (  '\     `-._.--."
echo "(_________.-====' / .' /\_)`--..__________..-- `====-. _________)"
echo "				 (.'(.'"
echo "************************************************************"

ECHO "                                                   "
ECHO "[SCANNER SCRIPT ..................................]"
ECHO "                                                   "

ren *.exe %COMPILER%

::
:: BASIC TESTS  ----------------------------------------------------------
::
:: Basic Tests (A22 - S22) - - - - - - - - - - - - - - - - - - - - - -

%COMPILER% %PARAM% %FILE1%.%EXTENSION%	> %FILE1%-%ASSIGNMENT%.%OUTPUT%	2> %FILE1%-%ASSIGNMENT%.%ERROR%
%COMPILER% %PARAM% %FILE2%.%EXTENSION%	> %FILE2%-%ASSIGNMENT%.%OUTPUT%	2> %FILE2%-%ASSIGNMENT%.%ERROR%
%COMPILER% %PARAM% %FILE3%.%EXTENSION%	> %FILE3%-%ASSIGNMENT%.%OUTPUT%	2> %FILE3%-%ASSIGNMENT%.%ERROR%
%COMPILER% %PARAM% %FILE4%.%EXTENSION%	> %FILE4%-%ASSIGNMENT%.%OUTPUT%	2> %FILE4%-%ASSIGNMENT%.%ERROR%
%COMPILER% %PARAM% %FILE5%.%EXTENSION%	> %FILE5%-%ASSIGNMENT%.%OUTPUT%	2> %FILE5%-%ASSIGNMENT%.%ERROR%
%COMPILER% %PARAM% %FILE6%.%EXTENSION%	> %FILE6%-%ASSIGNMENT%.%OUTPUT%	2> %FILE6%-%ASSIGNMENT%.%ERROR%

:: SHOW OUTPUTS - - - - - - - - - - - - - - - - - - - - - - - - - - -
DIR *.OUT
DIR *.ERR

:: -----------------------------------------------------------------------
:: End of Tests (A22 - S22)                                              -
:: -----------------------------------------------------------------------
