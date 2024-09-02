from nilearn import plotting
from nilearn.image import load_img

# Lade die entpackte .nii-Datei
file_path = '/Users/ezgiiioe/Desktop/Pythonprojekte/Bioinformatik/Brain/sub-10321_T1w.nii'
img = load_img(file_path)

# Erzeuge eine 3D-Darstellung des Gehirns
plotting.plot_glass_brain(img, display_mode='ortho', colorbar=True, threshold=0.2)
plotting.show()




















