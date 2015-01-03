#!/usr/bin/env python

import sys
import emissionTable

# Functions to build the syntax tree
def prepareSource(source):
    if source.count('[') != source.count("]"):
        raise SyntaxError("Mismatched loop operators")
    for char in source:
        if char in ".,<>[]+-":
            yield char

def buildTree(source):
    tree = []
    for char in source:
        if char == '[':    # loop char
            tree.append(buildTree(source))
        elif char == ']':
            return tree
        else:
            tree.append(char)
    return tree

def optimise(tree, level):
    return tree

def emit(source):
    ops = []
    for node in source:
        if type(node) == str:
            ops.append(emissionTable.op[node])
        else:
            ops.append("label")
            ops += emit(node)
            ops.append("jmp to label")
    return ops

if __name__ == '__main__':
    source = open(sys.argv[-1], 'r').read()
    source = prepareSource(source)  # clean and syntax check the source
    source = buildTree(source)      # convert from source to tree
    source = optimise(source, 0)    # optimise the tree
    output = emit(source)
    print output
