# -*- coding: utf-8 -*-
"""Схема подключения периферии с рисунками элементов."""
import os

OUT = os.path.join(os.path.dirname(os.path.abspath(__file__)), 'out')
os.makedirs(OUT, exist_ok=True)

FG = '#3d444d'
MUTED = '#8b949e'
BOARD = '#0f8a8a'
W_SIG = '#8250df'   # сигнальные
W_PWR = '#d1242f'   # силовые
W_I2C = '#0969da'   # I2C
W_1W = '#bf8700'    # 1-Wire
W_MOT = '#1a7f37'   # моторы/реле
F = 'font-family="Segoe UI, Helvetica, Arial, sans-serif"'

P = []


def add(s):
    P.append(s)


def txt(x, y, s, size=11, color=FG, anchor='start', weight='normal', opacity=1.0):
    add('<text x="%.1f" y="%.1f" font-size="%s" fill="%s" text-anchor="%s" font-weight="%s" '
        'fill-opacity="%.2f" %s>%s</text>' % (x, y, size, color, anchor, weight, opacity, F, s))


def rect(x, y, w, h, fill, rx=4, stroke='none', sw=1, op=1.0):
    add('<rect x="%.1f" y="%.1f" width="%.1f" height="%.1f" rx="%d" fill="%s" fill-opacity="%.2f" '
        'stroke="%s" stroke-width="%s"/>' % (x, y, w, h, rx, fill, op, stroke, sw))


def circle(cx, cy, r, fill, stroke='none', sw=1, op=1.0):
    add('<circle cx="%.1f" cy="%.1f" r="%.1f" fill="%s" fill-opacity="%.2f" stroke="%s" '
        'stroke-width="%s"/>' % (cx, cy, r, fill, op, stroke, sw))


def wire(pts, color, w=2.2, dash=None):
    d = ' stroke-dasharray="%s"' % dash if dash else ''
    path = 'M' + ' L'.join('%.1f %.1f' % p for p in pts)
    add('<path d="%s" fill="none" stroke="%s" stroke-width="%s" stroke-linecap="round" '
        'stroke-linejoin="round"%s/>' % (path, color, w, d))
    add('<circle cx="%.1f" cy="%.1f" r="3" fill="%s"/>' % (pts[0][0], pts[0][1], color))
    add('<circle cx="%.1f" cy="%.1f" r="3" fill="%s"/>' % (pts[-1][0], pts[-1][1], color))


# ---------------------------------------------------------------------------
# Рисунки элементов
# ---------------------------------------------------------------------------
def draw_lcd(x, y):
    """Дисплей 16x2."""
    rect(x, y, 150, 76, '#0d4d4d', 6, '#0a3a3a', 1.5)
    rect(x + 8, y + 10, 134, 46, '#1f9e6b', 3)
    for r in range(2):
        for c in range(16):
            rect(x + 11 + c * 8.2, y + 14 + r * 22, 6.4, 17, '#0d4d3a', 1, 'none', 1, 0.55)
    txt(x + 15, y + 27, 'Т у.:37.9', 9, '#eafff5')
    txt(x + 15, y + 49, 'В у.:66  65', 9, '#eafff5')
    for i in range(8):
        rect(x + 12 + i * 17, y + 60, 8, 5, '#c0c8d0', 1)
    txt(x + 75, y + 92, 'LCD 16×2 HD44780', 10, FG, 'middle', '600')
    txt(x + 75, y + 105, '4-битная шина + яркость/контраст', 9, MUTED, 'middle')


def draw_htu(x, y):
    """Датчик HTU21D."""
    rect(x, y, 74, 50, '#1b4b8f', 5, '#12356a', 1.5)
    rect(x + 22, y + 12, 30, 22, '#dfe6ee', 3)
    for i in range(5):
        circle(x + 28 + i * 4.6, y + 23, 1.6, '#8b949e')
    for i in range(4):
        rect(x + 6 + i * 16, y + 44, 9, 10, '#d4af37', 1)
    txt(x + 37, y + 74, 'HTU21D', 10, FG, 'middle', '600')
    txt(x + 37, y + 87, 'влажность + T воздуха', 9, MUTED, 'middle')


def draw_rtc(x, y):
    """Модуль часов DS1307."""
    rect(x, y, 74, 50, '#1b4b8f', 5, '#12356a', 1.5)
    rect(x + 6, y + 10, 26, 18, '#22272e', 2)
    txt(x + 19, y + 22, 'DS', 8, '#c9d1d9', 'middle')
    circle(x + 52, y + 22, 13, '#c0c8d0', '#98a2ad', 1.2)
    txt(x + 52, y + 26, 'CR', 8, '#3d444d', 'middle')
    for i in range(4):
        rect(x + 6 + i * 16, y + 44, 9, 10, '#d4af37', 1)
    txt(x + 37, y + 74, 'DS1307', 10, FG, 'middle', '600')
    txt(x + 37, y + 87, 'часы + батарейка', 9, MUTED, 'middle')


