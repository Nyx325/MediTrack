from PIL import Image

# Abre la imagen
imagen = Image.open('proveedores_menu.jpg')

# Redimensiona la imagen a un nuevo tamaño (ancho, alto)
nueva_imagen = imagen.resize((80, 80))

# Guarda la nueva imagen
nueva_imagen.save('proveedores_menu2.jpeg')
