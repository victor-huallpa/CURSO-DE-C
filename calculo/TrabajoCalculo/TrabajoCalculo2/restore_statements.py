import re
import os

# Configuration
base_dir = "/var/www/html/C/cursos/calculo/TrabajoCalculo/TrabajoCalculo2"
source_file = "/var/www/html/C/cursos/calculo/TrabajoCalculo/unidad2.tex"

# File suffix mapping
def get_filename(n):
    if n == 1: return "I/1er.tex"
    if n == 2: return "I/2do.tex"
    if n == 3: return "I/3ro.tex"
    if n == 4: return "I/4to.tex"
    if n == 5: return "I/5to.tex"
    if n == 6: return "I/6to.tex"
    if n == 7: return "II/7mo.tex"
    if n == 8: return "II/8vo.tex"
    if n == 9: return "II/9no.tex"
    if n == 10: return "II/10mo.tex"
    if n == 11: return "II/11vo.tex"
    
    # Determine section based on number
    section = ""
    if 12 <= n <= 15: section = "III"
    elif 16 <= n <= 35: section = "IV"
    elif 36 <= n <= 43: section = "V"
    elif 44 <= n <= 50: section = "VI"
    
    return f"{section}/{n}vo.tex"

# Template using placeholder
template = r"""{{STATEMENT}}

\nopagebreak
\begin{align*}
% Desarrollo paso a paso aquí
\end{align*}

\[
\boxed{\displaystyle 
% Respuesta final
}
\]
"""

# Parse unidad2.tex
exercises = {}
current_ex = 0
in_enumerate = False
buffer = []

with open(source_file, 'r') as f:
    lines = f.readlines()

for line in lines:
    stripped = line.strip()
    
    if "\\begin{enumerate}" in stripped:
        in_enumerate = True
        continue
    
    if "\\end{enumerate}" in stripped:
        # Save last exercise if exists
        if current_ex > 0 and buffer:
            exercises[current_ex] = "".join(buffer).strip()
            buffer = []
        in_enumerate = False
        continue
        
    if not in_enumerate:
        continue
        
    # Check for setcounter
    counter_match = re.search(r'\\setcounter\{enumi\}\{(\d+)\}', stripped)
    if counter_match:
        current_ex = int(counter_match.group(1))
        continue
        
    # Check for item
    if stripped.startswith("\\item"):
        # Save previous exercise
        if current_ex > 0 and buffer:
            exercises[current_ex] = "".join(buffer).strip()
        
        current_ex += 1
        buffer = []
        # Remove \item and add rest of line
        content = line.replace("\\item", "", 1).strip()
        if content:
            buffer.append(content + "\n")
    else:
        # Append line to current exercise
        if current_ex > 0:
            buffer.append(line)

# Save the very last one
if current_ex > 0 and buffer:
    exercises[current_ex] = "".join(buffer).strip()

# Write to files
print(f"Found {len(exercises)} exercises.")

for n, content in exercises.items():
    if n > 50: break # Safety
    
    filename = get_filename(n)
    full_path = os.path.join(base_dir, filename)
    
    # Ensure directory exists
    os.makedirs(os.path.dirname(full_path), exist_ok=True)
    
    # Replace placeholder
    file_content = template.replace("{{STATEMENT}}", content)
    
    with open(full_path, 'w') as f:
        f.write(file_content)
    
    print(f"Restored {filename}")

print("Done restoring exercises.")
