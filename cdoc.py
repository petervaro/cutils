## INFO ##
## INFO ##

# Import Python modules
from re import (VERBOSE as re_VERBOSE,
                DOTALL as re_DOTALL,
                MULTILINE as re_MULTILINE,
                compile as re_compile,
                sub as re_sub,
                finditer as re_finditer)
from errno import EEXIST as errno_EEXIST
from string import capwords as string_capwords
from os import (makedirs as os_makedirs,
                listdir as os_listdir)
from os.path import (splitext as os_path_splitext,
                     join as os_path_join,
                     dirname as os_path_dirname,
                     isdir as os_path_isdir,
                     isfile as os_path_isfile)
from itertools import count as iter_count
from collections import OrderedDict, _Link
from sys import argv as sys_argv

# Import third party modules
from yaml import load as yaml_load
from bs4 import BeautifulSoup

#------------------------------------------------------------------------------#
# Module level constants
SOUP = BeautifulSoup('<html><!-- www.cutils.org | Peter Varo | 2014 -->'
                     '<head><title></title><meta charset="UTF-8">'
                     '<link href="css/cdoc.css" rel="stylesheet" type='
                     '"text/css"></head><body></body></html>', 'lxml')

# Token type in order
TOKENS = ('comments', 'strings', 'macros', 'numbers', 'operators',
          'constants', 'types', 'keywords', 'functions')

# Mini C Syntax
SYNTAX = re_compile(r"""
(?P<comments>
    //.*?$|/\*.*?\*/)|

(?P<strings>
    ".+?"|'.')|

(?P<macros>
    ^\s*[#]\s*(include|define|error|pragma|line|
    (un|ifn?)def|else|(e(l|nd))?if))\b|

(?P<numbers>
    (((?<!\w)\.\d+([eE][+-]?\d+)?[fFlL]?\b)|
     ((?<!\w)\d+\.(\d+([eE][+-]?\d+)?)?[fFlL]?(?=\W))|
     ((\b0[xX](\h+)?\.\h*([pP][+-]?\d+)?[fFlL]?))|
     ((?<!\.)([1-9]\d*|0)([eE][+-]?\d+)?[uU]?(ll?|LL?)?\b)|
     (\b0[0-7]+)|
     (\b0[xX]\h+)))|

(?P<operators>(-|\+|/|\*|=|\.|%|&|\?|:|!|<|>|~|\||\^))|

\b(?P<constants>
    NULL|true|false|std(in|err|out)|EOFF|EXIT_(FAILURE|SUCCESS))\b|

\b(?P<types>
    void|char|(_B|b)ool|int|long|short|float|double|(un)?signed|
    _(Complex|Imaginary)(_I)?|complex|imaginary|FILE|va_list|lconv|
    (ptrdiff|r?size|wchar|fpos|l?l?div|char(16|32)|sig_atomic|clock|time|
    max_align|u?int((_(fast|least))?(8|16|32|64)|(max|ptr))|imaxdiv|
    fe(nv|xcept)|errno)_t)\b|

\b(?P<keywords>
    if|else|for|do|while|break|return|goto|continue|switch|case|default|typedef|
    struct|union|enum|extern|static|_Thread_local|auto|register|const|restrict|
    volatile|_Atomic|inline|(_N|n)oreturn|((_S|s)static_)?assert|
    (size|offset)of|(_A|a)lign(as|of)|_Generic|defined)\b|

(?P<functions>
    [a-zA-Z_]\w*(?=\())
""", flags=re_VERBOSE | re_DOTALL | re_MULTILINE)

# Mini MarkDown
MARKDOWN = re_compile(r"""
    (?P<br>\\\\n)
    (?P<code>`.+?`)
    (?P<bi>\*\*\*.+?\*\*\*)
    (?P<b>\*\*.+?\*\*)
    (?P<i>\*.+?\*)
    (?P<a>\[(.+?)\]\((.+?)\))
""", flags=re_VERBOSE | re_DOTALL | re_MULTILINE)

