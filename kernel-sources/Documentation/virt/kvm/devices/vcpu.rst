.. SPDX-License-Identifier: GPL-2.0

======================
Generic vcpu interface
======================

The virtual cpu "device" also accepts the ioctls KVM_SET_DEVICE_ATTR,
KVM_GET_DEVICE_ATTR, and KVM_HAS_DEVICE_ATTR. The interface uses the same struct
kvm_device_attr as other devices, but targets VCPU-wide settings and controls.

The groups and attributes per virtual cpu, if any, are architecture specific.

1. GROUP: KVM_ARM_VCPU_PMU_V3_CTRL
==================================

:Architectures: ARM64

1.1. ATTRIBUTE: KVM_ARM_VCPU_PMU_V3_IRQ
---------------------------------------

:Parameters: in kvm_device_attr.addr the address for PMU overflow interrupt is a
	     pointer to an int

Returns:

	 =======  ========================================================
	 -EBUSY   The PMU overflow interrupt is already set
	 -ENXIO   The overflow interrupt not set when attempting to get it
	 -ENODEV  PMUv3 not supported
	 -EINVAL  Invalid PMU overflow interrupt number supplied or
		  trying to set the IRQ number without using an in-kernel
		  irqchip.
	 =======  ========================================================

A value describing the PMUv3 (Performance Monitor Unit v3) overflow interrupt
number for this vcpu. This interrupt could be a PPI or SPI, but the interrupt
type must be same for each vcpu. As a PPI, the interrupt number is the same for
all vcpus, while as an SPI it must be a separate number per vcpu.

1.2 ATTRIBUTE: KVM_ARM_VCPU_PMU_V3_INIT
---------------------------------------

:Parameters: no additional parameter in kvm_device_attr.addr

Returns:

	 =======  ======================================================
	 -ENODEV  PMUv3 not supported or GIC not initialized
	 -ENXIO   PMUv3 not properly configured or in-kernel irqchip not
		  configured as required prior to calling this attribute
	 -EBUSY   PMUv3 already initialized
	 =======  ======================================================

Request the initialization of the PMUv3.  If using the PMUv3 with an in-kernel
virtual GIC implementation, this must be done after initializing the in-kernel
irqchip.


2. GROUP: KVM_ARM_VCPU_TIMER_CTRL
=================================

:Architectures: ARM, ARM64

2.1. ATTRIBUTES: KVM_ARM_VCPU_TIMER_IRQ_VTIMER, KVM_ARM_VCPU_TIMER_IRQ_PTIMER
-----------------------------------------------------------------------------

:Parameters: in kvm_device_attr.addr the address for the timer interrupt is a
	     pointer to an int

Returns:

	 =======  =================================
	 -EINVAL  Invalid timer interrupt number
	 -EBUSY   One or more VCPUs has already run
	 =======  =================================

A value describing the architected timer interrupt number when connected to an
in-kernel virtual GIC.  These must be a PPI (16 <= intid < 32).  Setting the
attribute overrides the default values (see below).

=============================  ==========================================
KVM_ARM_VCPU_TIMER_IRQ_VTIMER  The EL1 virtual timer intid (default: 27)
KVM_ARM_VCPU_TIMER_IRQ_PTIMER  The EL1 physical timer intid (default: 30)
=============================  ==========================================

Setting the same PPI for different timers will prevent the VCPUs from running.
Setting the interrupt number on a VCPU configures all VCPUs created at that
time to use the number provided for a given timer, overwriting any previously
configured values on other VCPUs.  Userspace should configure the interrupt
numbers on at least one VCPU after creating all VCPUs and before running any
VCPUs.

3. GROUP: KVM_ARM_VCPU_PVTIME_CTRL
==================================

:Architectures: ARM64

3.1 ATTRIBUTE: KVM_ARM_VCPU_PVTIME_IPA
--------------------------------------

:Parameters: 64-bit base address

Returns:

	 =======  ======================================
	 -ENXIO   Stolen time not implemented
	 -EEXIST  Base address already set for this VCPU
	 -EINVAL  Base address not 64 byte aligned
	 =======  ======================================

Specifies the base address of the stolen time structure for this VCPU. The
base address must be 64 byte aligned and exist within a valid guest memory
region. See Documentation/virt/kvm/arm/pvtime.rst for more information
including the layout of the stolen time structure.

4. GROUP: KVM_VCPU_TSC_CTRL
===========================

:Architectures: x86

4.1 ATTRIBUTE: KVM_VCPU_TSC_OFFSET

:Parameters: 64-bit unsigned TSC offset

Returns:

	 ======= ======================================
	 -EFAULT Error reading/writing the provided
		 parameter address.
	 -ENXIO  Attribute not supported
	 ======= ======================================

Specifies the guest's TSC offset relative to the host's TSC. The guest's
TSC is then derived by the following equation:

  guest_tsc = host_tsc + KVM_VCPU_TSC_OFFSET

This attribute is useful for the precise migration of a guest's TSC. The
following describes a possible algorithm to use for the migration of a
guest's TSC:

From the source VMM process:

1. Invoke the KVM_GET_CLOCK ioctl to record the host TSC (t_0),
   kvmclock nanoseconds (k_0), and realtime nanoseconds (r_0).

2. Read the KVM_VCPU_TSC_OFFSET attribute for every vCPU to record the
   guest TSC offset (off_n).

3. Invoke the KVM_GET_TSC_KHZ ioctl to record the frequency of the
   guest's TSC (freq).

From the destination VMM process:

4. Invoke the KVM_SET_CLOCK ioctl, providing the kvmclock nanoseconds
   (k_0) and realtime nanoseconds (r_0) in their respective fields.
   Ensure that the KVM_CLOCK_REALTIME flag is set in the provided
   structure. KVM will advance the VM's kvmclock to account for elapsed
   time since recording the clock values.

5. Invoke the KVM_GET_CLOCK ioctl to record the host TSC (t_1) and
   kvmclock nanoseconds (k_1).

6. Adjust the guest TSC offsets for every vCPU to account for (1) time
   elapsed since recording state and (2) difference in TSCs between the
   source and destination machine:

   new_off_n = t_0 + off_n + (k_1 - k_0) * freq - t_1

7. Write the KVM_VCPU_TSC_OFFSET attribute for every vCPU with the
   respective value derived in the previous step.
