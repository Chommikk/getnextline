/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchoma <mchoma@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 13:53:44 by mchoma            #+#    #+#             */
/*   Updated: 2025/05/20 13:53:51 by mchoma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"
#include <stdio.h>
// strjoin but frees the second argument
//ssize_t ft_read(int fd, void *buf, size_t nbyte);
char	*strjoinf2(char *buff, char *str)
{
	ssize_t	i[3];
	char	*fin;

	i[0] = 0;
	i[1] = 0;
	while (str && str[i[0]])
		i[0]++;
	while (buff && buff[i[1]])
		i[1]++;
	fin = malloc((i[1] + i[0] + 1) * sizeof(char));
	if (fin == NULL)
		return (NULL);
	i[0] = 0;
	while (str && str[i[0]++])
		fin[i[0] - 1] = str[i[0] - 1];
	i[1] = 0;
	while (buff && buff [i[1]++])
		fin[i[0] + i[1] - 1] = buff[i[1] - 1];
	i[2] = 0;
	if (buff && str)
		i[2] = -1;
	fin[i[0] - 1 + i[1] + i[2]] = 0;
	free(str);
	return (fin);
}

char	*substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	counter;

	sub = malloc(sizeof(char) * len + 1);
	if (sub == 0)
		return (0);
	counter = 0;
	while (counter < len && s[start + counter])
	{
		sub[counter] = s[start + counter];
		counter ++;
	}
	sub[counter] = 0;
	return (sub);
}

char	*nfound(char **buff, char **str, ssize_t *i)
{
	printf("%s buff %s str\n", buff[0], *str);
	buff[1] = substr(&buff[0][i[0] + 1], 0, BUFFER_SIZE);
	if (buff[1] == NULL)
		return (NULL);
	buff[3] = substr(buff[0], 0, i[0] + 2);
	if (buff[3] == NULL)
		return (NULL);
	buff[2] = strjoinf2(buff[3], *str);
	if (buff[2] == NULL)
		return (NULL);
	*str = buff[1];
	free(buff[3]);
	free(buff[0]);
	return (buff[2]);
}

void	ft_free(char **ptr)
{
	free(*ptr);
	*ptr = NULL;
}


char	*get_next_line(int fd)
{
	static char	*str;
	char		*buff[4];
	ssize_t		i[3];

	i[1] = BUFFER_SIZE;
	i[2] = 0;
	while(str && str[i[2]])
	{
		if(str[i[2]] == '\n')
		{
			buff[0] = substr(str, 0, i[2] + 1);
			if(buff[0] == NULL)
				return (ft_free(&str), NULL);
			buff[1] = substr(str, i[2] + 1, BUFFER_SIZE);
			if(buff[1] == NULL)
				return (ft_free(&str), NULL);
			free(str);
			str = buff[1];
			return (buff[0]);
		}
		i[2] ++;
	}
	buff[0] = malloc(BUFFER_SIZE + 1);
	if (buff[0] == NULL)
		return (ft_free(&str), NULL);
	while (i[1] == BUFFER_SIZE)
	{
		printf("%zi, zi115\n", i[1]);
		i[1] = read(fd, buff[0], BUFFER_SIZE);
		if (i[1] == -1 || i[1] == 0)
			return (free(buff[0]), ft_free(&str), NULL);
		buff[0][i[1]] = 0;
		i[0] = 0;
		while (buff[0][i[0]])
		{
			printf("%s, buff[0]120\n", buff[0]);
			printf("%s, str125\n", str);

			if (buff[0][i[0]] == '\n' && buff[0][i[0]])
				return (nfound(buff, &str, i));
			i[0]++;
		}
		str = strjoinf2(buff[0], str);
		printf("%s, str127\n", str);
		printf("%zi, zi128\n", i[1]);
	}
	return (free(buff[0]), buff[2]);
}
