# Dynamic Accelereted Linux kernel based on CentOS8s
### Version: 4.18.0-394.el8.x86_64
---
The idea originated from [this repository](https://github.com/ystk/dynamic-acceleration) </br>
A presenation by the original authors (Toshiba) discribing this work is at [this PDF](https://elinux.org/images/6/6d/Linux_Kernel_Acceleration_for_Long-term_Testing.pdf)

- **The kernel should be compiled under gcc-8 and g++-8** otherwise the compilation will fail. <br>
- The speedup_ratio (acceleration) can be changed using ```sysctl```. 

Example: ```sysctl --write kernel.accel=50```. 
The current value can be accessed through ```cat /proc/sys/kernel/accel```
