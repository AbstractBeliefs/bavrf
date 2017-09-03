.device {{device}}

.org 0x0000
    RJMP   setup

.org 0x0040
setup:
    RJMP   start

start:
{% for unit in output %}{{ unit }}{% endfor %}
end:
    RJMP   end
