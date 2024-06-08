import os

# Définissez les chemins de vos répertoires source et include
src_dir = "./sources"
include_dir = "./include"

# Assurez-vous que le répertoire include existe
if not os.path.exists(include_dir):
    os.makedirs(include_dir)

# Parcourez tous les fichiers .c dans le répertoire source
for filename in os.listdir(src_dir):
    if filename.endswith(".c"):
        # Nom du fichier source sans l'extension
        base_name = os.path.splitext(filename)[0]
        
        # Chemin complet vers le fichier .c
        c_file_path = os.path.join(src_dir, filename)
        
        # Chemin complet vers le fichier .h à créer
        h_file_path = os.path.join(include_dir, f"{base_name}.h")
        
        # Si le fichier .h n'existe pas déjà, créez-le
        if not os.path.exists(h_file_path):
            with open(h_file_path, 'w') as h_file:
                header_guard = base_name.upper() + "_H"
                
                # Écrire le contenu de base du fichier d'en-tête
                h_file.write(f"#ifndef {header_guard}\n")
                h_file.write(f"#define {header_guard}\n\n")
                h_file.write(f"// Déclarations pour {filename}\n\n")
                h_file.write(f"#endif // {header_guard}\n")
                
            print(f"Créé : {h_file_path}")
        else:
            print(f"Existe déjà : {h_file_path}")
