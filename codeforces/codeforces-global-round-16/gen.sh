n=100000
m=100000
q=100000
echo $n $m
for i in $(seq 1 $n); do
    echo $(($RANDOM%$n + 1)) $(($RANDOM%$n + 1)) $(($RANDOM*$RANDOM))
done
echo $q
for i in $(seq 1 $q); do
            echo 1 $(($RANDOM%$n + 1)) $(($RANDOM%$n + 1)) $(($RANDOM*$RANDOM))
done
