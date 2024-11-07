# Alternar entre as áreas de trabalho usando Scroll do mouse

Scripts para automatizar a troca de área de trabalho usando apenas o scroll do mouse.
Desenvolvido usando ajuda do `ChatGPT 4o - 11/2024`.

## Alternativa 1 - Python [pyautogui & pynput]

Instale as dependências (além do próprio Python)

> pip install pyautogui pynput pywin32

*TaskbarScrollDesktopSwitch.pyw*
```py
import pyautogui
from pynput import mouse
import win32gui

def is_cursor_on_taskbar():
    # Obtém a posição atual do cursor
    x, y = pyautogui.position()
    window = win32gui.WindowFromPoint((x, y))
    window_class = win32gui.GetClassName(window)
    return window_class == "Shell_TrayWnd"

def on_scroll(x, y, dx, dy):
    if is_cursor_on_taskbar():
        if dy > 0:  # Scroll up
            pyautogui.hotkey('ctrl', 'win', 'left')
        elif dy < 0:  # Scroll down
            pyautogui.hotkey('ctrl', 'win', 'right')

# Listener de rolagem do mouse
with mouse.Listener(on_scroll=on_scroll) as listener:
    listener.join()
```

## Alternativa 2 - AutoHotKey

O Script abaixo usa o [AutoHotKey](https://www.autohotkey.com/) para ser executado.

*TaskbarScrollDesktopSwitch.ahk*
```txt
#Persistent
CoordMode, Mouse, Screen

; Captura o scroll apenas quando o cursor estiver sobre a barra de tarefas
WheelUp::
    MouseGetPos, , , WindowUnderCursor
    WinGetClass, WindowClass, ahk_id %WindowUnderCursor%
    if (WindowClass = "Shell_TrayWnd")
    {
        Send, {Ctrl down}{LWin down}{Left}{LWin up}{Ctrl up} ; Muda para a área de trabalho anterior
        return
    }
    ; Permite que o scroll funcione normalmente em outras áreas
    Send, {WheelUp}
    return

WheelDown::
    MouseGetPos, , , WindowUnderCursor
    WinGetClass, WindowClass, ahk_id %WindowUnderCursor%
    if (WindowClass = "Shell_TrayWnd")
    {
        Send, {Ctrl down}{LWin down}{Right}{LWin up}{Ctrl up} ; Muda para a próxima área de trabalho
        return
    }
    ; Permite que o scroll funcione normalmente em outras áreas
    Send, {WheelDown}
    return
```

