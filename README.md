# dwm - dynamic window manager
------------
dwm is an extremely fast, small, and dynamic window manager for X.

# Requirements
------------

```bash
$ sudo xbps-install -y xinit xauth xorg-server xorg-minmal
```

### Dependencies needed for compile dwm in `void linux` from scratch is:
```bash
$ sudo xbps-install -y base-devel libX11-devel libXft-devel libXinerama-devel freetype-devel fontconfig-devel 
```

### Dependencies for arrabic font:
```bash
$ xbps-install -Sy xorg-util-macros
$ cd /opt/app/libxft/libxft
$ sh autogen.sh --sysconfdir=/etc --prefix=/usr --mandir=/usr/share/man
$ ./configure
$ make && make install
```
#Installation
------------
```bash
$ make clean install
```
