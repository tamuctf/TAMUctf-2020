#!/bin/bash
printf "Execute: "
while read text;
do
	bash -c "$text" >/dev/null 2>&1;
	echo $?;
	printf "Execute: "
done