# CSS
STYLE = """
/* FONT */
@import url(http://fonts.googleapis.com/css?family=Source+Sans+Pro:400,700,
400italic,700italic|Source+Code+Pro:400,700);

/* RESET: http://meyerweb.com/eric/tools/css/reset/ | v2.0b1 | 201101 */
html,body,div,span,applet,object,iframe,h1,h2,h3,h4,h5,h6,p,blockquote,pre,a,
abbr,acronym,address,big,cite,code,del,dfn,em,img,ins,kbd,q,s,samp,small,strike,
strong,sub,sup,tt,var,b,u,i,center,dl,dt,dd,ol,ul,li,fieldset,form,label,legend,
table,caption,tbody,tfoot,thead,tr,th,td,article,aside,canvas,details,figcaption,
figure,footer,header,hgroup,menu,nav,section,summary,time,mark,audio,video{
margin:0;padding:0;border:0;outline:0;font-size:100%;font:inherit;vertical-align:
baseline;text-decoration:none;}article,aside,details,figcaption,figure,footer,
header,hgroup,menu,nav,section{display:block;}body{line-height:1;}ol,ul{
list-style:none;}blockquote,q{quotes:none;}blockquote:before,blockquote:after,
q:before,q:after{content:'';content:none;}ins{text-decoration:none;}del{
text-decoration:line-through;}table{border-collapse:collapse;border-spacing:0;}

/* DESIGN: http://www.cutils.org | Peter Varo | 2014  */
body{font-family:'Source Sans Pro',sans-serif;color:#383838;padding:15pt}
::selection{background:#fd0}a{padding:.5pt 0 .5pt 3pt}a:active,a:link,a:visited{
color:#383838}a:hover{background:#ededed}h1{font-size:40pt}h2{font-size:28pt}h3{
font-size:22pt}img{display:block;max-width:100%;margin-left:auto;margin-right:
auto}.toc,code,pre{font-family:'Source Code Pro',monospace;line-height:1.5;
font-size:10pt}.toc_current{font-weight: 700}pre{padding:10pt;border-radius:5pt;
border:1pt solid #ededed;background:#f8f8f8;overflow:auto;overflow-y:hidden}
ul,ol{line-height:1.5}ul li::before{content:'—';position:relative;left:-5pt}
#column1{float:left;width:165pt;position:fixed;height:100%}#column1 img{width:
165pt}#column2{margin-left:180pt}#sidebar{padding:10pt;line-height:1.2;
border-radius:5pt;border:1pt solid #ededed;background:#f8f8f8;overflow-y:auto;
max-height:70%}.toc{display:block;margin-left:2pt;width:135pt;white-space:
nowrap;overflow:hidden;text-overflow:ellipsis}.code_functions,.code_keywords,
.code_operators,.code_types{font-weight:700}.code_comments{color:silver;}
.code_operators{color:#000}.code_constants{color:#d8af00}.code_strings{color:
#888;background:#e8e8e8}.code_keywords{color:#000}.code_functions{color:#303030}
.code_types{color:#a8a8a8}.code_numbers,.code_macros{color:#d8af00}
.code_constants::selection,.code_numbers::selection,.code_macros::selection{
color:#000}.title{border-top:1.5pt solid #d8d8d8;padding-top:15pt;padding-bottom:
15pt}.entity{border-top:1ptsolid #e8e8e8;padding-top:15pt}.return_values{
margin-left:45pt;line-height:1.5}.return_case{margin-right:5pt}.exception_message
{margin-left:45pt;line-height:1.5}.exception_note{margin-left:60pt;line-height:
1.5}.arg_comma,.arg_name,.arg_paren,.name{font-size:15pt}.arg_type{font-size:
13pt}.info{margin-left:30pt;line-height:1.5}.arg_comma,.arg_paren,.label,.name{
font-weight:700}.arg_comma,.arg_paren,.arg_type,.label,.note{font-style:italic}
"""

#------------------------------------------------------------------------------#
# Custom Exceptions
class _MissingValue(Exception):
    def __init__(self, value, name, section, *solutions):
        msg = """\n
    Missing {0!r} from {1!r} {2} definition
    Note: Add {3}{4} to {2} definition
    """
        # Create message if key is missing from a dictionary
        if isinstance(self, MissingDictValue):
            self.error = msg.format(value,
                                    name,
                                    section,
                                    ' or '.join(repr(s) for s in solutions),
                                    ' keys' if len(solutions) > 1 else ' key')
        # Create message if value is missing from a list
        elif isinstance(self, MissingListValue):
            self.error = msg.format(value, name, section, ' '.join(solutions), '')
    def __str__(self):
        return self.error

