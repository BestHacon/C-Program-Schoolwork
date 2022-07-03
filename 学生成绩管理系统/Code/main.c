#include"common.h"

int Login(void);
void Manege(void);
void CreatFiles(void);

int main(void)
{
	CreatFiles();
	while (1)
	{
		if (Login())
		{
			Manege();
		}
		else
			break;
	}
	return 0;
}
