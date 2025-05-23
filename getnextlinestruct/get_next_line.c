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
	fin = malloc((i[1] + i[0] + 1) * sizeof(char));
	if (fin == NULL)
		return (NULL);
	i[1] = 0;
	while (buff && buff [i[1]++])
		fin[i[0] + i[1] - 1] = buff[i[1] - 1];
	i[0] = 0;
	while (str && str[i[0]++])
		fin[i[0] - 1] = str[i[0] - 1];
	fin[i[0] + i[1] - (ssize_t)((str != NULL) * (buff != NULL))]  = 0;
//	free(str);
	return (fin);
}

char	*substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	counter;

	if(!s)
		return (NULL);
		
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


char	*get_next_line(int fd)
{
	static char	*str;
	t_data		data[1];

	data->storage = NULL;
	data->i1 = 0;
	while(str && str[data->i1])
	{
		if(str[data->i1] == '\n')
		{
			data->rt = substr(str, 0, data->i1 + 1);
			if(data->rt == NULL)
				return(NULL); //freeshit
			data->tmp = substr(str, data->i1 + 1, (size_t)-1);
			if(data->tmp == NULL)
				return(NULL); //freeshit
			str = data->tmp;
			return (data->rt);
		}
		data->i1 ++;
	}
	data->readcounter = BUFFER_SIZE;
	while(data->readcounter == BUFFER_SIZE)
	{
		data->readcounter = read(fd, data->buff, BUFFER_SIZE);
		data->buff[data->readcounter] = 0;
		if(data->readcounter == 0 || data->readcounter == -1)
			break;
		while(data->buff[data->i1])
		{
			printf("%s buff 90\n", data->buff);
			if (data->buff[data->i1] == '\n')
			{
				data->tmp = substr(data->buff, 0, data->i1 + 1);
				printf("%s, str 93\n", str);
				printf("%s, buff 99\n", data->tmp);
				data->rt = strjoinf2(data -> tmp, str);
				if(data->rt == NULL)
					return(NULL); //freeshit
	//			printf("%s, rt 105\n", data->rt);
				data->tmp = substr(data->buff, data->i1 + 1, (size_t)-1);
				if(data->tmp == NULL)
					return(NULL); //freeshit
				str = data->tmp;
				return (data->rt);
			}
			data->i1++;
		}
//		printf("%zi i1 104\n",data->i1);
		if(data->readcounter != BUFFER_SIZE)
			break;
		data->i1 = 0;
		str = strjoinf2(data->buff, str);
//		printf("%s storage114\n", data->storage);
	}
	if(data->readcounter == -1)
		return(NULL); // freeshit
//	printf("%s buff, %s str 118\n", data->buff, str);
	data->rt = strjoinf2(data->buff, str);
	if(data->rt == NULL)
		return (NULL); //free shit
	return (data->rt);
}
