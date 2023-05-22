/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrouwer <vbrouwer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 10:29:07 by vbrouwer          #+#    #+#             */
/*   Updated: 2023/05/22 17:38:42 by vbrouwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "libft.h"

int	main()
{
	char *line;

	while(true)
	{
		line = readline("shell-2023$>");
		sleep(1);
		if (line == NULL)
		{
			printf("No line to read.");
			exit(EXIT_SUCCESS);
		}
		if (ft_strncmp(line, "exit", 5))
			exit(0);
		printf("line = %s\n", line);
		tokenize(line);
		exit(EXIT_SUCCESS);
	}
}
