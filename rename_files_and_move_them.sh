#!/bin/bash

# Demander à l'utilisateur de saisir la valeur de départ pour la numérotation
read -p "À partir de quelle valeur voulez-vous commencer la numérotation des fichiers .rt ? " start_index

# Vérifier si la valeur saisie est un nombre entier
if ! [[ "$start_index" =~ ^[0-9]+$ ]]; then
    echo "La valeur saisie n'est pas un nombre entier. Sortie du script."
    exit 1
fi

# Créer le répertoire de destination s'il n'existe pas déjà
destination_folder="tests/rt_files"
mkdir -p "$destination_folder"

# Initialiser l'index de départ pour la renumérotation
index=$start_index

# Parcourir les fichiers .rt à la racine du dépôt
for file in file_*.rt; do
    if [[ -f "$file" ]]; then
        new_filename="file_$index.rt"
        mv "$file" "$destination_folder/$new_filename"
        echo "$file a été renommé et déplacé vers $destination_folder/$new_filename"
        ((index++))
    fi
done

echo "Tous les fichiers ont été renommés et déplacés avec succès."
