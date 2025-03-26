/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grohr <grohr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 20:54:44 by grohr             #+#    #+#             */
/*   Updated: 2025/03/26 21:06:23 by grohr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minitalk.h"

void	send_signal(int pid, char *str)
{
	int		i;
	int		c;
	char	*final;

	final = str + ft_strlen(str);
	while (str <= final)
	{
		c = *str;
		i = 0;
		while (i < 8)
		{
			if (c & (1 << i))
				kill(pid, SIGUSR2);
			else
				kill(pid, SIGUSR1);
			usleep(200);
			i++;
		}
		str++;
	}
}

int	main(int argc, char **argv)
{
	int	pid;

	if (argc != 3)
	{
		ft_printf("\033[38;5;196mError: wrong format.\033[0m\n");
		ft_printf("\033[33mFormat: ./client <PID> <MESSAGE>\033[0m\n");
		return (1);
	}
	pid = ft_atoi(argv[1]);
	if (pid <= 0)
	{
		ft_printf("\033[38;5;196mError: Invalid PID.\033[0m\n");
		return (1);
	}
	else
		send_signal(pid, argv[2]);
	return (0);
}
