for file in `ls *.dat`
do
 echo $file
 mv $file `echo $file|sed 's/20210123/20210504/g'`
done
