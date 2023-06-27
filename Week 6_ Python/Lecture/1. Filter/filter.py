from PIL import Image, ImageFilter

# Opens bridge.bmp and sets to before (object variable)
before = Image.open("courtyard.bmp")

# Sets after to a filtered image of before
blur = before.filter(ImageFilter.BoxBlur(1))
edge = before.filter(ImageFilter.FIND_EDGES)

# Saves after as out.bmp
blur.save("out1.bmp")
edge.save("out2.bmp")