# Dynamic Accelereted Linux kernel based on CentOS8s
### Version: 4.18.0-394.el8.x86_64
---
The idea originated from [this repository](https://github.com/ystk/dynamic-acceleration)</br>
A presenation by the original authors (Toshiba) - [PDF](https://elinux.org/images/6/6d/Linux_Kernel_Acceleration_for_Long-term_Testing.pdf)

- **The kernel should be compiled under gcc-8 and g++-8**, otherwise the compilation will probably fail. <br>
- The speedup_ratio (acceleration) can be changed using ```sysctl```. 

Example: ```sysctl --write kernel.accel=50```. 
The current value can be accessed through ```cat /proc/sys/kernel/accel```

### Linux kernel
---
There are several guides for kernel developers and users. These guides can
be rendered in a number of formats, like HTML and PDF. Please read
Documentation/admin-guide/README.rst first.

In order to build the documentation, use ```make htmldocs``` or
```make pdfdocs```.  The formatted documentation can also be read online at:
- https://www.kernel.org/doc/html/latest/

There are various text files in the Documentation/ subdirectory,
several of them using the Restructured Text markup notation.
See Documentation/00-INDEX for a list of what is contained in each file.

Please read the Documentation/process/changes.rst file, as it contains the
requirements for building and running the kernel, and information about
the problems which may result by upgrading your kernel.

### Notes

The ```../config-x86_64``` can be used to compile the kernel:<br/>
1. Copy the desired config file to the root of the kernel source - ```cp ../config-x86_64 ./kernel-sources/.config```.
2. Run ```make oldconfig```.
3. Run ```make menuconfig``` to make changes to the provided config. For a graphical UI, instead run - ```make xconfig```.


 
