/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envvars_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ae7th <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 23:29:26 by ae7th             #+#    #+#             */
/*   Updated: 2024/05/15 16:06:20 by ae7th            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char  *add_to_formats(char *formats, char f)
{
    char  *copy;
    int   i;

    if (formats == NULL)
    {
        formats = malloc(2);
        formats[0] = f;
        formats[1] = '\0';
        return (formats);
    }
    else
    {
        copy = malloc (ft_strlen(formats) + 2);
        ft_strlcpy(copy, formats, ft_strlen(formats) + 1);
        i = 0;
        while (copy[i] != '\0')
            i++;
        copy[i] = f;
        copy[i + 1] = '\0';
        free(formats);
        return (copy);
    }
}

char  *check_start(char *str, char *formats, int *i)
{
    int j;

    j = 0;
    if (str[j] != '$')
    {
        formats = add_to_formats(formats, 's');
        while ((str[*i] != '$') && (str[*i] != '\0'))
            (*i)++;
    }
    return (formats);
}

char *count_formats(char *str, char *formats)
{
    int i;

    i = 0;
    formats = check_start(str, formats, &i);
    while (str[i] != '\0')
    {
        if ((str[i + 1] == '$') || (str[i + 1] == '\0'))
        {
            while (str[i] == '$')
                i++;
            formats = add_to_formats(formats, 's');
        }
        else
        {
            i++;
            while ((str[i] != '$') && (str[i] != '\0'))
                i++;
            formats = add_to_formats(formats, 'v');
        }
    }
    return (formats);
}

static void reset_fne_vars(int *sp_i, int *i)
{
    *sp_i = 0;
    *i = 0;
}

char  *find_next_element(char *token, t_trash *trash, t_mini *mini)
{
    static int  i = 0;
    int  j = 0;
    static int  splitted_index = 0;

    if (trash->splitted[splitted_index] == NULL)
        reset_fne_vars(&splitted_index, &i);
    if (trash->formats[trash->i] == 's')
    {
        splitted_index++;
        trash->i++;
        j = i;
        while ((token[i] != '$') && (token[i] != '\0'))
            i++;
        while ((token[i] == '$') && (token[i + 1] == '$'))
            i++;
        return (ft_substr(token, j, i));
    }
    while ((token[i] != ' ') && (token[i] != '$') && (token[i] != '\0'))
        i++;
    splitted_index++;
    trash->i++;
    return (ft_getenv(mini, trash->splitted[splitted_index - 1]));
}
