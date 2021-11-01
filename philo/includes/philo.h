#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <memory.h>
# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_philo	t_philo;

typedef struct	    	s_var
{
	int		    		p_amount;
	int		    		sleep_time;
	int		    		eat_time;
	int		    		think_time;
	int		    		number_of_meals;
	int		    		dead;
	int		    		full;
    long long unsigned	start_time;
    pthread_mutex_t		*forks;
    pthread_mutex_t		print;
    pthread_t			monitoring;
    int                 ac;
	t_philo 	    	*philo;
}				    	t_var;

typedef struct	    	s_philo
{
    pthread_t			thread;
	int			    	name;
	int			    	eat_counter;
	unsigned	    	left_fork;
	unsigned	    	right_fork;
    long long unsigned	last_eat;
	t_var			    *var;
}					    t_philo;

void	ft_usleep(long long unsigned time);

#endif