#!/bin/bash

# Configurer une variable d'environnement pour signaler qu'il s'agit d'un test
export TESTING=true

# Dossier contenant les fichiers .rt de test
TEST_DIR="rt_files_test"
OUTPUT_DIR="test_outputs"

# Créer le dossier de sortie s'il n'existe pas
mkdir -p "$OUTPUT_DIR"

# Fonction pour tester un fichier .rt
test_file() {
    local file=$1
    local filename=$(basename -- "$file")
    local output_file="$OUTPUT_DIR/$filename.out"

    
    # Exécuter miniRT avec le fichier de test et rediriger la sortie
    ./miniRT_bonus "$file" > "$output_file" 2>&1

    # Vérifier le code de retour de miniRT
    if [ $? -eq 0 ]; then
        echo "✅: $file"
    else
        echo "❌: $file"
    fi
}

# Vérifier si le dossier de test existe
if [ ! -d "$TEST_DIR" ]; then
    echo "Test directory $TEST_DIR does not exist"
    exit 1
fi

# Tester chaque fichier .rt dans le dossier de test
for file in "$TEST_DIR"/*.rt; do
    if [ -f "$file" ]; then
        test_file "$file"
    fi
done

# Réinitialiser la variable d'environnement
unset TESTING

echo "All tests completed."
