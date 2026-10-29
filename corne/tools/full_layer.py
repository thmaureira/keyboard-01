"""Add the FULL layer (all layers on one keycap, Miryoku style) and mark the layer keys in keymap.yaml.

FULL: center = QWERTY, top-left = LOWER, top-right = RAISE, bottom-left = ADJUST; 2× tap dances in a free corner.
Keys that change layer get a `lk-<layer>` type so the diagram can make them breathe in that layer's color.

Run before tools/led_colors.py, with the keymap-drawer Python (needs PyYAML):  python corne/tools/full_layer.py
"""
import re
from pathlib import Path

import yaml

ROOT = Path(__file__).resolve().parent.parent
LAYERS = ["QWERTY", "LOWER", "RAISE", "ADJUST", "COLEMAK"]
SHORT = {"Mission Ctrl": "MCtl", "Launchpad": "LPad", "Right click": "RClk", "Bright +": "Bri+", "Bright −": "Bri−",
         "RGB on/off": "RGB", "RGB mode": "Mode", "⏎ Enter": "Enter"}


def short(t):
    t = SHORT.get(t, t)
    t = re.sub(r"^(Mouse|Wheel) ", lambda m: m[1][0], t)
    return re.sub(r" ([+−])$", r"\1", t)


def flat(rows):
    return [k if isinstance(k, dict) else {"t": k} for row in rows for k in row]


def rows(keys):
    return [keys[0:12], keys[12:24], keys[24:36], keys[36:42]]


path = ROOT / "keymap.yaml"
keymap = yaml.safe_load(path.read_text())
layers = {name: flat(keymap["layers"][name]) for name in LAYERS}

for name, keys in layers.items():
    for k in keys:
        types = [t for t in str(k.get("type", "")).split() if not t.startswith("lk-")]
        if k.get("t") in LAYERS and "layer" in str(k.get("s", "")):
            types.append("lk-" + k["t"].lower())
        if types:
            k["type"] = " ".join(types)
        else:
            k.pop("type", None)

full = []
for i, base in enumerate(layers["QWERTY"]):
    key = {"t": base["t"]}
    for corner, name in (("tl", "LOWER"), ("tr", "RAISE"), ("bl", "ADJUST")):
        t = layers[name][i].get("t", "")
        if t and t not in ("▽", base["t"]) and t not in LAYERS:
            key[corner] = short(t)
    if str(base.get("s", "")).startswith("2×"):
        # The 2× tap dance goes in the first free corner (type td-<corner> colors it).
        free = next(c for c in ("tl", "tr", "br", "s") if c not in key)
        key[free] = "2×" + short(base["s"].split(": ", 1)[1])
    types = [t for t in str(base.get("type", "")).split() if not t.startswith("led-")]
    if str(base.get("s", "")).startswith("2×"):
        types.append("td-" + free)
    if types:
        key["type"] = " ".join(types)
    full.append(key)

keymap["layers"] = {"FULL": rows(full), **{name: rows(layers[name]) for name in LAYERS}}
path.write_text(yaml.safe_dump(keymap, allow_unicode=True, sort_keys=False, width=1000))
