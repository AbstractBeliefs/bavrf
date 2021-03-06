#!/usr/bin/env python

import sys
import jinja2

import ops

def labelGen():
    labelNumber = 0
    while True:
        yield ops.Label("l" + str(labelNumber))
        labelNumber = labelNumber+1

# Functions to build the syntax tree
def prepareSource(source):
    if source.count('[') != source.count("]"):
        raise SyntaxError("Mismatched loop operators")
    for char in source:
        if char in ".,<>[]+-":
            yield char

def buildTree(source, labeller):
    tree = []
    for char in source:
        if char == '+': tree.append(ops.RegisterIncrement(1))
        elif char == '-': tree.append(ops.RegisterIncrement(-1))
        elif char == '>': tree.append(ops.Navigate(1))
        elif char == '<': tree.append(ops.Navigate(-1))
        elif char == '.': tree.append(ops.Communicate("RIT"))
        elif char == ',': tree.append(ops.Communicate("RED"))
        elif char == '[': tree.append(ops.Loop(labeller, buildTree(source, labeller)))
        elif char == ']': return tree
        else: RuntimeError("Couldn't identify operation")
    return tree

def optimise(tree, level):
    return tree

def emit(tree):
    for op in tree:
        yield op.emit()

if __name__ == '__main__':
    source = open(sys.argv[-1], 'r').read()
    source = prepareSource(source)          # clean and syntax check the source
    source = buildTree(source, labelGen())  # convert from source to tree

    outputEnv = jinja2.Environment(
        loader=jinja2.FileSystemLoader("."),
        trim_blocks=True,
        lstrip_blocks=True
    )

    template = outputEnv.get_template("runtime.S")
    print template.render(device="ATmega328P", output=emit(source))
