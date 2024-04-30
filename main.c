/* Password generator*/ 

/* Functionality:
 * length "-l <int>" (check if input valid with length)
 * number of alphabet chars "-a <int>"
 * number of numbers "-n <int>"
 * number of special symbols "-s <int>"
 * randomize case "-r"
 * mix "-m"
 * use defaults "-d"
 * verbose output "-v"
*/

#include <stdio.h> 
#include <stdbool.h> /* bools */
#include <string.h> /* strlen memset */
#include <stdlib.h> /* atoi malloc free srand rand*/
#include <time.h> /* for random numbers */
#include <ctype.h> /* to upper for randomize case */



#define DEFAULT_LENGTH     10 /* default length */
#define DEFAULT_NALPHAS     5 /* default number of alpha characters*/
#define DEFAULT_NDIGITS     3 /* default number of digits */
#define DEFAULT_NSYMBOLS    2 /* default number of symbols */
#define MAX_MIX_ITERATIONS 30 /* number of times mix should mix */
#define VERBOSE if (isverbose)
char alphas[] = "abcdefghijklmnoprstuwyxz";
char digits[] = "0123456789";
char symbols[] = "!@#$%^&*()";

unsigned int length = 0;
unsigned int nalphas = 0;
unsigned int ndigits = 0;
unsigned int nsymbols = 0;

/* Check if option was specified or not */
bool isdefault = false;
bool ismix = false;
bool israncase = false;
bool islength = false;
bool isalphas = false;
bool isnumbers = false;
bool issymbols = false;
bool isverbose = false;

void addAlphas(char* dest);
void addDigits(char* dest);
void addSymbols(char* dest);
void mix(char* dest);
void randomizeCase(char* dest);
int get_length(void);
int is_one_category_missing(void);
void autofill_category(int code);

int main(int argc, char* argv[])
{
	srand(time(0)); /* initialize random integer sequence*/
	if (argc == 1)
	{
		printf(
				"Create password:\n"
				"\t-l <uint> - length\n"
				"\t-a <uint> - alphabet chars\n"
				"\t-n <uint> - digits\n"
				"\t-s <uint> - special\n"
				"\t-r       - randomize case (default is all lower)\n"
				"\t-m       - mix password (default password: <alpha><symb><numbers>)\n"
				"\t-d -> default -l, -a, -n, -s values\n"
				"\t-v -> verbose output\n"
				);
		return 0;
	}
	char* current_option;
	for (int i = 1; i < argc ; ++i)
	{
		current_option = argv[i];
		if (current_option[0] != '-') continue;
		if (strlen(current_option) != 2) 
		{
			printf("Illegal option detected: \"%s\".\n",current_option);
			return 1;
		}
		switch(current_option[1])
		{
			case 'l':
				if (i + 1 == argc) /* check if flag with mandatory parameter is last argument*/
				{
					printf("%s: no parameter given.\n", current_option);
					return 1;
				}
				else if (atoi(argv[i+1]) == 0 && argv[i+1][0] != 0)
				{
					printf("%s: invalid value: \"%s\"\n",current_option, argv[i+1]);
					return 1;
				}
				length = atoi(argv[i+1]);
				islength = true;
				break;
			case 'a':
				if (i + 1 == argc)
				{
					printf("%s: no parameter given.\n", current_option);
					return 1;
				}
				else if (atoi(argv[i+1]) == 0 && argv[i+1][0] != 0)
				{
					printf("%s: invalid value: \"%s\"\n",current_option, argv[i+1]);
					return 1;
				}
				nalphas = atoi(argv[i+1]);
				isalphas = true;
				break;
			case 'n':
				if (i + 1 == argc)
				{
					printf("%s: no parameter given.\n", current_option);
					return 1;
				}
				else if (atoi(argv[i+1]) == 0 && argv[i+1][0] != 0)
				{
					printf("%s: invalid value: \"%s\"\n",current_option, argv[i+1]);
					return 1;
				}
				ndigits = atoi(argv[i+1]);
				isnumbers = true;
				break;
			case 's':
				if (i + 1 == argc) 
				{
					printf("%s: no parameter given.\n", current_option);
					return 1;
				}
				else if (atoi(argv[i+1]) == 0 && argv[i+1][0] != 0)
				{
					printf("%s: invalid value: \"%s\"\n",current_option, argv[i+1]);
					return 1;
				}
				nsymbols = atoi(argv[i+1]);
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
			case 'v':
				isverbose = true;
				break;
			default:
				printf("Unrecognized option: \"%s\".\n",current_option);
				return 1;


		}
	}
	if (isdefault)
	{
		VERBOSE printf("Default: reseting values!\n");
		isnumbers = true;
		issymbols = true;
		islength  = true;
		isalphas  = true;
		length = DEFAULT_LENGTH;
		nalphas = DEFAULT_NALPHAS;
		nsymbols = DEFAULT_NSYMBOLS;
		ndigits = DEFAULT_NDIGITS;
	}
	else if (!islength)
	{
		length = get_length();
		VERBOSE printf("Autofilled length(=%d).\n",get_length());
	}
	else 
	{
		if (length < get_length()) 
		{
			printf("Password length contradiction!\n");
			return 1;
		}


		else if (length > get_length())
		{
			int code;
			if ( (code = is_one_category_missing()) == 0 ) 
			{
				printf("At least 2 categories missing, input not valid!\n");
				return 1;
			}
			autofill_category(code);

		}
	}
	char* password = (char*) malloc(sizeof(char) * (length + 1));
	memset(password, 0, length+1);
	if (password == NULL)
	{
		printf("Couln\'t allocate space for password on heap.\n");
		return 1;
	}
	if (isalphas) addAlphas(password);
	if (isnumbers) addDigits(password);
	if (issymbols) addSymbols(password);
	VERBOSE printf("Charred:  \"%s\"\n",password);
	if (israncase) 
	{
		randomizeCase(password);
		VERBOSE printf("Randomcase: \"%s\".\n",password);
	}
	if (ismix) 
	{
		mix(password);
		VERBOSE printf("Mixed:      \"%s\".\n",password);
	}
	VERBOSE printf("Password:  \"");
	printf("%s",password);
	VERBOSE printf("\".");
	printf("\n");
	free(password);
	return 0;
}

