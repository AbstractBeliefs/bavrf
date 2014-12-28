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
