# Micropolis Unlimited

— a patched version of Micropolis, an Open Source project derived from the code of the original SimCity™

This project starts from 2016-03-06 patched version of Micropolis source from:
http://git.zerfleddert.de/cgi-bin/gitweb.cgi/micropolis

It already runs better than the common Micropolis original release.

Current changes here are for debugging, so far.

---

#### To build and use, tested on Linux only:

1. put the contents of this repo into a directory

2. commands in a terminal emulator in that directory
```
$ cd src/
$ make clean
$ make install
$ cd ..
$ ./Micropolis
```

(Note: This "installs" the program only locally within its directory. The source apparently comes with some other ways to build and install and run it, but those would be more difficult to use.)

----

#### Dependencies:

The following files may be needed to build this version of Micropolis. If you try without a necessary file, a compiler error message should give a hint.

* MB        package

*   .262   make (required)
* 16.3     libx11-xcb-dev
*   .247   libxcb-image0-dev
*   .206   libxpm-dev
*  2.004   bison (tested on ARMv7 Ubuntu 14.04 era packages) OR byacc (tested on Ubuntu x86_64 17.10 packages)
*   .522   libxshmfence-dev
*  1.2     libxext-dev (definitely necessary)
