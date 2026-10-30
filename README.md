# Corne: keymap and tools to learn the layers

Configuration of my Corne (foostan crkbd, QMK, Pro Micro), recovered by reading the firmware that was on the keyboard.

![Layer map](corne/keymap.svg)

The first layer of the diagram, **FULL**, puts every layer on each key: QWERTY in the center, LOWER top left, RAISE top right, ADJUST bottom left and the double taps (`2×`) in purple. Keys that switch layer breathe in the color of the layer they open (when the SVG is opened in a browser).

| Corne Dojo (FULL) | One layer (LOWER) |
|---|---|
| ![Corne Dojo on FULL](corne/img/dojo-full.png) | ![Corne Dojo on LOWER](corne/img/dojo-lower.png) |
| **Layers stacked in 3D** | **Help: ⌘ Esc shortcut** |
| ![3D layers](corne/img/dojo-stack.png) | ![Help mode](corne/img/dojo-help.png) |
| **⌘ Esc window (Large)** | **Thumbnail (Mini)** |
| ![Large window](corne/img/overlay-large.png) | ![Thumbnail](corne/img/overlay-mini.png) |

## Layers

| Layer | How to activate | LEDs | Contents |
|---|---|---|---|
| **QWERTY** | base layer | EVA purple, lime green edges | Letters. Double tap `Esc` = Caps Lock, double tap `A` = `@` |
| **LOWER** | hold the left middle thumb key | orange, purple edges | Numbers, mouse and wheel, arrows, media, Mission Control |
| **RAISE** | hold the right middle thumb key | lime green, purple edges | Symbols `! @ # $ % ^ & * ( ) = [ ] { } \ \| ~ _ + -` |
| **ADJUST** | from LOWER or RAISE, hold the middle thumb key on the other side | mint, orange edges | Numpad and RGB control |
| **COLEMAK** | in ADJUST, the `COLEMAK` key swaps the base; the same key goes back | QWERTY colors, Esc and Backspace breathe red | Colemak layout |

All LEDs breathe slowly (KB-01 firmware). Layer keys are *tap-toggle*: holding one activates the layer while held; tapping it several times in a row locks it. Symbols assume macOS with the **Spanish ISO** layout.

## On-screen help on the Mac (⌘ Esc)

Opens Corne Dojo in a window above any app, without recompiling the keyboard.

