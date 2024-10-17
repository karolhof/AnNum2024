import numpy as np
import plotly.graph_objects as go

# Define la función que quieres integrar
fx = lambda x: 8 + 5 * np.cos(x)

# intervalo de integración
a = 0
b = np.pi
tramos = 10

# Longitud del paso
h = (b-a)/tramos
xi = a
suma = fx(xi)

# Ciclo para aplicar la regla del trapecio
for i in range(1, tramos):  # Cambiado para incluir todos los tramos
    xi = xi + h
    suma += 2 * fx(xi)
suma += fx(b)
area = h * (suma / 2)

# SALIDA
print('Tramos: ', tramos)
print('Integral: ', area)

# GRAFICA
# Puntos de muestra
muestras = tramos + 1
xi = np.linspace(a, b, muestras)
fi = fx(xi)

# Línea suave
muestraslinea = tramos * 10 + 1
xk = np.linspace(a, b, muestraslinea)
fk = fx(xk)

# Graficando con Plotly
fig = go.Figure()

# Línea suave de la función f(x)
fig.add_trace(go.Scatter(x=xk, y=fk, mode='lines', name='f(x)'))

# Muestras de los puntos
fig.add_trace(go.Scatter(x=xi, y=fi, mode='markers+lines', name='muestras', line=dict(color='orange')))

# Relleno para los trapecios
fig.add_trace(go.Scatter(x=xi, y=fi, fill='tozeroy', mode='none', name='trapecios', fillcolor='rgba(0, 255, 0, 0.5)'))

# Añadiendo líneas verticales para los trapecios
for i in range(len(xi)):
    fig.add_shape(type='line', x0=xi[i], y0=0, x1=xi[i], y1=fi[i], line=dict(color='white'))

# Detalles del gráfico
fig.update_layout(title='Integral: Regla de Trapecios',
                  xaxis_title='x',
                  yaxis_title='f(x)',
                  showlegend=True)

# Mostrar el gráfico
fig.show()

# Para la segunda parte del código (integración sobre muestras xi, fi)

def integratrapecio_fi(xi, fi):
    '''Sobre muestras de fi para cada xi
       integral con método de trapecio
    '''
    n = len(xi)
    suma = 0
    for i in range(0, n-1, 1):
        dx = xi[i+1] - xi[i]
        untrapecio = dx * (fi[i+1] + fi[i]) / 2
        suma = suma + untrapecio
    return suma

# PROGRAMA -----------------
# INGRESO
xi = [1., 1.5, 2., 2.5, 3.]
fi = [0.84147098, 1.22167687, 1.28594075, 0.94626755, 0.24442702]

# PROCEDIMIENTO
Area = integratrapecio_fi(xi, fi)

# SALIDA
print('Tramos: ', len(xi)-1)
print('Integral con trapecio: ', Area)
