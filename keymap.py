#!/usr/bin/python3

import os

from typing import List, Iterator, Union
import itertools
import json
import sys

# expects to be called from qmk firmware dir
sys.path.append(os.path.join(os.getcwd(), "lib", "python"))
try:
    import qmk
    from qmk import path
    from qmk.keymap import template
except ImportError:
    print(
        "Could not import qmk utils. Please make sure you are in the qmk_firmware repository root."
    )
    sys.exit(1)

MATRIX_COLS = 15


def space_equally(keys: List[str], keys_per_row=MATRIX_COLS) -> List[str]:
    """
    Find max keycode width in column and add whitespace around smaller keys for
    nice spacing
    """
    if not keys:
        return keys

    # pad to specified width with " "
    _pad = lambda s, width: f"{s: ^{width}}"

    for column_num in range(keys_per_row):
        column = keys[column_num::keys_per_row]
        max_width = max((len(keycode.strip()) for keycode in column))
        keys[column_num::keys_per_row] = [
            _pad(keycode, max_width) for keycode in column
        ]

    return keys


def join_into_rows(
    keys: Union[List[str], Iterator[str]], keys_per_row: int = MATRIX_COLS
) -> Iterator[str]:
    """
    Joins list of keys into strings representing each row
    """
    if isinstance(keys, list):
        keys = iter(keys)
    while True:
        row = list(itertools.islice(keys, keys_per_row))
        if not row:
            break
        yield ", ".join(row) + ","


def _strip_any(keycode: str) -> str:
    """
    Remove ANY() from a keycode.
    """
    if keycode.startswith("ANY(") and keycode.endswith(")"):
        keycode = keycode[4:-1]

    return keycode


def _replace_trans_no(keycode: str) -> str:
    """
    replace KC_TRANS with ________ and KC_NO with ___xx___
    """
    keycode = keycode.replace("KC_TRANS", "________")
    return keycode.replace("KC_NO", "___xx___")


def generate(keyboard: str, layout: str, layers: List):
    """
    Returns a keymap.c for the specified keyboard, layout, and layers.
    """
    layer_txt: List[str] = []

    for layer_num, layer in enumerate(layers):
        # add comma at start if not first layer
        if layer_num != 0:
            layer_txt[-1] = layer_txt[-1] + ","

        # empty layer
        if not layer:
            # fill layer with KC_NO
            # get num keys from first layer
            layer = len(layers[0]) * ["___xx___"]

        layer = [_strip_any(kc) for kc in layer]
        layer = [_replace_trans_no(kc) for kc in layer]
        layer = space_equally(layer)
        layer_keys = join_into_rows(layer)

        layout_begin = f"    [{layer_num}] = {layout}("
        layer_keys_txt = f"\n{len(layout_begin)*' '}".join(layer_keys)
        # drop final comma
        layer_keys_txt = layer_keys_txt[:-1]
        layer_txt.append(f"{layout_begin}{layer_keys_txt})")
    keymap = "\n".join(layer_txt)
    keymap_c = template(keyboard)

    return keymap_c.replace("__KEYMAP_GOES_HERE__", keymap)


def main(input_file: "keymap.json"):
    """
    Generate the `keymap.c` and write it to disk
    """

    with open(input_file, "r") as f:
        keymap_json = json.load(f)

    keyboard: str = keymap_json["keyboard"]
    keymap: str = keymap_json["keymap"]
    layout: str = keymap_json["layout"]  # layout macro
    layers: List[str] = keymap_json["layers"]  # keycodes

    keymap_c = generate(keyboard, layout, layers)

    keymap_file = path.keymap(keyboard) / keymap / "keymap.c"

    keymap_file.parent.mkdir(parents=True, exist_ok=True)
    keymap_file.write_text(keymap_c)

    print(f"Wrote keymap to {keymap_file}")

    return keymap_file


if __name__ == "__main__":
    _, *args = sys.argv
    keymap_file_path = args[0]
    main(input_file=keymap_file_path)
