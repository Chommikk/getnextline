/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchoma <mchoma@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 01:18:55 by mchoma            #+#    #+#             */
/*   Updated: 2025/05/14 01:18:56 by mchoma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>


int main()
{
	char	 *filename = "text.txt";
	int		fd = open(filename, O_RDWR);
	char	*line;
	
	line = get_next_line(fd);
	printf("%stest |",line);
	free(line);
	line = get_next_line(fd);
	printf("%stest |",line);
	free(line);
	line = get_next_line(fd);
	printf("%stest |",line);
	free(line);
	line = get_next_line(fd);
	printf("%stest |",line);
	free(line);
	
	line = get_next_line(fd);
	printf("%stest |",line);
	free(line);
	line = get_next_line(fd);
	printf("%stest |",line);
	free(line);
	line = get_next_line(fd);
	printf("%stest |",line);
	free(line);
	line = get_next_line(fd);
	printf("%stest |",line);
	free(line);
}
