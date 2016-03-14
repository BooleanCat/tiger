#!/bin/bash

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
LIB_DIR=${DIR}/lib

if [ -d $DIR/bin ]; then rm -r $DIR/bin; fi
mkdir $DIR/bin

gcc \
    -std=c99 \
    $LIB_DIR/main.c $LIB_DIR/utils.c $LIB_DIR/statements.c \
    -I./include \
    -o $DIR/bin/test
