#!/bin/bash

mkdir -p frontend/app/pkg/USRDIR/mamebins

for i in {1..14}; do
export PS3_SET_NUM=$i
touch src/mame/mamedriv.c
make NOWERROR=1 CROSS_BUILD=1 CROSSBUILD=1 TARGETOS=linux OSD=osdmini NO_X11=1 NO_OPENGL=1 -f makefile.ps3 -j3
make_self_wc mame frontend/app/pkg/USRDIR/mamebins/mame-$i.self
done

