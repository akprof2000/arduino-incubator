# -*- coding: utf-8 -*-
"""Генерация SVG-иллюстраций для README (без внешних зависимостей)."""
import os

OUT = os.path.join(os.path.dirname(os.path.abspath(__file__)), 'out')
os.makedirs(OUT, exist_ok=True)

# Цвета, читаемые и в светлой, и в тёмной теме GitHub
FG = '#57606a'
GRID = '#d0d7de'
C_TEMP = '#d1242f'
C_HUM = '#0969da'
C_ROT = '#8250df'
C_VENT = '#1a7f37'
C_ACC = '#bf8700'

FONT = 'font-family="Segoe UI, Helvetica, Arial, sans-serif"'

# Заводские таблицы (совпадают с Incubation/storage.cpp)
BIRDS = ['Куры', 'Индейка', 'Утки', 'Индоутки', 'Гуси', 'Перепела']
# day, temp(x10-300), hum(-45), rot, vent, venttime
FACTORY = [
    [(11, 79, 21, 4, 0, 0), (6, 73, 8, 4, 4, 5), (2, 73, 2, 4, 4, 20), (2, 79, 21, 0, 4, 5)],
    [(8, 80, 25, 4, 0, 0), (4, 75, 15, 4, 2, 5), (10, 72, 11, 4, 4, 20), (3, 70, 25, 0, 2, 10)],
    [(16, 80, 15, 4, 2, 5), (10, 75, 7, 4, 4, 20), (2, 72, 25, 0, 2, 10), (2, 70, 25, 0, 0, 0)],
    [(3, 78, 10, 4, 0, 0), (8, 75, 7, 4, 2, 5), (10, 72, 7, 4, 6, 20), (2, 70, 25, 0, 2, 10)],
    [(6, 78, 10, 4, 0, 0), (8, 75, 7, 4, 2, 5), (13, 72, 7, 4, 4, 20), (2, 70, 25, 0, 2, 10)],
    [(12, 76, 13, 4, 2, 5), (4, 73, 8, 4, 2, 20), (2, 72, 2, 0, 0, 0), (2, 70, 21, 0, 0, 0)],
]
BASETEMP, BASEHUM = 30, 45


def plural_days(n):
    if n % 10 == 1 and n % 100 != 11:
        return '%d день' % n
    if n % 10 in (2, 3, 4) and n % 100 not in (12, 13, 14):
        return '%d дня' % n
    return '%d дней' % n


def svg(w, h, body, title):
    return (
        '<svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 %d %d" width="%d" height="%d" '
        'role="img" aria-label="%s">\n'
        '<style>text{%s}</style>\n%s</svg>\n' % (w, h, w, h, title, 'fill:' + FG, body)
    )


def txt(x, y, s, size=12, color=FG, anchor='start', weight='normal'):
    return ('<text x="%.1f" y="%.1f" font-size="%d" fill="%s" text-anchor="%s" '
            'font-weight="%s" %s>%s</text>\n' % (x, y, size, color, anchor, weight, FONT, s))


def line(x1, y1, x2, y2, color=GRID, w=1, dash=None):
    d = ' stroke-dasharray="%s"' % dash if dash else ''
    return '<line x1="%.1f" y1="%.1f" x2="%.1f" y2="%.1f" stroke="%s" stroke-width="%s"%s/>\n' % (
        x1, y1, x2, y2, color, w, d)


def rect(x, y, w, h, fill, opacity=1.0, rx=2, stroke='none'):
    return ('<rect x="%.1f" y="%.1f" width="%.1f" height="%.1f" rx="%d" fill="%s" '
            'fill-opacity="%.2f" stroke="%s"/>\n' % (x, y, w, h, rx, fill, opacity, stroke))


