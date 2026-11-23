/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: betdemir@student.42istanbul.com.tr         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/21 22:15:29 by betdemir          #+#    #+#             */
/*   Updated: 2026/11/23 23:06:02 by betdemir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_extract_line(char	*stash)
{
	char	*temp;
	size_t	i;

	i = 0;
	if (!stash[i])
		return (NULL);
	while (stash[i] && stash[i] != '\n')
		i++;
	temp = ft_calloc(i + 2, sizeof(char));
	if (!temp)
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
	{
		temp[i] = stash[i];
		i++;
	}
	if (stash[i] == '\n')
		temp[i] = '\n';
	return (temp);
}

char	*ft_next(char *stash)
{
	char	*temp;
	size_t	i;
	size_t	j;

	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (!stash[i])
		return (ft_free(stash));
	temp = ft_calloc(ft_strlen(stash) - i + 1, sizeof(char));
	if (!temp)
		return (ft_free(stash));
	i++;
	j = 0;
	while (stash[i])
	{
		temp[j] = stash[i];
		i++;
		j++;
	}
	free(stash);
	return (temp);
}

char	*ft_strjoin_and_free(char *stash, char *buffer)
{
	char	*temp;

	temp = ft_strjoin(stash, buffer);
	if (!temp)
		return (ft_free(stash));
	free(stash);
	return (temp);
}

char	*read_file(int fd, char *stash)
{
	char	*buffer;
	ssize_t	byte_read;

	if (!stash)
		stash = ft_calloc(1, 1);
	if (!stash)
		return (NULL);
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (ft_free(stash));
	byte_read = 1;
	while (byte_read > 0 && stash && !ft_strchr(stash, '\n'))
	{
		byte_read = read(fd, buffer, BUFFER_SIZE);
		if (byte_read == -1)
		{
			free(buffer);
			return (ft_free(stash));
		}
		buffer[byte_read] = '\0';
		stash = ft_strjoin_and_free(stash, buffer);
	}
	free(buffer);
	return (stash);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stash = read_file(fd, stash);
	if (!stash)
		return (NULL);
	line = ft_extract_line(stash);
	if (!line)
	{
		stash = ft_free(stash);
		return (NULL);
	}
	stash = ft_next(stash);
	return (line);
}
