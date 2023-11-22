from PIL import Image

# Abre la imagen
imagen = Image.open('report.png')

# Redimensiona la imagen a un nuevo tamaño (ancho, alto)
nueva_imagen = imagen.resize((20, 20))

# Guarda la nueva imagen
nueva_imagen.save('report2.png')
