#!/bin/bash

count=0
seednum=0
for name in `cat ./filenamelist_Crymuons_hodoTrig.txt`
do
    #echo $name
#    thisarray[$count]=$name
    ((count = count + 1))
    ((seednum = count * 12))
    thisseedstr[$count]="-s$seednum"
    echo ${thisseedstr[$count]}


datstr=$name
new1=$datstr
new2=$datstr
new3=$datstr
replace1="tophodo.mac"
replace2="tophodo.root"
replace3="tophodo.sh"
find=".dat"
macstr=${new1//$find/$replace1}
rootstr=${new2//$find/$replace2}
jobstr=${new3//$find/$replace3}
#seedStr=${thisseedstr[${1}]}
#echo -s$seednum
echo ${macstr} ${rootstr} ${datstr} ${jobstr}
python PrepareRatPacMacFile.py ${macstr} ${rootstr} ${datstr}
>$jobstr
echo "#!/bin/bash">>$jobstr
echo "cd /public/users/zhaoy/softwares/rat-pac/data/20210322watermc">>$jobstr
#echo "cd /public/users/zhaoy/bnlwbls/simulation/water_run/20210303watermc">>$jobstr
echo "/public/users/zhaoy/softwares/rat-pac/bin/rat" -s $seednum  ${macstr} >>$jobstr
chmod a+x $jobstr
#sh $jobstr &>/dev/null &
#bash $jobstr
#qsub 
done

#datstr=${thisarray[${1}]}
#new1=$datstr
#new2=$datstr
#replace1=".mac"
#replace2=".root"
#find=".dat"
#macstr=${new1//$find/$replace1}
#rootstr=${new2//$find/$replace2}
#
#seedStr=${thisseedstr[${1}]}
#echo ${macstr} ${rootstr} ${datstr}
#python PrepareRatPacMacFile.py ${macstr} ${rootstr} ${datstr}
#/public/users/zhaoy/softwares/rat-pac/bin/rat $seedStr  ${macstr}

#echo ${old}
#echo ${result}


