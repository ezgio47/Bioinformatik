from rdkit import Chem
from rdkit.Chem import AllChem

# Beispiel: Visualisierung von Adrenalin
smiles = "C1=CC(=CC=C1CC(CN)O)O"
mol = Chem.MolFromSmiles(smiles)

# Füge explizite Wasserstoffatome hinzu
mol = Chem.AddHs(mol)

# Setze die 3D-Koordinaten des Moleküls
AllChem.EmbedMolecule(mol)

# Zeichne das Molekül und speichere es als Bild
from rdkit.Chem import Draw
img = Draw.MolToImage(mol)
img.save("molecule.png")