def draw_ds18b20(x, y, label, sub):
    """Датчик DS18B20 в гильзе."""
    rect(x + 4, y, 22, 40, '#b8bfc7', 4, '#98a2ad', 1.2)
    rect(x + 4, y, 22, 12, '#98a2ad', 4)
    add('<path d="M%.1f %.1f Q %.1f %.1f %.1f %.1f" fill="none" stroke="#3d444d" '
        'stroke-width="3"/>' % (x + 15, y + 40, x + 15, y + 58, x + 40, y + 58))
    txt(x + 15, y - 8, label, 9, FG, 'middle', '600')
    if sub:
        txt(x + 15, y + 74, sub, 8, MUTED, 'middle')


def draw_button(x, y, label):
    """Тактовая кнопка."""
    rect(x, y, 42, 30, '#22272e', 4, '#12161a', 1.2)
    circle(x + 21, y + 14, 9, '#d0d7de', '#98a2ad', 1.2)
    circle(x + 21, y + 14, 5.5, '#f0f3f6')
    txt(x + 21, y + 44, label, 9, FG, 'middle', '600')


def draw_relay(x, y, label, sub, color):
    """Модуль реле / силовой ключ."""
    rect(x, y, 96, 54, '#0f4d2a', 5, '#0a3a1f', 1.5)
    rect(x + 8, y + 8, 34, 30, '#1f2937', 3)
    rect(x + 12, y + 12, 26, 12, '#4b5563', 2)
    circle(x + 25, y + 32, 3, '#d1242f')
    rect(x + 50, y + 10, 38, 26, '#1a7f37', 3, '#0d5c26', 1)
    txt(x + 69, y + 27, 'AC', 9, '#eafff0', 'middle', '700')
    txt(x + 48, y + 74, label, 10, color, 'middle', '600')
    txt(x + 48, y + 87, sub, 9, MUTED, 'middle')


def draw_heater(x, y):
    """ТЭН."""
    pts = 'M%d %d' % (x, y + 20)
    for i in range(6):
        pts += ' q 7 -16 14 0 q 7 16 14 0' if i == 0 else ' q 7 -16 14 0 q 7 16 14 0'
    add('<path d="%s" fill="none" stroke="#d1242f" stroke-width="4" stroke-linecap="round"/>'
        % pts)
    add('<path d="%s" fill="none" stroke="#ff9b8a" stroke-width="1.4" stroke-linecap="round" '
        'stroke-dasharray="3 4"/>' % pts)
    txt(x + 84, y + 48, 'ТЭН нагрева', 10, W_PWR, 'middle', '600')


def draw_fan(x, y, label, sub, color):
    """Вентилятор."""
    cx, cy = x + 34, y + 34
    rect(x, y, 68, 68, '#22272e', 8, '#12161a', 1.2)
    circle(cx, cy, 27, '#2f3742')
    for a in (0, 72, 144, 216, 288):
        add('<path d="M %.1f %.1f Q %.1f %.1f %.1f %.1f Z" fill="%s" fill-opacity="0.85" '
            'transform="rotate(%d %.1f %.1f)"/>'
            % (cx, cy, cx + 26, cy - 14, cx + 8, cy - 25, color, a, cx, cy))
    circle(cx, cy, 7, '#c0c8d0')
    txt(cx, y + 88, label, 10, color, 'middle', '600')
    txt(cx, y + 101, sub, 9, MUTED, 'middle')


def draw_humidifier(x, y):
    """Ультразвуковой испаритель."""
    rect(x, y + 26, 70, 44, '#1b4b8f', 6, '#12356a', 1.4)
    add('<path d="M%d %d h70" stroke="#4aa8ff" stroke-width="3"/>' % (x, y + 40))
    circle(x + 35, y + 55, 10, '#0d2f5c', '#4aa8ff', 1.5)
    for i, r in enumerate((7, 12, 17)):
        add('<path d="M %.1f %.1f a %d %d 0 0 1 %d 0" fill="none" stroke="#4aa8ff" '
            'stroke-width="1.8" stroke-opacity="%.2f"/>'
            % (x + 35 - r, y + 24, r, r, r * 2, 0.9 - i * 0.25))
    txt(x + 35, y + 88, 'Испаритель', 10, W_I2C, 'middle', '600')
    txt(x + 35, y + 101, 'ультразвуковой', 9, MUTED, 'middle')


