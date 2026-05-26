# ============================
# MODELO DE COBERTURA DE PRUEBAS
# Inclusión–Exclusión
# ============================

# Conjuntos simulados de casos de prueba
A = set(range(1, 41))    # Statement Coverage
B = set(range(20, 61))   # Branch Coverage
C = set(range(50, 81))   # Condition Coverage

# ============================
# OPERACIONES DE CONJUNTOS
# ============================

union = A | B | C

AB = A & B
AC = A & C
BC = B & C
ABC = A & B & C

# ============================
# PRINCIPIO DE INCLUSIÓN–EXCLUSIÓN
# ============================


pie = (
    len(A) + len(B) + len(C)
    - len(AB) - len(AC) - len(BC)
    + len(ABC)
)

# ============================
# MÉTRICAS
# ============================

suma_directa = len(A) + len(B) + len(C)
union_real = len(union)

redundancia = suma_directa - union_real
porcentaje_redundancia = (redundancia / suma_directa) * 100

# ============================
# RESULTADOS
# ============================

print("RESULTADOS DEL MODELO")
print("----------------------")

print(f"Tamaño A: {len(A)}")
print(f"Tamaño B: {len(B)}")
print(f"Tamaño C: {len(C)}")

print("\nINTERSECCIONES")
print(f"A ∩ B: {len(AB)}")
print(f"A ∩ C: {len(AC)}")
print(f"B ∩ C: {len(BC)}")
print(f"A ∩ B ∩ C: {len(ABC)}")

print("\nCÁLCULOS")
print(f"Suma directa: {suma_directa}")
print(f"Unión real: {union_real}")
print(f"Inclusión–Exclusión: {pie}")

print("\nREDUNDANCIA")
print(f"Casos duplicados: {redundancia}")
print(f"Porcentaje de redundancia: {porcentaje_redundancia:.2f}%")