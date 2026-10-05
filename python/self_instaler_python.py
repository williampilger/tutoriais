# Como criar o executavel:
# pip install tkinter
# pyinstaller --onefile --windowed hello.py

import os
import sys
import shutil
import subprocess
from tkinter import messagebox

destino = os.path.join(os.environ["LOCALAPPDATA"], "HelloWorld.exe")

if sys.executable != destino:
    shutil.copy(sys.executable, destino)
    subprocess.Popen(destino)
else:
    messagebox.showinfo("HelloWorld", "Hello World")
