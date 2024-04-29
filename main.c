#include <stdio.h>

/* Password generator*/ 

/* should fill empty space with not specified characters*/
/* should append chars, then symbols, then numbers (if want good password, see -m) */


/* Functionality:
 * length "-l <int>" (check if input valid with length)
 * number of alphabet chars "-a <int>"
 * number of numbers "-n <int>"
 * number of special symbols "-s <int>"
 * randomize case "-rc"
 * mix "-m"
 * use defaults "-d"
*/


int main(int argc, char* argv[])
{
	if (argc == 1)
	{
		printf(
				"Create password:\n"
				"\t-l <int> -> specify length\n"
				"\t-a <int> -> specify number of alpha chars\n"
				"\t-n <int> -> specify number of digits\n"
				"\t-s <int> -> specify number of special chars\n"
				"\t-rc -> randomize case of alpha chars (default is all lower)\n"
				"\t-m -> mix password (default password: <alpha><symb><numbers>)\n"
				"\t-d -> default password (-l, -a, -n not allowed)\n"
				);
		return 0;
	}
}
