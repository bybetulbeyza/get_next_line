/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: betdemir@student.42istanbul.com.tr         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/23 20:25:26 by betdemir          #+#    #+#             */
/*   Updated: 2026/11/23 22:19:22 by betdemir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# ifndef MAX_FILES
#  define MAX_FILES 1024
# endif

char		*get_next_line(int fd);
char		*ft_strjoin(char const *arr1, char const *arr2);
void		*ft_calloc(size_t count, size_t size);
char const	*ft_strchr(const char *arr, int c);
size_t		ft_strlen(char const *arr);
void		*ft_free(char *arr);
#endif
