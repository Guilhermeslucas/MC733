#/bin/bash

#script done to optimize the work

folders_path=`echo $HOME"/dinero/d4-7/traces/"`
folders=`ls $folders_path`
dinero_path=`echo $HOME"/dinero/d4-7/dineroIV"`

for folder in $folders;
do
    folder_path=`echo $folders_path$folder"/"`
    cd $folder_path
    for j in {3..6}; 
    do
        $dinero_path -informat s -trname $folder -maxtrace 20 -l1-isize `echo "2^$j" | bc`k -l1-dsize `echo "2^$j" | bc`k -l1-ibsize 32 -l1-dbsize 32 >> $folder\_"output.txt"
    done    
done
