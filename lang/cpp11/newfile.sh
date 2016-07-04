#!/usr/bin/env bash

NAME=$1
if [ -z $NAME ]; then echo "please give name"; exit 1; fi

FNAME=$1.cpp
if [ -e $FNAME ]; then echo "$FNAME exists"; exit 1; fi

cat <<EOM > $FNAME
#include "lang.hpp"

EOM

sed -i~ 's/#source_files/#source_files\'$'\n    '$FNAME'/' CMakeLists.txt
