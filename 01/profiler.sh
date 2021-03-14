#!/bin/bash
# compile programs if necessary
echo "Compilation: "
make
echo

implementations=(slow medium fast)
mkdir -p data
declare -A iterations
iterations[${implementations[0]}]=1
iterations[${implementations[1]}]=2
iterations[${implementations[2]}]=2


for exec in ${implementations[*]}; do
  # create/empty files
  > ./data/$exec.txt
  echo -e "#Threads\t Time">>./data/$exec.txt
  echo "Profiling" $exec "implementation"
  echo "Iterating" ${iterations[$exec]} "times for each OMP_NUM_THREADS"
  for i in {1..12}; do
    # write results to files
    echo -e "\n OMP_NUM_THREADS =" $i "\n \t iteration_no:"
    export OMP_NUM_THREADS=$i
    temp=0

    # execute each program for each value of OMP_NUM_THREADS $iterations times
    # add all times
    for (( j=1; j<=${iterations[$exec]}; j++ ))
    do
      echo -e "\t" $j
      str=$(./$exec)
      temp=$(echo $temp"+" "${str:21:-8}" | bc)
    done

    # write to file
    echo -e $i "\t" $temp>>./data/$exec.txt
  done
done

# check for gnuplot
if ! command -v gnuplot &> /dev/null
then
    echo -e "gnuplot could not be found \n install gnuplot to see plots"
    exit
fi

# plot results
for exec in ${implementations[*]}; do
  echo
  cat ./data/$exec.txt
  cat ./data/$exec.txt | gnuplot -p -e "set xrange [0:13]; set pointsize 3; plot '-' linetype 2 pointtype 2"
done
