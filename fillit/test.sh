#!/bin/bash

rm -rf /tmp/fillit
cp -rf ~/Documents/03-fillit /tmp/fillit
rm -rf /tmp/fillit/tests
rm /tmp/fillit/sujet.pdf
rm /tmp/fillit/fillit.exe*
rm /tmp/fillit/fillit
rm /tmp/fillit/test.sh
sh ~/42FileChecker/42FileChecker.sh
