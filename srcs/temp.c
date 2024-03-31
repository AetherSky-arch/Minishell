
#include "../includes/minishell.h"

void	temp_display_tabs(char **token, t_type *type)
{
	int		i;
	char	*t_type_names[] = {"INFILE", "OUTFILE", "OUTFAPP", "GREAT",
			"DGREAT", "LESS", "HEREDOC", "LIMITER", "PIPE", "CMD", "ARG"};

	i = 0;
	printf("token\n");
	while (token[i])
	{
		printf("%s / ", token[i]);
		i++;
	}
	// printf("%ld\n", ft_tablen(token));
	// printf("%ld\n", temp_ft_tablen2(type));
	i = 0;
	printf("\n");
	printf("type\n");
	while (i < (int)ft_tablen(token))
	{
		printf("%d / ", type[i]);
		i++;
	}
	i = 0;
	printf("\n");
	printf("type name\n");
	while (i < (int)ft_tablen(token))
	{
		printf("%s / ", t_type_names[type[i]]);
		i++;
	}
	printf("\n");
}

size_t	temp_ft_tablen2(t_type *tab)
{
	size_t i;

	if (!tab)
		return (0);
	i = 0;
	while (tab[i])
		i++;
	return (i);
}