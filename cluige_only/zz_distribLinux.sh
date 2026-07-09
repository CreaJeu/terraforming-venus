#!/usr/bin/env bash
set -uo pipefail


mode="Release"
dir="../releases/terraformingVenus_linux"

# Validate mode (exact match)
if [ "$mode" != "Debug" ] && [ "$mode" != "Release" ]; then
  echo "bug in script" >&2
  exit 2
fi

# Validate directory exists and is a directory
if [ ! -d "$dir" ]; then
  echo "bug in script" >&2
  exit 2
fi



#libXCurses.so is regenerated either as Debug or as Release => think to rebuild it in codeblocks if needed
pdc_so_path="../../PDCurses/x11/libXCurses.so"
if ! command -v readelf >/dev/null 2>&1; then
  echo "Error: readelf not found in PATH." >&2
  exit 3
fi
if [ ! -f "$pdc_so_path" ]; then
  echo "Error: '$pdc_so_path' not found." >&2
  exit 4
fi
# detect presence of DWARF debug sections
if readelf --sections "$pdc_so_path" 2>/dev/null | grep -qE '\.debug_info|\.debug_frame|\.debug_abbrev|\.stab'; then
  has_debug=1
else
  has_debug=0
fi
if [ "$mode" = "Debug" ]; then
  if [ ! "$has_debug" -eq 1 ]; then
    echo "Error: mode is Debug but '$pdc_so_path' has no debug symbols. => rebuild it as Debug first" >&2
    exit 5
  fi
else  # mode is Release
  if [ "$has_debug" -eq 1 ]; then
    echo "Error: mode is Release but '$pdc_so_path' contains debug symbols. => rebuild it as Release first" >&2
    exit 6
  fi
fi


#copy only what needed for cluige game
mkdir -p $dir/assets
#mkdir -p $dir/scenes
mkdir -p $dir/scenes/upgrades
cp -vu $pdc_so_path $dir
cp -vu ../../cluige/bin/$mode/libcluige.so $dir
cp -vu ../bin/$mode/terraformVenus $dir/terraformVenus_x86_64
#cp -vur assets $dir
cp -vu ../project.godot $dir/
cp -vu ../assets/*.svg  $dir/assets
#cp -vu ../godot_only/*.tscn $dir/godot_example/godot_only
cp -vur ../scenes/*.tscn $dir/scenes
cp -vur ../scenes/upgrades/*.tscn $dir/scenes/upgrades

echo done

