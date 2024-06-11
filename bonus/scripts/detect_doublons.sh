#!/bin/bash

# Définir une variable pour activer le mode de test automatisé
export AUTOMATED_TEST=true

# Définir les répertoires des fichiers .rt et des fichiers .bin de référence
rt_dir="tests/rt_files"
bin_dir="../../goinfre/miniRT_test_files"
dup_dir="tests/duplicates"  # Dossier où déplacer les doublons

# Créer le répertoire des doublons s'il n'existe pas
mkdir -p "$dup_dir"

# Compter le nombre de fichiers .rt dans le répertoire spécifié
total_files=$(ls "$rt_dir"/*.rt 2>/dev/null | wc -l)
if [ "$total_files" -eq 0 ]; then
    echo "Aucun fichier .rt trouvé dans le répertoire $rt_dir."
    exit 1
fi

# Créer un dictionnaire pour stocker les hachages des fichiers binaires
declare -A bin_hashes
duplicates=()

# Fonction pour calculer le hachage SHA-256 d'un fichier
hash_file() {
    sha256sum "$1" | awk '{ print $1 }'
}

# Boucle pour traiter chaque fichier .rt
for rt_file in "$rt_dir"/*.rt; do
    echo "Traitement de $rt_file..."
    # Exécuter miniRT avec le fichier .rt en arrière-plan
    ./miniRT "$rt_file" &
    sleep 0.5
    
    # Attendre la génération du fichier .bin
    while [ ! -f "file_0.bin" ]; do
        sleep 0.5
    done
    
    # Calculer le hachage du fichier .bin généré
    bin_hash=$(hash_file "file_0.bin")
    
    # Vérifier si ce hachage existe déjà dans le dictionnaire
    if [[ -n "${bin_hashes[$bin_hash]}" ]]; then
        # Ajouter le fichier .rt à la liste des doublons et déplacer le fichier
        duplicates+=("$rt_file est un doublon de ${bin_hashes[$bin_hash]}")
        mv "$rt_file" "$dup_dir"
    else
        # Ajouter le hachage et le fichier .rt correspondant au dictionnaire
        bin_hashes["$bin_hash"]="$rt_file"
    fi
    
    # Supprimer le fichier .bin généré
    rm "file_0.bin"
    sleep 0.5
    pkill miniRT
done

# Afficher les résultats
if [ ${#duplicates[@]} -eq 0 ]; then
    echo "Aucun doublon trouvé."
else
    echo "Doublons trouvés:"
    for dup in "${duplicates[@]}"; do
        echo "$dup"
    done
fi

exit 0




# #!/bin/bash

# # Définir une variable pour activer le mode de test automatisé
# export AUTOMATED_TEST=true

# # Définir les répertoires des fichiers .rt et des fichiers .bin de référence
# rt_dir="tests/rt_files"
# bin_dir="../../goinfre/miniRT_test_files"
# dup_dir="duplicates"

# # Compter le nombre de fichiers .rt dans le répertoire spécifié
# total_files=$(ls "$rt_dir"/*.rt 2>/dev/null | wc -l)
# if [ "$total_files" -eq 0 ]; then
#     echo "Aucun fichier .rt trouvé dans le répertoire $rt_dir."
#     exit 1
# fi

# # Créer un dictionnaire pour stocker les hachages des fichiers binaires
# declare -A bin_hashes
# duplicates=()

# # Fonction pour calculer le hachage SHA-256 d'un fichier
# hash_file() {
#     sha256sum "$1" | awk '{ print $1 }'
# }

# # Boucle pour traiter chaque fichier .rt
# for rt_file in "$rt_dir"/*.rt; do
#     echo "Traitement de $rt_file..."
#     # Exécuter miniRT avec le fichier .rt en arrière-plan
#     ./miniRT "$rt_file" &
#     sleep 0.5
    
#     # Attendre la génération du fichier .bin
#     while [ ! -f "file_0.bin" ]; do
#         sleep 0.5
#     done
    
#     # Calculer le hachage du fichier .bin généré
#     bin_hash=$(hash_file "file_0.bin")
    
#     # Vérifier si ce hachage existe déjà dans le dictionnaire
#     if [[ -n "${bin_hashes[$bin_hash]}" ]]; then
#         # Ajouter le fichier .rt à la liste des doublons
#         duplicates+=("$rt_file est un doublon de ${bin_hashes[$bin_hash]}")
#     else
#         # Ajouter le hachage et le fichier .rt correspondant au dictionnaire
#         bin_hashes["$bin_hash"]="$rt_file"
#     fi
    
#     # Supprimer le fichier .bin généré
#     rm "file_0.bin"
#     sleep 0.5
#     pkill miniRT
# done

# # Afficher les résultats
# if [ ${#duplicates[@]} -eq 0 ]; then
#     echo "Aucun doublon trouvé."
# else
#     # echo "Doublons trouvés:"
#     for dup in "${duplicates[@]}"; do
# 		mv dup $dup_dir
#         echo "$dup"
#     done
# fi

# exit 0