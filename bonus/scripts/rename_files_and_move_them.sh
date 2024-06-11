#!/bin/bash

read -p "À partir de quelle valeur voulez-vous commencer la numérotation des fichiers .rt ? " start_index
if ! [[ "$start_index" =~ ^[0-9]+$ ]]; then
    echo "La valeur saisie n'est pas un nombre entier. Sortie du script."
    exit 1
fi
destination_folder="tests/rt_files"
mkdir -p "$destination_folder"
index=$start_index
for file in file_*.rt; do
    if [[ -f "$file" ]]; then
        new_filename="file_$index.rt"
        mv "$file" "$destination_folder/$new_filename"
        echo "$file a été renommé et déplacé vers $destination_folder/$new_filename"
        ((index++))
    fi
done
echo "Tous les fichiers ont été renommés et déplacés avec succès."
