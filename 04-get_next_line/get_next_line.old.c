
static char	*get_next_line_append(
	char *line,
	char buffer[BUFF_SIZE],
	size_t length)
{
	char	*result;
	size_t	offset;
	size_t	i;

	offset = (line == NULL) ? 0 : ft_strlen(line);
	if (!(result = (char *)malloc(offset + length + 1)))
		return (NULL);
	if (line)
	{
		i = 0;
		while (line[i])
		{
			result[i] = line[i];
			++i;
		}
		offset = i;
	}
	i = 0;
	while (i < length)
	{
		result[offset + i] = buffer[i];
		++i;
	}
	result[offset + length] = '\0';
	return (result);
}

static int	get_next_line_buffer(
	char **line,
	char buffer[BUFF_SIZE],
	size_t *offset,
	size_t *length)
{
	char	*newline;

	if (*line != NULL)
	{
		*offset += *length + 1;
		if (*offset < BUFF_SIZE)
		{
			if ((newline = ft_strchr(buffer + *offset, '\n')))
			{
				*length = (size_t)(newline - (buffer + *offset));
				*line = ft_strsub(buffer, *offset, *length);
				return (1);
			}
			else
				*line = ft_strdup(buffer + *offset);
ft_putstr("buffer -> offset:"); ft_putstr(ft_strpad_l(ft_itoa(*offset), ' ', 2));
ft_putstr(        ", length:"); ft_putstr(ft_strpad_l(ft_itoa(*length), ' ', 2)); ft_putstr("\n");
		}
	}
	*offset = 0;
	return (0);
}

int			get_next_line(const int fd, char **line)
{
	static char		buffer[BUFF_SIZE] = {0};
	static size_t	offset = 0;
	static size_t	length = 0;
	int				result;
	char			*newline;

	if (get_next_line_buffer(line, buffer, &offset, &length))
		return (GNL_LINE);
	while ((result = read(fd, buffer, BUFF_SIZE)))
	{
		if (result < 0)
			return (GNL_ERROR);
		if (result < BUFF_SIZE)
			buffer[result] = '\0';
		newline = ft_strchr(buffer, '\n');
		length = (newline) ? (size_t)(newline - buffer) : BUFF_SIZE;
		newline = get_next_line_append(*line, buffer, length);
		if (newline == NULL)
			return (GNL_ERROR);
		free(*line);
		*line = newline;
ft_putstr("append -> offset:"); ft_putstr(ft_strpad_l(ft_itoa(offset), ' ', 2));
ft_putstr(        ", length:"); ft_putstr(ft_strpad_l(ft_itoa(length), ' ', 2)); ft_putstr("\n");
		if (length < BUFF_SIZE)
			return (GNL_LINE);
	}
	return (GNL_END);
}
