#include "../includes/philo.h"

int	ft_atoi(char *str) // TODO защитить атой
{
	int res;

	res = 0;
	while (*str && *str >= '0' && *str <= '9')
	{
		res = res * 10 + (*str - 48);
		++str;
	}
	return res;
}

void	init_philo(t_philo *philo, int name, unsigned left, unsigned right)
{
	philo->name = name + 1;
	philo->left_fork = left;
	philo->right_fork = right;
	philo->eat_counter = 0;
}

LLU	current_time()
{
	struct timeval tv1;

	gettimeofday(&tv1, NULL);
	return (tv1.tv_sec * 1000 + tv1.tv_usec / 1000);
}


void* eat(void *args)
{
	t_philo *philo;

	philo = (t_philo *)args;
	while (philo->var->dead == 0)
	{
		PML(&philo->var->forks[philo->left_fork]);

		PML(&philo->var->print);
		printf("%llu %d has taken a left fork\n", current_time() - philo->var->start_time, philo->name);
		PMU(&philo->var->print);

		PML(&philo->var->forks[philo->right_fork]);

		PML(&philo->var->print);
		printf("%llu %d has taken a right fork\n", current_time() - philo->var->start_time, philo->name);
		printf("%llu %d is eating\n", current_time() - philo->var->start_time, philo->name);
		PMU(&philo->var->print);
		philo->eat_counter++;
		if (philo->eat_counter == philo->var->number_of_meals)
			philo->var->full++;
		philo->last_eat = current_time();

		usleep(philo->var->eat_time * 1000);
	// UNLOCK
		PMU(&philo->var->forks[philo->left_fork]);
		PMU(&philo->var->forks[philo->right_fork]);
	// UNLOCK END
		PML(&philo->var->print);
		printf("%llu %d is sleeping\n", current_time() - philo->var->start_time, philo->name);
		PMU(&philo->var->print);

		usleep(philo->var->sleep_time * 1000);

		PML(&philo->var->print);
		printf("%llu %d is thinking\n", current_time() - philo->var->start_time, philo->name);
		PMU(&philo->var->print);
	}
}

void	ft_usleep(LLU time, int flag)
{
	while (current_time() - time != 0 && flag != 1)
		usleep(1);
}

void init_vars(t_var *var, char **av)
{
	var->dead = 0;
	var->full = 0;
	var->p_amount = ft_atoi(av[1]);
	var->think_time = ft_atoi(av[2]);
	var->eat_time = ft_atoi(av[3]);
	var->sleep_time = ft_atoi(av[4]);
	if (var->p_amount == 6)
		var->number_of_meals = ft_atoi(av[5]);
	else
		var->number_of_meals = -1;
	var->forks = (PMT *)malloc(sizeof(PMT) * var->p_amount);
	var->philo = (t_philo *)malloc(sizeof(t_philo));
	int i = 0;
	while (i < var->p_amount)
	{
		PMI(&var->forks[i], NULL);
		i++;
	}
	PMI(&var->print, NULL);
}

void	*check_dead(void *args)
{
	t_var *var = (t_var *)args;
	int i;

	i = 0;
	while (1)
	{
		if (current_time() - var->philo[i].last_eat > var->think_time || var->full == var->p_amount)
		{
			PML(&var->print);
			printf("%llu %d died\n", current_time() - var->philo->last_eat, var->philo->name);
			break;
		}
		i++;
		if (i < var->p_amount)
		{
			i = 0;
		}
	}
}
void	create_tread(t_var *var)
{
	int i;

	i = 0;
	var->start_time = current_time();

	while (i < var->p_amount)
	{
		var->philo[i].last_eat = var->start_time;
		i++;
	}
	i = 0;
	while (i < var->p_amount)
	{
		pthread_create(&var->philo[i].thread, NULL, eat, &var->philo[i]);
		i++;
		usleep(10);
	}
	pthread_create(&var->monitoring, NULL,  check_dead, var);
}

int	main(int ac, char **av)
{
	t_var		var;
	int			i;

	init_vars(&var, av);
	i = 0;
	while (i < var.p_amount)
	{
		init_philo(&var.philo[i], i, i, i + 1);
		var.philo[i].var = &var;
		i++;
	}
	i--;
	init_philo(&var.philo[i], i, i, 0);
	var.philo[i].var = &var;
	create_tread(&var);

	i = 0;
	while (i < var.p_amount)
	{
		pthread_join(&var.philo->thread[i], NULL);
		i++;
	}
	pthread_join(var.monitoring, NULL);

	//DEBUG
//	int j = 0;
//	while (j < var.p_amount)
//	{
//		printf("%d - name, %d - left, %d right\n", var.philo[j].name, var.philo[j].left_fork, var.philo[j].right_fork);
//		j++;
//	}
	return (0);
}