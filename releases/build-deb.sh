#!/bin/bash

dpkg-deb --build gxe-ispf-1.29/  gxe-ispf-1.29-armhf.deb
lintian gxe-ispf-1.29-armhf.deb

