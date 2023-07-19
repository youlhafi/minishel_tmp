#include <stdio.h>

int	ft_isalnum(int c)
{
	if ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z')
		|| (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}

int main(int argc, char const *argv[])
{
    int i;

    i = 0;
    while (argv[i])
    {
        printf("%s\n", )
    }
    return 0;
}
