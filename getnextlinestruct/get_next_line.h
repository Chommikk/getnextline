/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchoma <mchoma@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 01:19:37 by mchoma            #+#    #+#             */
/*   Updated: 2025/05/14 01:19:37 by mchoma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef BUFFER_SIZE
//BUFFER_SIZE has to be positive number
# define BUFFER_SIZE 4 

#endif 

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <stddef.h>
# include <limits.h>
# include <stdint.h>

typedef struct s_data
{
	char	buff[(int)BUFFER_SIZE + 1];
	char	*tmp;
	char	*rt;
	ssize_t	readcounter;
	ssize_t	i1;
	ssize_t	i2;
} t_data;
char	*get_next_line(int fd);
#endif

