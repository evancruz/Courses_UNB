import re

def split_csv(s):
    return [split_row(row) for row in s.splitlines()]
    #first try
    #return [row.split(',') for row in s.splitlines()]

    #comprehension
    #return[ [strip_quotes(col) for col in row.split(',')]
        #for row in s.splitlines()]

    # rows = []
    #for row in s.splitlines():
    #    rows.append([strip_quotes(col) for col in split_row_3(row)])
    #return rows

def strip_quotes(s):
    strip_regex = re.compile(r'"?([^"]+)"?')
    search = strip_regex.search(s)
    if search:
        return search.group(1)
    else:
        return None

def split_row_3(s):
    split_regex=re.compile(
        r'''^   # start
        ("[^"]*"|'[^']*'|[^,]+) #first column, including single quote example (not used)
        ,
        ("[^"]*"|[^,]+) #second column
        ,
        ("[^"]*"|[^,]+) #third column
        $''', re.VERBOSE)
    search = split_regex.search(s)
    if search:
        return [ strip_quotes(col) for col in search.groups() ]
    else:
        return None

def split_row(s):
    col_regex = re.compile(r'("[^"]*"|[^,]+)')
    search = col_regex.findall(s)
    if search:
        return [strip_quotes(col) for col in search]
    else:
        return None

