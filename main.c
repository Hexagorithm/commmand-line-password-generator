

/* Password generator*/ 

/* should fill empty space with not specified characters*/
/* should append chars, then symbols, then numbers (if want good password, see -m) */


/* Functionality:
 * length "-l <int>" (check if input valid with length)
 * number of alphabet chars "-a <int>"
 * number of numbers "-n <int>"
 * number of special symbols "-s <int>"
 * randomize case "-r"
 * mix "-m"
 * use defaults "-d"
*/

#include <stdio.h> 
#include <stdbool.h> //bools
#include <string.h> //strlen

#define DEFAULT_LENGTH 10 /* default length */
#define DEFAULT_NALPHAS 5 /* default number of alpha characters*/
#define DEFAULT_NDIGITS 3 /* default number of digits */
#define DEFAULT_NSYMBOLS 2 /* default number of symbols */
char alphas[] = "abcdefghijklmnoprstuwyxz";
char digits[] = "0123456789";
char symbols[] = "!@#$%^&*()";

int length = DEFAULT_LENGTH; 
int nalphas = DEFAULT_NALPHAS; 
int ndigits = DEFAULT_NDIGITS; 
int nsymbols = DEFAULT_NSYMBOLS; 

/* Check if option was specified or not */
bool isdefault = false;
bool ismix = false;
bool israncase = false;
bool islength = false;
bool isalphas = false;
bool isnumbers = false;
bool issymbols = false;


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
				"\t-r -> randomize case of alpha chars (default is all lower)\n"
				"\t-m -> mix password (default password: <alpha><symb><numbers>)\n"
				"\t-d -> default password (-l, -a, -n not allowed)\n"
				);
		return 0;
	}
	char* current_option;
	for (int i = 1; i < argc ; ++i)
	{
		current_option = argv[i];
		if (current_option[0] != '-') continue;
		printf("Option detected: %s\n",current_option);
		if (strlen(current_option) != 2) 
		{
			printf("Illegal option detected: \"%s\".\n",current_option);
			return 1;
		}
		switch(current_option[1])
		{
			case 'l':
				islength = true;
				break;
			case 'a':
				isalphas = true;
				break;
			case 'n':
				isnumbers = true;
				break;
			case 's':
				issymbols = true;
				break;
			case 'r':
				israncase =true;
				break;
			case 'm':
				ismix = true;
				break;
			case 'd':
				isdefault = true;
				break;
			default:
				printf("Unrecognized option: \"%s\".\n",current_option);
				return 1;


		}
	}
}
