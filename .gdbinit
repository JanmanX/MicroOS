set arch i386:x86-64:intel
file os/kernel.bin
target remote localhost:1234
layout src



# Temporary
#watch *3221100764
#break *xsdt_init
#continue
#find 0xE0000, 0x1000000, 0x2052545020445352