def draw_motor(x, y):
    """Мотор-редуктор лотка."""
    rect(x, y + 10, 46, 40, '#4b5563', 5, '#374151', 1.2)
    rect(x + 46, y + 20, 16, 20, '#6b7280', 3)
    circle(x + 78, y + 30, 20, '#9ca3af', '#6b7280', 1.5)
    for a in range(0, 360, 40):
        add('<rect x="%.1f" y="%.1f" width="5" height="7" fill="#6b7280" '
            'transform="rotate(%d 78 30) translate(%d 0)"/>' % (x + 75.5, y + 8, a, x))
    circle(x + 78, y + 30, 7, '#4b5563')
    txt(x + 23, y + 30, 'M', 15, '#f0f3f6', 'middle', '700')
    txt(x + 45, y + 72, 'Мотор-редуктор лотка', 10, W_MOT, 'middle', '600')
    txt(x + 45, y + 85, 'реверс двумя реле', 9, MUTED, 'middle')


def draw_switch(x, y, label):
    """Концевой выключатель."""
    rect(x, y, 54, 26, '#22272e', 3, '#12161a', 1.2)
    add('<path d="M%.1f %.1f l 22 -9" stroke="#d0d7de" stroke-width="2.4" '
        'stroke-linecap="round"/>' % (x + 12, y + 18))
    circle(x + 12, y + 18, 3, '#d0d7de')
    circle(x + 42, y + 18, 3, '#d0d7de')
    add('<path d="M%.1f %.1f l 10 -5" stroke="#8b949e" stroke-width="1.6"/>' % (x + 34, y + 8))
    txt(x + 27, y + 42, label, 9, FG, 'middle', '600')


def draw_led_buzz(x, y):
    """Светодиод и зуммер."""
    circle(x + 16, y + 16, 13, '#d1242f', '#a01020', 1.4, 0.85)
    circle(x + 12, y + 12, 4, '#ff8a8a', 'none', 1, 0.9)
    add('<path d="M%d %d v 12 M%d %d v 12" stroke="#8b949e" stroke-width="2"/>'
        % (x + 11, y + 28, x + 21, y + 28))
    txt(x + 16, y + 56, 'Авария', 9, '#d1242f', 'middle', '600')

    circle(x + 74, y + 16, 15, '#22272e', '#12161a', 1.4)
    circle(x + 74, y + 16, 5, '#4b5563')
    for i, r in enumerate((20, 25)):
        add('<path d="M %.1f %.1f a %d %d 0 0 1 0 %d" fill="none" stroke="#8b949e" '
            'stroke-width="1.6" stroke-opacity="%.2f"/>' % (x + 88, y + 16 - r / 2, r, r, r, 0.8 - i * 0.3))
    txt(x + 74, y + 56, 'Зуммер', 9, FG, 'middle', '600')


# ---------------------------------------------------------------------------
# Плата
# ---------------------------------------------------------------------------
W, H = 1280, 900
BX, BY, BW, BH = 470, 250, 330, 420

add('<rect width="%d" height="%d" fill="#ffffff" fill-opacity="0"/>' % (W, H))
txt(40, 42, 'Схема подключения периферии', 22, FG, 'start', '700')
txt(40, 66, 'Инкубатор на Arduino Mega 2560 · пины соответствуют Incubation/consts.h', 12, MUTED)

# плата
rect(BX, BY, BW, BH, BOARD, 12, '#0a6a6a', 2, 0.92)
rect(BX + 14, BY + 14, BW - 28, BH - 28, '#ffffff', 8, 'none', 1, 0.07)
txt(BX + BW / 2, BY + 52, 'Arduino', 20, '#eafffb', 'middle', '700')
txt(BX + BW / 2, BY + 76, 'MEGA 2560', 16, '#eafffb', 'middle', '600')
txt(BX + BW / 2, BY + 96, 'ATmega2560 · 16 МГц', 10, '#bfeeea', 'middle')
# «чип»
rect(BX + 110, BY + 120, 110, 110, '#12161a', 6)
for i in range(9):
    rect(BX + 104, BY + 130 + i * 11, 6, 5, '#c0c8d0', 1)
    rect(BX + 220, BY + 130 + i * 11, 6, 5, '#c0c8d0', 1)
