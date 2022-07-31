from distutils.core import setup, Extension
from glob import glob
import os


VERSION = '0.0.1'

SOURCE_FILES = sorted(glob(os.path.join('mikro', '*c')))

COMPILE_ARGS = [
    '-std=c99', '-fno-strict-aliasing', '-fcommon',
    '-fPIC', '-Wall', '-Wextra', '-Wno-unused-parameter',
    '-Wno-missing-field-initializers', '-g'
]

mikro_extension = Extension(
    name='_mikro',
    libraries=['libev'],
    include_dirs=['/usr/include/libev'],
    sources=SOURCE_FILES,
    extra_compile_args=COMPILE_ARGS
)


if __name__ == '__main__':
    setup(
        name='mikro',
        author='uncle-lv',
        author_email='uncle.lv@outlook.com',
        license='MIT',
        url='https://github.com/uncle-lv/mikro',
        description='A simplified version of bjoern',
        version=VERSION,
        py_modules=['mikro'],
        ext_modules=[mikro_extension]
    )