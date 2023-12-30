/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbbot <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 11:34:01 by fbbot             #+#    #+#             */
/*   Updated: 2023/12/30 14:34:50 by fbbot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

ssize_t	new_line(int fd, char **line)
{
	ssize_t		i;

	*line = malloc(sizeof(char) * ((size_t)BUFFER_SIZE + 1));
	if (!*line)
		return (-1);
	i = read(fd, *line, BUFFER_SIZE);
	if (i != -1)
		line[0][i] = '\0';
	return (i);
}

void	free_everything(char **buffer, char **str)
{
	if (*buffer)
	{
		free(*buffer);
		*buffer = NULL;
	}
	if (*str)
		free(*str);
}

char	*get_the_line(char **buffer, int i)
{
	char	*line;
	char	*temp;

	while (buffer[0][i] != '\n')
		i++;
	line = ft_strldup(*buffer, i + 1);
	if (!line)
	{
		free_everything(buffer, &line);
		return (NULL);
	}
	temp = *buffer;
	if (!buffer[0][++i])
		*buffer = NULL;
	else
	{
		*buffer = ft_strldup(&buffer[0][i], ft_strlen(&buffer[0][i]));
		if (!*buffer)
		{
			free_everything(&temp, &line);
			return (NULL);
		}
	}
	free(temp);
	return (line);
}

ssize_t	fill_buffer(int fd, char **buffer, char **line)
{
	ssize_t	i;

	i = new_line(fd, line);
	if ((i == -1) || (!i && !*buffer))
	{
		free_everything(buffer, line);
		return (-1);
	}
	if (i && *buffer)
	{
		*buffer = ft_strjoin(*buffer, *line);
		if (!*buffer)
			return (-1);
	}
	else if (i && !*buffer)
	{
		*buffer = ft_strldup(*line, ft_strlen(*line));
		free(*line);
		if (!*buffer)
			return (-1);
	}
	else
		free(*line);
	return (i);
}

char	*get_next_line(int fd)
{
	static char	*buffer[FD_SETSIZE];
	char		*line;
	ssize_t		i;

	if (fd < 0 || (fd > FD_SETSIZE))
		return (NULL);
	i = 1;
	while (i)
	{
		i = fill_buffer(fd, &buffer[fd], &line);
		if (i == -1)
			return (NULL);
		if (buffer[fd] && ft_strchr(buffer[fd], '\n'))
			return (get_the_line(&buffer[fd], 0));
	}
	if (!i && buffer[fd])
	{
		line = ft_strldup(buffer[fd], ft_strlen(buffer[fd]));
		free(buffer[fd]);
		buffer[fd] = NULL;
		if (!line)
			return (NULL);
		return (line);
	}
	return (0);
}
