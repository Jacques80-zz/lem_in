#include "../includes/lem_in.h"

void	ft_error(int nb)
{
	if (nb == ERROR)
	{
		write(STDERR_FILENO, "Error\n", 6);
		exit(1);
	}
}

void	ft_save_map(t_all *elem, char *line)
{
	t_map	*new;
	t_map	*last;

	ft_error(!(new = malloc(sizeof(t_map))));
	ft_error(!(new->str = ft_strdup(line)));
	new->next = NULL;
	if (elem->map == NULL)
	{
		elem->map = new;
		return ;
	}
	last = elem->map;
	while (last->next)
	{
		last = last->next;
	}
	last->next = new;
}
