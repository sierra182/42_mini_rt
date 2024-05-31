#!/bin/bash

# Nombre total de fichiers à traiter
total_files=$(ls tests/rt_files/*.rt | wc -l)

# Boucle pour traiter chaque fichier
for ((i=0; i<total_files; i++)); do
    # Chemin du fichier .rt
    rt_file="tests/rt_files/file_$i.rt"
    # Chemin du fichier .bin de référence
    ref_bin_file="tests/ref_files/file_$i.bin"

    # Commande pour exécuter miniRT avec le fichier .rt
    ./miniRT "$rt_file" &
    # Attendre 1 seconde pour s'assurer que le programme s'est ouvert
    sleep 1

    # Attendre que le fichier .bin soit généré
    while [ ! -f "file_0.bin" ]; do
        sleep 0.1
    done

    # Comparer le fichier .bin généré avec le fichier de référence
    if cmp -s "file_0.bin" "$ref_bin_file"; then
        echo "No difference found: file_$i"
    else
        echo "Difference found: file_$i"
    fi

    # Nettoyer le fichier .bin généré
    rm "file_0.bin"

    pkill miniRT

done
