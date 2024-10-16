/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david_chellen <david_chellen@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 15:21:09 by david_chell       #+#    #+#             */
/*   Updated: 2024/09/26 20:10:44 by david_chell      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*clean_line(char *box)
{
	int		i;
	char	*new;

	i = 0;
	while (box[i] != '\n' && box[i] != '\0')
	{
		i++;
	}
	new = ft_substr(box, 0, i + 1);
	return (new);
}

static char	*read_file(int fd, char *buf, char *box, char *temp)
{
	ssize_t	bytes_read;

	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buf, BUFFER_SIZE);
		if (bytes_read == -1)
			return (NULL);
		buf[bytes_read] = '\0';
		if (box == NULL)
			box = ft_strdup(buf);
		else
		{
			temp = ft_strjoin(box, buf);
			free(box);
			box = temp;
		}
		if (ft_strchr(box, '\n') != NULL)
		{
			return (box);
		}
	}
	return (box);
}

static char	*rest_of_line(char *box, char *temp)
{
	if (ft_strchr(box, '\n') != NULL)
	{
		temp = ft_strdup(ft_strchr(box, '\n') + 1);
		free(box);
		box = temp;
	}
	else
	{
		free(box);
		box = NULL;
	}
	return (box);
}

int	check_error(int fd, char **buf, char **box)
{
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		free(*box);
		*box = NULL;
		free (*buf);
		return (1);
	}
	else
		return (0);
}

char	*get_next_line(int fd)
{
	static char	*box;
	char		*new;
	char		*temp;
	char		*buf;

	new = NULL;
	temp = NULL;
	buf = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (check_error(fd, &buf, &box) == 1)
		return (NULL);
	box = read_file(fd, buf, box, temp);
	free (buf);
	if (box != NULL)
	{
		new = clean_line(box);
		box = rest_of_line(box, temp);
		if (new[0] == '\0')
		{
			free (new);
			return (NULL);
		}
	}
	return (new);
}

// int main(void)
// {
// 	int fd;
// 	fd = open ("freeze.txt", O_RDONLY);
// 	if (fd == -1)
// 		return (1);
// 	printf("%s\n", get_next_line(fd));
// 	printf("%s\n", get_next_line(fd));
// 	printf("%s\n", get_next_line(fd));
// 	printf("%s\n", get_next_line(fd));
// 	printf("%s\n", get_next_line(fd));
// 	printf("%s\n", get_next_line(fd));
// }