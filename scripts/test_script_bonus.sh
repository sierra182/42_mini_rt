#!/bin/bash

export AUTOMATED_TEST=true
total_files=$(ls sebonustest/*.rt 2>/dev/null | wc -l)
if [ "$total_files" -eq 0 ]; then
    echo "Aucun fichier .rt trouvé dans le répertoire sebonustest."
    exit_code=0
	exit 1
fi

for ((i=0; i<total_files; i++)); do
    rt_file="sebonustest/file_$i.rt"
    ref_bin_file="../../../goinfre/miniRT_test_files/bonus/file_$i.bin"
    ./miniRT_bonus "$rt_file" &
    sleep 0.5
    while [ ! -f "file_0.bin" ]; do
        sleep 0.5
    done
    if cmp -s "file_0.bin" "$ref_bin_file"; then
        echo "file_$i ✅ : no difference found"
    else
        echo "file_$i ❌ : files are different"
		exit_code=1
    fi
    rm "file_0.bin"
	sleep 0.5
    pkill miniRT_bonus
done
exit $exit_code