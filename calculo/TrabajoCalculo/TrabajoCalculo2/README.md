# Trabajo Encargado de Cálculo Integral - 2da Unidad

## 📚 Descripción

Proyecto LaTeX organizado para resolver 50 ejercicios de Cálculo Integral, distribuidos en 7 secciones temáticas.

**Institución:** UNAJ - JULIACA - E.P. INGENIERIA DE SOFTWARE Y SISTEMAS  
**Fecha:** Diciembre 2025

## 👥 Autores

- Carlos Jhampier Apaza Gonzales
- Victor Hugo Huallpa Huahuacondori
- Sayi Xiomara Merma Japura
- George Fermando Aliaga Ramos
- Ruby Nicolt Peralex Apaza
- Anders Litman Barreda Sucapuca

## 📁 Estructura del Proyecto

```
TrabajoCalculo2/
├── main.tex                    # Archivo principal
├── README.md                   # Este archivo
├── I/                          # Sección I: Sumatorias (6 ejercicios)
│   ├── 1er.tex
│   ├── 2do.tex
│   ├── 3ro.tex
│   ├── 4to.tex
│   ├── 5to.tex
│   └── 6to.tex
├── II/                         # Sección II: Áreas con límites de Riemann (5 ejercicios)
│   ├── 7mo.tex
│   ├── 8vo.tex
│   ├── 9no.tex
│   ├── 10mo.tex
│   └── 11vo.tex
├── III/                        # Sección III: Integrales definidas (4 ejercicios)
│   ├── 12vo.tex
│   ├── 13vo.tex
│   ├── 14vo.tex
│   └── 15vo.tex
├── IV/                         # Sección IV: Áreas entre curvas (20 ejercicios)
│   ├── 16vo.tex
│   ├── 17vo.tex
│   ├── ... (18 archivos más)
│   └── 35vo.tex
├── V/                          # Sección V: Volúmenes de revolución (8 ejercicios)
│   ├── 36vo.tex
│   ├── 37vo.tex
│   ├── ... (6 archivos más)
│   └── 43vo.tex
├── VI/                         # Sección VI: Integrales impropias (7 ejercicios)
│   ├── 44vo.tex
│   ├── 45vo.tex
│   ├── ... (5 archivos más)
│   └── 50vo.tex
└── VII/                        # Sección VII: Longitud de curva
    └── (por definir)
```

## 📖 Contenido por Sección

### I. Sumatorias (Ejercicios 1-6)
Hallar fórmulas para sumatorias dadas.

### II. Áreas con Límites de Riemann (Ejercicios 7-11)
Encontrar áreas expresadas como límite de sumas de Riemann con particiones iguales.

### III. Integrales Definidas (Ejercicios 12-15)
Hallar integrales definidas.

### IV. Áreas entre Curvas (Ejercicios 16-35)
Calcular el área de regiones acotadas por curvas dadas.

### V. Volúmenes de Revolución (Ejercicios 36-43)
Encontrar volúmenes generados por rotación de áreas planas alrededor de ejes.

### VI. Integrales Impropias (Ejercicios 44-50)
Calcular integrales impropias y determinar convergencia.

### VII. Longitud de Curva
Hallar longitud de curvas o arcos indicados.

## 🔧 Compilación

### Requisitos
- LaTeX (TeX Live, MiKTeX, o similar)
- Paquetes: `amsmath`, `amssymb`, `enumitem`, `geometry`, `titling`, `graphicx`

### Compilar el Documento

```bash
cd TrabajoCalculo2
pdflatex main.tex
pdflatex main.tex  # Segunda pasada para referencias
```

O usando `latexmk`:

```bash
latexmk -pdf main.tex
```

### Resultado
Se generará el archivo `main.pdf` con todos los ejercicios resueltos.

## ✏️ Formato de Ejercicios

Cada archivo de ejercicio sigue esta plantilla:

```latex
$\displaystyle \mathbf{[ENUNCIADO DEL EJERCICIO]}$

\nopagebreak
\begin{align*}
% Desarrollo paso a paso aquí
\end{align*}

\[
\boxed{\displaystyle 
% Respuesta final
}
\]
```

## 📝 Guía de Uso

1. **Abrir un ejercicio:** Navega al directorio correspondiente y abre el archivo `.tex`
2. **Resolver:** Reemplaza los comentarios con tu desarrollo matemático
3. **Compilar:** Ejecuta `pdflatex main.tex` para ver el resultado
4. **Verificar:** Revisa el PDF generado

## 🎯 Nomenclatura de Archivos

- Ejercicios 1-3: `1er.tex`, `2do.tex`, `3ro.tex`
- Ejercicios 4-10: `4to.tex`, `5to.tex`, `6to.tex`, `7mo.tex`, `8vo.tex`, `9no.tex`, `10mo.tex`
- Ejercicios 11+: `11vo.tex`, `12vo.tex`, ..., `50vo.tex`

## 📊 Progreso

- [ ] Sección I: Sumatorias (0/6)
- [ ] Sección II: Áreas con Riemann (0/5)
- [ ] Sección III: Integrales definidas (0/4)
- [ ] Sección IV: Áreas entre curvas (0/20)
- [ ] Sección V: Volúmenes de revolución (0/8)
- [ ] Sección VI: Integrales impropias (0/7)
- [ ] Sección VII: Longitud de curva (0/?)

**Total:** 0/50 ejercicios completados

## 🚀 Comandos Útiles

```bash
# Ver estructura del proyecto
tree -L 2

# Contar archivos .tex
find . -name "*.tex" | wc -l

# Limpiar archivos auxiliares
rm -f *.aux *.log *.out *.toc *.synctex.gz

# Compilación completa
pdflatex main.tex && pdflatex main.tex && open main.pdf
```

## 📚 Recursos

- [LaTeX Math Symbols](https://www.overleaf.com/learn/latex/List_of_Greek_letters_and_math_symbols)
- [Integral Calculus Reference](https://tutorial.math.lamar.edu/Classes/CalcII/CalcII.aspx)
- [LaTeX Equation Editor](https://latexeditor.lagrida.com/)

## 📄 Licencia

Proyecto académico - UNAJ 2025
