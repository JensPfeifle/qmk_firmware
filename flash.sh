#!/bin/bash

set -e

if [ $# -eq 0 ]
  then
    echo "No arguments supplied. Required: name of keymap json file"
    exit 1
fi

JSONFILE=$1

source ./venv/bin/activate

python3 keymap.py ./my_keymaps/$JSONFILE

qmk compile

qmk flash

