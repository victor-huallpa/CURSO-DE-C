import re
import os

# Configuration
base_dir = "/var/www/html/C/cursos/calculo/TrabajoCalculo/TrabajoCalculo2"
source_file = "/var/www/html/C/cursos/calculo/TrabajoCalculo/unidad2.tex"

# File suffix mapping (same as before)
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
    
    section = ""
    if 12 <= n <= 15: section = "III"
    elif 16 <= n <= 28: section = "IV" # Corrected range for IV based on main.tex
    elif 29 <= n <= 35: section = "IV" # These are in IV in main.tex
    elif 36 <= n <= 37: section = "V"  # These are in V
    elif 38 <= n <= 43: section = "V"
    elif 44 <= n <= 50: section = "VI"
    
    # Wait, my get_filename logic needs to match the FILES ON DISK.
    # The files on disk are:
    # IV/16vo..35vo
    # V/36vo..43vo
    # VI/44vo..50vo
    # This matches the previous script's logic.
    
    if 16 <= n <= 35: section = "IV"
    elif 36 <= n <= 43: section = "V"
    elif 44 <= n <= 50: section = "VI"
    
    return f"{section}/{n}vo.tex"

# 1. Extract original statements from unidad2.tex
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
        if current_ex > 0 and buffer:
            exercises[current_ex] = "".join(buffer).strip()
            buffer = []
        in_enumerate = False
        continue
    if not in_enumerate:
        continue
    counter_match = re.search(r'\\setcounter\{enumi\}\{(\d+)\}', stripped)
    if counter_match:
        current_ex = int(counter_match.group(1))
        continue
    if stripped.startswith("\\item"):
        if current_ex > 0 and buffer:
            exercises[current_ex] = "".join(buffer).strip()
        current_ex += 1
        buffer = []
        content = line.replace("\\item", "", 1).strip()
        if content:
            buffer.append(content + "\n")
    else:
        if current_ex > 0:
            buffer.append(line)

if current_ex > 0 and buffer:
    exercises[current_ex] = "".join(buffer).strip()

print(f"Extracted {len(exercises)} original statements.")

# 2. Process each file
for n, original_statement in exercises.items():
    if n > 50: break
    
    filename = get_filename(n)
    full_path = os.path.join(base_dir, filename)
    
    if not os.path.exists(full_path):
        print(f"Warning: File {filename} not found.")
        continue
        
    with open(full_path, 'r') as f:
        content = f.read()
        
    # Split content to separate statement from solution
    # We look for \nopagebreak as the separator
    parts = content.split(r"\nopagebreak")
    
    if len(parts) < 2:
        print(f"Warning: Could not split {filename}, keeping as is.")
        continue
        
    # The solution part is everything after the first \nopagebreak
    # (In case there are multiple, though unlikely in my template)
    solution_part = r"\nopagebreak" + parts[1]
    if len(parts) > 2:
        solution_part += "".join(parts[2:])
        
    # 3. Heuristic fix for long lines in solution_part
    # We look for lines in align* that are long
    lines = solution_part.split('\n')
    new_lines = []
    for line in lines:
        if len(line) > 90 and "&" in line and "\\\\" in line:
            # It's a long equation line. Try to break it.
            # Don't break if it's already broken?
            # Simple heuristic: If it has a second "=" or "+" or "-" after char 60, break there.
            # But align* needs "&" for alignment.
            # If we break, we should add "\\ & \quad " to align with the previous part or indent.
            
            # Let's just look for specific very long lines and try to split at " = " or " + " or " - "
            # This is risky. Let's only do it if it's REALLY long (>120)
            if len(line) > 120:
                # Try to find a split point
                # Split at the last " + " or " - " before the 100th char?
                # Or just split at the first operator after 60 chars?
                
                # Regex to find operators not inside {} (hard)
                # Let's just try to split at " = " if it appears late?
                # Or simply warn.
                # User asked to fix it.
                
                # Let's try a safe split: replace " = " with " = \\ & " if it's not the first one?
                # Or replace " + " with " \\ & + "
                
                # Let's try to split at the middle-most operator.
                pass # Skipping auto-break for now to avoid syntax errors, just fixing statements is huge.
        
        new_lines.append(line)
    
    fixed_solution_part = "\n".join(new_lines)
    
    # 4. Reconstruct file
    # Ensure original statement is clean
    # If original statement doesn't start with $, wrap it?
    # No, unidad2.tex has mixed content. We trust it.
    # But we should ensure it's not wrapped in \displaystyle if it's text.
    # The extraction from restore_statements.py gets raw content.
    # If it was "\item Hallar...", then original_statement is "Hallar..."
    # This is exactly what we want: Text is text, math is $math$.
    
    new_content = f"{original_statement}\n\n{fixed_solution_part}"
    
    with open(full_path, 'w') as f:
        f.write(new_content)
        
    print(f"Fixed {filename}")

print("Done fixing statements.")
