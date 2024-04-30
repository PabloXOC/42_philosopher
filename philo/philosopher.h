/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paxoc01 <paxoc01@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 12:48:21 by paxoc01           #+#    #+#             */
/*   Updated: 2024/04/24 14:35:43 by paxoc01          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# define EXIT_SUCCESS 0
# define EXIT_FAILURE 1

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>
# include <limits.h>
# include <stdbool.h>
# include <errno.h>

# define RST   "\033[0m"        /* Reset color */

// Regular Colors
# define BLK   "\033[0;30m"     /* Black */
# define R     "\033[0;31m"     /* Red */
# define G   "\033[0;32m"     /* Green */
# define YE  "\033[0;33m"     /* Yellow */
# define B    "\033[0;34m"     /* Blue */
# define M "\033[0;35m"     /* Magenta */
# define Y    "\033[0;36m"     /* Cyan */
# define W   "\033[0;37m"     /* White */

// Bold
# define BBLK   "\033[1;30m"      /* Bold Black */
# define BR     "\033[1;31m"      /* Bold Red */
# define BG   "\033[1;32m"      /* Bold Green */
# define BYE  "\033[1;33m"      /* Bold Yellow */
# define BB    "\033[1;34m"      /* Bold Blue */
# define BM "\033[1;35m"      /* Bold Magenta */
# define BC    "\033[1;36m"      /* Bold Cyan */
# define BW   "\033[1;37m"      /* Bold White */

typedef pthread_mutex_t	t_mtx;
typedef struct s_fork	t_fork;
typedef struct s_philo	t_philo;

typedef struct s_data
{
	long			n_philo;
	long			t_die;
	long			t_eat;
	long			t_sleep;
	long			n_times_eat;
	long			start_time_simulation;
	long			threads_running;
	bool			error;
	bool			end_simulation;
	bool			all_ready_to_start;
	t_mtx			data_mutex;
	t_mtx			write_mutex;
	t_fork			*forks;
	t_philo			*philos;
	pthread_t		monitor_thread_id;
}						t_data;

typedef struct s_philo
{
	long		id;
	long		meals_counter;
	bool		full;
	long		last_meal_time;
	t_fork		*first_fork;
	t_fork		*second_fork;
	pthread_t	thread_id;
	t_mtx		philo_mutex;
	t_data		*data;
}					t_philo;

typedef struct s_fork
{
	t_mtx	fork_m;
	int		fork_id;
}					t_fork;

typedef enum e_mutex_code
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
	DETACH,
}			t_mutex_code;

typedef enum e_time_code
{
	SEC,
	MILSEC,
	MICROSEC,
}			t_time_code;

typedef enum e_philo_status
{
	EATING,
	SLEEPING,
	THINKING,
	TAKES_FORK_1,
	TAKES_FORK_2,
	RELEASES_FORKS,
	DIED,
}			t_philo_status;

//dinner
void	ft_desync(t_philo *philo);
void	ft_philo_think(t_philo *philo);
void	ft_philo_eat(t_philo *philo);
void	*ft_philo_dinner(void *dataa);
void	*ft_monitor_dinner(void	*dataa);

//safe get set
bool	ft_get_bool(t_mtx *mutex, bool	*value);
void	ft_set_bool(t_mtx *mutex, bool	value, bool *dest);
long	ft_get_long(t_mtx *mutex, long	*value);
void	ft_set_long(t_mtx *mutex, long value, long *dest);
bool	ft_simulation_end(t_data *data);

//init
int		ft_init(t_data *data);
int		ft_init_philos(t_data *data);
void	ft_assign_forks(t_philo *philo, t_fork *forks, int i, int n_philo);
t_data	*get_data(char **argv, int argc);
int		get_data2(t_data *data, char **argv, int argc);

// libft
int		ft_atoi(const char *str);
bool	is_space(char c);
bool	is_digit(int c);
int		ft_valid_str(char *str);
bool	all_threads_running(t_data *data);

//philosophers
void	ft_dinner(t_data *data);
int		philosopher(char **argv, int argc);
int		main(int argc, char **argv);
void	ft_dinner_multiple(t_data *data, int i);
void	*ft_lone_philo(void	*dataa);

//safe
void	*ft_safe_malloc(int n_bytes);
int		ft_mutex_error(int result, t_mutex_code m_code);
int		ft_safe_mutex(t_mtx *mutex, t_mutex_code m_code);
int		ft_thread_error(int result, t_mutex_code t_code);
int		ft_safe_thread(pthread_t *thread, void *(*foo)(void *),
			void *data, t_mutex_code t_code);

//time utils
void	wait4allthreads(t_data *data);
long	ft_get_time(t_time_code time_code);
void	ft_usleep(long usec, t_data *data);
bool	ft_philo_died(t_philo *philo);

//write
void	ft_write_status(t_philo *philo, t_philo_status status);
void	ft_pe(char *str);

//utils
void	ft_free(t_data *data);
void	ft_increase_long(t_mtx *mutex, long amount, long *dest);

#endif