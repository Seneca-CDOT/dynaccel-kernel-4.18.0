/*
 * Dynamic (Fake) Acceleration for Linux Kernel
 * Copyright (C) 2022 OSTEP 
 */

#ifndef _LINUX_DYNACCEL_H
#define _LINUX_DYNACCEL_H


#define DEFAULT_SPEEDUP_RATIO 1 /* NO ACCELERATION */

#ifdef __KERNEL__
extern unsigned int speedup_ratio;
#endif /* __KERNEL__ */

#endif /* _LINUX_DYNACCEL_H */