class MissingDictValue(_MissingValue): pass
class MissingListValue(_MissingValue): pass


#------------------------------------------------------------------------------#
# Function wrapper (post-decorator for BS's factory function)
def _append_new_tag_wrapper(func):
    def new(parent, type, class_='', string='', **attrs):
        if class_:
            attrs['class'] = class_
        tag = func(type, **attrs)
        if string:
            tag.string = string
        parent.append(tag)
        return tag
    return new
# Create a useful and easy to use new tag function
new = _append_new_tag_wrapper(SOUP.new_tag)


#------------------------------------------------------------------------------#
# Open and load file and replace child object in parent with the new content
def _replace(parent, keyindex, child, path, loader):
    try:
        with open(os_path_join(path, child['FILE'])) as file:
            content = file.read()
            # Replace variables with values if there is any
            for key, value in child.get('VARS', {}).items():
                content = content.replace(key, value)
            # Reassign new child into parent
            parent[keyindex] = loader(content)
    except (KeyError, TypeError):
        pass


#------------------------------------------------------------------------------#
# Recursive external file import
def _import(source, path, loader):
    if isinstance(source, dict):
        for key, value in source.items():
            _replace(source, key, value, path, loader)
            _import(source[key], path, loader)
    elif isinstance(source, list):
        for index, item in enumerate(source):
            _replace(source, index, item, path, loader)
            _import(source[index], path, loader)
    return source


#------------------------------------------------------------------------------#
def _const(value):
    return {None  : 'NULL',
            True  : 'true',
            False : 'false'}[value]


#------------------------------------------------------------------------------#
def _ref(string):
    return re_sub(r'\W', '_', string)


#------------------------------------------------------------------------------#
# Parse string for special multiline character and code markdown syntax
def _str(parent, string):
    index = 0
    for match in re_finditer(r'(\\\\n)|(`.+?`)', string):
        start, stop = match.span()
        # If found multiline character
        if match.group(1):
            new(parent, 'span', string=string[index:start])
            new(parent, 'br')
        # If found code-block
        else:
            new(parent, 'span', string=string[index:start])
            new(parent, 'code', string=string[start + 1: stop - 1])
        index = stop
    new(parent, 'span', string=string[index:])


#------------------------------------------------------------------------------#
# Parse string and tokenise it if doesn't start with the \\OFF sign
def _code(parent, string):
    index = 0
    # Replace multiline markers
    string = string.replace('\\\\n', '').replace('\\\\N', '\\\\n')
    # If syntax highlighter explictly turned off (like: for output)
    if string.startswith('\\\\OFF'):
        parent.string = string[5:].strip()
    # If code is syntax highlighted
    else:
        # Parse code
        for match in re_finditer(SYNTAX, string):
            start, stop = match.span()
            new(parent, 'span', string=string[index:start])
            # Process matches in order
            for token in TOKENS:
                # If a token found it to parent and stop
                if match.group(token):
                    new(parent, 'span', class_='code_' + token,
                                        string=string[start:stop])
                    break
            index = stop
        # Add the rest to parent
        new(parent, 'span', string=string[index:])


#------------------------------------------------------------------------------#
# Format 'arguments' in definition of a function
def _func_args(parent, func_name, args, new_line):
    # If more than one variant
    if new_line:
        new(parent, 'br')
    # Create name and open parenthesis
    new(parent, 'span', class_='name', string=func_name)
    new(parent, 'span', class_='space_name_arg_paren', string=' ')
    new(parent, 'span', class_='arg_paren', string='(')
    # Add arguments
    for comma, (arg_type, arg_name) in enumerate(args):
        # If more than one argument
        if comma:
            new(parent, 'span', class_='arg_comma', string=',')
        # Add type
        new(parent, 'span', class_='space_arg_comma_type', string=' ')
        new(parent, 'span', class_='arg_type', string=arg_type)
        new(parent, 'span', class_='space_arg_type_name', string=' ')
        # Add name
        if arg_name:
            new(parent, 'span', class_='arg_name', string=arg_name)
            new(parent, 'span', class_='space_arg_name_paren', string=' ')
    # Close parenthesis
    new(parent, 'span', class_='arg_paren', string=')')


