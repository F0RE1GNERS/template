#!/usr/bin/env python3
'''
Filter to wrap Pandoc's CodeBlocks into minted blocks when using latex.
Pandoc's `fence_code_attributes` can be used to provide:
- the language (first class)
- minted's argumentless options (following classes)
- minted's options with arguments (attributes)
'''

from pandocfilters import toJSONFilter, RawBlock


TEMPLATE = r'''
\begin{{minted}}[fontsize=\footnotesize,breaklines,linenos{options}]{{{lang}}}
{cont}
\end{{minted}}
'''.strip()


def latex(x):
    return RawBlock('latex', x)


def join_options(opts):
    return ',\n'.join(opts)


def process_atts(kws):
    '''Preprocess the attributes provided by pandoc - they come as a list of
    2-lists, convert to a list of strings'''
    return ['%s=%s' % (l, r) for l, r in kws]


def mintedify(key, value, format_, meta):
    if key == 'CodeBlock':
        (ident, classes, attributes), contents = value
        if format_ == 'latex' and classes:
            language, *pos = classes
            atts = process_atts(attributes)
            return [latex(TEMPLATE.format(lang=language,
                                          options=join_options(pos+atts),
                                          cont=contents))]

if __name__ == '__main__':
    toJSONFilter(mintedify) 
