# PLAN DE DESARROLLO DE LA MONOGRAFÍA

## Proyecto

**Título:**

Aplicación del Principio de Inclusión–Exclusión en Análisis de Cobertura de Prueba

---

# Objetivo del proyecto

Construir una monografía académica rigurosa alineada con los requisitos del docente, con una extensión final aproximada entre **12 y 20 páginas**, integrando:

- fundamentos matemáticos;
- teoría de testing de software;
- modelado formal;
- análisis cuantitativo;
- implementación experimental;
- visualización computacional mediante Python.

---

# Cómo trabajaremos

Existen **dos niveles de trabajo**:

## NIVEL 1 — PLAN DE CONSTRUCCIÓN (interno)

Corresponde al proceso de desarrollo del proyecto.

Aquí definimos:

- qué construiremos primero;
- cómo dividiremos el trabajo;
- qué entregará cada fase.

Las **fases NO son capítulos del documento final**.

Son únicamente **etapas de producción**.

---

## NIVEL 2 — DOCUMENTO FINAL (monografía entregable)

El resultado final seguirá estrictamente la estructura exigida por el docente:

1. Portada
2. Resumen
3. Índice
4. Introducción
5. Marco Teórico
6. Metodología
7. Desarrollo / Implementación
8. Resultados
9. Discusión
10. Conclusiones y Recomendaciones
11. Referencias
12. Anexos

---

# PLAN DE CONSTRUCCIÓN (FASES DE TRABAJO)

---

# FASE 1 — DISEÑO DEL ENFOQUE ACADÉMICO

## Qué estamos construyendo

La base conceptual del proyecto.

Todavía NO se escribe un capítulo completo.

Aquí se toman las decisiones que darán coherencia a toda la monografía.

---

## Objetivo

Definir el alcance real del trabajo.

---

## Construiremos

- delimitación temática;
- pregunta de investigación;
- problema;
- objetivos;
- justificación;
- enfoque metodológico base.

---

## Dónde terminará esto en la monografía

| Elemento producido | Sección final |
|--------------------|---------------|
| Problema | Introducción |
| Objetivos | Introducción |
| Justificación | Introducción |
| Enfoque metodológico | Metodología |
| Delimitación | Base global del documento |

---

## Resultado esperado

Proyecto claramente definido antes de comenzar la redacción formal.

---

# FASE 2 — CONSTRUCCIÓN DEL MARCO TEÓRICO

## Qué estamos construyendo

Ahora sí se redactará un **capítulo real del documento final**.

Capítulo correspondiente:

**5. Marco Teórico**

---

## Objetivo

Construir la base conceptual y académica del trabajo.

---

## Subapartados previstos

### 2.1 Lógica matemática

Contenido:

- proposiciones;
- conectores lógicos;
- inferencia.

---

### 2.2 Teoría de conjuntos

Contenido:

- conjuntos;
- subconjuntos;
- operaciones;
- cardinalidad.

---

### 2.3 Relaciones y combinatoria

Contenido:

- relaciones binarias;
- conteo;
- permutaciones;
- combinaciones.

---

### 2.4 Principio de Inclusión–Exclusión

Contenido:

- formulación;
- interpretación matemática;
- generalización a n conjuntos;
- aplicaciones.

---

### 2.5 Ingeniería de Software y Testing

Contenido:

- pruebas de software;
- verificación;
- validación;
- testing estructural.

---

### 2.6 Cobertura de pruebas

Contenido:

- Statement Coverage;
- Branch Coverage;
- Condition Coverage;
- Path Coverage.

---

### 2.7 Relación matemática–testing

Contenido:

Modelado de cobertura usando teoría de conjuntos.

---

## Resultado esperado

Capítulo teórico sólido de aproximadamente **4–6 páginas**.

---

# FASE 3 — METODOLOGÍA

## Qué estamos construyendo

Capítulo:

**6. Metodología**

---

## Objetivo

Definir cómo se realizará el análisis.

---

## Se desarrollará