#------------------------------------------------------------------------------#
# Format 'returns' in definition of a function
def _func_returns(name, parent, values):
    # Get values
    return_type, *return_values = values
    # Create a basic return note
    returns = new(parent, 'p', class_='info return')
    return_info = new(returns, 'span', class_='label', string='Return: ')
    # Return value type
    _str(new(returns, 'code', class_='return_case'), return_type[0])
    # OPTIONAL: return type explanation
    try:
        notes = return_type[1]
        if notes:
            new(returns, 'span', class_='return_case', string=':')
            _str(returns, notes)
    except IndexError:
        pass
    # OPTIONAL: If return values have detailed informations
    if return_values:
        new(returns, 'br')
        # Create a table for the values
        table = new(parent, 'table', class_='return_values')
        # For each value add a type and an explanation row
        for return_value in return_values:
            try:
                tr = new(table, 'tr')
                new(new(tr, 'td'), 'code', class_='return_case',
                                           string=_const(return_value[0]))
                new(new(tr, 'td'), 'span', class_='return_case', string=':')
                _str(new(tr, 'td'), return_value[1])
            except IndexError:
                raise MissingListValue('explanation of return value',
                                       name, 'function', 'a second item') from None
    new(parent, 'br')


#------------------------------------------------------------------------------#
# Format 'exceptions' in definition of a function
def _func_exceptions(parent, source):
    NAME = 'exceptions'
    try:
        exceptions = source['exceptions']
        # If renaming exceptions
        if isinstance(exceptions, dict):
            NAME = exceptions['NAME']
            exceptions = source.get(NAME, exceptions)
        # Get values
        for label, (message, description) in enumerate(exceptions):
            if not label:
                new(parent, 'p', class_='info label',
                                 string=string_capwords(NAME) + ':')
            new(parent, 'code', class_='exception_message', string=message)
            _str(new(parent, 'p', class_='exception_note'), description)
            new(parent, 'br')
    except (KeyError, ValueError):
        return


#------------------------------------------------------------------------------#
# Format 'examples' in definition of a function
def _func_examples(parent, source):
    try:
        for label, (note, example) in enumerate(source['example']):
            if not label:
                new(parent, 'p', class_='info label', string='Examples:')
            n = new(parent, 'p', class_='info note')
            _str(n, note + ':')
            new(parent, 'br')
            pre = new(parent, 'pre', class_='info')
            c = new(pre, 'code', class_='snippet')
            _code(c, example)
            new(parent, 'br')
    except KeyError:
        return


#------------------------------------------------------------------------------#
# Mini recursive HTML generator and file importer
def _html_format(parent, source, path):
    # If external file defined
    try:
        soup = BeautifulSoup(open(os_path_join(path, source['HTML'])))
        for tag in soup.body:
            parent.append(tag)
    # If internal structure to parse
    except (TypeError, KeyError):
        for item in source:
            tag = item[0]
            try:
                attrs = {}
                children = []
                for params in item[1:]:
                    # If tag has attributes
                    if isinstance(params, dict):
                        attrs.update(params)
                    # If nested tags
                    elif isinstance(params, list):
                        children.append(params)
                    else:
                        return
                # Try to get string attribute
                string = attrs.pop('string', '')
            except IndexError:
                string = ''
            # Create new tag
            new_tag = new(parent, tag, **attrs)
            # If has string parse it
            if string:
                _str(new_tag, string)
            # If has nested tags
            _html_format(new_tag, children, path)


#------------------------------------------------------------------------------#
# Index formatter -- TOC generator
def _indx_format(sidebar, selfname, sources):
    for pagename, (filepath, pagedata) in sources.items():
        if pagename == selfname:
            new(sidebar, 'a', href='#', class_='toc toc_current', string=pagename)
            continue
        new(sidebar, 'a', href=filepath, class_='toc', string=pagename)


