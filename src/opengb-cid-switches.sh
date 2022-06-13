#!/bin/bash
# *-* encoding: utf-8 *-*

src_dir="."
src_filename="test"



echo "src_dir=$src_dir"
echo "src_filename=$src_filename"
src_path="$src_dir/$src_filename"
echo "src_path=$src_path"

echo "\$*=$*" # All arguments in one string
echo -n "\$@[\$#=$#]={" # All arguments in a array
if [ $# -gt 0 ]; then
	echo -n " \"$@[0]\""
	i=1
	while [ $i -lt $# ]; do
		echo -n ", \"$@[$i]\""
		let "i++"
	done
fi
echo " }"
echo  # The number of arguments

if [ "$1" == "-p" ] || [ "$1" == "--pre-commit" ]; then
	echo "OpenGB-CId-Switches Script: Pre-commit Mode"

	echo -n "Macro switch \"_OPENGB_CID_SWITCHES_FIRST_EDIT\" status is "
	if [ -z "$(cat "$src_path" | grep -Pzo '(^|\n).*?//.*?#define _OPENGB_CID_SWITCHES_FIRST_EDIT')" ] \
		&& [-n "$(cat "$src_path" | grep -Pzo '((^|\n).*?)#define _OPENGB_CID_SWITCHES_FIRST_EDIT')"]; then
		echo "[On]"

		echo -n "Turn off macro switch \"_OPENGB_CID_SWITCHES_FIRST_EDIT\" "
		sed -i -E -e "s/(^|\n).*?\\/\\/.*?#define _OPENGB_CID_SWITCHES_FIRST_EDIT/" "$src_path"
		if [ -n "$(cat "$src_path" | grep -Pzo '(^|\n).*?//.*?#define _OPENGB_CID_SWITCHES_FIRST_EDIT')" ]; then
			echo "[FAILURE]"
			exit 1
		else
			echo "[Passed]"
		fi

	else
		echo "[Off]"
	fi
elif [ "$1" == "-d" ] || [ "$1" == "--development" ]; then
	echo "OpenGB-CId-Switches Script: Development Mode"


else
	echo "Command syntax: opengb-cid-switches.sh [-p|--pre-commit] | [-d|--development]"
	echo "Use -p or --pre-commit to run in pre-commit mode. It will turn off the macro switch \"_OPENGB_CID_SWITCHES_FIRST_EDIT\"."
	echo "Use -d or --development to run in development mode. It will turn on the macro switch \"_OPENGB_CID_SWITCHES_FIRST_EDIT\"."
fi

exit 0