txt(BX + 165, BY + 180, 'ATmega', 10, '#8b949e', 'middle')
txt(BX + 165, BY + 194, '2560', 10, '#8b949e', 'middle')
# USB и питание
rect(BX - 12, BY + 30, 26, 34, '#98a2ad', 3)
txt(BX + 1, BY + 82, 'USB', 8, '#eafffb', 'middle')
circle(BX - 2, BY + 130, 14, '#22272e', '#12161a', 1.4)
circle(BX - 2, BY + 130, 6, '#4b5563')
txt(BX + 2, BY + 156, '7–12 В', 8, '#eafffb', 'middle')

# гребёнки контактов
for gy in (BY + 250, BY + 300):
    rect(BX + 30, gy, BW - 60, 16, '#12161a', 3)
    for i in range(18):
        rect(BX + 36 + i * 14.4, gy + 3, 7, 10, '#d4af37', 1)


def pin(x, y, label, color, side):
    circle(x, y, 5, '#12161a', color, 2)
    if side == 'L':
        txt(x - 12, y + 4, label, 10, color, 'end', '700')
    else:
        txt(x + 12, y + 4, label, 10, color, 'start', '700')


# ---------------------------------------------------------------------------
# Левая сторона: входы
# ---------------------------------------------------------------------------
LX = BX
btn_specs = [('A15', 'OK'), ('A13', '▲ вверх'), ('A12', '▼ вниз'), ('A14', '← назад')]
for i, (pn, lbl) in enumerate(btn_specs):
    y = BY + 130 + i * 34
    pin(LX, y, pn, W_SIG, 'L')
    bx = 150
    draw_button(bx, y - 15, lbl)
    wire([(bx + 42, y), (bx + 70, y), (LX - 42, y), (LX - 5, y)], W_SIG, 2)

txt(150, BY + 110, 'КНОПКИ УПРАВЛЕНИЯ · INPUT_PULLUP', 10, W_SIG, 'start', '700')
rect(140, BY + 118, 320, 152, W_SIG, 8, W_SIG, 1, 0.05)

# концевики
txt(150, BY + 300, 'КОНЦЕВЫЕ ВЫКЛЮЧАТЕЛИ', 10, W_SIG, 'start', '700')
rect(140, BY + 308, 320, 106, W_SIG, 8, W_SIG, 1, 0.05)
for i, (pn, lbl) in enumerate((('A10', 'Дверь камеры'), ('A11', 'Лоток по центру'))):
    y = BY + 336 + i * 46
    pin(LX, y, pn, W_SIG, 'L')
    draw_switch(160, y - 13, lbl)
    wire([(214, y), (250, y), (LX - 46, y), (LX - 5, y)], W_SIG, 2)

# 1-Wire
txt(60, 150, '1-WIRE · до 4 датчиков на одной шине (пин 19)', 10, W_1W, 'start', '700')
rect(50, 158, 380, 66, W_1W, 8, W_1W, 1, 0.05)
for i in range(4):
    draw_ds18b20(70 + i * 92, 176, 'Т%d' % (i + 1), 'DS18B20' if i == 0 else '')
txt(240, 216, 'Т1 — на яйце (контроль перегрева кладки)', 9, MUTED, 'middle')
pin(LX, BY + 20, '19', W_1W, 'L')
wire([(110, 234), (110, 240), (40, 240), (40, BY + 20), (LX - 5, BY + 20)], W_1W, 2.4)

# ---------------------------------------------------------------------------
# Правая сторона: выходы
# ---------------------------------------------------------------------------
RX = BX + BW

# ТЭН
txt(870, 116, 'СИЛОВАЯ ЧАСТЬ ~220 В', 10, W_PWR, 'start', '700')
rect(860, 124, 390, 150, W_PWR, 8, W_PWR, 1, 0.05)
draw_relay(880, 150, 'Ключ нагрева', 'симистор / МОП', W_PWR)
draw_heater(1060, 160)
wire([(976, 176), (1050, 176)], W_PWR, 2.4)
pin(RX, BY + 20, '2', W_PWR, 'R')
txt(RX + 26, BY + 34, 'ШИМ', 8, MUTED)
wire([(RX + 5, BY + 20), (840, BY + 20), (840, 176), (880, 176)], W_PWR, 2.4)

# вентилятор
draw_fan(880, 320, 'Вентилятор', 'обдув / вытяжка', W_VENT := '#1a7f37')
pin(RX, BY + 70, '3', W_VENT, 'R')
txt(RX + 26, BY + 84, 'медл. ШИМ', 8, MUTED)
wire([(RX + 5, BY + 70), (840, BY + 70), (840, 354), (880, 354)], W_VENT, 2.4)