- **Hold `⌘ Esc`**: the window appears; release and it disappears. On the Corne: Cmd with the left thumb and Esc with the left pinky (Esc has a double tap, so it shows up a fraction of a second later).
- **Pin** (in the window) or **click `KB-01`** in the menu bar: keeps it open. **Close** or `Esc` hides it.
- **Mini**: pins a small translucent thumbnail in the bottom-right corner (at most 40 % of the screen width). Drag it from anywhere that is not a button; it remembers where you left it. **Large** goes back to the normal size.
- It opens in the last size you used (Mini or Large).
- With the window pinned, the tabs (or keys `1`–`6`) show only that layer. It always opens on **FULL**.
- **FULL** (first tab) shows every layer on the same key, like [Miryoku](https://github.com/manna-harbour/miryoku): QWERTY in the center, LOWER top left (orange), RAISE top right (green), ADJUST bottom left (mint). COLEMAK is left out because it replaces the base. Keys that switch layer breathe in the color of the layer they open, and a purple `2×` tag marks the double taps (Esc → Caps, A → @, Ctrl → Mission Control).

Install (once):

```sh
brew install --cask hammerspoon
mkdir -p ~/.hammerspoon/corne
cp corne/hammerspoon/corne-overlay.lua corne/corne-dojo.html ~/.hammerspoon/corne/
cat > ~/.hammerspoon/init.lua <<'EOF'
require("hs.ipc")
package.path = hs.configdir .. "/corne/?.lua;" .. package.path
corneOverlay = require("corne-overlay")
EOF
open -a Hammerspoon
```

To change the shortcut, edit the line `hs.hotkey.bind({ "cmd" }, "escape", ...)` in `corne-overlay.lua` and restart Hammerspoon.

## What the Japanese means

The style is inspired by *Evangelion*'s EVA-01. The keyboard is called **KB-01** (KEYBOARD-01).

| Text | Reading | Meaning |
|---|---|---|
| **キボド 01** | *kibodo zero-wan* | "Keyboard 01", shortened. The Japanese name of KB-01 |
| キ | *ki* | syllable "ki" |
| ボ | *bo* | syllable "bo" (ホ *ho* with the two ticks ゛ that make it voiced) |
| ド | *do* | syllable "do" (ト *to* with ゛) |

キボド is "keyboard" in katakana, clipped: the full form is キーボード (*kībōdo*), where `ー` lengthens the previous vowel.

### Katakana on the keys (QWERTY)

These are the kana printed on Japanese keycaps (JIS layout for kana input). Each one is a syllable, not a word, so on their own they mean nothing.

| Key | Kana | Syllable | | Key | Kana | Syllable | | Key | Kana | Syllable |
|---|---|---|---|---|---|---|---|---|---|---|
| Q | タ | ta | | A | チ | chi | | Z | ツ | tsu |
| W | テ | te | | S | ト | to | | X | サ | sa |
| E | イ | i | | D | シ | shi | | C | ソ | so |
| R | ス | su | | F | ハ | ha | | V | ヒ | hi |
| T | カ | ka | | G | キ | ki | | B | コ | ko |
| Y | ン | n | | H | ク | ku | | N | ミ | mi |
| U | ナ | na | | J | マ | ma | | M | モ | mo |
| I | ニ | ni | | K | ノ | no | | | | |
| O | ラ | ra | | L | リ | ri | | | | |
| P | セ | se | | | | | | | | |

## Web trainer (Corne Dojo)

`corne/corne-dojo.html` (open it in a browser; the same page is in `docs/index.html` for GitHub Pages). It opens on FULL and, below, shows the layers stacked in 3D (click one to see it). It lights up the key and layer of what you type, and has a practice mode that repeats the characters you struggle with more often. Published at https://claude.ai/artifact/FbiRLyb5SXwaoRFzvND5iT

## Files

| File | What it is |
|---|---|
| `corne/keymap.c` | Reconstructed QMK keymap (without the Luna/OLED code, which is compiled) |
| `corne/corne_dump.hex` | Exact copy of the firmware; can be flashed back as is |
| `corne/corne_eeprom.hex` | Copy of the EEPROM (saved RGB settings) |
| `corne/led-colors.json` | Key and underglow color for each layer (the KB-01 EVA palette) |
| `corne/tools/led_colors.py` | Generates those colors (keys = layer color, modifier keys = shifted hue) and applies them to the YAML and diagram config |
| `corne/tools/build_dojo.py` | Builds `corne-dojo.html` and `docs/index.html` from the template, `keymap.c` and `led-colors.json` |
| `corne/tools/full_layer.py` | Adds the FULL layer to the YAML and marks the layer keys so they breathe |
| `corne/img/` | Screenshots of the Dojo, the ⌘ Esc window and the OLED |
| `corne/qmk/kb01/` | KB-01 QMK keymap: `keymap.c`, `eva_sprites.h` (OLED sprites), `rgb_matrix_user.inc` (breathing effect) |
| `corne/qmk/kb01.hex` | KB-01 compiled firmware |
| `docs/index.html` | Corne Dojo for GitHub Pages |
| `corne/keymap.yaml` | Diagram source for [keymap-drawer](https://github.com/caksoylar/keymap-drawer) |
| `corne/drawer-config.yaml` | Per-layer colors (the firmware's) and the shortcut note |
| `corne/keymap.svg` | Layer diagram |
| `corne/hammerspoon/corne-overlay.lua` | On-screen help: opens `corne-dojo.html#overlay` with ⌘ Esc |
| `corne/trainer.template.html` | Web trainer source (the keymap is inserted at `__LAYERS__`) |

## Regenerating the diagrams

```sh
pip install keymap-drawer
python corne/tools/full_layer.py   # FULL layer and layer keys (use the Python where keymap-drawer is installed)
python corne/tools/led_colors.py   # per-key colors
python corne/tools/build_dojo.py
keymap -c corne/drawer-config.yaml draw corne/keymap.yaml > corne/keymap.svg
cp corne/corne-dojo.html ~/.hammerspoon/corne/   # the ⌘ Esc window uses the same Dojo
```

## New firmware (KB-01)

`corne/qmk/kb01/` is a QMK keymap rebuilt from the recovered one, with an EVA-01 OLED and LED palette:

- **COLEMAK no longer traps you**: the `COLEMAK` key in ADJUST swaps the base layer, so LOWER, RAISE and ADJUST keep working on top of Colemak and the same key goes back to QWERTY. Unplugging always starts on QWERTY.
- **Layer report to the Mac**: every layer change taps F16 (base), F17 (LOWER), F18 (RAISE), F19 (ADJUST) or F20 (COLEMAK). The ⌘ Esc window switches to that layer and swallows the keys (Hammerspoon needs Accessibility permission).
- **Two taps lock a layer** (`TAPPING_TOGGLE 2`).
- **EVA LEDs**: a custom effect (`EVA_BREATH`) makes every LED breathe in the layer color; modifiers get a shifted hue. On COLEMAK, Esc and Backspace breathe red.

### OLED

![OLED states](corne/img/oled.png)

- **Left half**: the layer name, `CAPS` when Caps Lock is on and an EVA-01 silhouette that follows your typing speed. It stands still when idle, walks under 50 wpm, runs from 50 and gets a halo from 70. Space makes it jump, Caps Lock makes it draw the rifle (every key fires a bullet) and on COLEMAK it grows wings.
- **Right half**: the KB-01 plate and a SYNC bar, where 100 wpm is full sync, with the wpm below.

The sprites in `eva_sprites.h` are 32 px wide OLED pages.

To fit in 28 KB, features the keymap does not use are compiled out: one-shot keys, 32-bit layer state, the other RGB effects (except Breathing) and LED state sync between halves.

`corne/qmk/kb01.hex` is the compiled firmware (27,404 of 28,672 bytes). Build it again with:

```sh
brew tap osx-cross/avr && brew install avr-gcc@8
python3 -m pip install qmk
git clone --depth 1 https://github.com/qmk/qmk_firmware ~/qmk_firmware
ln -s "$PWD/corne/qmk/kb01" ~/qmk_firmware/keyboards/crkbd/keymaps/kb01
cd ~/qmk_firmware && make crkbd/rev1:kb01   # -> crkbd_rev1_kb01.hex
```

Flash **both halves**, one at a time, each with its own USB cable: double tap reset and within 8 s

```sh
avrdude -p atmega32u4 -c avr109 -P /dev/cu.usbmodemXXXX -U flash:w:corne/qmk/kb01.hex:i
```

The left half is the one that goes to the computer (`MASTER_LEFT`). On the Mac, set the input source to **Spanish ISO**. To go back, flash `corne/corne_dump.hex` (below) on both halves.

## Recovering or restoring the firmware

With the left half connected, double tap the reset button and within 8 s:

```sh
# read (changes nothing)
avrdude -p atmega32u4 -c avr109 -P /dev/cu.usbmodemXXXX -U flash:r:corne_dump.hex:i
# restore the backup
avrdude -p atmega32u4 -c avr109 -P /dev/cu.usbmodemXXXX -U flash:w:corne/corne_dump.hex:i
```
