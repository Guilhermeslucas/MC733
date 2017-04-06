#/bin/bash

#script done to optimize the work

folders_path=`echo $HOME"/dinero/d4-7/traces/"`
folders=`ls $folders_path`
dinero_path=`echo $HOME"/dinero/d4-7/dineroIV"`

for folder in $folders;
do
    folder_path=`echo $folders_path$folder"/"`
    cd $folder_path
    for j in {3..5}; 
    do
        for k in {3..5};
        do
            $dinero_path -informat s -trname $folder -maxtrace 20 -l1-isize 64k -l1-dsize 64k -l1-ibsize `echo "2^$j" | bc` -l1-dbsize `echo "2^$j" | bc`  -l1-iassoc `echo "2^$k" | bc` -l1-dassoc `echo "2^$k" | bc` >> $folder\_"output.txt"
        done
    done    
done
