#!/bin/bash

export AUTOMATED_TEST=true

total_files=$(ls tests/rt_files_bonus/*.rt 2>/dev/null | wc -l)
if [ "$total_files" -eq 0 ]; then
    echo "Aucun fichier .rt trouvé dans le répertoire tests/rt_files_bonus."
    exit 1
fi
read -p "À partir de quelle valeur voulez-vous commencer la numérotation des fichiers .bin ? " start_index
if ! [[ "$start_index" =~ ^[0-9]+$ ]]; then
    echo "La valeur saisie n'est pas un nombre entier. Sortie du script."
    exit 1
fi
for ((i=0; i<total_files; i++)); do
    rt_file="tests/rt_files_bonus/file_$i.rt"
	new_bin_file="file_$((start_index + i)).bin"
	bin_folder="../../goinfre/miniRT_test_files/bonus/"
	if [ ! -d "$bin_folder" ]; then
    mkdir -p "$bin_folder"
    echo "Dossier $bin_folder créé."
fi
    ./bonus/miniRT_bonus "$rt_file" &
    sleep 1
    while [ ! -f "file_0.bin" ]; do
        sleep 1
    done
    mv "file_0.bin" "$new_bin_file"
    mv "$new_bin_file" "$bin_folder/"
    pkill miniRT
    echo "$new_bin_file ✅ : bin file created and moved"
done
echo "All files processed successfully."