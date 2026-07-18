#include "utils.h"

int	count_words(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c && s[i] != '\0')
		{
			i++;
		}
		if (s[i] != '\0')
			count++;
		while (s[i] != c && s[i] != '\0')
		{
			i++;
		}
	}
	return (count);
}

static char	**free_all(char **str, size_t count)
{
	size_t	i;

	i = 0;
	while (i < count && str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
	return (NULL);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	s_len;
	size_t	copy_len;
	size_t	i;
	char	*x;

	if (s == NULL)
		return (NULL);
	s_len = strlen(s);
	if (start >= s_len)
		copy_len = 0;
	else if (len > s_len - start)
		copy_len = s_len - start;
	else
		copy_len = len;
	x = malloc(copy_len + 1);
	if (x == NULL)
		return (NULL);
	i = 0;
	while (i < copy_len)
	{
		x[i] = s[start + i];
		i++;
	}
	x[i] = '\0';
	return (x);
}

static char	**set_split(char **str, char const *s, char c)
{
	size_t	len;
	size_t	i;
	size_t	j;
	size_t	start;

	i = 0;
	j = 0;
	while (s[i] != '\0')
	{
		while (s[i] != '\0' && s[i] == c)
			i++;
		start = i;
		while (s[i] != '\0' && s[i] != c)
			i++;
		len = i - start;
		if (len > 0)
		{
			str[j] = ft_substr(s, start, len);
			if (str[j] == NULL)
				return (free_all(str, j));
			j++;
		}
	}
	str[j] = NULL;
	return (str);
}

char	**ft_split(char const *s, char c)
{
	char	**str;
	size_t	word_count;

	if (!s)
		return (NULL);
	word_count = count_words(s, c);
	str = malloc(word_count + 1);
	if (!str){
		free_all(str, word_count);
		return (NULL);
	}

	return (set_split(str, s, c));
}
