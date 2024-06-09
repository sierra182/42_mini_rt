import os
from PIL import Image
import numpy as np

# Paramètres d'entrée
input_directory = 'videos/bin_files'  # Remplacez par le chemin de votre dossier
output_directory = 'videos/jpg_files'  # Remplacez par le chemin de votre dossier de sortie
width = 800  # largeur de l'image
height = 600  # hauteur de l'image

# Vérifiez si le dossier de sortie existe, sinon créez-le
if not os.path.exists(output_directory):
    os.makedirs(output_directory)

# Parcourir tous les fichiers du répertoire d'entrée
for filename in os.listdir(input_directory):
    if filename.endswith('.bin'):
        input_bin_file = os.path.join(input_directory, filename)
        output_jpg_file = os.path.join(output_directory, f"{os.path.splitext(filename)[0]}.jpg")

        # Lire le fichier .bin
        with open(input_bin_file, 'rb') as f:
            data = f.read()

        # Assurez-vous que la taille des données est correcte pour BGRA
        if len(data) != width * height * 4:
            raise ValueError(f'La taille des données ne correspond pas aux dimensions de l\'image pour le fichier {filename}.')

        # Convertir les données en un tableau numpy pour BGRA
        img_data = np.frombuffer(data, dtype=np.uint8).reshape((height, width, 4))

        # Réorganiser les canaux de BGRA à RGBA
        img_data = img_data[..., [2, 1, 0, 3]]

        # Créer une image à partir des données en utilisant RGBA puis convertir en RGB
        img = Image.fromarray(img_data, 'RGBA').convert('RGB')

        # Sauvegarder l'image en format .jpg avec une qualité améliorée
        img.save(output_jpg_file, quality=95)  # Vous pouvez ajuster cette valeur (0-100)

        print(f'Image sauvegardée sous {output_jpg_file}')

print('Conversion terminée.')
