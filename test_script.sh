#!/bin/bash

export AUTOMATED_TEST=true
total_files=$(ls tests/rt_files/*.rt | wc -l)
exit_code=0
for ((i=0; i<total_files; i++)); do
    rt_file="tests/rt_files/file_$i.rt"
    ref_bin_file="tests/bin_files/file_$i.bin"
    ./miniRT "$rt_file" &
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
    pkill miniRT
done
exit $exit_code