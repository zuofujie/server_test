#!/bin/bash

current_dir=$(cd `dirname $0`; pwd)

base_dir=`dirname $current_dir`

echo $base_dir

date1=`date +%s`

i=10
while [ $i -gt 0 ]
do
	echo $i
	$base_dir/client &
	i=`expr $i - 1`
done

wait

date2=`date +%s`

date3=`expr $date2 - $date1`

echo $date3
