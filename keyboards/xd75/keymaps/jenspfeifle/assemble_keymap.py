#!/usr/bin/python3

import os
import copy
from typing import List
import itertools

MATRIX_COLS = 15

WORKDIR = os.path.join(os.getcwd(), "keyboards/xd75/keymaps/jenspfeifle/")
PRE_FILE = "keymap.pre.c"
POST_FILE = "keymap.post.c"
LAYERS_FILE = "keymap.layers.c"  # raw layer info from QMK Configurator
OUTPUT_FILE = "keymap.c"

keymap_path = os.path.join(os.getcwd(), "keyboards/xd75/keymaps/jenspfeifle/keymap.c")


def read_pre():
    with open(os.path.join(WORKDIR, PRE_FILE), "r") as f:
        for line in f:
            yield line


def read_post():
    with open(os.path.join(WORKDIR, POST_FILE), "r") as f:
        for line in f:
            yield line


def read_layers():
    with open(os.path.join(WORKDIR, LAYERS_FILE), "r") as f:
        for line in f:
            yield line


def write_output_file(pre: str, layers: str, post: str):
    output = os.path.join(WORKDIR, OUTPUT_FILE)
    with open(output, "w") as f:
        print(f"Writing to {output}")
        f.write(pre)
        f.write(layers)
        f.write(post)


def clean_up_and_split(keys_str: str):
    return (
        keys_str.replace("KC_TRNS", "________").replace("KC_NO", "___xx___").split(",")
    )


def make_layers(lines: List[str]):
    for line in clean_up(lines):
        if is_layer(line):
            before_keys, keys_str, after_keys = extract_keys(line)
            keys = clean_up_and_split(keys_str)
            keys = space_equally(keys)
            rows = join_into_rows(keys, keys_per_row=MATRIX_COLS)
            layer = assemble_layer(before_keys, rows, after_keys)
            yield layer
        else:
            yield line


def clean_up(lines):
    for line in lines:
        yield line.replace("\t", "    ")


def is_layer(line):
    if "LAYOUT" in line:
        return True
    return False


def extract_keys(line):
    keys_begin = line.find("(") + 1
    keys_end = line.rfind(")")

    before = line[:keys_begin]
    keys = line[keys_begin:keys_end]
    after = line[keys_end:]

    return before, keys, after


def space_equally(keys):
    max_width = max((len(s.strip()) for s in keys))
    for key in keys:
        yield "{0:{fill}^{width}}".format(key.strip(), fill=" ", width=max_width)


def join_into_rows(keys, keys_per_row=MATRIX_COLS):
    while True:
        row = list(itertools.islice(keys, keys_per_row))
        if len(row) == 0:
            break
        yield ",".join(row)


def assemble_layer(before, key_rows, after):
    # replace indentation of first key row with 'before"
    firstline = before + next(key_rows) + ",\n"
    rows = indent(key_rows, len((before)))
    return firstline + ",\n".join(rows) + after + "\n"


def indent(lines, indentation_width):
    for line in lines:
        yield " " * indentation_width + line


if __name__ == "__main__":
    pre = "".join(read_pre())
    layers = "".join(make_layers(read_layers()))
    post = "".join(read_post())

    write_output_file(pre, layers, post)

