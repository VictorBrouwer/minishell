#include <stdio.h>

int main(int arc, char ** arv)
{
	for (int i = 0; i < arc; i++)
		printf("arg %d: %s\n", i, arv[i]);
	return (0);
}