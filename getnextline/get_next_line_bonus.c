/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelacou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 23:13:59 by ddelacou          #+#    #+#             */
/*   Updated: 2023/04/18 17:01:35 by ddelacou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_strchr(char *s, int c)
{
	int		i;
	char	cc;

	cc = (char)c;
	i = 0;
	while (s[i] != cc && s[i])
	{
		i++;
	}
	if (s[i] == cc)
		return (&*(char *)(s + i));
	else
		return (0);
}

char	*buffme(int fd, char *buffer, char *str, int ret)
{
	if (!str)
		str = ft_calloc(1, 1);
	if (!str)
		return (NULL);
	while (ret > 0)
	{
		buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
		if (!buffer)
		{
			free(str);
			free(buffer);
			return (NULL);
		}
		ret = read(fd, buffer, BUFFER_SIZE);
		if (ret < 0)
			return (NULL);
		str = ft_strjoin(str, buffer);
		if (str == NULL)
			return (NULL);
		free(buffer);
		buffer = NULL;
		if (ft_strchr(str, '\n') != 0)
			break ;
	}
	return (str);
}

char	*givemetheline(char *str)
{
	char	*temp;
	int		i;

	i = 0;
	while (str[i] != '\n' && str[i])
		i++;
	if (str[i] == '\n')
		i++;
	temp = ft_calloc((i + 1), sizeof(char));
	if (!temp)
		return (NULL);
	i = 0;
	while (str[i] != '\n' && str[i])
	{
		temp[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
		temp[i] = '\n';
	return (temp);
}

char	*deleteline(char *str, int i)
{
	char	*temp;
	int		size;

	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	size = ft_strlen(str + i);
	if (size == 0)
	{
		free(str);
		return (NULL);
	}
	temp = ft_calloc((size + 1), sizeof(char));
	if (!temp)
	{
		free(temp);
		free(str);
		return (NULL);
	}
	size++;
	while (--size > 0)
		temp[size - 1] = str[i + size - 1];
	free(str);
	return (temp);
}

char	*get_next_line(int fd)
{
	char		*buffer;
	static char	*str[4096];
	char		*temp;

	buffer = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, buffer, 0) == -1)
	{
		free(str[fd]);
		str[fd] = NULL;
		return (NULL);
	}
	str[fd] = buffme(fd, buffer, str[fd], BUFFER_SIZE);
	if (!str[fd])
		return (NULL);
	temp = givemetheline(str[fd]);
	if (!temp || temp[0] == 0)
	{
		free(temp);
		free(str[fd]);
		str[fd] = NULL;
		return (NULL);
	}
	str[fd] = deleteline(str[fd], 0);
	return (temp);
}