# ---------------------------------------------------------------------------
# 1. График режима инкубации по дням
# ---------------------------------------------------------------------------
def schedule_chart(index, filename):
    rows = FACTORY[index]
    days = sum(r[0] for r in rows)
    W, H = 760, 340
    L, R, T, B = 55, 55, 46, 76
    pw, ph = W - L - R, H - T - B

    tmin, tmax = 36.5, 38.5
    hmin, hmax = 40, 80

    def xd(d):
        return L + pw * d / days

    def yt(t):
        return T + ph * (tmax - t) / (tmax - tmin)

    def yh(h):
        return T + ph * (hmax - h) / (hmax - hmin)

    b = []
    b.append(txt(L, 24, 'Режим инкубации: %s (%s)' % (BIRDS[index], plural_days(days)),
                 15, FG, 'start', '600'))

    # фон периодов
    d0 = 0
    for i, r in enumerate(rows):
        shade = 0.05 if i % 2 == 0 else 0.10
        b.append(rect(xd(d0), T, xd(d0 + r[0]) - xd(d0), ph, FG, shade, 0))
        b.append(txt((xd(d0) + xd(d0 + r[0])) / 2, T - 8, 'Период %d' % (i + 1), 11, FG, 'middle'))
        d0 += r[0]

    # сетка и оси
    for t in [36.5, 37.0, 37.5, 38.0, 38.5]:
        b.append(line(L, yt(t), L + pw, yt(t), GRID))
        b.append(txt(L - 8, yt(t) + 4, '%.1f' % t, 10, C_TEMP, 'end'))
    for h in [40, 50, 60, 70, 80]:
        b.append(txt(L + pw + 8, yh(h) + 4, '%d' % h, 10, C_HUM, 'start'))

    b.append(txt(14, T - 14, '°C', 11, C_TEMP, 'start', '600'))
    b.append(txt(W - 34, T - 14, '%', 11, C_HUM, 'start', '600'))

    # ступенчатые линии
    for color, idx, conv, ymap in ((C_TEMP, 1, lambda v: v / 10.0 + BASETEMP, yt),
                                   (C_HUM, 2, lambda v: v + BASEHUM, yh)):
        pts, d0 = [], 0
        for r in rows:
            v = ymap(conv(r[idx]))
            pts.append((xd(d0), v))
            pts.append((xd(d0 + r[0]), v))
            d0 += r[0]
        path = 'M' + ' L'.join('%.1f %.1f' % p for p in pts)
        b.append('<path d="%s" fill="none" stroke="%s" stroke-width="2.5" '
                 'stroke-linejoin="round"/>\n' % (path, color))

    # ось дней
    b.append(line(L, T + ph, L + pw, T + ph, FG, 1.2))
    d0 = 0
    for r in rows:
        b.append(line(xd(d0), T + ph, xd(d0), T + ph + 5, FG))
        b.append(txt(xd(d0), T + ph + 18, str(d0 + 1), 10, FG, 'middle'))
        d0 += r[0]
    b.append(txt(xd(days), T + ph + 18, str(days), 10, FG, 'middle'))
    b.append(txt(L + pw / 2, T + ph + 36, 'день цикла', 11, FG, 'middle'))

    # полоса операций
    yb = H - 26
    d0 = 0
    for r in rows:
        x0, x1 = xd(d0), xd(d0 + r[0])
        parts = []
        if r[3]:
            parts.append(('поворот %d/сут' % r[3], C_ROT))
        if r[4]:
            parts.append(('провет. %dx%dм' % (r[4], r[5]), C_VENT))
        label = ', '.join(p[0] for p in parts) if parts else '—'
        color = parts[0][1] if parts else FG
        b.append(rect(x0 + 1, yb - 11, x1 - x0 - 2, 17, color, 0.14, 3))
        b.append(txt((x0 + x1) / 2, yb + 1, label, 9, color, 'middle'))
        d0 += r[0]

    # легенда
    lx = L + pw - 190
    b.append(line(lx, 20, lx + 18, 20, C_TEMP, 2.5))
    b.append(txt(lx + 24, 24, 'температура', 10, C_TEMP))
    b.append(line(lx + 110, 20, lx + 128, 20, C_HUM, 2.5))
    b.append(txt(lx + 134, 24, 'влажность', 10, C_HUM))

    open(os.path.join(OUT, filename), 'w', encoding='utf-8').write(
        svg(W, H, ''.join(b), 'График режима инкубации: ' + BIRDS[index]))


