/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migarrid <migarrid@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 23:20:58 by migarrid          #+#    #+#             */
/*   Updated: 2025/02/27 23:24:37 by migarrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

//Implemantación Obligatoria
int	main(int ac, char **av)
{
	int		fd;
	char	*line;

	if (ac < 2)
		fd = 0;
	else
	{
		fd = open(av[1], O_RDONLY);
		if (fd == -1)
		{
			perror("Error opening the file");
			return (0);
		}
	}
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line);
		free(line);
	}
	if (fd != 0)
		close(fd);
	return (0);
}

//Implemantación Bonus
int main(void)
{
	int fd1, fd2, fd3;
	char *line1 = NULL;
	char *line2 = NULL;
	char *line3 = NULL;

	fd1 = open("test1.txt", O_RDONLY);
	fd2 = open("test2.txt", O_RDONLY);
	fd3 = open("test3.txt", O_RDONLY);

	if (fd1 == -1 || fd2 == -1 || fd3 == -1)
	{
		perror("Error al abrir los archivos");
		return (1);
	}

	while (1)
	{
		line1 = get_next_line(fd1);
		line2 = get_next_line(fd2);
		line3 = get_next_line(fd3);

		if (!line1 && !line2 && !line3)
			break;

		if (line1)
		{
			printf("FD1: %s", line1);
			free(line1);
		}
		if (line2)
		{
			printf("FD2: %s", line2);
			free(line2);
		}
		if (line3)
		{
			printf("FD3: %s", line3);
			free(line3);
		}
	}
	close(fd1);
	close(fd2);
	close(fd3);
    return (0);
}
