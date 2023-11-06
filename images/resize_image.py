from PIL import Image

# Abre la imagen
imagen = Image.open('MT2.png')

# Redimensiona la imagen a un nuevo tamaño (ancho, alto)
nueva_imagen = imagen.resize((700, 150))

# Guarda la nueva imagen
nueva_imagen.save('MT2(2).png')
