# Ezgi Özkan
# Die heruntergeladene .nii.gz Datei kann mit diesem Code entpackt werden.

import gzip
import shutil

# Pfad zur .nii.gz Datei
gz_file_path = '/Users/ezgiiioe/Desktop/Pythonprojekte/Bioinformatik/Brain/sub-10321_T1w.nii.gz'
# Pfad zur entpackten .nii Datei
nii_file_path = '/Users/ezgiiioe/Desktop/Pythonprojekte/Bioinformatik/Brain/sub-10321_T1w.nii'

# Entpacke die .nii.gz Datei
with gzip.open(gz_file_path, 'rb') as f_in:
    with open(nii_file_path, 'wb') as f_out:
        shutil.copyfileobj(f_in, f_out)

print(f'Datei entpackt: {nii_file_path}')



















