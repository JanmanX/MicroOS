mkdir ./src


# QEMU
wget http://download.qemu-project.org/qemu-2.8.0.tar.xz
tar xvJf qemu-2.8.0.tar.xz
cd qemu-2.8.0
./configure
make




############################### OPTIONAL #######################################
# QBOOT
# Better BIOS for QEMU
wget https://github.com/bonzini/qboot.git


