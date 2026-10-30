"""Build corne-dojo.html (and docs/index.html for GitHub Pages) from trainer.template.html + the KB-01 keymap
(qmk/kb01/keymap.c) + led-colors.json."""
import json
import re
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent

src = (ROOT / "qmk" / "kb01" / "keymap.c").read_text()
# The Dojo names layers by index (ORDER in the template) and uses the classic QMK keycode names.
ORDER = ["QWERTY", "LOWER", "RAISE", "ADJUST", "COLEMAK"]
src = re.sub(r"TT\(_(\w+)\)", lambda m: f"TT({ORDER.index(m[1])})", src)
for new, old in {"CLMK_TG": "TG(4)", "RM_TOGG": "RGB_TOG", "MS_UP": "KC_MS_U", "MS_DOWN": "KC_MS_D", "MS_LEFT": "KC_MS_L",
                 "MS_RGHT": "KC_MS_R", "MS_WHLU": "KC_WH_U", "MS_WHLD": "KC_WH_D", "MS_BTN1": "KC_BTN1", "MS_BTN2": "KC_BTN2"}.items():
    src = re.sub(rf"\b{new}\b", old, src)
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
