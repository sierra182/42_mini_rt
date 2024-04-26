/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_store.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seblin <seblin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 18:35:28 by seblin            #+#    #+#             */
/*   Updated: 2024/04/10 21:16:47 by seblin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data_store.h"

static void	close_semaphore(sem_t *sem, int id, char *name)
{
	sem_close(sem);
	name = ft_strjoin_up(name, ft_itoa(id), 0, 1);
	sem_unlink(name);
	free(name);
}

void	store_and_free_philos(t_exit *exit, void *philos)
{
	int		i;

	if (exit && philos)
		exit->philos = (t_philo *) philos;
	else if (exit && exit->philos)
	{
		i = -1;
		while (++i < exit->data->n_philo)
		{
			close_semaphore(exit->philos[i].sem_last_meal,
				exit->philos[i].id, "/sem_last_meal");
			close_semaphore(exit->philos[i].sem_end_needed,
				exit->philos[i].id, "/sem_end_needed");
			close_semaphore(exit->philos[i].sem_death_notice,
				exit->philos[i].id, "/sem_death_notice");
		}
		free(exit->philos);
		exit->philos = NULL;
	}
}

void	store_and_free_data(t_exit *exit, void *data)
{
	if (exit && data)
		exit->data = data;
	else if (exit && exit->data)
	{
		sem_close(exit->data->sem_death);
		sem_unlink("/sem_death");
		sem_close(exit->data->sem_mic);
		sem_unlink("/sem_mic");
		sem_close(exit->data->sem_forks);
		sem_unlink("/sem_forks");
		free(exit->data);
		exit->data = NULL;
	}
}
