i=0
j=1
./ch1-ex-1-18-01 <test.txt >out1.txt
while [ $? -eq 1 ] && [ $j -lt 20 ]; do
    let i+=1
    let j+=1
    ./ch1-ex-1-18-01 <out${i}.txt >out${j}.txt
done
