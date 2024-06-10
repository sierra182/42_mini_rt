#!/usr/bin/env python3

import os

# Définissez les chemins de vos répertoires source et include
src_dir = "./sources"
include_dir = "./includes"

# Fonction pour créer un fichier d'en-tête pour un fichier .c donné
def create_header_file(c_file_path, h_file_path):
    base_name = os.path.splitext(os.path.basename(c_file_path))[0]
    header_guard = base_name.upper() + "_H"

    with open(h_file_path, 'w') as h_file:
        h_file.write(f"#ifndef {header_guard}\n")
        h_file.write(f"# define {header_guard}\n\n")
        h_file.write(f"// Déclarations pour {os.path.basename(c_file_path)}\n\n")
        h_file.write(f"#endif\n")

    print(f"Créé : {h_file_path}")

# Fonction pour parcourir récursivement les répertoires
def process_directory(current_src_dir, current_include_dir):
    # Assurez-vous que le répertoire include correspondant existe
    if not os.path.exists(current_include_dir):
        os.makedirs(current_include_dir)

    # Parcourez les fichiers et sous-répertoires dans le répertoire source actuel
    for item in os.listdir(current_src_dir):
        src_path = os.path.join(current_src_dir, item)
        include_path = os.path.join(current_include_dir, item)

        if os.path.isdir(src_path):
            # Si l'élément est un répertoire, procédez récursivement
            process_directory(src_path, include_path)
        elif src_path.endswith(".c"):
            # Si l'élément est un fichier .c, créez le fichier .h correspondant
            h_file_path = os.path.splitext(include_path)[0] + ".h"
            if not os.path.exists(h_file_path):
                create_header_file(src_path, h_file_path)
            else:
                print(f"Existe déjà : {h_file_path}")

# Démarrez le traitement à partir du répertoire source racine
process_directory(src_dir, include_dir)
