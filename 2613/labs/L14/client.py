import humansize

#have to call print because in humansize looks for if main

def approximate_size (bytes, k_is_1024=False) :
    '''Convert a file size to human-readable form.

    Keyword arguments:
    size -- file size in bytes
    k_is_1024_bytes -- if True,  use multiples of 1024
                                if False(default), use multiples of 1000

    Returns: string

    '''
    return humansize.approximate_size(bytes,k_is_1024)

if __name__ == '__main__':
    print(approximate_size(1000000000000, True))
    print(approximate_size(1000000000000))