# ---------------------------------------------------------------------------
# 2. Закон регулирования
# ---------------------------------------------------------------------------
def regulator_chart():
    W, H = 720, 330
    L, R, T, B = 60, 30, 50, 60
    pw, ph = W - L - R, H - T - B
    dmax, dmin_pct = 2.0, 15

    def x(d):
        return L + pw * d / dmax

    def y(p):
        return T + ph * (100 - p) / 100.0

    b = [txt(L, 24, 'Закон регулирования: мощность = (отклонение / порог)² × 100 %', 15, FG,
             'start', '600')]

    for p in range(0, 101, 20):
        b.append(line(L, y(p), L + pw, y(p), GRID))
        b.append(txt(L - 8, y(p) + 4, '%d' % p, 10, FG, 'end'))
    b.append(txt(L - 40, T - 16, 'мощность, %', 11, FG, 'start', '600'))

    # зона нечувствительности
    b.append(rect(x(0), T, x(0.1) - x(0), ph, FG, 0.10, 0))
    b.append(txt(x(0.1) + 6, T + 16, 'зона нечувствительности (порог alTmpDel)', 10, FG))

    # минимальный процент
    b.append(line(L, y(dmin_pct), L + pw, y(dmin_pct), C_ACC, 1.5, '4 3'))
    b.append(txt(L + pw - 4, y(dmin_pct) - 6, 'minheat = %d %% — ниже не опускаемся' % dmin_pct,
                 10, C_ACC, 'end'))

    pts = []
    for i in range(0, 101):
        d = dmax * i / 100.0
        p = min(100.0, (d / dmax) ** 2 * 100.0)
        if d > 0.1:
            p = max(p, dmin_pct)
        else:
            p = 0
        pts.append((x(d), y(p)))
    b.append('<path d="M%s" fill="none" stroke="%s" stroke-width="2.5"/>\n'
             % (' L'.join('%.1f %.1f' % p for p in pts), C_TEMP))

    b.append(line(L, T + ph, L + pw, T + ph, FG, 1.2))
    for d in [0, 0.5, 1.0, 1.5, 2.0]:
        b.append(line(x(d), T + ph, x(d), T + ph + 5, FG))
        b.append(txt(x(d), T + ph + 18, '%.1f' % d, 10, FG, 'middle'))
    b.append(txt(L + pw / 2, T + ph + 38,
                 'отклонение от уставки, °C  (при alTmpMax = 2 °C — 100 %)', 11, FG, 'middle'))

    open(os.path.join(OUT, 'regulator.svg'), 'w', encoding='utf-8').write(
        svg(W, H, ''.join(b), 'Квадратичный закон регулирования'))


