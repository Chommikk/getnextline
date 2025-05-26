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
// ssize_t ft_read(int fd, void *buf, size_t nbyte);
char	*strjoinf2(char *buff, char *str)
{
	ssize_t	i[2];
	char	*fin;

	i[0] = 0;
	i[1] = 0;
	while (str && str[i[0]])
		i[0]++;
	while (buff && buff[i[1]])
		i[1]++;
//	printf("%zi, i[0] %zi i[1] 27\n", i[0], i[1]);
	fin = malloc((i[1] + i[0] + 1) * sizeof(char));
	if (fin == NULL)
		return (NULL);
	i[1] = 0;
	while (buff && buff [i[1]++])
		fin[i[0] + i[1] - 1] = buff[i[1] - 1];
	i[0] = 0;
	while (str && str[i[0]++])
		fin[i[0] - 1] = str[i[0] - 1];
//	printf("%zi, i[0] %zi i[1] 37\n", i[0], i[1]);
	fin[i[0] + i[1] - 2 + (str == NULL) + (buff == NULL)]  = 0;
	free(str);
	return (fin);
}

void	initialize(t_data *data)
{
	data->tmp = NULL;
	data->rt = NULL;
	data->readcounter = BUFFER_SIZE;
	data->i1 = 0;
}

void	freeall(t_data *data, char **str)
{
	free(data->tmp);
	data->tmp = NULL;
	free(data->rt);
	data->rt = NULL;
	free(*str);
	*str = NULL;
}

char	*substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	counter;

	if(!s)
		return (NULL);
		
	sub = malloc(sizeof(char) * len + 2);
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


char	*get_next_line(int fd)
{
	static char	*str = NULL;
	t_data		data[1];

	if (BUFFER_SIZE == -1)
		return NULL;
	initialize(data);
	while (1)
	{
		while (str && str[data->i1])
		{
			if (str[data->i1] == '\n')
			{
				data->rt = substr(str, 0, data->i1 + 1);
				if(data->rt == NULL)
					return (freeall(data, &str), NULL); //freeshit
				data->tmp = substr(str, data->i1 + 1, BUFFER_SIZE + 1);
				if(data->tmp == NULL)
					return (freeall(data, &str), NULL); //freeshit
				free(str);
				str = data->tmp;
				return (data->rt);
			}
			data->i1 ++;
		}

		data->readcounter = read(fd, data->buff, BUFFER_SIZE);
		if (data->readcounter == -1)
			return (freeall(data, &str), NULL); //freeshit
		data->buff[data->readcounter] = 0;
	//	printf("%zi 90readcounter \n", data->readcounter);
	//	printf("%s 90buff \n", data->buff);
		str = strjoinf2(data->buff, str);
//		printf("%s str, %p stradress 95\n", str, str);
		if (str == NULL)
			return (freeall(data, &str), NULL); //freeshit
		if (data->readcounter == 0)
			return (free(str), str = NULL, data->rt);
	}
}
