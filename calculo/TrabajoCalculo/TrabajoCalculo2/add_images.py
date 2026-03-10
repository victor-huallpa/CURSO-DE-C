import os

# Base directory
base_dir = "/var/www/html/C/cursos/calculo/TrabajoCalculo/TrabajoCalculo2"

# Mapping of exercise numbers to folders
# Based on previous reorganization:
# 7-11 -> II
# 12-15 -> III
# 16-28 -> IV
# 29-37 -> V
# 38-44 -> VI
# 45-50 -> VII

folders = {
    "II": range(7, 12),
    "III": range(12, 16),
    "IV": range(16, 29),
    "V": range(29, 38),
    "VI": range(38, 45),
    "VII": range(45, 51)
}

# Template for appending image
image_template = r"""
\begin{center}
    \includegraphics[width=0.5\textwidth]{Graficas/ejer%d.png}
\end{center}
"""

for folder, exercises in folders.items():
    for i in exercises:
        file_path = os.path.join(base_dir, folder, f"{i}vo.tex")
        # Handle special naming for 7-11 if they are 7mo, 8vo, etc.
        # Actually, let's check the file existence first.
        # The user said "7mo.tex", "8vo.tex", etc.
        # Let's try to find the file.
        
        suffixes = ["vo", "mo", "ro", "to", "no"]
        found = False
        for suffix in suffixes:
            temp_path = os.path.join(base_dir, folder, f"{i}{suffix}.tex")
            if os.path.exists(temp_path):
                file_path = temp_path
                found = True
                break
        
        if not found:
            print(f"Warning: File for exercise {i} not found in {folder}")
            continue

        print(f"Updating {file_path}...")
        
        # Check if image exists
        image_path = os.path.join(base_dir, "Graficas", f"ejer{i}.png")
        if not os.path.exists(image_path):
             print(f"Warning: Image for exercise {i} not found at {image_path}")
             # We might still want to add the code if the user plans to add images later, 
             # but the user said "place all images from Graficas", implying they exist.
             # Let's skip if image doesn't exist to avoid broken builds, or add it anyway?
             # User said "coloca tolas las imagenes... que estan como ejer 7 hasta ejer50".
             # So I will assume I should add the code.
        
        with open(file_path, "a") as f:
            f.write(image_template % i)

print("Done.")
