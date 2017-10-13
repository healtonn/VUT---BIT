#!/usr/bin/env bash
limitPokladen=5
limitKucharu=10
limitVydejcu=4
file="output.txt"
echo "Spoustim simulace..."
> output.txt
rm -rf o*
for (( p=2; p<=3; p++ ))
do  
	for (( k=4; k<=7; k++ ))
	do
		for (( v=2; v<=3; v++ ))
		do
			./ims -p $p -k $k -v $v >> output.txt
		done
	done
done