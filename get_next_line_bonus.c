#include<unistd.h>
#include<stdio.h>
#include<fcntl.h>
#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*stash[FOPEN_MAX];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	stash[FOPEN_MAX] = copy_to_stash(fd, stash[FOPEN_MAX]);
	if (!stash[FOPEN_MAX])
		return (NULL);
	line = create_line(stash[FOPEN_MAX]);
	stash[FOPEN_MAX] = what_next(stash[FOPEN_MAX]);
	return (line);
}

char	*jeofree(char *stash, char *temp)
{
	char	*buff;

	buff = ft_strjoin(stash, temp);
	free(stash);
	return (buff);
}

char	*copy_to_stash(int fd, char *stash)
{
	char	*temp;
	int		read_char;

	if (!stash)
		stash = ft_calloc(1, 1);
	temp = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	read_char = 1;
	while (read_char > 0)
	{
		read_char = read(fd, temp, BUFFER_SIZE);
		if (read_char == -1)
		{
			free(temp);
			return (NULL);
		}
		temp[read_char] = 0;
		stash = jeofree(stash, temp);
		if (new_line(temp, '\n'))
			break ;
	}
	free(temp);
	return (stash);
}

char	*create_line(char *stash)
{
	char	*line;
	int		i;

	i = 0;
	if (!stash[i])
		return (NULL);
	while (stash[i] && stash[i] != '\n')
		i++;
	line = ft_calloc(i + 2, sizeof(char));
	i = 0;
	while (stash[i] && stash[i] != '\n')
	{
		line[i] = stash[i];
		i++;
	}
	if (stash[i] && stash[i] == '\n')
		line[i++] = '\n';
	return (line);
}

char	*what_next(char *stash)
{
	char	*rest;
	int		i;
	int		n;

	i = 0;
	n = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (!stash[i])
	{
		free(stash);
		return (NULL);
	}
	rest = ft_calloc(ft_strlen(stash)- i + 1, sizeof(char));
	i++;
	while (stash[i])
		rest[n++] = stash[i++];
	rest[n] = 0;
	free(stash);
	return (rest);
}
