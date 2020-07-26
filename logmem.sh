grep VmPeak /proc/`ps aux | grep -v "grep" | egrep './d2' | awk '{print $2;}'`/status >> ~/log


