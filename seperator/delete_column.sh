#！/bin/bash
#author:Zelin Li
#date:2020/05/11

grep -n "" 7.txt | awk -F ':' '{print $1}' > 7line.txt
awk '{print $2"\t"$3}' 7.txt | sort -n -r > 7se.txt
for line in $(cat 7line.txt); do
	s=`echo $(sed -n ${line}p 7se.txt) | awk NR==1'{print $1}'`;
	e=`echo $(sed -n ${line}p 7se.txt) | awk NR==1'{print $2}'`;
	if ((s==e)); then
		awk -F '\t' '{$($e)=null;print $0}' out.txt > out.txt
	elif ((s<=e)); then
		for (( i = e; i > s; i=i-1 )); do
			awk -F '\t' '{$($i)=null;print $0}' out.txt > out.txt
		done
	fi
done
