#!/bin/bash

export AUTOMATED_TEST=true

# Nombre total de fichiers à traiter
total_files=$(ls tests/rt_files/*.rt | wc -l)

if [ "$total_files" -eq 0 ]; then
    exit 1
fi

# Demander à l'utilisateur à partir de quelle valeur commencer la numérotation des fichiers .bin
read -p "À partir de quelle valeur voulez-vous commencer la numérotation des fichiers .bin ? " start_index

# Vérifier si la valeur saisie est un nombre entier
if ! [[ "$start_index" =~ ^[0-9]+$ ]]; then
    echo "La valeur saisie n'est pas un nombre entier. Sortie du script."
    exit 1
fi


# Boucle pour traiter chaque fichier
for ((i=0; i<total_files; i++)); do
    # Chemin du fichier .rt
    rt_file="tests/rt_files/file_$i.rt"
    # Chemin du fichier .bin de référence
    ref_bin_file="tests/bin_files/file_$i.bin"


	
	new_bin_file="file_$((start_index + i)).bin"
	bin_folder="tests/new_files"

    # Commande pour exécuter miniRT avec le fichier .rt
    ./miniRT "$rt_file" &
    # Attendre 1 seconde pour s'assurer que le programme s'est ouvert
    sleep 0.5

    # Attendre que le fichier .bin soit généré
    while [ ! -f "file_0.bin" ]; do
        sleep 0.5
    done

    # Comparer le fichier .bin généré avec le fichier de référence
    mv "file_0.bin" "$new_bin_file"

    # Déplacer le fichier .bin renommé vers le dossier de destination
    mv "$new_bin_file" "$bin_folder/"

    pkill miniRT

    echo "$new_bin_file ✅ : bin file created and moved"
done

echo "All files processed successfully."
