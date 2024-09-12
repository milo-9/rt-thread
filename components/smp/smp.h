#ifndef __SMP_IPI_H__
#define __SMP_IPI_H__
#include <rtthread.h>
typedef void (*smp_call_func_back)(void *data);
typedef rt_bool_t (*smp_cond)(int cpu, void *info);

#define SMP_CALL_EVENT_FUNC 0x1

#define SMP_CALL_WAIT_ALL (1 << 0)
#define SMP_CALL_NO_WAIT (1 << 1)

#define RT_ALL_CPU ((1 << RT_CPUS_NR) - 1)
struct smp_event
{
    int cpu_mask;
    int event_id;
    void *data;
    smp_call_func_back func;
};
struct smp_call
{
    struct rt_spinlock lock;
    struct smp_event event;
};


void rt_smp_call_ipi_handler(int vector, void *param);
void rt_call_each_cpu(smp_call_func_back func, void *data,rt_uint8_t flag);
void rt_call_each_cpu_cond(smp_call_func_back func, void *data,rt_uint8_t flag,smp_cond cond_func);
void rt_call_any_cpu(int cpu_mask,smp_call_func_back func, void *data,rt_uint8_t flag);
void rt_call_any_cpu_cond(int cpu_mask,smp_call_func_back func, void *data,rt_uint8_t flag,smp_cond cond_func);
void smp_init(void);

#endif
