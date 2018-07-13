import os

G_PROJECT_DIR   = os.path.dirname(__file__)

G_CXX_STANDARD  = 17

G_CXX_PIC       = True


# ====================================================================================================================
def IsHeaderFile(path):
    _, ext = os.path.splitext(path)
    return ext in ['.h', '.hh', '.hpp', '.hxx']


# ====================================================================================================================
def GetCompilationInfoForFile(path):
    pass


# ====================================================================================================================
def FlagsForFile(path):
    project_include_dir = os.path.join(G_PROJECT_DIR, 'include')
    generated_include_dir = os.path.join(G_PROJECT_DIR, 'build', 'include')
    cxx_standard_flags  = '-std=c++{}'.format(G_CXX_STANDARD)

    flags = [
        '-I', project_include_dir,
        '-I', generated_include_dir,
        '-x', 'c++',
        '-Wall',
        '-Wextra',
        '-fexceptions',
        cxx_standard_flags
    ]

    if G_CXX_PIC:
        flags.append('-fPIC')

    return {
        'flags':    flags,
    }

