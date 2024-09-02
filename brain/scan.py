# Ezgi Özkan 

# Visiualisierung von Gehirnscans.
# Analyse von medizinischen Bilddaten.

import nibabel as nib
import matplotlib.pyplot as plt
import numpy as np

# Pfad zur entpackten .nii-Datei
file_path = '/Users/ezgiiioe/Desktop/Pythonprojekte/Bioinformatik/Brain/sub-10321_T1w.nii'

# Überprüfe, ob die Datei existiert
import os
if not os.path.isfile(file_path):
    print(f"Die Datei '{file_path}' wurde nicht gefunden. Bitte überprüfe den Pfad.")
else:
    try:
        # Lade das Gehirn-MRT-Bild
        img = nib.load(file_path)
        data = img.get_fdata()

        # Wähle eine Schicht zur Visualisierung
        slice_index = data.shape[2] // 2
        slice_data = data[:, :, slice_index]

        # Visualisiere die Schicht
        plt.figure(figsize=(8, 8))
        plt.imshow(slice_data.T, cmap='gray', origin='lower')
        plt.colorbar(label='Intensity')
        plt.title('MRT Brain Scan Slice')
        plt.xlabel('X axis')
        plt.ylabel('Y axis')
        plt.show()

    except Exception as e:
        print(f"Ein Fehler ist aufgetreten: {e}")























