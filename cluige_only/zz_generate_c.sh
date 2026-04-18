#!/usr/bin/env bash

# Need exactly 2 args
if [ "$#" -ne 2 ]; then
  echo "Missing arguments (name of script without '.gd', path of .gd without res:/ nor .gd)." >&2
fi

script_name="$1"
script_path="$2"

cp  blink_label.c ${script_name}.c
cp  blink_label.h ${script_name}.h
sed -i "s/BlinkLabel/$script_name/g" ${script_name}.c
sed -i "s/BlinkLabel/$script_name/g" ${script_name}.h
sed -i "s/BLINK_LABEL/$script_name/g" ${script_name}.h
sed -i "s/blink_label.h/$script_name.h/g" ${script_name}.c
sed -i "s/blink_label/$script_path/g" ${script_name}.c

#not good with scripts in subdirs
