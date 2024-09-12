#include <stdio.h>
int main()
{ 	
	char string[20] = "abcd";
	int i;
	printf("%d\n", sizeof(string));
	i = printf("%s",string);
	printf("%d\n",i);
	return 0;
}