# испаритель
draw_humidifier(1040, 306)
pin(RX, BY + 120, '4', W_I2C, 'R')
wire([(RX + 5, BY + 120), (1010, BY + 120), (1010, 360), (1040, 360)], W_I2C, 2.4)

# мотор лотка
txt(870, 470, 'ПОВОРОТ ЛОТКА', 10, W_MOT, 'start', '700')
rect(860, 478, 390, 130, W_MOT, 8, W_MOT, 1, 0.05)
draw_motor(1060, 500)
draw_relay(880, 500, 'Реле реверса', '2 канала', W_MOT)
wire([(976, 526), (1055, 526)], W_MOT, 2.4)
pin(RX, BY + 180, '17', W_MOT, 'R')
pin(RX, BY + 210, '18', W_MOT, 'R')
txt(RX + 40, BY + 184, 'влево', 9, MUTED)
txt(RX + 40, BY + 214, 'вправо', 9, MUTED)
wire([(RX + 5, BY + 180), (830, BY + 180), (830, 516), (880, 516)], W_MOT, 2.2)
wire([(RX + 5, BY + 210), (820, BY + 210), (820, 536), (880, 536)], W_MOT, 2.2)

# сигнализация
txt(870, 660, 'СИГНАЛИЗАЦИЯ', 10, '#d1242f', 'start', '700')
rect(860, 668, 260, 106, '#d1242f', 8, '#d1242f', 1, 0.05)
draw_led_buzz(900, 692)
pin(RX, BY + 260, '5', '#d1242f', 'R')
pin(RX, BY + 290, '6', '#d1242f', 'R')
wire([(RX + 5, BY + 260), (830, BY + 260), (830, 708), (912, 708)], '#d1242f', 2.2)
wire([(RX + 5, BY + 290), (845, BY + 290), (845, 730), (970, 730), (970, 712)], '#d1242f', 2.2)

# ---------------------------------------------------------------------------
# Низ: I2C и дисплей
# ---------------------------------------------------------------------------
txt(60, 700, 'ШИНА I²C (SDA 20 / SCL 21)', 10, '#0969da', 'start', '700')
rect(50, 708, 340, 128, '#0969da', 8, '#0969da', 1, 0.05)
draw_htu(80, 726)
draw_rtc(240, 726)
pin(BX + 60, BY + BH, 'SDA', '#0969da', 'L')
pin(BX + 120, BY + BH, 'SCL', '#0969da', 'L')
wire([(117, 786), (117, 812), (420, 812), (420, BY + BH), (BX + 55, BY + BH)], '#0969da', 2.2)
wire([(277, 786), (277, 824), (436, 824), (436, BY + BH + 14),
      (BX + 120, BY + BH + 14), (BX + 120, BY + BH + 5)], '#0969da', 2.2)

# дисплей
txt(560, 720, 'ДИСПЛЕЙ', 10, FG, 'start', '700')
rect(550, 728, 260, 152, FG, 8, FG, 1, 0.05)
draw_lcd(575, 746)
pin(BX + 200, BY + BH, '13…8', FG, 'R')
txt(BX + 214, BY + BH + 18, 'RS, E, D4–D7', 9, MUTED)
pin(BX + 280, BY + BH, '7 / A1', FG, 'R')
txt(BX + 250, BY + BH + 40, 'яркость / контраст', 9, MUTED)
wire([(BX + 200, BY + BH + 5), (BX + 200, 736), (650, 736), (650, 746)], FG, 2.2)
wire([(BX + 280, BY + BH + 5), (BX + 280, 726), (740, 726), (740, 746)], FG, 2.2)

# легенда
LGX, LGY = 50, 862
legend = [('сигнальные входы', W_SIG), ('1-Wire', W_1W), ('I²C', '#0969da'),
          ('силовая часть ~220 В', W_PWR), ('моторы и реле', W_MOT)]
for i, (lbl, c) in enumerate(legend):
    x = LGX + i * 175
    add('<path d="M%d %d h 22" stroke="%s" stroke-width="3" stroke-linecap="round"/>'
        % (x, LGY, c))
    txt(x + 30, LGY + 4, lbl, 10, FG)

txt(W - 40, LGY - 22,
    '⚠ Силовую часть разводить отдельно от логики. Ставить термопредохранитель на ТЭН.',
    10, W_PWR, 'end', '600')

svg = ('<svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 %d %d" width="%d" height="%d" '
       'role="img" aria-label="Схема подключения периферии инкубатора">\n%s\n</svg>\n'
       % (W, H, W, H, '\n'.join(P)))
open(os.path.join(OUT, 'wiring.svg'), 'w', encoding='utf-8').write(svg)
print('ok', len(svg))
