#!/bin/bash
# compile programs if necessary
echo "Compilation: "
make
echo

implementations=(slow medium fast)
mkdir -p data
declare -A iterations
iterations[${implementations[0]}]=10
iterations[${implementations[1]}]=30
iterations[${implementations[2]}]=100


for exec in ${implementations[*]}; do
  # create/empty files
  > ./data/new2/$exec.txt
  echo -n -e "#Threads\t">>./data/new2/$exec.txt
  for (( j=1; j<=${iterations[$exec]}; j++ )); do echo -n -e "Time\t">>./data/new2/$exec.txt; done
  echo "TotalTime">>./data/new2/$exec.txt
  echo "Profiling" $exec "implementation"
  echo "Iterating" ${iterations[$exec]} "time(s) for each OMP_NUM_THREADS"
  for i in {1..12}; do
    # write lcc2_results to files
    echo -e "\n OMP_NUM_THREADS =" $i "\n \t iteration_no:"
    export OMP_NUM_THREADS=$i
    temp=0

    # execute each program for each value of OMP_NUM_THREADS $iterations times
    # add all times
    echo -n -e $i "\t">>./data/new2/$exec.txt
    for (( j=1; j<=${iterations[$exec]}; j++ ))
    do
      echo -e "\t" $j
      str=$(./$exec)
      temp=$(echo $temp"+" "${str:21:-8}" | bc)
      echo -n -e "${str:21:-8}" "\t">>./data/new2/$exec.txt
    done

    # write to file
    echo $temp>>./data/new2/$exec.txt
  done
done

# check for gnuplot
if ! command -v gnuplot &> /dev/null
then
    echo -e "gnuplot could not be found \n install gnuplot to see plots"
    exit
fi

# plot lcc2_results
for exec in ${implementations[*]}; do
  echo
  cat ./data/new2/$exec.txt
  cat ./data/new2/$exec.txt | gnuplot -p -e "set xrange [0:13]; set pointsize 3; plot '-' linetype 2 pointtype 2"
done
