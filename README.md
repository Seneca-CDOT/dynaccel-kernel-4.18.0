# Dynamic Accelereted Linux kernel based on CentOS8s
### Version: 4.18.0-394.el8.x86_64
---

### Table of Contents

#### [1. Overview](#Overview)
#### [2. Project Structure](#Project-Structure)
#### [3. Limitations](#Limitation)
#### [4. Kernel Usage](#Kernel-Usage)
#### [5. Source RPM build](#Source-RPM-Build)
---

### Overview

The **Dynaccel kernel** is a Linux kernel that can speed up the testing process in an environment by accelerating the kernel flow of time. The ratio to which the time is accelerated can be change dynamically through the kernel interface - ```/proc```.
<br/><br/>The idea originated from [the repository](https://github.com/ystk/dynamic-acceleration).</br>
A presenation by the original authors (Toshiba) describing this work - [this PDF](https://elinux.org/images/6/6d/Linux_Kernel_Acceleration_for_Long-term_Testing.pdf). 

### Project Structure

- ```kernel-sources``` - a folder containing the Dynaccel kernel source code
- ```config-x86_64```  - a reference of kernel config for x86_64 used in compilation
- ```dynaccel-patches.patch``` - a patch file containing the changes for Dynaccel functionality 
- ```kernel-4.18.0-394.el8.dynaccel.src.rpm``` - a SRC.RPM file containing everything for the RPM build

### Limitations

- **The kernel and SRC.RPM should be compiled under ```gcc-8``` and ```g++-8```** otherwise the compilation will fail.
- **The SRC.RPM should be built using ```mock``` utility with ```-r centos-stream-8-x86_64```** if required compiler version is not present.

### Kernel Usage

The ```speedup_ratio``` (dynamic acceleration) can be changed using ```sysctl```. Example: ```sysctl --write kernel.accel=50```.<br/>
The current value can be accessed through ```cat /proc/sys/kernel/accel```.

### Source RPM Build
