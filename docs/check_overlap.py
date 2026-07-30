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
    r'<text x="([\d.\-]+)" y="([\d.\-]+)" font-size="(\d+)"[^>]*?text-anchor="(\w+)"[^>]*?>(.*?)</text>')

problems = 0
for path in sorted(glob.glob(os.path.join(OUT, '*.svg'))):
    boxes = []
    for m in RE.finditer(open(path, encoding='utf-8').read()):
        x, y, size, anchor, body = float(m.group(1)), float(m.group(2)), int(m.group(3)), \
            m.group(4), html.unescape(m.group(5))
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
        boxes.append((x0, y - size * 0.78, x0 + w, y + size * 0.22, body))

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
