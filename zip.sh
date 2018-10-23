#!/bin/sh

LOGIN=xtotha01

rm -rf $LOGIN.zip $LOGIN
mkdir -pv $LOGIN/projekt

echo
cp -v doc/doc.pdf $LOGIN
cp -Rv data $LOGIN/projekt
cp -Rv src $LOGIN/projekt
cp -Rv doc $LOGIN/projekt

echo
make clean-all -C $LOGIN/projekt/doc

echo
tree $LOGIN

zip -r --verbose $LOGIN.zip $LOGIN
rm -rf $LOGIN
