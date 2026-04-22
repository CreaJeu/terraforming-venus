#!/usr/bin/env bash

# Need exactly 2 args
if [ "$#" -ne 2 ]; then
  echo "Missing arguments (name of script without '.gd', path of .gd without res:/ nor .gd)." >&2
fi

script_name="$1"
script_path="$2"

cp  MoreWindmills.c ${script_name}.c
cp  MoreWindmills.h ${script_name}.h
sed -i "s/MoreWindmills/$script_name/g" ${script_name}.c
sed -i "s/MoreWindmills/$script_name/g" ${script_name}.h
sed -i "s/more_windmills/$script_path/g" ${script_name}.c

#not good with scripts in subdirs
