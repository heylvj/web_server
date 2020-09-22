#ifndef LOCKER_H
#define LOCKER_H

#include <exception>
#include <pthread.h>
#include <semaphore.h>

class sem
{
public:
	sem() {
		//agc2 = pshare, arg3 = init_value
		if (sem_init(&m_sem, 0, 0) != 0) {
			throw std::exception();
		}
	}
	~sem() {
		sem_destroy(&m_sem);
	}
	bool wait() {
		return sem_wait(&m_sem) == 0;
	}
	bool post() {
		return sem_post(&m_sem) == 0;
	}

private:
	sem_t m_sem;
};

class locker
{
public:
	locker() {
		//arg2 = attr
		if (pthread_mutex_init(&m_mutex, NULL) != 0) {
			throw std::exception();
		}
	}
	~locker() {
		pthread_mutex_destroy(&m_mutex);
	}
	bool lock() {
		return pthread_mutext_lock(&m_mutex) == 0;
	}
	bool unlock() {
		return pthread_mutex_unlock(&m_mutex) == 0;
	}
	
private:
	pthread_mutex_t m_mutex;
};
class cond
{
public:
	cond() {
		if (pthread_mutex_init(&m_mutex) != 0) {
			throw std::exception();
		}
		if (pthread_cond_init(&m_cond) != 0) {
			throw std::exception();
		}
	}
	~cond() {
		pthread_mutex_destroy(&m_mutex);
		pthread_cond_destroy(&m_cond);
	}
	bool wait() {
		//等待信号变量
		pthread_mutex_lock(&m_mutex);
		int ret = pthread_cond_wait(&m_cond, &m_mutex);
		pthread_mutex_unlock(&m_mutex);
		return ret == 0;
	}
	bool signal() {
		//唤醒那个等待信号变量的线程
		return pthread_cond_signal(&m_cond) == 0;
	}

private:
	pthread_mutex_t m_mutex;
	pthread_mutex_t m_cond;
};

#endif