void addAlphas(char* dest)
{
	int char_index;
	int i = 0;
	while(dest[i] != '\0') ++i; /* skip previous input till nulls (nulls =free space)*/
	for (int _ = 0; _ < nalphas; ++_)
	{
		char_index = rand() % strlen(alphas);
		dest[i++] = alphas[char_index];
	}
}

void addDigits(char* dest)
{
	int char_index;
	int i = 0;
	while(dest[i] != '\0') ++i; /* skip previous input till nulls (nulls =free space)*/
	for (int _ = 0 ; _ < ndigits; ++_)
	{
		char_index = rand() % strlen(digits);
		dest[i++] = digits[char_index];
	}
}

void addSymbols(char* dest)
{
	int char_index;
	int i = 0;
	while(dest[i] != '\0') ++i; /* skip previous input till nulls (nulls =free space)*/
	for (int _ = 0 ; _ < nsymbols; ++_)
	{
		char_index = rand() % strlen(symbols);
		dest[i++] = symbols[char_index];
	}
}

void mix(char* dest)
{
	int index1;
	int index2;
	char buffer;
	for (int _ = 0; _ < MAX_MIX_ITERATIONS; ++_)
	{
		index1 = rand() % length;
		index2 = rand() % length;
		buffer = dest[index1];
		dest[index1] = dest[index2];
		dest[index2] = buffer;
	}
}

void randomizeCase(char* dest)
{
	for (int i = 0; i < length; ++i)
	{
		if ( isalpha(dest[i]) && rand() % 2 == 1)
		{
			dest[i] = toupper(dest[i]);
		}

	}
}

int get_length(void) /* calculate length if not length was inputted*/
{
	return ndigits + nalphas + nsymbols;

}


int is_one_category_missing(void) /* check if only 1 category is missing, autofill*/
{
	if ( !isalphas && isnumbers && issymbols) return 1;
	else if ( isalphas && !isnumbers && issymbols) return 2;
	else if ( isalphas && isnumbers && !issymbols) return 3;
	return 0;
}

void autofill_category(int code)
{
	if (code == 1)
	{
		isalphas = true;
		nalphas = length - ndigits - nsymbols;
		VERBOSE printf("autofill nalphas(=%d)\n",nalphas);
	}
	else if (code == 2)
	{
		isnumbers = true;
		ndigits = length - nalphas - nsymbols;
		VERBOSE printf("autofill ndigits(=%d)\n",ndigits);
	}
	else if (code == 3)
	{
		issymbols = true;
		nsymbols = length - nalphas - ndigits;
		VERBOSE printf("autofill nsymbols(=%d)",nsymbols);
	}
	else printf("Wtf?\n");
}
