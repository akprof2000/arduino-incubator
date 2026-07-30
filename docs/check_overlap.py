# -*- coding: utf-8 -*-
"""Проверка SVG на пересечение текстовых подписей."""
import os, re, glob, html

OUT = os.path.join(os.path.dirname(os.path.abspath(__file__)), 'out')


def text_w(s, size):
    w = 0.0
    for ch in s:
        if ch in 'ilj.,:;| ':
            w += 0.30
        elif ch in 'frt()':
            w += 0.38
        elif ch.isdigit():
            w += 0.55
        elif ch.isupper() or ch in 'мшщжюфыЮ':
            w += 0.72
        else:
            w += 0.56
    return w * size


RE = re.compile(
    r'<text x="([\d.\-]+)" y="([\d.\-]+)" font-size="(\d+)"[^>]*?text-anchor="(\w+)"([^>]*?)>(.*?)</text>')
RE_ROT = re.compile(r'rotate\(([\d.\-]+) ([\d.\-]+) ([\d.\-]+)\)')

problems = 0
for path in sorted(glob.glob(os.path.join(OUT, '*.svg'))):
    src = open(path, encoding='utf-8').read()
    vb = re.search(r'viewBox="0 0 (\d+) (\d+)"', src)
    CW, CH = (float(vb.group(1)), float(vb.group(2))) if vb else (1e9, 1e9)
    boxes = []
    for m in RE.finditer(src):
        x, y, size, anchor, attrs, body = float(m.group(1)), float(m.group(2)), \
            int(m.group(3)), m.group(4), m.group(5), html.unescape(m.group(6))
        if not body.strip():
            continue
        w = text_w(body, size)
        if anchor == 'middle':
            x0 = x - w / 2
        elif anchor == 'end':
            x0 = x - w
        else:
            x0 = x
        # прямоугольник строки: базовая линия y, высота ~ size
        bx0, by0, bx1, by1 = x0, y - size * 0.78, x0 + w, y + size * 0.22

        rot = RE_ROT.search(attrs)
        if rot:
            import math
            ang = math.radians(float(rot.group(1)))
            cx, cy = float(rot.group(2)), float(rot.group(3))
            ca, sa = math.cos(ang), math.sin(ang)
            pts = []
            for px, py in ((bx0, by0), (bx1, by0), (bx1, by1), (bx0, by1)):
                dx, dy = px - cx, py - cy
                pts.append((cx + dx * ca - dy * sa, cy + dx * sa + dy * ca))
            bx0 = min(q[0] for q in pts)
            bx1 = max(q[0] for q in pts)
            by0 = min(q[1] for q in pts)
            by1 = max(q[1] for q in pts)

        boxes.append((bx0, by0, bx1, by1, body))

        # Обрезка краем холста — именно так пропадали первые буквы
        # у подписей полос («поворот» -> «рот»).
        if bx0 < -0.5 or bx1 > CW + 0.5 or by0 < -0.5 or by1 > CH + 0.5:
            print('%-18s ОБРЕЗАНО холстом %.0fx%.0f: %r (x %.0f..%.0f, y %.0f..%.0f)'
                  % (os.path.basename(path), CW, CH, body, bx0, bx1, by0, by1))
            problems += 1

    for i in range(len(boxes)):
        for j in range(i + 1, len(boxes)):
            a, b = boxes[i], boxes[j]
            ox = min(a[2], b[2]) - max(a[0], b[0])
            oy = min(a[3], b[3]) - max(a[1], b[1])
            if ox > 1.5 and oy > 1.5:
                print('%-18s ПЕРЕСЕЧЕНИЕ %.0f×%.0f px: %r  <>  %r'
                      % (os.path.basename(path), ox, oy, a[4], b[4]))
                problems += 1

print('---')
print('найдено пересечений:', problems)
