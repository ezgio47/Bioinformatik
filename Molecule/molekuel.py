from rdkit import Chem

# Beispiel: Visualisierung von Adrenalin
smiles = "C1=CC(=CC=C1CC(CN)O)O"
mol = Chem.MolFromSmiles(smiles)
mol = Chem.AddHs(mol)

# Setze die 3D-Koordinaten des Moleküls
from rdkit.Chem import AllChem
AllChem.EmbedMolecule(mol)

# Exportiere das Molekül als PDB-Datei
with open("molecule.pdb", "w") as f:
    f.write(Chem.MolToPDBBlock(mol))













