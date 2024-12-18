#include <stdio.h>

//int main(void)
//{
//	int total = 0;
//
//	// total‚ª10‚æ‚è¬‚³‚¢ŠÔŒJ‚è•Ô‚·
//	while (total < 10)
//	{
//		printf_s("total = %d\n", total);
//		total = total + 1;	// total‚ğ1‘‚â‚·
//	}
//
//	return 0;
//}

int main(void)
{
	char character = ' ';

	// e‚Ì•¶š‚ª“ü—Í‚³‚ê‚é‚Ü‚ÅŒJ‚è•Ô‚·
	while (character != 'e')
	{
		printf_s("1•¶š“ü—Í");
		scanf_s(" %c", &character);

		printf_s("character = %c\n", character);
	}

	return 0;
}
