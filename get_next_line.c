/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hklein <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 11:54:28 by hklein            #+#    #+#             */
/*   Updated: 2018/12/06 13:17:23 by hklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_strnjoinf(char *s1, char *s2, size_t rm, size_t len)
{
	char	*new_s;

	if ((int)rm < 0 || (int)rm > 3)
		return (NULL);
	if (!s1 || !s2)
		return (NULL);
	if ((new_s = ft_strnew(ft_strlen(s1) + ft_strlen(s2))) == NULL)
		return (NULL);
	ft_strcpy(new_s, s1);
	ft_strncat(new_s, s2, len);
	if (rm == 1 || rm == 3)
		ft_strdel(&s1);
	if (rm == 2 || rm == 3)
		ft_strdel(&s2);
	return (new_s);
}

static int	get_return(char **line)
{
	if ((**line))
		return (1);
	else
	{
		ft_strdel(line);
		return (0);
	}
}

int			get_next_line(const int fd, char **line)
{
	static char	fdstock[OPEN_MAX][BUFF_SIZE + 1];
	char		*tmp;
	int			ret;

	tmp = fdstock[fd];
	if (!line || fd < 0 || BUFF_SIZE < 1 || read(fd, NULL, 0) < 0)
		return (-1);
	if (!((*line) = ft_strnew(0)))
		return (-1);
	while (1)
	{
		if (ft_strchr(tmp, '\n'))
		{
			(*line) = ft_strnjoinf((*line), tmp, 1,
				(ft_strchr(tmp, '\n') - tmp));
			ft_strncpy(tmp, &tmp[ft_strchr(tmp, '\n') - tmp + 1],
				BUFF_SIZE - (ft_strchr(tmp, '\n') - tmp));
			return (1);
		}
		(*line) = ft_strnjoinf((*line), tmp, 1, BUFF_SIZE);
		ret = read(fd, fdstock[fd], BUFF_SIZE);
		tmp[ret] = '\0';
		if (ret == 0)
			return (get_return(line) == 1 ? 1 : 0);
	}
}
