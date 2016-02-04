sfarkxtc
========

[![Build Status](https://travis-ci.org/raboof/sfarkxtc.svg?branch=master)](https://travis-ci.org/raboof/sfarkxtc)

sfArk extractor, console version

Converts soundfonts in the legacy sfArk v2 file format to sf2

Building
========

Prerequisites
-------------

* Install zlib, e.g. from the zlib1g-dev package
* Build and install sfarklib as described at https://github.com/raboof/sfArkLib

Building
--------

    $ sudo make install

that's it!
    
Usage
=====

    $ ./sfarkxtc somefile.sfArk somefile.sf2
