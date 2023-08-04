# Define project
project('craft',
        'cpp',
        default_options : [
            'buildtype=debugoptimized',
            'b_sanitize=none',
            'werror=false',
            'optimization=s',
            'cpp_std=c++14',
            'strip=true',
        ],
        version : '0.1.0',
        license : 'MIT',
)
add_project_arguments(
    language : 'cpp',
)

# Build tests
test_files = [
    './main.cpp',
    './utils/FixedPointMath.cpp',
]
inc = include_directories(
    '.',
    './../src'
)
tests = executable('craftUnitTests',
    test_files,
    include_directories: inc
)

# Run tests
test(
    'Unit Tests',
    tests,
    args : ['--success']
)
