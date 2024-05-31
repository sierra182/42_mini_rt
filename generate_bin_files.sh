#!/bin/bash

export AUTOMATED_TEST=true

# Nombre total de fichiers à traiter
total_files=$(ls tests/rt_files/*.rt | wc -l)

# Boucle pour traiter chaque fichier
for ((i=0; i<total_files; i++)); do
    # Chemin du fichier .rt
    rt_file="tests/rt_files/file_$i.rt"
    # Chemin du fichier .bin de référence
    ref_bin_file="tests/bin_files/file_$i.bin"


	
	new_bin_file="file_$i.bin"
	bin_folder="tests/bin_files"

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

    echo "file_$i ✅ : bin file created and moved"
done

echo "All files processed successfully."
