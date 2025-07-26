/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogi <hnogi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 22:02:06 by hnogi             #+#    #+#             */
/*   Updated: 2025/07/26 14:59:25 by hnogi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_free(char *buffer, char *buf)
{
	char	*temp;

	temp = ft_strjoin(buffer, buf);
	if (!temp)
	{
		if (buffer)
			free(buffer);
		return (NULL);
	}
	if (buffer)
		free(buffer);
	return (temp);
}

static char	*ft_next(char *buffer)
{
	int		i;
	int		j;
	char	*next_buf;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\0')
		return (free(buffer), NULL);
	next_buf = ft_calloc((ft_strlen(buffer) - i + 1), sizeof(char));
	if (!next_buf)
		return (free(buffer), NULL);
	i++;
	j = 0;
	while (buffer[i])
		next_buf[j++] = buffer[i++];
	free(buffer);
	return (next_buf);
}

static char	*ft_line(char *buffer)
{
	char	*line;
	int		i;

	i = 0;
	if (!buffer[i])
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	line = ft_calloc(i + 2, sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] && buffer[i] == '\n')
		line[i++] = '\n';
	return (line);
}

static char	*read_file(int fd, char *buffer)
{
	char	*str;
	int		byte_read;

	if (!buffer)
		buffer = ft_calloc(1, 1);
	str = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!str || !buffer)
		return (free(str), free(buffer), NULL);
	byte_read = 1;
	while (byte_read > 0)
	{
		byte_read = read(fd, str, BUFFER_SIZE);
		if (byte_read == -1)
			return (free(str), free(buffer), NULL);
		str[byte_read] = 0;
		buffer = ft_free(buffer, str);
		if (!buffer)
			return (free(str), NULL);
		if (ft_strchr(str, '\n'))
			break ;
	}
	return (free(str), buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (free(buffer), buffer = NULL, NULL);
	buffer = read_file(fd, buffer);
	if (!buffer)
		return (NULL);
	line = ft_line(buffer);
	buffer = ft_next(buffer);
	return (line);
}
