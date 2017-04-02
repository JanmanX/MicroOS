NJOBS=8

mkdir ./src


# QEMU
wget http://download.qemu-project.org/qemu-2.8.0.tar.xz
tar xvJf qemu-2.8.0.tar.xz
cd qemu-2.8.0
./configure
make -j${NJOBS}
cd ..

# BOCHS
wget https://downloads.sourceforge.net/project/bochs/bochs/2.6.8/bochs-2.6.8.tar.gz?r=&ts=1491134677&use_mirror=netcologne
tar xf bochs-2.6.8.tar.gz
cd bochs-2.6.8
./configure --enable-debugger --enable-debugger-gui --enable-x86-debugger --with-sdl --enable-x86-64
make -j${NJOBS}
#sudo make install
cd ..


############################### OPTIONAL #######################################
# QBOOT
# Better BIOS for QEMU
git clone https://github.com/bonzini/qboot.git