# ---------------------------------------------------------------------------
# 3. Диаграмма «медленного» ШИМ
# ---------------------------------------------------------------------------
def softpwm_chart():
    W, H = 720, 300
    L, T = 70, 56
    pw = W - L - 30
    b = [txt(L - 56, 24, '«Медленный» ШИМ вентилятора и испарителя (период задаётся PEEKVALUE)',
             15, FG, 'start', '600')]

    rows = [(200, 78), (155, 60), (100, 39)]
    for i, (val, pct) in enumerate(rows):
        y = T + i * 74
        delta = (255.0 - val) * 5000 / 100.0  # мс паузы
        on_ms, off_ms = 5000.0, delta
        total = on_ms + off_ms
        b.append(txt(L - 60, y + 6, 'val=%d' % val, 11, FG, 'start', '600'))
        b.append(txt(L - 60, y + 22, '%d %%' % pct, 10, FG))
        b.append(line(L, y + 30, L + pw, y + 30, GRID))

        x = L
        cycle_w = pw / 2.4
        while x < L + pw - 2:
            won = cycle_w * on_ms / total
            woff = cycle_w * off_ms / total
            b.append(rect(x, y - 8, min(won, L + pw - x), 38, C_VENT, 0.75, 2))
            x += won + woff
        b.append(txt(L + 6, y - 14, 'вкл %0.1f с / выкл %0.1f с' % (on_ms / 1000, off_ms / 1000),
                     10, C_VENT))

    b.append(txt(L, H - 16,
                 'Обычный analogWrite на такой нагрузке даёт гудение и не создаёт тяги '
                 'на малых значениях.', 11, FG))
    open(os.path.join(OUT, 'softpwm.svg'), 'w', encoding='utf-8').write(
        svg(W, H, ''.join(b), 'Диаграмма медленного ШИМ'))


# ---------------------------------------------------------------------------
# 4. Память: до и после
# ---------------------------------------------------------------------------
def memory_chart():
    W, H = 720, 300
    b = [txt(30, 26, 'Расход памяти ATmega2560: до и после рефакторинга', 15, FG, 'start', '600')]

    groups = [
        ('FLASH (из 253 952 Б)', 55074, 39912, 253952, 30),
        ('SRAM (из 8 192 Б)', 3736, 1793, 8192, 165),
    ]
    L, barw, maxw = 210, 26, 420
    for title, before, after, total, y0 in groups:
        b.append(txt(30, y0 + 24, title, 12, FG, 'start', '600'))
        for j, (label, val, color) in enumerate((('было', before, FG), ('стало', after, C_VENT))):
            y = y0 + 44 + j * 40
            w = maxw * val / total
            b.append(txt(L - 12, y + 18, label, 11, FG, 'end'))
            b.append(rect(L, y, maxw, barw, FG, 0.08, 3))
            b.append(rect(L, y, w, barw, color, 0.85 if j else 0.45, 3))
            b.append(txt(L + w + 8, y + 18, '%s Б (%d %%)' % ('{:,}'.format(val).replace(',', ' '),
                                                              round(100.0 * val / total)), 11, FG))
        saved = round(100.0 * (before - after) / before)
        b.append(txt(30, y0 + 74, '−%d %%' % saved, 15, C_VENT, 'start', '700'))

    b.append(txt(30, H - 18,
                 'Освободилось 1 943 Б SRAM — это 24 % всей оперативной памяти контроллера.',
                 11, FG))
    open(os.path.join(OUT, 'memory.svg'), 'w', encoding='utf-8').write(
        svg(W, H, ''.join(b), 'Сравнение расхода памяти'))


