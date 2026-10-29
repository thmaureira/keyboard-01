"""Build corne-dojo.html (and docs/index.html for GitHub Pages) from trainer.template.html + keymap.c + led-colors.json."""
import json
import re
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent

src = (ROOT / "keymap.c").read_text()
layers = {
    name: [t.strip() for t in re.split(r",(?![^(]*\))", body) if t.strip()]
    for name, body in re.findall(r"\[_(\w+)\] = LAYOUT_split_3x6_3\((.*?)\n    \)", src, re.S)
}
html = (ROOT / "trainer.template.html").read_text()
html = html.replace("__LAYERS__", json.dumps(layers)).replace("__LEDS__", (ROOT / "led-colors.json").read_text())
(ROOT / "corne-dojo.html").write_text(html)
# GitHub Pages (Settings → Pages → branch main, folder /docs)
(ROOT.parent / "docs").mkdir(exist_ok=True)
(ROOT.parent / "docs" / "index.html").write_text(html)
