import queue
import threading
import pygame as g
import sys

c_w = (255, 255, 255)
c_bl = (0, 0, 0)
c_def = (128, 128, 128)

g.init()
screen = g.display.set_mode((620, 620))  # , g.RESIZABLE)
g.display.set_caption("Title")
clock = g.time.Clock()

frame_q = queue.Queue()


def read_pipe():
    grid = []
    for line in sys.stdin:
        cline = line.strip()
        if cline == "---":
            frame_q.put(grid)
            grid = []
        else:
            grid.append(cline)


threading.Thread(target=read_pipe, daemon=True).start()
cgrid = []
running = True
while running:
    for event in g.event.get():
        if event.type == g.QUIT:
            running = False
        if event.type == g.MOUSEBUTTONDOWN and event.button == 1:
            running = False
    screen.fill(c_def)
    g.draw.rect(screen, c_bl, (10, 10, 600, 600))

    if not frame_q.empty():
        cgrid = frame_q.get()

    if cgrid:
        for y, row in enumerate(cgrid):
            for x, cell in enumerate(row):
                if cell == "1":
                    g.draw.rect(screen, c_w, (x * 12 + 10, y * 12 + 10, 10, 10))
                else:
                    g.draw.rect(screen, c_bl, (x * 12 + 10, y * 12 + 10, 10, 10))

    g.display.flip()
    clock.tick(5)

g.quit()
