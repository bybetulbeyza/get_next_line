/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: betdemir@student.42istanbul.com.tr         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/21 21:41:18 by betdemir          #+#    #+#             */
/*   Updated: 2026/11/16 11:46:25 by betdemir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strjoin(char const *arr1, char const *arr2)
{
	char	*res;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	res = malloc(ft_strlen(arr1) + ft_strlen(arr2) + 1);
	if (!res)
		return (NULL);
	while (arr1[i])
	{
		res[i] = arr1[i];
		i++;
	}
	while (arr2[j])
	{
		res[i] = arr2[j];
		i++;
		j++;
	}
	res[i] = '\0';
	return (res);
}

void	*ft_calloc(size_t count, size_t size)
{
	char	*arr;
	size_t	i;

	if (size != 0 && count > (size_t) - 1 / size)
		return (NULL);
	arr = malloc(count * size);
	if (!arr)
		return (NULL);
	i = 0;
	while (i < (count * size))
	{
		arr[i] = '\0';
		i++;
	}
	return (arr);
}

char const	*ft_strchr(const char *arr, int c)
{
	size_t	i;

	i = 0;
	while (arr[i] != '\0' && arr[i] != c)
		i++;
	if (arr[i] == c)
		return (&arr[i]);
	else
		return (NULL);
}

size_t	ft_strlen(char const *arr)
{
	size_t	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}
