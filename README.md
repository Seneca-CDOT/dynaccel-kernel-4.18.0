# Dynamic Accelereted Linux kernel based on CentOS8s
### Version: 4.18.0-394.el8.x86_64
### [Presentation](./Dynamic%20Acceleration%20Kernel.pdf)
---

### Table of Contents

#### [1. Overview](#Overview)
#### [2. Kernel Installation](#Kernel-Installation)
#### [3. Project Structure](#Project-Structure)
#### [4. Kernel Usage](#Kernel-Usage)
#### [5. Source RPM build](#Source-RPM-Build)
#### [6. Notes](#Notes)
#### [7. Limitations](#Limitations)
---

### Overview

The **Dynaccel kernel** is a Linux kernel that can speed up the long-term testing process through accelerated kernel's flow of time. The ratio to which the time is accelerated can be changed dynamically through the kernel interface - ```/proc```.
<br/><br/>
The idea originated from [the repository](https://github.com/ystk/dynamic-acceleration).
</br>
A slides by the original authors (Toshiba) describing this work - [PDF](https://elinux.org/images/6/6d/Linux_Kernel_Acceleration_for_Long-term_Testing.pdf).
<br/><br/>
The kernel is based on the upstream CentOS8s kernel 4.18.0.

### Kernel Installation

The **Dynaccel kernel** can be installed through a DNF update on a Centos8 Strean system:
- Create `dynaccel.repo` file in the `/etc/yum.repos.d/` folder
- Add the following content to the created file:
``` 
[dynaccel]
name=dynaccel
baseurl=http://portugal.cdot.systems/dynaccel
gpgcheck=0
enabled=1
```

**After the RPM repository is set up locally, a simple ```dnf update --refresh``` will install all the packages and update to the Dynaccel kernel.**

### Project Structure

- ```kernel-sources``` - a folder containing the Dynaccel kernel source code. [README.md](./kernel-sources/README.md)
- ```config-x86_64```  - a reference of kernel config for x86_64 used for compilation.
- ```dynaccel-patches.patch``` - a patch file containing the changes for the Dynaccel functionality.
- ```kernel-4.18.0-394.el8.dynaccel.src.rpm``` - a SRC.RPM file containing sources for the RPM package build.

### Kernel Usage

The ```speedup_ratio``` (acceleration) can be changed with ```sysctl```.
<br/>
Example: ```sysctl --write kernel.accel=50```.
<br/>
The current acceleration ratio can be accessed through ```cat /proc/sys/kernel/accel```.

### Source RPM Build

Below is the steps required to build the Dynaccel RPM packages:
1. Install RPM Developer tools - ```sudo dnf -y install rpmdevtools``` or ```sudo yum -y install rpmdevtools```.
2. Set up the RPM build tree - ```rpmdev-setuptree``` and ```cd rpmbuild```.
   <br/><br/>
   ![RPMbuild tree](https://i.ibb.co/QQpsVbp/RPMbuild-tree.png)
3. Copy the ```*src.rpm``` to the ```SRPMS``` folder and install it - ```rpm -i kernel*src.rpm```.
4. Build the RPM:
   - With ```rpmbuild -bb --target=x86_64 SPECS/kernel.spec```, if gcc-8 is present.
   - With ```mock``` utility - ```mock -r centos-stream-8-x86_64 *src.rpm```, if gcc-8 is not present.
5. Next steps would be to create and sign an RPM repository. 
   Refer to [the Wiki Page](https://wiki.cdot.senecacollege.ca/wiki/Signing_and_Creating_a_Repository_for_RPM_Packages) on how to do it.
   
Additionally, there is a good [guide](https://www.fedoraproject.org/wiki/Building_a_custom_kernel/Source_RPM) on the Fedora Wiki page on how to build a custom kernel RPM package.

### Notes

- The ```kernel.spec``` specifies EPOCH 1 for Dynaccel to take precedence over the latest kernel present in DNF.
- Inner VM's installed under the Dynaccel kernel inherit the flow of time (accelerated as well).
  * However, an Inner VM's Watchdog that kernel should reset periodically does not function properly and goes off early. It causes kernel panics, making the system almost unusable.
    * The issue can temporarily be fixed by disabling the Watchdog with ```sysctl kernel.nmi_watchdog=0```
    * To disable for subsequent boots add ```kernel.nmi_watchdog=0``` line to /etc/sysctl.conf
- The acceleration ratio can be adjusted in the range of 1 to 1000, but the 'stable' range is from 1 to 200.

### Limitations

- The kernel and SRC.RPM should be compiled under ```gcc-8``` and ```g++-8```, otherwise compilation will fail.
- The Dynaccel patches were only applied and tested on kernel version 4.18.0.
- It is not a hardware acceleration, so there isn't any performance boost, just accelerated time.