#------------------------------------------------------------------------------#
# User-defined schema formatter
def _user_format(sidebar, content, source):
    UD = 'user defined'
    # Get feature name
    try:
        name = source['name']
    except KeyError:
        raise MissingDictValue('name of feature', '...', UD, 'name') from None
    # Add feature to sidebar and to body too
    ref = 'user_{}'.format(_ref(name))
    new(sidebar, 'a', href='#' + ref, class_='toc', string=name)
    user = new(content, 'div', id=ref, class_='entity')
    new(user, 'p', class_='name', string=name)
    # Add info about the user
    new(user, 'br')
    p = new(user, 'p', class_='info')
    try:
        _str(p, source['info'])
    except KeyError:
        raise MissingDictValue('summary', name, UD, 'info') from None
    new(user, 'br')
    # OPTIONAL: Add examples
    _func_examples(content, source)


#------------------------------------------------------------------------------#
# Function schema formatter
def _func_format(sidebar, content, source):
    FN = 'function'
    VOID = (('void', ''),)
    # Add new function to content
    try:
        name = source['func']
    except KeyError:
        raise MissingDictValue('name of function', '...', FN, 'func') from None
    ref = 'function_{}'.format(_ref(name))
    new(sidebar, 'a', href='#' + ref, class_='toc', string='{}()'.format(name))
    func = new(content, 'div', id=ref, class_='entity')
    parameters = new(func, 'p')
    # If any argument provided or if none -> VOID
    for br, args in enumerate(source.get('vargs', (source.get('args', VOID),))):
        _func_args(parameters, name, args, br)
    new(func, 'br')
    # Add general info/summary
    p = new(func, 'p', class_='info')
    try:
        _str(p, source['info'])
    except KeyError:
        raise MissingDictValue('summary', name, FN, 'info') from None
    new(func, 'br')
    # OPTIONAL: Add return values; if not provided, functions is 'void'
    _func_returns(name, func, source.get('return', VOID))
    # OPTIONAL: Add exceptions
    _func_exceptions(func, source)
    # OPTIONAL: Add examples
    _func_examples(func, source)


#------------------------------------------------------------------------------#
# Type schema formatter
def _type_format(sidebar, content, source):
    # Get type name
    try:
        name = source['type']
    except KeyError:
        raise MissingDictValue('name of type', 'type', 'type') from None
    # Add type to sidebar and to body too
    ref = 'type_{}'.format(_ref(name))
    new(sidebar, 'a', href='#' + ref, class_='toc', string=name)
    type = new(content, 'div', id=ref, class_='entity')
    new(type, 'span', class_='name', string=name)
    # OPTIONAL: If there is a related or original type
    try:
        original = source['original']
        # Open parenthesis
        new(type, 'span', class_='arg_paren', string=' < ')
        # Add type
        new(type, 'span', class_='arg_type', string=original)
        # Close parenthesis
        new(type, 'span', class_='arg_paren', string=' >')
    except KeyError:
        pass
    # Add info about the type
    new(type, 'br')
    p = new(type, 'p', class_='info')
    try:
        _str(p, source['info'])
    except KeyError:
        raise MissingDictValue('summary', name, 'type', 'info') from None
    new(type, 'br')


