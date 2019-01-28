/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdouniol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 15:21:43 by jdouniol          #+#    #+#             */
/*   Updated: 2018/04/04 23:30:46 by jdouniol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

/*
** Fonction endline takes the last buffered string char *buff,
** return an int of how may char before the next '\n', else return (-1)
*/

static int		endline(char *buff)
{
	int	count;

	count = 0;
	while (buff[count] != '\n' && buff[count])
		count++;
	if (buff[count] == '\n')
	{
		buff[count] = '\0';
		return (count);
	}
	else
		return (-1);
}

/*
** Fonction join takes the two string to concatenate, we use successivly
** ft_strlen / ft_memcpy / and ft_bzero (for put to '\0' the first n bytes
** (buff_size + 1) pointed by tab)
*/

static char		*join(char *buff, char *tab)
{
	size_t	i;
	size_t	j;
	char	*ptr;

	i = 0;
	j = 0;
	if (buff)
		i = ft_strlen(buff);
	if (tab)
		j = ft_strlen(tab);
	ptr = (char *)malloc(sizeof(*ptr) * (i + j + 1));
	ft_memcpy(ptr, buff, i);
	ft_memcpy(ptr + i, tab, j);
	ptr[i + j] = '\0';
	free(buff);
	ft_bzero(tab, GNL_BUFF_SIZE + 1);
	return (ptr);
}

/*
** Fonction Verif use fonction final to know if there is a rest after \n,
** if yes, ft_verif add   return = 1, if not, return 0
*/

static int		verif(char **buff, char **tab, char **line)
{
	char	*ptr;
	int		final;

	*buff = join(*buff, *tab);
	final = endline(*buff);
	if (final > -1)
	{
		*line = ft_strdup(*buff);
		ptr = *buff;
		*buff = ft_strdup(*buff + final + 1);
		free(ptr);
		return (1);
	}
	return (0);
}

/*
** Fonction get next line, first check error case (-1),  return 1 if there is
** still a line to display, return 0 if this is the last line
*/

int				get_next_line(int const fd, char **line)
{
	static char *buff[12000];
	char		*tmp;
	int			result;
	int			ret;

	tmp = ft_strnew(GNL_BUFF_SIZE);
	if (!line || GNL_BUFF_SIZE <= 0 || fd < 0 || (ret = read(fd, tmp, 0)) < 0)
		return (-1);
	while ((ret = read(fd, tmp, GNL_BUFF_SIZE)) > 0)
	{
		result = verif(&buff[fd], &tmp, line);
		free(tmp);
		if (result == 1)
			return (1);
		tmp = ft_strnew(GNL_BUFF_SIZE);
	}
	if ((result = verif(&buff[fd], &tmp, line)))
		return (1);
	else if (ft_strlen(buff[fd]) > 0)
	{
		*line = ft_strdup(buff[fd]);
		ft_strdel(&buff[fd]);
		return (1);
	}
	return (result);
}
