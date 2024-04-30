

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
#include <stdbool.h> /* bools */
#include <string.h> /* strlen memset */
#include <stdlib.h> /* atoi malloc free srand rand*/
#include <time.h> /* for random numbers */



#define DEFAULT_LENGTH 10 /* default length */
#define DEFAULT_NALPHAS 5 /* default number of alpha characters*/
#define DEFAULT_NDIGITS 3 /* default number of digits */
#define DEFAULT_NSYMBOLS 2 /* default number of symbols */
#define MAX_MIX_ITERATIONS 30 /* number of times mix should mix */
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

void addAlphas(char* dest);
void addDigits(char* dest);
void addSymbols(char* dest);
void mix(char* dest);
/*
printf("length   -> %d\n",length);
printf("nalphas  -> %d\n",nalphas);
printf("ndigits  -> %d\n",ndigits);
printf("nsymbols -> %d\n",nsymbols);
printf("\n");
printf("islength -> %d\n",islength);
printf("isalphas -> %d\n",isalphas);
printf("isnumbers -> %d\n",isnumbers);
printf("issymbols -> %d\n",issymbols);
printf("israncase -> %d\n",israncase);
printf("ismix -> %d\n",ismix);
printf("isdefault -> %d\n",isdefault);

*/

int main(int argc, char* argv[])
{
	srand(time(0)); /* initialize random integer sequence*/
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
					printf("%s: invalid integer: \"%s\"\n",current_option, argv[i+1]);
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
					printf("%s: invalid integer: \"%s\"\n",current_option, argv[i+1]);
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
					printf("%s: invalid integer: \"%s\"\n",current_option, argv[i+1]);
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
					printf("%s: invalid integer: \"%s\"\n",current_option, argv[i+1]);
					return 1;
				}
				nsymbols = atoi(argv[i+1]);
				issymbols = true;
				break;
			case 'r':
				printf("\n");
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
	if (isdefault)
	{
		printf("Reseting values to default!\n");
		isnumbers = false;
		issymbols = false;
		islength  = false;
		isalphas  = false;
		length = DEFAULT_LENGTH;
		nalphas = DEFAULT_NALPHAS;
		nsymbols = DEFAULT_NSYMBOLS;
		ndigits = DEFAULT_NDIGITS;
	}
	else
	{
		printf("Non-default password generation not inplemented, please check back later!\n");
		return 1;
	}
	/* test functions */
	char* password = (char* ) malloc((length+1) * sizeof(char));
	memset(password, '\0', length+1); /* set it all to null */
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


