"""Write the per-layer legends of keymap.yaml from Corne Dojo, so the diagram and the Dojo label keys the same way.

Opens corne-dojo.html in headless Chrome, reads the decoded keymap (DATA) and turns each key into a keymap-drawer
key: t = legend, s = shifted character / double tap / layer hint, right = katakana on QWERTY, type trans for ▽.
Run after tools/build_dojo.py and before tools/full_layer.py, with the keymap-drawer Python (needs PyYAML).
"""
import html
import json
import re
import subprocess
from pathlib import Path

import yaml

ROOT = Path(__file__).resolve().parent.parent
CHROME = "/Applications/Google Chrome.app/Contents/MacOS/Google Chrome"
LAYERS = ["QWERTY", "LOWER", "RAISE", "ADJUST", "COLEMAK"]

page = ROOT / "_dump.html"
page.write_text((ROOT / "corne-dojo.html").read_text()
                + '<pre id="dump"></pre><script>document.getElementById("dump").textContent = JSON.stringify(DATA)</script>')
try:
    dom = subprocess.run([CHROME, "--headless", "--disable-gpu", "--virtual-time-budget=1000", "--dump-dom", page.as_uri()],
                         capture_output=True, text=True, check=True).stdout
finally:
    page.unlink()
data = json.loads(html.unescape(re.search(r'<pre id="dump">(.*?)</pre>', dom, re.S)[1]))


def key(k, name):
    t, s = k.get("t", ""), k.get("s") or ""
    out = {"t": t}
    if k.get("cls") == "layer":
        s = "toggle" if s == "lock" else "TT · layer"
    elif s.startswith("⇧ "):
        s = s[2:]
    elif s.startswith("2× "):
        s = "2×: " + s[3:]
    if s:
        out["s"] = s
    if name == "QWERTY" and k.get("kana"):
        out["right"] = k["kana"]
    if k.get("cls") == "trans":
        out["type"] = "trans"
    return out


path = ROOT / "keymap.yaml"
keymap = yaml.safe_load(path.read_text())
for name in LAYERS:
    keys = [key(k, name) for k in data[name]]
    keymap["layers"][name] = [keys[0:12], keys[12:24], keys[24:36], keys[36:42]]
path.write_text(yaml.safe_dump(keymap, allow_unicode=True, sort_keys=False, width=1000))
