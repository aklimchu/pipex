// 42 header!!!

#include "../inc_bonus/pipex_bonus.h"

size_t	ft_strchr_fix(const char *s, int c)
{
	char	new_c;
	int		i;

	new_c = c + '\0';
	i = 0;
	while (1)
	{
		if (*s == new_c)
			return (i);
		s++;
		i++;
	}
	return (0);
}

int	free_str(char *str1, char *str2)
{
	if (str1)
	{
		free(str1);
		str1 = NULL;
	}
	if (str2)
	{
		free(str2);
		str2 = NULL;
	}
	return (1);
}
