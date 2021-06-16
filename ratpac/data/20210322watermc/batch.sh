#!/bin/bash

count=0
seednum=0
for name in `cat ./filenamelist_Crymuons_hodoTrig.txt`
do
    #echo $name
    thisarray[$count]=$name
    ((count = count + 1))
    ((seednum = count * 10))
    thisseedstr[$count]="-s$seednum"
    #echo ${thisseedstr[$count]}
done

datstr=${thisarray[${1}]}
new1=$datstr
new2=$datstr
replace1=".mac"
replace2=".root"
find=".dat"
macstr=${new1//$find/$replace1}
rootstr=${new2//$find/$replace2}

seedStr=${thisseedstr[${1}]}

/gpfs01/lbne/users/aw325/sw/Python2.7.13.install/bin/python2.7 PrepareRatPacMacFile.py ${macstr} ${rootstr} ${datstr}
/gpfs01/lbne/users/aw325/rat-pac/bin/rat $seedStr  ${macstr}

#echo ${old}
#echo ${result}


