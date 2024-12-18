#include <stdio.h>

//int main(void)
//{
//	int total = 0;
//
//	// total‚ª10‚æ‚è¬‚³‚¢ŠÔŒJ‚è•Ô‚·
//	while(total < 10)
//	{
//		printf_s("total = %d\n", total);
//		// a = a + x ‚Í a += x ‚É’u‚«Š·‚¦‚ç‚ê‚é
//		total += 1;
//	}
//
//	return 0;
//}

//int main(void)
//{
//	// total‚ª10‚æ‚è¬‚³‚¢ŠÔŒJ‚è•Ô‚·
//	for (int total = 0; total < 10; total++)
//	{
//		printf_s("total = %d\n", total);
//	}
//
//	return 0;
//}

//int main(void)
//{
//	// total‚ª0‚æ‚è‘å‚«‚¢ŠÔŒJ‚è•Ô‚·
//	for (int total = 10; total > 0; total--)
//	{
//		printf_s("total = %d\n", total);
//	}
//
//	return 0;
//}

//int main(void)
//{
//	// total‚ª10‚æ‚è¬‚³‚¢ŠÔŒJ‚è•Ô‚·
//	for (int total = 0; total < 10; total++)
//	{
//		// 2‚ÅŠ„‚Á‚½—]‚è‚ª0‚Æ‚¢‚¤‚±‚Æ‚Í‹ô”
//		if (total % 2 == 0)
//		{
//			// printf‚Í‚¹‚¸‚ÉŒJ‚è•Ô‚µ–`“ª‚É–ß‚é
//			continue;
//		}
//
//		printf_s("total = %d\n", total);
//	}
//
//	return 0;
//}

//int main(void)
//{
//	// total‚ª10‚æ‚è¬‚³‚¢ŠÔŒJ‚è•Ô‚·
//	for (int total = 0; total < 10; total++)
//	{
//		// total‚ª8‚Å‹­§I—¹
//		if (total == 8)
//		{
//			break;
//		}
//
//		printf_s("total = %d\n", total);
//	}
//
//	return 0;
//}

int main(void)
{
	printf_s("e‚ª“ü—Í‚³‚ê‚é‚Ü‚Å–³ŒÀƒ‹[ƒv‚µ‚Ü‚·\n");

	while (1)
	{
		char character = ' ';
		printf_s("1•¶š“ü—Í\n");
		scanf_s(" %c", &character);

		// 'e'‚ª“ü—Í‚³‚ê‚½‚çbreak‚Åƒ‹[ƒv‚ğ”²‚¯‚é
		if (character == 'e')
		{
			break;
		}
	}

	return 0;
}
