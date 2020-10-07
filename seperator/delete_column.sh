#！/bin/bash
#author:Zelin Li
#date:2020/05/11

input=$1
grep -n "" $input | awk -F ':' '{print $1}' > line.txt
awk '{print $2"\t"$3}' $input | sort -n -r > se.txt
for line in $(cat line.txt); do
	s=`echo $(sed -n ${line}p se.txt) | awk NR==1'{print $1}'`;
	e=`echo $(sed -n ${line}p se.txt) | awk NR==1'{print $2}'`;
	if ((s==e)); then
		awk -F '\t' '{$($e)=null;print $0}' out.txt > out.txt
	elif ((s<=e)); then
		for (( i = e; i > s; i=i-1 )); do
			awk -F '\t' '{$($i)=null;print $0}' out.txt > out.txt
		done
	fi
done
rm -rf line.txt
rm -rf se.txt
