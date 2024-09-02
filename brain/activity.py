from nilearn import plotting, image

# Gehirnaktivitätsbild laden
fmri_img = image.load_img('sub-10321_T1w.nii')

# Das Bild visualisieren
plotting.plot_stat_map(fmri_img, threshold=3.0, display_mode='ortho', title='fMRI Brain Activity')
plotting.show()




























