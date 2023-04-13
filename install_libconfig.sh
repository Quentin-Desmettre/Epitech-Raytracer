#!/bin/bash

TARBALL="libconfig-1.7.3.tar.gz"
LIB_NAME="libconfig-1.7.3"

# Clean workspace
rm -rf $LIB_NAME
rm -f $TARBALL

# Curl tarball
curl -O https://hyperrealm.github.io/libconfig/dist/$TARBALL

# Unzip tarball
tar -xvf $TARBALL
cd $LIB_NAME

# Configure, build, and install
./configure
make
sudo make install

# Clean workspace
cd ..
rm -rf $LIB_NAME
rm -f $TARBALL
