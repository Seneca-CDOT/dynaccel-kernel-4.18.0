# Dynamic Accelereted Linux kernel based on CentOS8s
### Version: 4.18.0-394.el8.x86_64
---

### Table of Contents

#### [1. Overview](#Overview)
#### [2. Limitations](#Limitation)
#### [3. Kernel Usage](#Kernel-Usage)
#### [4. Source RPM build](#Source-RPM-Build)
---

### Overview

The **Dynaccel kernel** can be used in testing environments where 
<br/><br/>The idea originated from [this repository](https://github.com/ystk/dynamic-acceleration).</br>
A presenation by the original authors (Toshiba) discribing this work is at [this PDF](https://elinux.org/images/6/6d/Linux_Kernel_Acceleration_for_Long-term_Testing.pdf). 

### Limitations

- **The kernel and SRC.RPM should be compiled under ```gcc-8``` and ```g++-8```** otherwise the compilation will fail.
- **The SRC.RPM should be built using ```mock``` utility with ```-r centos-stream-8-x86_64```** if required compiler version is not present.

### Kernel Usage

The ```speedup_ratio``` (dynamic acceleration) can be changed using ```sysctl```. Example: ```sysctl --write kernel.accel=50```.<br/>
The current value can be accessed through ```cat /proc/sys/kernel/accel```.

### Source RPM Build
