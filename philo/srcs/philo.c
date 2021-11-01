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

void	init_philo(t_philo *philo, int name, unsigned left, unsigned right) //, t_var *var)
{
	philo->name = name + 1;
	philo->left_fork = left;
	philo->right_fork = right;
	philo->eat_counter = 0;
}

long long unsigned	current_time()
{
	struct timeval tv1;

	gettimeofday(&tv1, NULL);
	return (tv1.tv_sec * 1000 + tv1.tv_usec / 1000);
}

void* eat(void *args)
{
	t_philo *philo;

	philo = (t_philo *)args;
    philo->last_eat = current_time();
	while (philo->var->dead == 0)
	{
		pthread_mutex_lock(&philo->var->forks[philo->left_fork]);

		pthread_mutex_lock(&philo->var->print);
        if (philo->var->dead == 0)
		    printf("%llu %d has taken a left fork\n", current_time() - philo->var->start_time, philo->name);

		pthread_mutex_unlock(&philo->var->print);
        if (philo->var->p_amount == 1)
        {
            pthread_mutex_unlock(philo->var->forks);
            break;
        }

		pthread_mutex_lock(&philo->var->forks[philo->right_fork]);

		pthread_mutex_lock(&philo->var->print);
        if (philo->var->dead == 0)
        {
            printf("%llu %d has taken a right fork\n", current_time() - philo->var->start_time, philo->name);
            printf("%llu %d is eating\n", current_time() - philo->var->start_time, philo->name);
        }
		pthread_mutex_unlock(&philo->var->print);
		philo->eat_counter++;
		if (philo->eat_counter == philo->var->number_of_meals)
			philo->var->full++;
		philo->last_eat = current_time();
        if (philo->var->dead == 0)
            ft_usleep(philo->var->eat_time);

		pthread_mutex_unlock(&philo->var->forks[philo->left_fork]);
		pthread_mutex_unlock(&philo->var->forks[philo->right_fork]);

		pthread_mutex_lock(&philo->var->print);
        if (philo->var->dead == 0)
            printf("%llu %d is sleeping\n", current_time() - philo->var->start_time, philo->name);
		pthread_mutex_unlock(&philo->var->print);

        if (philo->var->dead == 0)
            ft_usleep(philo->var->sleep_time);

		pthread_mutex_lock(&philo->var->print);
        if (philo->var->dead == 0)
            printf("%llu %d is thinking\n", current_time() - philo->var->start_time, philo->name);
		pthread_mutex_unlock(&philo->var->print);
	}
    return (NULL);
}

void	ft_usleep(long long unsigned time)
{
	long long unsigned temp;

    temp = current_time();
    while (current_time() - temp < time)
        usleep(100);
}

void init_vars(t_var *var, char **av)
{
	var->dead = 0;
	var->full = 0;
	var->p_amount = ft_atoi(av[1]);
	var->think_time = ft_atoi(av[2]);
	var->eat_time = ft_atoi(av[3]);
	var->sleep_time = ft_atoi(av[4]);
	if (var->ac == 6)
		var->number_of_meals = ft_atoi(av[5]);
	else
		var->number_of_meals = -1;
	var->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * var->p_amount);
	var->philo = (t_philo *)malloc(sizeof(t_philo) * var->p_amount);
	int i = 0;
	while (i < var->p_amount)
	{
		pthread_mutex_init(&var->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&var->print, NULL);
}

void	*check_dead(void *args)
{
	t_var *var = (t_var *)args;
	int i;

	i = 0;
	while (1)
	{
		if (current_time() - var->philo[i].last_eat > var->think_time)
		{
			pthread_mutex_lock(&var->print);
			printf("%llu %d died\n", current_time() - var->start_time, var->philo->name);
            var->dead = 1;
            pthread_mutex_unlock(&var->print);
			break;
		}
		i++;
		if (i < var->p_amount)
			i = 0;
        if (var->full == var->p_amount)
            break;
	}
    return (NULL);
}
void	create_tread(t_var *var)
{
	int i;

    i = 0;
    var->start_time = current_time();
    while (i < var->p_amount)
	{
		pthread_create(&var->philo[i].thread, NULL, &eat, &var->philo[i]);
		i++;
		usleep(10);
	}
	pthread_create(&var->monitoring, NULL, check_dead, var);
}

void    free_all(t_var *var)
{
    free(var->philo);
    int i = 0;
    while (i < var->p_amount)
        pthread_mutex_destroy(&var->forks[i++]);
    free(var->forks);
}

int	main(int ac, char **av)
{
	t_var		var;
	int			i;

    var.ac = ac;
    init_vars(&var, av);
	i = 0;
	while (i < var.p_amount)
	{
		init_philo(&var.philo[i], i, i, i + 1); //, &var);
		var.philo[i].var = &var;
		i++;
	}
	i--;
	init_philo(&var.philo[i], i, i, 0); //, &var);
	var.philo[i].var = &var;
	create_tread(&var);

	i = 0;

	while (i < var.p_amount)
	{
//		pthread_detach(var.philo[i].thread);
        pthread_join(var.philo[i].thread, NULL);
		i++;
	}
	pthread_join(var.monitoring,NULL);
    free_all(&var);
	return (0);
}