# ---------------------------------------------------------------------------
# 5. Распиновка
# ---------------------------------------------------------------------------
def pinout_chart():
    W, H = 760, 470
    b = [txt(30, 26, 'Подключение периферии к Arduino Mega 2560', 15, FG, 'start', '600')]

    bx, by, bw, bh = 300, 60, 160, 370
    b.append(rect(bx, by, bw, bh, '#1a7f37', 0.10, 8, '#1a7f37'))
    b.append(txt(bx + bw / 2, by + 26, 'ATmega2560', 13, FG, 'middle', '700'))
    b.append(txt(bx + bw / 2, by + 44, 'Arduino Mega', 11, FG, 'middle'))

    left = [
        ('A15', 'Кнопка «OK»', C_ACC), ('A13', 'Кнопка «вверх»', C_ACC),
        ('A12', 'Кнопка «вниз»', C_ACC), ('A14', 'Кнопка «назад»', C_ACC),
        ('A10', 'Концевик двери', C_ROT), ('A11', 'Концевик центра лотка', C_ROT),
        ('19', 'DS18B20 (1-Wire)', C_TEMP), ('SDA/SCL', 'HTU21D + DS1307 (I²C)', C_TEMP),
    ]
    right = [
        ('2', 'ТЭН нагрева (ШИМ)', C_TEMP), ('3', 'Вентилятор обдува', C_VENT),
        ('4', 'Испаритель', C_HUM), ('5', 'Светодиод аварии', '#d1242f'),
        ('6', 'Звук аварии', '#d1242f'), ('17', 'Лоток: влево', C_ROT),
        ('18', 'Лоток: вправо', C_ROT), ('7 / A1', 'LCD: яркость / контраст', FG),
        ('13,12,11,10,9,8', 'LCD 16x2 (RS,E,D4-D7)', FG),
    ]

    for i, (pin, label, color) in enumerate(left):
        y = by + 66 + i * 38
        b.append(line(bx - 46, y, bx, y, color, 1.6))
        b.append('<circle cx="%d" cy="%.1f" r="3.5" fill="%s"/>\n' % (bx, y, color))
        b.append(txt(bx - 52, y - 4, pin, 11, color, 'end', '700'))
        b.append(txt(bx - 52, y + 11, label, 10, FG, 'end'))

    for i, (pin, label, color) in enumerate(right):
        y = by + 46 + i * 38
        b.append(line(bx + bw, y, bx + bw + 46, y, color, 1.6))
        b.append('<circle cx="%d" cy="%.1f" r="3.5" fill="%s"/>\n' % (bx + bw, y, color))
        b.append(txt(bx + bw + 52, y - 4, pin, 11, color, 'start', '700'))
        b.append(txt(bx + bw + 52, y + 11, label, 10, FG, 'start'))

    open(os.path.join(OUT, 'pinout.svg'), 'w', encoding='utf-8').write(
        svg(W, H, ''.join(b), 'Распиновка контроллера'))


# ---------------------------------------------------------------------------
# 6. Сравнение всех схем
# ---------------------------------------------------------------------------
def overview_chart():
    W, H = 760, 400
    L, T = 120, 70
    pw = W - L - 40
    maxdays = max(sum(r[0] for r in rows) for rows in FACTORY)
    b = [txt(30, 26, 'Длительность и температурный профиль всех шести схем', 15, FG, 'start', '600'),
         txt(30, 46, 'Ширина блока — длительность периода в днях, цвет — уставка температуры',
             11, FG)]

    for i, rows in enumerate(FACTORY):
        y = T + i * 50
        total = sum(r[0] for r in rows)
        b.append(txt(L - 12, y + 20, BIRDS[i], 12, FG, 'end', '600'))
        x = L
        for r in rows:
            w = pw * r[0] / maxdays
            t = r[1] / 10.0 + BASETEMP
            # 37.0 -> светлее, 38.0 -> насыщеннее
            op = 0.25 + 0.65 * max(0.0, min(1.0, (t - 37.0) / 1.0))
            b.append(rect(x + 1, y, w - 2, 30, C_TEMP, op, 3))
            if w > 44:
                b.append(txt(x + w / 2, y + 13, '%.1f°' % t, 10, '#ffffff', 'middle', '700'))
                b.append(txt(x + w / 2, y + 25, '%d%%' % (r[2] + BASEHUM), 9, '#ffffff', 'middle'))
            x += w
        b.append(txt(x + 8, y + 20, '%d дн.' % total, 11, FG, 'start', '600'))
        b.append(txt(x + 8, y + 32, '%d пер.' % len(rows), 9, FG, 'start'))

    open(os.path.join(OUT, 'schemes.svg'), 'w', encoding='utf-8').write(
        svg(W, H, ''.join(b), 'Сравнение схем инкубации'))


for i in range(6):
    schedule_chart(i, 'schedule-%d.svg' % i)
regulator_chart()
softpwm_chart()
memory_chart()
pinout_chart()
overview_chart()
print('готово:', sorted(os.listdir(OUT)))
