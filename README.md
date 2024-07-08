# Welcome!
This is the repository where CatK's core utilities are developed, for use with Disk images, LiveCDs, and installation. This repositiory aims to provide the kernel with a set of simple, usable utilities to make the system usable. (Especially from the Shell)

# How do I compile these?
To compile the binaries, run `compile.sh` to compile them for Catkernel, and place the binaries into this repositories' `/bin` folder. These may now be used in Catkernel via the `make_root` script, or by other means.

# What if I compile these on another kernel?
While some of these binaries may cross-compile on Linux, BSD, or other Unix-like operating systems, these are intended for Catkernel. Specific parts **will not work on other kernels**, and I strongly advise to not use these on anything but Catkernel, as that is what I have built, and tested these for.
