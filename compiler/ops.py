class Operation(object):
    def emit(self):
        raise NotImplementedError


class RegMath(Operation):
    """Useful as an optimisation target"""
    def __init__(self, value):
        self.value = value


class RegisterIncrement(RegMath):
    """Change the working register by a given amount"""
    emissions = {
        "inc": "    INC    r16\n",
        "dec": "    DEC    r16\n",
        "add": "    LDI    r1, %d\n"
               "    ADD    r16, r1\n",
        "sub": "    SUBI   r16, %d\n",  # why we have a subtract immediate but
    }                                   # but not add immediate, we'll never know

    def emit(self):
        if self.value == 1:
            return self.emissions["inc"]
        elif self.value == -1:
            return self.emissions["dec"]
        else:
            if self.value > 0:
                return self.emissions["add"] % self.value
            else:
                return self.emissions["sub"] % self.value

    def __repr__(self):
        return "INC (%d)" %self.value


class Navigate(RegMath):
    """
    Change the RAM pointer (Z) by a given amount,
    remembering to save and load working register
    """
    emissions = {
        "add": "    ST     Z, r16\n"
               "    ADIW   r30, %d\n"
               "    LD     r16, Z\n",
        "sub": "    ST     Z, r16\n"
               "    SBIW   r30, %d\n"
               "    LD     r16, Z\n",
    }

    def emit(self):
        if self.value > 0:
            return self.emissions["add"] % self.value
        else:
            return self.emissions["sub"] % self.value

    def __repr__(self):
        return "NAV (%d)" % self.value


class Loop(Operation):
    """Manage looped operation segments"""
    def __init__(self, name, operations):
        self.name = name
        self.operations = operations

    def emit(self):
        prologue = "%s:\n"\
                   "    CPSE   r16, r0\n"\
                   "    RJMP   %s_end\n" %(self.name, self.name)
        epilogue = "    RJMP   %s\n"\
                   "%s_end:\n" %(self.name, self.name)
        body = [op.emit() for op in self.operations]

        return "".join([prologue]+body+[epilogue])

    def __repr__(self):
        return "NAV (%s)[%s]" % (self.name, "".join(repr(op) for op in self.operations))


class Communicate(Operation):
    emissions = {
        "RED": "    NOP    ; It's a comms read\n",
        "RIT": "    NOP    ; It's a comms write\n",
    }

    def __init__(self, direction):
        self.direction = direction

    def emit(self):
        return self.emissions[self.direction]

    def __repr__(self):
        return self.direction