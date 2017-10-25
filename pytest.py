import re
import collections

Token = collections.namedtuple('Token', ['type', 'value'])

def tokenize(s):
    token_specification = [
        ('NUMBER',  r'\d+(\.\d*)?'), # Integer or decimal number
        ('ASSIGN',  r'='),          # Assignment operator
        ('ID',      r'[A-Za-z]+'),   # Identifiers
        ('OP',      r'[+*\/\-]'),    # Arithmetic operators
        ('SKIP',    r'[ \t\n]'),       # Skip over spaces and tabs
        ('PUNCTUATION', r'[ ,;():]')
    ]
    tok_regex = '|'.join('(?P<%s>%s)' % pair for pair in token_specification)
    get_token = re.compile(tok_regex).match
    pos = 0
    mo = get_token(s)
    while mo is not None:
        typ = mo.lastgroup
        if typ != 'SKIP':
            val = mo.group(typ)
            yield Token(typ, val)
        pos = mo.end()
        mo = get_token(s, pos)
    if pos != len(s):
        raise RuntimeError('Unexpected character %r on line %d')

statements = "MetaData(123,123.222), Editor = false, Serilizable = true, Hello = 1, Type = Class::Hello"

for token in tokenize(statements):
    print(token)