#------------------------------------------------------------------------------#
def _build(sources, filepath, gentoc):
    for pagename in sources:
        # Clear soup and add en empty, new body
        SOUP.body.decompose()
        new(SOUP.html, 'body')

        # Set title
        SOUP.html.head.title.string = pagename
        # Get essentail values
        filename, source = sources[pagename]
        # Constants
        SECTIONS = 6
        # Build basic structure
        column1 = new(SOUP.body, 'div', id='column1')
        column2 = new(SOUP.body, 'div', id='column2')

        generic = new(column1, 'div', id='generic')
        sidebar = new(column1, 'div', id='sidebar')
        content = new(column2, 'div', id='content')

        # OPTIONAL: custom header section
        try:
            _html_format(generic, source['HEAD'], filepath)
            new(generic, 'br')
        except KeyError:
            SECTIONS -= 1
        # OPTIONAL: custom menu in sidebar
        try:
            _html_format(sidebar, source['MENU'], filepath)
            new(sidebar, 'br')
        except KeyError:
            SECTIONS -= 1
        # OPTIONAL: custom abstract and introduction
        try:
            _html_format(content, source['INFO'], filepath)
            new(content, 'br')
        except KeyError:
            SECTIONS -= 1
        # OPTIONAL: index
        if gentoc:
            sidebar_type = new(sidebar, 'div')
            new(sidebar_type, 'p', class_='label', string='Modules:')
            new(sidebar, 'br')
            _indx_format(sidebar, pagename, sources)
            new(sidebar, 'br')
        # OPTIONAL: user defined
        try:
            userdefs = source['USER']
            for userdef in userdefs:
                # Get the first element of the list
                # as the section name
                try:
                    section = string_capwords(userdef[0])
                except IndexError:
                    continue
                sidebar_user = new(sidebar, 'div')
                new(sidebar_user, 'p', class_='label',
                                       string='{}:'.format(section))
                new(sidebar_user, 'br')
                content_user = new(content, 'div')
                new(content_user, 'h2', class_='title', string=section)
                for user in userdef[1:]:
                    _user_format(sidebar_user, content_user, user)
                new(sidebar, 'br')
        except KeyError:
            SECTIONS -= 1
        # OPTIONAL: type definitions
        try:
            types = source['TYPE']
            sidebar_type = new(sidebar, 'div')
            new(sidebar_type, 'p', class_='label', string='Types:')
            new(sidebar_type, 'br')
            content_type = new(content, 'div')
            new(content_type, 'h2', class_='title', string='Types')
            for type in types:
                _type_format(sidebar_type, content_type, type)
            new(sidebar, 'br')
        except KeyError:
            SECTIONS -= 1
        # OPTIONAL: function definitions
        try:
            funcs = source['FUNC']
            sidebar_func = new(sidebar, 'div')
            new(sidebar_func, 'p', class_='label', string='Functions:')
            new(sidebar_func, 'br')
            content_func = new(content, 'div')
            new(content_func, 'h2', class_='title', string='Functions')
            for func in funcs:
                _func_format(sidebar_func, content_func, func)
        except KeyError:
            SECTIONS -= 1

        # Create HTML file
        if SECTIONS:
            output = os_path_join(filepath, filename)
            with open(output, 'w', encoding='utf-8') as file:
                file.write(SOUP.decode(formatter='html'))
                print('File {!r} has been successfully generated.'.format(output))
            continue
        print('Warning: in {!r} no data provided'.format(pagename))
    # Create folder if not exists to css
    stylepath = os_path_join(filepath, 'css')
    try:
        os_makedirs(stylepath)
    except OSError as e:
        if not (e.errno == errno_EEXIST and os_path_isdir(stylepath)):
            raise
    # Rewrite CSS file
    stylesheet = os_path_join(stylepath, 'cdoc.css')
    with open(stylesheet, 'w', encoding='utf-8') as file:
        file.write(STYLE)
        print('File {!r} has been '
              'successfully generated.'.format(stylesheet))


#------------------------------------------------------------------------------#
def document(infolder, outfolder, extension, loader, generate_toc=None):
    pages = OrderedDict()
    anonym = iter_count()
    # Load all pages
    for file in os_listdir(infolder):
        if file.endswith(extension):
            with open(os_path_join(infolder, file), encoding='utf-8') as f:
                pagedata = _import(loader(f.read()), infolder, loader)
                pagename = pagedata.get('PAGE', 'Document {}'.format(next(anonym)))
                filename = pagedata.get('NAME', os_path_splitext(file)[0]) + '.html'
                pages[pagename] = filename, pagedata
    # Generate Table of Content?
    if generate_toc is None:
        generate_toc = len(pages) > 1
    # Create documents
    _build(pages, outfolder, generate_toc)


#------------------------------------------------------------------------------#
if __name__ == '__main__':
    try:
        script, infolder, outfolder, *rest = sys_argv
        document(infolder=infolder,
                 outfolder=outfolder,
                 extension='.yaml',
                 loader=yaml_load)
    except ValueError:
        print('Warning: No folder provided.')
