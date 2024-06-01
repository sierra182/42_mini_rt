#!/bin/bash

total_files=$(ls tests/rt_files/*.rt 2>/dev/null | wc -l)
if [ "$total_files" -eq 0 ]; then
    echo "Aucun fichier .rt trouvé dans le répertoire tests/rt_files."
    exit_code=0
    exit 1
fi

for ((i=0; i<total_files; i++)); do
    rt_file="tests/rt_files/file_$i.rt"
    ./miniRT "$rt_file" &
    sleep 0.5

    while true; do
        read -p "Appuyez sur espace ou entrée pour continuer, ou 'q' pour quitter..." -n 1 key
        if [[ "$key" == " " || "$key" == "" ]]; then
            pkill miniRT
            break
        elif [ "$key" == "q" ]; then
            exit 0
        fi
    done
done
exit $exit_code