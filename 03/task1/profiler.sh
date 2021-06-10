#!/bin/bash
# compile programs if necessary
echo "Compilation: "
make
echo

implementations=(task1 task2 task3)
mkdir -p data
declare -A iterations
iterations[${implementations[0]}]=1
iterations[${implementations[1]}]=1
iterations[${implementations[2]}]=1


for exec in ${implementations[*]}; do
  # create/empty files
  > ./data/$exec.txt
  echo -n -e "#Threads\t">>./data/$exec.txt
  for (( j=1; j<=${iterations[$exec]}; j++ )); do echo -n -e "Time\t">>./data/$exec.txt; done
  echo "TotalTime">>./data/$exec.txt
  echo "Profiling" $exec "implementation"
  echo "Iterating" ${iterations[$exec]} "time(s) for each OMP_NUM_THREADS"
  for i in {1..12}; do
    # write lcc2_results to files
    echo -e "\n OMP_NUM_THREADS =" $i "\n \t iteration_no:"
    export OMP_NUM_THREADS=$i
    temp=0

    # execute each program for each value of OMP_NUM_THREADS $iterations times
    # add all times
    echo -n -e $i "\t">>./data/$exec.txt
    for (( j=1; j<=${iterations[$exec]}; j++ ))
    do
      echo -e "\t" $j
      str=$(./$exec 500000000)
      temp=$(echo $temp"+" "${str}" | bc)
      echo -n -e "${str}" "\t">>./data/$exec.txt
    done

    # write to file
    echo $temp>>./data/$exec.txt
  done
done

make clean
