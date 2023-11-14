import re

def minify_html(file_path):
    with open(file_path, 'r') as file:
        content = file.read()

    # Elimina comentarios HTML
    content = re.sub(r'<!--.*?-->', '', content, flags=re.DOTALL)

    # Elimina espacios en blanco y saltos de línea
    content = re.sub(r'\s+', ' ', content)

    # Escapa comillas simples y dobles, así como barras invertidas
    content = content.replace('\\', '\\\\').replace('"', '\\"').replace("'", "\\'")

    return content

file_path = './index.html'
minified_code = minify_html(file_path)

output_file_path = './salida.txt'
with open(output_file_path, 'w') as output_file:
    output_file.write('String htmlCode = "' + minified_code + '";')

print(f'Se ha creado el archivo de salida en: {output_file_path}')