- tipo de investigación;
- enfoque teórico–experimental;
- herramientas;
- caso de estudio;
- criterios de evaluación.

---

## Resultado esperado

Capítulo metodológico completo.

---

# FASE 4 — MODELO FORMAL DEL PROBLEMA

## Qué estamos construyendo

Parte del capítulo:

**7. Desarrollo / Implementación**

---

## Objetivo

Formalizar matemáticamente el problema.

---

## Se desarrollará

Universo:

U

Conjuntos:

A → Statement Coverage

B → Branch Coverage

C → Condition Coverage

Aplicación:

|A∪B∪C|

---

## Incluirá

- ecuaciones;
- demostraciones;
- formalización matemática;
- interpretación computacional.

---

## Resultado esperado

Modelo matemático formal del análisis de cobertura.

---

# FASE 5 — IMPLEMENTACIÓN COMPUTACIONAL EN PYTHON

## Qué estamos construyendo

Otra parte del capítulo:

**7. Desarrollo / Implementación**

---

## Objetivo

Construir evidencia experimental reproducible.

---

## Modelo previsto

Mini implementación Python para:

1. generar conjuntos de cobertura;

2. calcular PIE automáticamente;

3. simular superposición de cobertura;

4. calcular cobertura total;

5. producir visualizaciones.

---

## Librerías previstas

- numpy
- matplotlib
- pandas
- matplotlib-venn

---

## Visualizaciones previstas

- diagramas de Venn;
- gráficos comparativos;
- métricas de cobertura.

---

## Resultado esperado

Implementación funcional lista para análisis experimental.

---

# FASE 6 — RESULTADOS

## Qué estamos construyendo

Capítulo:

**8. Resultados**

---

## Objetivo

Presentar resultados obtenidos.

---

## Se incluirá

- tablas;
- gráficas;
- métricas;
- comparación matemática vs implementación.

---

## Resultado esperado

Presentación cuantitativa de resultados.

---

# FASE 7 — DISCUSIÓN

## Qué estamos construyendo

Capítulo:

**9. Discusión**

---

## Objetivo

Interpretar críticamente los resultados.

---

## Se analizará

- utilidad del modelo;
- precisión del PIE;
- ventajas;
- limitaciones;
- comparación con literatura.

---

## Resultado esperado

Análisis académico crítico.

---

# FASE 8 — CONCLUSIONES + CIERRE

## Qué estamos construyendo

Capítulo:

**10. Conclusiones y Recomendaciones**

---

## Objetivo

Cerrar formalmente la investigación.

---

## Se generará

- conclusiones;
- recomendaciones;
- posibles trabajos futuros.

---

## Resultado esperado

Cierre académico coherente.

---

# MAPEO ENTRE FASES Y DOCUMENTO FINAL

| Fase | Produce |
|------|----------|
| Fase 1 | Introducción + Metodología (base conceptual) |
| Fase 2 | Marco Teórico |
| Fase 3 | Metodología |
| Fase 4 | Desarrollo Matemático |
| Fase 5 | Desarrollo Python |
| Fase 6 | Resultados |
| Fase 7 | Discusión |
| Fase 8 | Conclusiones |

---

# ESTIMACIÓN DE PÁGINAS

| Sección | Páginas |
|----------|----------|
| Introducción | 1–2 |
| Marco Teórico | 4–6 |
| Metodología | 1–2 |
| Desarrollo / Implementación | 2–4 |
| Resultados | 1–2 |
| Discusión | 1–2 |
| Conclusiones | 1 |

**TOTAL ESPERADO: 12–20 páginas**

---

# REQUISITOS DE CALIDAD

Todo contenido generado deberá cumplir:

✓ tono académico;

✓ nivel universitario;

✓ rigor matemático;

✓ relevancia para Ingeniería de Software;

✓ integración matemática–testing;

✓ coherencia metodológica;

✓ mínimo 6 fuentes académicas;

✓ compatibilidad con Zotero;

✓ cumplimiento de requisitos del docente.
