#!/bin/bash
install -m 644 devmod.ko /lib/modules/`uname -r`/kernel/drivers/sum-module.ko
/sbin/depmod -a