#!/bin/bash

export AUTOMATED_TEST=true

# Nombre total de fichiers à traiter
total_files=$(ls tests/rt_files/*.rt | wc -l)

exit_code=0

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
        echo "file_$i ✅ : no difference found"
    else
        echo "file_$i ❌ : files are different"
		exit_code=1
    fi

    # Nettoyer le fichier .bin généré
    rm "file_0.bin"

    pkill miniRT

done

# Retourner le code de sortie approprié
exit $exit_code