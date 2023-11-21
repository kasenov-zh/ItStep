import tkinter as tk
from tkinter import filedialog
import time

print( time.time() )

print( time.asctime() )
print( time.strftime('%d.%m.%Y  %H:%M:%S') )


def open_file():
    file_name = entry.get()
    try:
        with open(file_name, 'r') as file:
            text.delete(1.0, tk.END)  # Очищаем поле Text
            text.insert(tk.END, file.read())  # Загружаем содержимое файла в поле Text
    except FileNotFoundError:
        text.delete(1.0, tk.END)
        text.insert(tk.END, "Файл не найден")

def save_file():
    file_name = entry.get()
    with open(file_name, 'w') as file:
        file.write(text.get(1.0, tk.END))

# Создаем главное окно
root = tk.Tk()
root.title("Редактор файлов")

# Создаем виджеты
entry = tk.Entry(root)
text = tk.Text(root)
open_button = tk.Button(root, text="Открыть", command=open_file)
save_button = tk.Button(root, text="Сохранить", command=save_file)

# Размещаем виджеты на окне
entry.pack()
text.pack()
open_button.pack()
save_button.pack()

# Запускаем основной цикл
root.mainloop()
