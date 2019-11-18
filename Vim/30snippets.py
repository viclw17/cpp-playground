def spread(arg):
    ret = []
    for i in arg:
        if isinstance(i, list):
            ret.extend(i)
        else:
            ret.append()
    return ret

def deep_flatten(xs):
    flat_list = []
    [flat_list.extend(deep_flatten(x)) for x in xs] if isinstance(xs, list) else flat_list.append(xs)
    return flat_list

#a = [1,[2],[[3],4],5]
#print deep_flatten(a)

# 18
def has_duplicates(lst):
    return len(lst) != len(set(lst))

# 19
def merge_two_dicts(a,b):
    c = a.copy()
    c.update(b)
    return c
# def merge_dictionaries(a,b):
#    return {**a, **b}

# 20
def to_dictionary(keys, values):
    return dict(zip(keys, values))

# 21
list = ["a","b"]
