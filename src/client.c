/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaramuk <mkaramuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 16:59:31 by mkaramuk          #+#    #+#             */
/*   Updated: 2022/02/08 18:43:58 by mkaramuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	g_isitmario;

void	send_bits(unsigned char c, pid_t pid)
{
	int	count;

	count = 7;
	while (count >= 0)
	{
		if ((c >> count) & 1)
			send_signal(SIGUSR1, pid);
		else
			send_signal(SIGUSR2, pid);
		count--;
		usleep(100);
	}
}

void	bit_sended(int signo)
{
	(void)signo;
	ft_printf("Data sent\n");
}

void	parse_args(int len, char **args, pid_t *pid)
{
	if (len > 1)
	{
		if (ft_strncmp(args[1], "--help", ft_strlen(args[1])) == 0)
		{
			print_usage_client();
			exit(0);
		}
	}
	if (len < 3)
	{
		print_usage_client();
		error("I think you didn't give the arguments enough.");
	}
	*pid = ft_atoi(args[1]);
	if (*pid == 0)
		error("PID cannot be zero");
}

/* It's must be Mario! */
void	itsamemario(int signo)
{
	(void)signo;
	g_isitmario = 1;
}

int	main(int argc, char **argv)
{
	pid_t	server_pid;
	char	*data;
	int		sended_byte;
	int		i;

	g_isitmario = 0;
	sended_byte = 0;
	i = 2;
	signal(SIGUSR1, bit_sended);
	signal(SIGUSR2, itsamemario);
	parse_args(argc, argv, &server_pid);
	while (i < argc)
	{
		data = argv[i++];
		while (*data)
		{
			if (!g_isitmario && sended_byte >= 1)
				error("It's not a Mario!");
			send_bits(*data++, server_pid);
			sended_byte++;
		}
	}
	send_bits('\0', server_pid);
	return (0);
}
