while True:
    height = input('Height: ')
    if height.isdigit():
        height = int(height)
        if 1 <= height <= 8:
            break

for layer in range(height):
    spaces = (height - layer - 1) * ' '
    blocks = (1 + layer) * '#'
    print(f'{spaces}{blocks}  {blocks}')